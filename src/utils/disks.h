/*
 * disks.h
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

#include <udisks/udisks.h>

#ifndef DISKS_H
#define DISKS_H
struct DiskData
{
	const char *disk_name;
	const char *disk_path;
	const char *udisk_path;
	const char *disk_size_readable;
	guint64 disk_size;
	gboolean is_spinny;
};
#endif /* DISKS_H */

UDisksClient* init_udisks (void);

void disk_list_free (gpointer data, gpointer user_data);

GList* get_disks (UDisksClient* client);
