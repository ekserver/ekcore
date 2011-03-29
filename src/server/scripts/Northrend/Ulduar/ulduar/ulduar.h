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

#include "SpellAuraEffects.h"

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
    DATA_RAZORSCALE_CONTROL,

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
    NPC_RAZORSCALE_CONTROLLER   = 33233,
    NPC_STEELFORGED_DEFFENDER   = 33236,
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

enum eGameObjects
{
    GO_KOLOGARN_CHEST_HERO  = 195047,
    GO_KOLOGARN_CHEST       = 195046,
    GO_KOLOGARN_BRIDGE      = 194232,
    GO_KOLOGARN_DOOR        = 194553,
    GO_THORIM_CHEST_HERO    = 194315,
    GO_THORIM_CHEST         = 194314,
    GO_THORIM_ENCOUNTER_DOOR= 194559,
    GO_THORIM_STONE_DOOR    = 194558,
    GO_THORIM_RUNIC_DOOR    = 194557,
    GO_HODIR_CHEST_HERO     = 194308,
    GO_HODIR_CHEST          = 194307,
    GO_FREYA_CHEST_HERO     = 194325,
    GO_FREYA_CHEST          = 194324,
    GO_LEVIATHAN_DOOR       = 194905,
    GO_LEVIATHAN_GATE       = 194630,
    GO_MIMIRON_TRAIN        = 194675,
    GO_MIMIRON_ELEVATOR     = 194749,
    GO_MIMIRON_DOOR_1       = 194776,
    GO_MIMIRON_DOOR_2       = 194774,
    GO_MIMIRON_DOOR_3       = 194775,
    GO_WAY_TO_YOGG          = 194255,
    GO_VEZAX_DOOR           = 194750,
    GO_YOGGSARON_DOOR       = 194773,
    GO_YOGGBRAIN_DOOR_1     = 194635,
    GO_YOGGBRAIN_DOOR_2     = 194636,
    GO_YOGGBRAIN_DOOR_3     = 194637,
    GO_MOLE_MACHINE         = 194316,
    GO_RAZOR_HARPOON_1      = 194542,
    GO_RAZOR_HARPOON_2      = 194541,
    GO_RAZOR_HARPOON_3      = 194543,
    GO_RAZOR_HARPOON_4      = 194519,
    GO_RAZOR_BROKEN_HARPOON = 194565,
    GO_ALGALON_ACCESS       = 194628,
    GO_ALGALON_DOOR_1       = 194911,
    GO_ALGALON_DOOR_2       = 194767,
    GO_ALGALON_PLATFORM     = 194715,
    GO_ALGALON_GLOBE        = 194148,
    GO_ALGALON_BRIDGE       = 194253,
    GO_ALGALON_B_VISUAL     = 194716,
    GO_ALGALON_B_DOOR       = 194910,
    GO_GIFT_OF_THE_OBSERVER = 194821,
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
    ACHIEVEMENT_UNBROKEN_10                              = 10044, // Leviathan
    ACHIEVEMENT_UNBROKEN_25                              = 10045,
    ACHIEVEMENT_CRITERIA_SHUTOUT_10                      = 10054,
    ACHIEVEMENT_CRITERIA_SHUTOUT_25                      = 10055,
    ACHIEVEMENT_CRITERIA_3_CAR_GARAGE_CHOPPER_10         = 10046,
    ACHIEVEMENT_CRITERIA_3_CAR_GARAGE_SIEGE_10           = 10047,
    ACHIEVEMENT_CRITERIA_3_CAR_GARAGE_DEMOLISHER_10      = 10048,
    ACHIEVEMENT_CRITERIA_3_CAR_GARAGE_CHOPPER_25         = 10049,
    ACHIEVEMENT_CRITERIA_3_CAR_GARAGE_SIEGE_25           = 10050,
    ACHIEVEMENT_CRITERIA_3_CAR_GARAGE_DEMOLISHER_25      = 10051,
    ACHIEVEMENT_CRITERIA_HOT_POCKET_10                   = 10430, // Ignis
    ACHIEVEMENT_CRITERIA_HOT_POCKET_25                   = 10431,
    ACHIEVEMENT_CRITERIA_QUICK_SHAVE_10                  = 10062, // Razorscale
    ACHIEVEMENT_CRITERIA_QUICK_SHAVE_25                  = 10063,
};

enum eKeeperSupport
{
    THORIM_SUPPORT = 0x01,
    HODIR_SUPPORT = 0x02,
    FREYA_SUPPORT = 0x04,
    MIMIRON_SUPPORT = 0x08,
};

enum eWorldstates
{
    WORLDSTATE_ALGALON_TIME = 4131,
    WORLDSTATE_ALGALON_SHOW = 4132
};

#endif
