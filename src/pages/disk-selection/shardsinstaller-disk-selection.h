/* shardsinstaller-disk-select.h
 *
 * Copyright 2024 Rose <axtlos@disroot.org>
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

#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define SHARDSINSTALLER_TYPE_DISK_SELECTION (shardsinstaller_disk_selection_get_type())

G_DECLARE_FINAL_TYPE (ShardsinstallerDiskSelection, shardsinstaller_disk_selection, SHARDSINSTALLER, DISKSELECTION, AdwBin)

void disk_selected (ShardsinstallerDiskSelection *self);
void shardsinstaller_disk_selection_populate_disks (ShardsinstallerDiskSelection *self);

G_END_DECLS
