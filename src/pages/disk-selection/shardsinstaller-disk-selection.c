/*
 * shardsinstaller-disk-selection.c
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


#include "../../widgets/shardsinstaller-disk-entry.h"
#include "../../utils/disks.h"
#include <udisks/udisks.h>
#include "shardsinstaller-disk-selection.h"

struct _ShardsinstallerDiskSelection
{
        AdwBin         parent;

	GtkButton     *continue_button;
	GtkBox	      *disk_list;

	char 	      *chosen_disk;
};

enum {
  SIGNAL_CONTINUE_INSTALLATION,
  SIGNAL_LAST_SIGNAL,
};

static guint signals[SIGNAL_LAST_SIGNAL];

const char *disk_name;
const char *disk_path;

G_DEFINE_FINAL_TYPE (ShardsinstallerDiskSelection, shardsinstaller_disk_selection, ADW_TYPE_BIN)

static void
response_cb (AdwAlertDialog    		  *dialog,
             GAsyncResult      		  *result,
             ShardsinstallerDiskSelection *self
)
{
	const char *response = adw_alert_dialog_choose_finish (dialog, result);
	if (strcmp (response, "cancel") == 0)
		return;

	FILE *optionfiles = fopen ("/tmp/shardsinstaller", "w");
	fprintf (optionfiles, "INSTALL_DISK='%s'\n", disk_name);
	fclose (optionfiles);

	g_signal_emit (self, signals[SIGNAL_CONTINUE_INSTALLATION], 0, NULL);
}

static void
installation_continue (ShardsinstallerDiskSelection *self)
{
	AdwDialog *dialog;
	dialog = adw_alert_dialog_new ("Continue Installation?", NULL);
	adw_alert_dialog_format_body (ADW_ALERT_DIALOG (dialog),
				      "All data on the target disk '%s' will be destroyed. You will lose all of your apps, files and documents.",
				      disk_name);


	adw_alert_dialog_add_responses (ADW_ALERT_DIALOG (dialog),
                                	"cancel",  "_Cancel",
                                	"continue", "_Continue",
                                	NULL);

	adw_alert_dialog_set_response_appearance (ADW_ALERT_DIALOG (dialog),
                                          	  "continue",
                                          	  ADW_RESPONSE_DESTRUCTIVE);

	adw_alert_dialog_set_default_response (ADW_ALERT_DIALOG (dialog), "continue");
	adw_alert_dialog_set_close_response (ADW_ALERT_DIALOG (dialog), "cancel");

	adw_alert_dialog_choose (ADW_ALERT_DIALOG (dialog), GTK_WIDGET (self), NULL,
                           (GAsyncReadyCallback) response_cb, self);
}

void
selected_disk (GtkWidget *self, const char *chosen_disk)
{
	disk_name = chosen_disk;
	ShardsinstallerDiskSelection *page = SHARDSINSTALLER_DISKSELECTION (self);
	gtk_widget_set_sensitive (GTK_WIDGET (page->continue_button), true);
}

void
shardsinstaller_disk_selection_populate_disks (ShardsinstallerDiskSelection *self)
{
	UDisksClient *client = init_udisks ();
	GList *disks = get_disks (client);

	struct DiskData *disk = disks->data;

	if (!disk)
		return;

	GtkWidget *first_disk = shardsinstaller_disk_entry_new (disk->disk_name, disk->disk_size_readable, disk->is_spinny, GTK_WIDGET (self), selected_disk);
	gtk_box_append (self->disk_list, first_disk);


	for (GList *l = disks->next; l != NULL; l = l->next)
	{
        if (!disks)
            return;
		disk = l->data;
		GtkWidget *disk_widget = shardsinstaller_disk_entry_new (disk->disk_name, disk->disk_size_readable, disk->is_spinny, GTK_WIDGET (self), selected_disk);
		gtk_toggle_button_set_group (GTK_TOGGLE_BUTTON (disk_widget), GTK_TOGGLE_BUTTON (first_disk));
		gtk_box_append (self->disk_list, disk_widget);
		disk_list_free (l->data, NULL);
	}
	g_list_free (disks);
}

static void
shardsinstaller_disk_selection_class_init (ShardsinstallerDiskSelectionClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	signals[SIGNAL_CONTINUE_INSTALLATION] =
    		g_signal_new ("continue-installation",
                  	      G_TYPE_FROM_CLASS (klass),
                  	      G_SIGNAL_RUN_FIRST,
                  	      0,
                  	      NULL, NULL, NULL,
                  	      G_TYPE_NONE, 0);

	gtk_widget_class_set_template_from_resource (widget_class, "/projects/shards/installer/pages/disk-selection/shardsinstaller-disk-selection.ui");
	gtk_widget_class_bind_template_child (widget_class, ShardsinstallerDiskSelection, continue_button);
	gtk_widget_class_bind_template_child (widget_class, ShardsinstallerDiskSelection, disk_list);
	gtk_widget_class_bind_template_callback (widget_class, installation_continue);
}

static void
shardsinstaller_disk_selection_init (ShardsinstallerDiskSelection *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}


