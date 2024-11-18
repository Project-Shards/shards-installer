/*
 * shardsinstaller-disk-entry.h
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


#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

GtkWidget* shardsinstaller_disk_entry_new (const char *diskname, const char *size, const gboolean is_ssd, GtkWidget *page, void (*toggle_callback)(GtkWidget*, const char*));

#define SHARDSINSTALLER_TYPE_DISK_ENTRY (shardsinstaller_disk_entry_get_type())

G_DECLARE_FINAL_TYPE (ShardsinstallerDiskEntry, shardsinstaller_disk_entry, SHARDSINSTALLER, DISKENTRY, GtkToggleButton)

G_END_DECLS
