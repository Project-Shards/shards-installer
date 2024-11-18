/*
 * shardsinstaller-install-success.c
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

#include "../../utils/gnome-session-quit.h"

#include "shardsinstaller-install-success.h"

struct _ShardsinstallerInstallSuccess
{
	AdwBin         parent;
};

G_DEFINE_FINAL_TYPE (ShardsinstallerInstallSuccess, shardsinstaller_install_success, ADW_TYPE_BIN)

void
reboot_system (ShardsinstallerInstallSuccess *self)
{
    GDBusProxy *gsm = gsm_init_session ();
    gsm_power_action (gsm, "Reboot");
}

static void
shardsinstaller_install_success_class_init (ShardsinstallerInstallSuccessClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/projects/shards/installer/pages/install-success/shardsinstaller-install-success.ui");
	gtk_widget_class_bind_template_callback (widget_class, reboot_system);
}

static void
shardsinstaller_install_success_init (ShardsinstallerInstallSuccess *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}
