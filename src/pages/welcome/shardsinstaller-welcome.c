/*
 * shardsinstaller-welcome.c
 *
 * Copyright 2024 rose <axtlos@disroot.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */


#include "config.h"

#include "shardsinstaller-welcome.h"

struct _ShardsinstallerWelcome
{
        AdwBin         parent;

	GtkButton     *start_button;
};

enum {
  SIGNAL_START_INSTALLATION,
  SIGNAL_LAST_SIGNAL,
};

static guint signals[SIGNAL_LAST_SIGNAL];

G_DEFINE_FINAL_TYPE (ShardsinstallerWelcome, shardsinstaller_welcome, ADW_TYPE_BIN)

void
start_install (ShardsinstallerWelcome *self) {
	g_signal_emit (self, signals[SIGNAL_START_INSTALLATION], 0, NULL);
}

static void
shardsinstaller_welcome_class_init (ShardsinstallerWelcomeClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	signals[SIGNAL_START_INSTALLATION] =
    		g_signal_new ("start-installation",
                  	      G_TYPE_FROM_CLASS (klass),
                  	      G_SIGNAL_RUN_FIRST,
                  	      0,
                  	      NULL, NULL, NULL,
                  	      G_TYPE_NONE, 0);

	gtk_widget_class_set_template_from_resource (widget_class, "/projects/shards/installer/pages/welcome/shardsinstaller-welcome.ui");
	gtk_widget_class_bind_template_child (widget_class, ShardsinstallerWelcome, start_button);
	gtk_widget_class_bind_template_callback (widget_class, start_install);
}

static void
shardsinstaller_welcome_init (ShardsinstallerWelcome *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}
