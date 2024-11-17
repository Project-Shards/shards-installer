/* shardsinstaller-application.h
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

#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define SHARDSINSTALLER_TYPE_APPLICATION (shardsinstaller_application_get_type())

G_DECLARE_FINAL_TYPE (ShardsinstallerApplication, shardsinstaller_application, SHARDSINSTALLER, APPLICATION, AdwApplication)

ShardsinstallerApplication *shardsinstaller_application_new (const char        *application_id,
                                                             GApplicationFlags  flags);

G_END_DECLS
