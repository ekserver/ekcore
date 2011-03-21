/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
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

#ifndef DEF_ULDUAR_H
#define DEF_ULDUAR_H

enum eTypes
{
    MAX_ENCOUNTER               = 15,

    TYPE_LEVIATHAN              = 0,
    TYPE_IGNIS                  = 1,
    TYPE_RAZORSCALE             = 2,
    TYPE_XT002                  = 3,
    TYPE_ASSEMBLY               = 4,
    TYPE_KOLOGARN               = 5,
    TYPE_AURIAYA                = 6,
    TYPE_MIMIRON                = 7,
    TYPE_HODIR                  = 8,
    TYPE_THORIM                 = 9,
    TYPE_FREYA                  = 10,
    TYPE_VEZAX                  = 11,
    TYPE_YOGGSARON              = 12,
    TYPE_ALGALON                = 13,
    TYPE_COLOSSUS               = 14,

    TYPE_SARA,
    TYPE_BRAIN_DOOR_1,
    TYPE_BRAIN_DOOR_2,
    TYPE_BRAIN_DOOR_3,
    DATA_KEEPER_SUPPORT_YOGG,
    
    // Assembly of Iorn
    DATA_STEELBREAKER,
    DATA_MOLGEIM,
    DATA_BRUNDIR,

    DATA_EXP_COMMANDER,

    // Kologarn:
    DATA_LEFT_ARM,
    DATA_RIGHT_ARM,

    // Freya Elders
    TYPE_ELDER_BRIGHTLEAF,
    TYPE_ELDER_IRONBRANCH,
    TYPE_ELDER_STONEBARK,

    // Thorim
    DATA_RUNIC_COLOSSUS,
    DATA_RUNE_GIANT,
    DATA_RUNIC_DOOR,
    DATA_STONE_DOOR,
    DATA_HODIR_RARE_CHEST,

    DATA_CALL_TRAM,
    //Mimiron
    DATA_LEVIATHAN_MK_II,
    DATA_MIMIRON_ELEVATOR,
    DATA_AERIAL_UNIT,
    DATA_VX_001,
    DATA_MAGNETIC_CORE,

    //Pre YoggSaron
    DATA_ADD_HELP_FLAG,
};

enum eNPCs
{
    NPC_LEVIATHAN               = 33113,
    NPC_IGNIS                   = 33118,
    NPC_RAZORSCALE              = 33186,
    NPC_EXPEDITION_COMMANDER    = 33210,
    NPC_XT002                   = 33293,
    NPC_STEELBREAKER            = 32867,
    NPC_MOLGEIM                 = 32927,
    NPC_BRUNDIR                 = 32857,
    NPC_KOLOGARN                = 32930,
    NPC_KOLOGARN_BRIDGE         = 34297,
    NPC_FOCUSED_EYEBEAM         = 33632,
    NPC_FOCUSED_EYEBEAM_RIGHT   = 33802,
    NPC_LEFT_ARM                = 32933,
    NPC_RIGHT_ARM               = 32934,
    NPC_RUBBLE                  = 33768,
    NPC_AURIAYA                 = 33515,
    NPC_MIMIRON                 = 33350,
    NPC_AERIAL_UNIT             = 33670,
    NPC_MAGNETIC_CORE           = 34068,
    NPC_LEVIATHAN_MKII          = 33432,
    NPC_VX_001                  = 33651,
    NPC_HODIR                   = 32845,
    NPC_THORIM                  = 32865,
    NPC_RUNIC_COLOSSUS          = 32872,
    NPC_RUNE_GIANT              = 32873,
    NPC_FREYA                   = 32906,
    NPC_ELDER_IRONBRANCH        = 32913,
    NPC_ELDER_STONEBARK         = 32914,
    NPC_ELDER_BRIGHTLEAF        = 32915,
    NPC_VEZAX                   = 33271,
    NPC_YOGGSARON               = 33288,
    NPC_SARA                    = 33134,
    NPC_ALGALON                 = 32871,
};

enum eTowerEvents
{
    EVENT_TOWER_OF_STORM_DESTROYED     = 21031,
    EVENT_TOWER_OF_FROST_DESTROYED     = 21032,
    EVENT_TOWER_OF_FLAMES_DESTROYED    = 21033,
    EVENT_TOWER_OF_LIFE_DESTROYED      = 21030
};

enum eAchievementCriteria
{
    ACHIEVEMENT_CRITERIA_HOT_POCKET_10                   = 10430, //ignis
    ACHIEVEMENT_CRITERIA_HOT_POCKET_25                   = 10431,
};

enum eKeeperSupport
{
    THORIM_SUPPORT = 0x01,
    HODIR_SUPPORT = 0x02,
    FREYA_SUPPORT = 0x04,
    MIMIRON_SUPPORT = 0x08,
};

#endif
