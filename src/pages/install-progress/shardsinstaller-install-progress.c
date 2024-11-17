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


#include "config.h"

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

void
shardsinstaller_install_progress_begin_install (ShardsinstallerInstallProgress *self)
{
	return;
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
