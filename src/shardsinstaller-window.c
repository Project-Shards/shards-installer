/* shardsinstaller-window.c
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

#include "pages/welcome/shardsinstaller-welcome.h"
#include "pages/disk-selection/shardsinstaller-disk-selection.h"
#include "pages/install-progress/shardsinstaller-install-progress.h"
#include "shardsinstaller-window.h"
#include "widgets/shardsinstaller-disk-entry.h"

struct _ShardsinstallerWindow
{
	AdwApplicationWindow  parent_instance;

	AdwCarousel	     *carousel;
	ShardsinstallerDiskSelection *disk_select_page;
	ShardsinstallerInstallProgress *install_progress_page;
};

G_DEFINE_FINAL_TYPE (ShardsinstallerWindow, shardsinstaller_window, ADW_TYPE_APPLICATION_WINDOW)

static void
start_installation_cb (ShardsinstallerWindow *self)
{
	printf ("starting installation\n");
	shardsinstaller_disk_selection_populate_disks (self->disk_select_page);
	adw_carousel_scroll_to (self->carousel, GTK_WIDGET (self->disk_select_page), true);
	return ;
}

static void
disk_selected_cb (ShardsinstallerWindow *self)
{
	printf ("starting imge\n");
	system ("cat /tmp/shardsinstaller");
	shardsinstaller_install_progress_begin_install (self->install_progress_page);
	adw_carousel_scroll_to (self->carousel, GTK_WIDGET (self->install_progress_page), true);
	return;
}

static void
shardsinstaller_window_class_init (ShardsinstallerWindowClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/projects/shards/installer/shardsinstaller-window.ui");
	gtk_widget_class_bind_template_child (widget_class, ShardsinstallerWindow, carousel);
	gtk_widget_class_bind_template_child (widget_class, ShardsinstallerWindow, disk_select_page);
	gtk_widget_class_bind_template_child (widget_class, ShardsinstallerWindow, install_progress_page);
	gtk_widget_class_bind_template_callback (widget_class, start_installation_cb);
	gtk_widget_class_bind_template_callback (widget_class, disk_selected_cb);
}

static void
shardsinstaller_window_init (ShardsinstallerWindow *self)
{
    g_type_ensure (SHARDSINSTALLER_TYPE_WELCOME);
    g_type_ensure (SHARDSINSTALLER_TYPE_DISK_SELECTION);
	g_type_ensure (SHARDSINSTALLER_TYPE_INSTALL_PROGRESS);

	gtk_widget_init_template (GTK_WIDGET (self));
}
