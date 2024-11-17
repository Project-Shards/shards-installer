/* shardsinstaller-application.c
 *
 * Copyright 2024 Unknown
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "config.h"
#include <glib/gi18n.h>

#include "shardsinstaller-application.h"
#include "shardsinstaller-window.h"

struct _ShardsinstallerApplication
{
	AdwApplication parent_instance;
};

G_DEFINE_FINAL_TYPE (ShardsinstallerApplication, shardsinstaller_application, ADW_TYPE_APPLICATION)

ShardsinstallerApplication *
shardsinstaller_application_new (const char        *application_id,
                                 GApplicationFlags  flags)
{
	g_return_val_if_fail (application_id != NULL, NULL);

	return g_object_new (SHARDSINSTALLER_TYPE_APPLICATION,
	                     "application-id", application_id,
	                     "flags", flags,
	                     NULL);
}

static void
shardsinstaller_application_activate (GApplication *app)
{
	GtkWindow *window;

	g_assert (SHARDSINSTALLER_IS_APPLICATION (app));

	window = gtk_application_get_active_window (GTK_APPLICATION (app));

	if (window == NULL)
		window = g_object_new (SHARDSINSTALLER_TYPE_WINDOW,
		                       "application", app,
		                       NULL);
	gtk_window_present (window);
}

static void
shardsinstaller_application_class_init (ShardsinstallerApplicationClass *klass)
{
	GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

	app_class->activate = shardsinstaller_application_activate;
}

static void
shardsinstaller_application_about_action (GSimpleAction *action,
                                          GVariant      *parameter,
                                          gpointer       user_data)
{
	static const char *developers[] = {"Unknown", NULL};
	ShardsinstallerApplication *self = user_data;
	GtkWindow *window = NULL;

	g_assert (SHARDSINSTALLER_IS_APPLICATION (self));

	window = gtk_application_get_active_window (GTK_APPLICATION (self));

	adw_show_about_dialog (GTK_WIDGET (window),
	                       "application-name", "shardsinstaller",
	                       "application-icon", "projects.shards.installer",
	                       "developer-name", "Unknown",
	                       "translator-credits", _("translator-credits"),
	                       "version", "0.1.0",
	                       "developers", developers,
	                       "copyright", "© 2024 Unknown",
	                       NULL);
}

static void
shardsinstaller_application_quit_action (GSimpleAction *action,
                                         GVariant      *parameter,
                                         gpointer       user_data)
{
	ShardsinstallerApplication *self = user_data;

	g_assert (SHARDSINSTALLER_IS_APPLICATION (self));

	g_application_quit (G_APPLICATION (self));
}

static const GActionEntry app_actions[] = {
	{ "quit", shardsinstaller_application_quit_action },
	{ "about", shardsinstaller_application_about_action },
};

static void
shardsinstaller_application_init (ShardsinstallerApplication *self)
{
	g_action_map_add_action_entries (G_ACTION_MAP (self),
	                                 app_actions,
	                                 G_N_ELEMENTS (app_actions),
	                                 self);
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "app.quit",
	                                       (const char *[]) { "<primary>q", NULL });
}
