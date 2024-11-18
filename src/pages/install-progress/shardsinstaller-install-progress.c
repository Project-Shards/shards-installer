/*
 * shardsinstaller-install-progress.c
 *
 * Copyright 2024 Rose <axtlos@disroot.org>
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: LGPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <gio/gio.h>
#include <gio-unix-2.0/gio/gunixinputstream.h>
#include "shardsinstaller-install-progress.h"

struct _ShardsinstallerInstallProgress
{
	AdwBin         parent;

	GtkProgressBar     *progressbar;
};

enum {
  	SIGNAL_INSTALLATION_FAIL,
	SIGNAL_INSTALLATION_SUCCESS,
	SIGNAL_LAST_SIGNAL,
};

static guint signals[SIGNAL_LAST_SIGNAL];

G_DEFINE_FINAL_TYPE (ShardsinstallerInstallProgress, shardsinstaller_install_progress, ADW_TYPE_BIN)

gboolean install_finished = false;

static void
child_watch_cb (GPid     pid,
                gint     status,
                gpointer user_data)
{
    ShardsinstallerInstallProgress *self = user_data;

	if (g_spawn_check_wait_status (status, NULL))
		g_signal_emit (self, signals[SIGNAL_INSTALLATION_SUCCESS], 0, NULL);
	else
		g_signal_emit (self, signals[SIGNAL_INSTALLATION_FAIL], 0, NULL);

	install_finished = true;
	g_spawn_close_pid (pid);
}

void
shardsinstaller_read_progress_thread (GTask *task,
							  		 gpointer source_object,
							  		 gpointer task_data,
							  		 GCancellable *cancellable)
{
	ShardsinstallerInstallProgress *self = source_object;
	GInputStream *stderr_stream = task_data;
	GError *error = NULL;

	char *buf = malloc (4);
	memset (buf, 0, 4);
	while (!install_finished)
	{
		g_input_stream_read (stderr_stream, buf, 4, NULL, NULL);
		if (buf)
		{
			int progress = atoi (buf);
			gtk_progress_bar_set_fraction (self->progressbar, progress/100.0);
		}
	}
	g_task_return_int (task, 0);
}

void
shardsinstaller_install_progress_begin_install (ShardsinstallerInstallProgress *self)
{
	gchar * argv[] = { "/usr/bin/shardsimgr", NULL };
	gint child_stdout, child_stderr;
	GPid child_pid;
	g_autoptr(GError) error = NULL;

	g_spawn_async_with_pipes (NULL, argv, NULL, G_SPAWN_DO_NOT_REAP_CHILD, NULL,
                          	 NULL, &child_pid, NULL, &child_stdout,
                          	 &child_stderr, &error);
	if (error != NULL)
  	{
	    g_error ("Spawning child failed: %s", error->message);
	    return;
  	}
	g_child_watch_add (child_pid, child_watch_cb, self);

	GTask *task = g_task_new (self, NULL, NULL, NULL);

	GInputStream *stderr_stream = g_unix_input_stream_new (child_stderr, false);

	g_task_set_task_data (task, stderr_stream, NULL);
	g_task_run_in_thread (task, shardsinstaller_read_progress_thread);
	g_object_unref (task);
}

static void
shardsinstaller_install_progress_class_init (ShardsinstallerInstallProgressClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	signals[SIGNAL_INSTALLATION_FAIL] =
    		g_signal_new ("installation-fail",
                  	      G_TYPE_FROM_CLASS (klass),
                  	      G_SIGNAL_RUN_FIRST,
                  	      0,
                  	      NULL, NULL, NULL,
                  	      G_TYPE_NONE, 0);

	signals[SIGNAL_INSTALLATION_SUCCESS] =
		g_signal_new ("installation-success",
					  G_TYPE_FROM_CLASS (klass),
					  G_SIGNAL_RUN_FIRST,
					  0,
					  NULL, NULL, NULL,
					  G_TYPE_NONE, 0);

	gtk_widget_class_set_template_from_resource (widget_class, "/projects/shards/installer/pages/install-progress/shardsinstaller-install-progress.ui");
	gtk_widget_class_bind_template_child (widget_class, ShardsinstallerInstallProgress, progressbar);
}

static void
shardsinstaller_install_progress_init (ShardsinstallerInstallProgress *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}
