/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ExtraDatabase.h"

void ExtraDatabaseConnection::DoPrepareStatements()
{
    if (!m_reconnecting)
        m_stmts.resize(MAX_EXTRADATABASE_STATEMENTS);

    PREPARE_STATEMENT(EXTRA_ADD_ITEMSTAT, "INSERT INTO item_stats (guid, item, state, map) VALUES (?, ?, ?, ?)", CONNECTION_ASYNC)
    PREPARE_STATEMENT(EXTRA_ADD_BGSTAT, "INSERT INTO battleground_stats (bg_id, winner) VALUES (?, ?)", CONNECTION_ASYNC)
    PREPARE_STATEMENT(EXTRA_ADD_GMLOG, "INSERT INTO `gm_log` (`player`, `account`, `command`, `position`, `selected`) VALUES (?, ?, ?, ?, ?)", CONNECTION_ASYNC)
}
