/*
 * disks.c
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
#include <string.h>
#include <stdbool.h>
#include <udisks/udisks.h>
#include <math.h>
#include "disks.h"

GList*
get_disks (UDisksClient* client)
{
	GList *disks = NULL;
	GList *objects = g_dbus_object_manager_get_objects (udisks_client_get_object_manager (client));
	GList *l;
	UDisksBlock *udisk_block;
	for (l = objects; l != NULL; l = l->next)
	{
		UDisksObject *object = UDISKS_OBJECT(l->data);
		udisk_block = udisks_object_peek_block (object);
		if (udisk_block != NULL)
		{
			if (strstr (udisks_block_get_id (udisk_block), "-part") != NULL)
				continue;

			const gchar *device, *drive;
			const gchar *id, *label;
			const gchar * const *symlinks;
			UDisksDrive *udisk_drive = udisks_client_get_drive_for_block (client, udisk_block);

			if (udisk_block == NULL)
				continue;

			drive = udisks_block_get_drive(udisk_block);
			if (drive == NULL || g_strcmp0(drive, "/") == 0)
				continue;

			device = udisks_block_get_device(udisk_block);
			if (device == NULL)
				continue;

			const gchar *name = udisks_drive_get_model (udisk_drive);
			if (name == NULL)
				name = "";

			guint64 size = udisks_block_get_size (udisk_block);

			gboolean is_spinny = (udisks_drive_get_rotation_rate (udisk_drive) != 0);

			gboolean device_exists = false;
			for (GList *i = disks; i != NULL; i = i->next)
			{
				struct DiskData *disk = i->data;
				if (!disk)
				{
					continue;
				}
				if (!disk->udisk_path)
					continue;
				if (g_strcmp0 (disk->udisk_path, drive) == 0)
				{
					device_exists = true;
					break;
				}
			}

			if (!device_exists)
			{
				struct DiskData *new_disk = malloc(sizeof (struct DiskData));
				new_disk->disk_name = (const char*) strdup(name);
				new_disk->disk_path = (const char*) strdup(device);
				new_disk->udisk_path = (const char*) strdup(drive);
				new_disk->disk_size_readable = (const char*) udisks_client_get_size_for_display (client, size, false, false);
				new_disk->disk_size = size;
				new_disk->is_spinny = is_spinny;

				disks = g_list_append (disks, new_disk);
			}
		}
	}
	g_list_foreach(objects, (GFunc)g_object_unref, NULL);
    g_list_free(objects);
	return disks;
}

void
disk_list_free (gpointer data, gpointer user_data)
{
	struct DiskData *disk = data;
	free (disk->disk_path);
	free (disk->udisk_path);
	free (disk->disk_name);
	free (disk->disk_size_readable);
	free (data);
}

UDisksClient*
init_udisks (void)
{
	GError *error = NULL;
	UDisksClient *client = udisks_client_new_sync (NULL, &error);
	if (client == NULL)
	{
		g_printerr ("Error connecting to udisks: %s\n", error->message);
		g_error_free (error);
	}
	return client;
}

