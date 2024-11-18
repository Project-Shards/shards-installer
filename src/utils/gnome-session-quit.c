/*
 * gnome-session-quit.c
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

#include <gio/gio.h>
#include "gnome-session-quit.h"

void
gsm_power_action (GDBusProxy *gsm, const char *action)
{
	GVariant   *reply;
	GError     *error;

	error = NULL;
	reply = g_dbus_proxy_call_sync (gsm,
								   action,
								   NULL,
								   G_DBUS_CALL_FLAGS_NONE,
								   -1, NULL, &error);

	if (error != NULL) {
		g_warning ("Failed to call %s: %s", action, error->message);
		g_error_free (error);
    } else {
        g_variant_unref (reply);
    }
}

GDBusProxy*
gsm_init_session (void)
{
	GDBusConnection *bus;
	GDBusProxy *gsm;
	GError *error = NULL;

	bus = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, &error);
	if (bus == NULL) {
		g_warning ("Failed to connect to session bus: %s", error->message);
		g_error_free (error);
		return NULL;
	}

	gsm = g_dbus_proxy_new_sync (bus,
								G_DBUS_PROXY_FLAGS_NONE,
								NULL,
								"org.gnome.SessionManager",
								"/org/gnome/SessionManager",
								"org.gnome.SessionManager",
								NULL, NULL);

	g_object_unref (bus);

	if (gsm == NULL) {
		g_error ("Failed to connect to gnome session manager");
	}
	return gsm;
}
