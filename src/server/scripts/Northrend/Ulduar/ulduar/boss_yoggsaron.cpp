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

#include "ScriptPCH.h"
#include "ulduar.h"

/*
LandofLegends - Entwicklungsnotizen:

Allgemein:
Abbrüfen ob Keeper benutzt werden
Keeper secoundary spell prüfen/fixen
Loot
Legendaere Waffen Quest fixen
Archievments - teilweise schon erledigt

Script ist zu 82% fertig.

Phase 1 ist komplett
Phase 2 ist fast fertig
  Allgemein:
    Rausteleportieren Gameobjekte fehlen noch (DB- oder Scriptspawn)
    Die kleinen Geschichten muessen noch gescriptet werden
    Yells raussuchen
  Sara:
    Death Ray muss getestet werden bzw. gefixt
    Brain Link entweder per workaround fixen (Mutter Sharaz) oder spellscript
  YoggSauron:
    Maddnesspell vom Gehirn hat noch kein Effekt (fuer Tests erstmal aus lassen) wird aber gecastet korrekt
    Spells von Sara noch nicht richtig implementiert alle
    Tentakle Spawns Timer fixen
    Tentakle brauch vehicleID
    MindControl bei Sanity = 0
Phase 3 fast fertig
    Spell Lunatic Gaze testen fixen
    Empower Shadows scripten
    Yells raussuchen
*/

enum Sara_Yells
{
    SAY_SARA_PREFIGHT_1                         = -1603310,
    SAY_SARA_PREFIGHT_2                         = -1603311,
    SAY_SARA_AGGRO_1                            = -1603312,
    SAY_SARA_AGGRO_2                            = -1603313,
    SAY_SARA_AGGRO_3                            = -1603314,
    SAY_SARA_SLAY_1                             = -1603315,
    SAY_SARA_SLAY_2                             = -1603316,
    WHISP_SARA_INSANITY                         = -1603317,
    SAY_SARA_PHASE2_1                           = -1603318,
    SAY_SARA_PHASE2_2                           = -1603319,
};

enum YoggSaron_Yells
{
    SAY_PHASE2_1                                = -1603330,
    SAY_PHASE2_2                                = -1603331,
    SAY_PHASE2_3                                = -1603332,
    SAY_PHASE2_4                                = -1603333,
    SAY_PHASE2_5                                = -1603334,
    SAY_PHASE3                                  = -1603335,
    SAY_VISION                                  = -1603336,
    SAY_SLAY_1                                  = -1603337,
    SAY_SLAY_2                                  = -1603338,
    WHISP_INSANITY_1                            = -1603339,
    WHISP_INSANITY_2                            = -1603340,
    SAY_DEATH                                   = -1603341,
};

enum Events
{
    ACHIEV_TIMED_START_EVENT                    = 21001,
};

enum Achievments
{
    ACHIEVMENT_KISS_AND_MAKE_UP_10              = 3009,
    ACHIEVMENT_KILL_AND_MAKE_UP_25              = 3011,
};

enum Entrys
{
    ENTRY_OMINOUS_CLOUD                         = 33292,
    ENTRY_GUARDIAN_OF_YOGG_SARON                = 33136,
    ENTRY_YOGG_SARON                            = 33288,
    ENTRY_BRAIN_OF_YOGG_SARON                   = 33890,
    ENTRY_CRUSHER_TENTACLE                      = 33966,
    ENTRY_CORRUPTOR_TENTACLE                    = 33985,
    ENTRY_CONSTRICTOR_TENTACLE                  = 33983,
    ENTRY_BRAIN_PORTAL                          = 34072,
    ENTRY_INFULENCE_TENTACLE                    = 33943,
    ENTRY_RUBY_CONSORT                          = 33716, // 2 on Roomexit (l & r)
    ENTRY_OBSIDIAN_CONSORT                      = 33720, // 2 on End of the Room (l & r)
    ENTRY_EMERAL_CONSORT                        = 33719, // 2 on North West of the room
    ENTRY_AZURE_CONSORT                         = 33717, // 2 on North East of the room
    ENTRY_SUIT_OF_ARMOR                         = 33433, // around the Room
    ENTRY_DEATHSWORN_ZEALOT                     = 33567, // 3 Groups of 3 ... left middle right
    ENTRY_IMMORTAL_GUARDIAN                     = 33988,

    ENTRY_KEEPER_FREYA                          = 33410,
    ENTRY_KEEPER_HODIR                          = 33411,
    ENTRY_KEEPER_MIMIRON                        = 33412,
    ENTRY_KEEPER_THORIM                         = 33413,

    ENTRY_SANITY_WELL                           = 33991,

    OBJECT_FLEE_TO_SURFACE                      = 194625,
};

enum ModelIds
{
    SARA_NORMAL                                 = 29117,
    SARA_TRANSFORM                              = 29182,
    //YOGGSARON_NORMAL                            = 28817,
    //YOGGSARON_TRANSFORM                         = 28945
};

enum MindlessSpell
{
    BRAIN_LINK = 0,
    MALADY_OF_MIND = 1,
    DEATH_RAY = 2
};

enum EncounterConstants
{
    CONSTANT_MAX_NOVA_HITS = 8,
    CONSTANT_MAX_LLIANE_TENTACLE_SPAWNS = 8,
    CONSTANT_MAX_LICHKING_TENTACLE_SPAWNS = 9,
    CONSTANT_MAX_DRAGONSOUL_TENTACLE_SPAWNS = 8
};

enum Actions
{
    ACTION_NOVA_HIT = 0,
    ACTION_ACTIVATE_CLOUDS = 1,
    ACTION_DEACTIVATE_CLOUDS = 2,
    ACTION_PORTAL_TO_MADNESS_STORMWIND = 3,
    ACTION_PORTAL_TO_MADNESS_DRAGON = 4,
    ACTION_PORTAL_TO_MADNESS_LICHKING = 5,
    ACTION_BRAIN_UNDER_30_PERCENT = 6,
};

enum Spells
{
    //All Phases
    // Keeper Freya
    SPELL_RESILIENCE_OF_NATURE                  = 62670,
    SPELL_SANITY_WELL                           = 64170,
    // Keeper Thorim
    SPELL_FURY_OF_THE_STORM                     = 62702,
    SPELL_TITANIC_STORM                         = 64171, // Triggers 64172
    SPELL_TITANIC_STORM_DUMMY                   = 64172, // Dummy Spell ... kills weakend guardians
    // Keeper Mimiron
    SPELL_SPEED_OF_INVENTION                    = 62671,
    SPELL_DESTABILIZATION_MATRIX                = 65210,
    // Keeper Hodir
    SPELL_FORTITUDE_OF_FROST                    = 62650,
    SPELL_HODIRS_PROTECTIVE_GAZE                = 64174,
    // Sanity
    SPELL_SANITY                                = 63050,
    SPELL_INSANE                                = 63120,
    //Phase 1:
    SPELL_SUMMON_GUARDIAN                       = 63031,
    SPELL_OMINOUS_CLOUD                         = 60977,
    SPELL_OMINOUS_CLOUD_TRIGGER                 = 60978,
    SPELL_OMINOUS_CLOUD_DAMAGE                  = 60984,
    SPELL_OMINOUS_CLOUD_EFFECT                  = 63084,
    //  Sara
    SPELL_SARAS_FERVOR                          = 63138, // On Player
    SPELL_SARAS_BLESSING                        = 63134, // On Player
    SPELL_SARAS_ANGER                           = 63147, // On "Enemy"
    //  Guardians of Yogg-Saron 
    SPELL_DOMINATE_MIND                         = 63042, // Removed by blizz, Needs Sanity Scripting
    SPELL_DARK_VOLLEY                           = 63038, // Needs Sanity Scripting
    SPELL_SHADOW_NOVA                           = 65209, // On Death
    //Phase 2:
    //  Sara - She spams Psychosis without pause on random raid members unless she casts something else. The other three abilities each have a 30 second cooldown, and are used randomly when available.
    SPELL_PSYCHOSIS                             = 65301, // Needs Sanity Scripting
    SPELL_BRAIN_LINK                            = 63802, // Only Apply Aura
    SPELL_BRAIN_LINK_DAMAGE                     = 63803, // Needs Sanity Scripting
    SPELL_BRAIN_LINK_DUMMY                      = 63804, // Dummy Effekt
    SPELL_MALADY_OF_MIND                        = 63830, // Needs Sanity Scripting, Trigger 63881 on remove
    SPELL_DEATH_RAY_PERIODIC                    = 63883, // Trigger 63884
    SPELL_SARA_SHADOWY_BARRIER                  = 64775,
    // Tentacle
    SPELL_ERUPT                                 = 64144,
    //  Crusher Tentacle
    SPELL_DIMISH_POWER                          = 64145, // Aura around Caster
    SPELL_FOCUS_ANGER                           = 57688, // Trigger 57689
    SPELL_CRUSH                                 = 64146, 
    //  Corruptor Tentacle
    SPELL_DRAINING_POISON                       = 64152, 
    SPELL_BLACK_PLAGUE                          = 64153, // Trigger 64155
    SPELL_APATHY                                = 64156,
    SPELL_CURSE_OF_DOOM                         = 64157,
    //  Constrictor Tentacles
    SPELL_LUNGE                                 = 64123, // Need Vehicle
    SPELL_SQUEEZE                               = 64126, // Until killed
    //  Influence Tentacle
    SPELL_GRIM_REPRISAL                         = 63305, // Dummy aura
    SPELL_GRIM_REPRISAL_DAMAGE                  = 64039, // Damage 1
    //  Yogg-Saron
    SPELL_EXTINGUISH_ALL_LIFE                   = 64166, // After 15 Minutes
    SPELL_SHADOWY_BARRIER                       = 63894,
    SPELL_SUMMON_CRUSHER_TENTACLE               = 64139,
    SPELL_SUMMON_CURRUPTOR_TENTACLE             = 64143,
    SPELL_SUMMON_CONSTRICTOR_TENTACLES          = 64133,
    //  Brain of Yogg-Sauron
    SPELL_INDUCE_MADNESS                        = 64059,
    SPELL_SHATTERED_ILLUSIONS                   = 64173,
    //  Mind Portal 
    SPELL_TELEPORT                              = 64027, // Not Used
    //  Lauthing Skull
    SPELL_LS_LUNATIC_GAZE                       = 64167,
    SPELL_LS_LUNATIC_GAZE_EFFECT                = 64168,
    //Phase 3:
    //  Yogg-Saron
    SPELL_DEAFENING_ROAR                        = 64189, // Cast only on 25plr Mode and only with 0-3 Keepers active
    SPELL_SUMMON_IMMORTAL_GUARDIAN              = 64158,

    SPELL_SHADOW_BEACON                         = 64465, // Casted on Immortal Guardian - trigger 64466
    SPELL_EMPOWERING_SHADOWS_SCRP_1             = 64466, // Script Effekt ... as index 64467
    SPELL_EMPOWERING_SHADOWS_SCRP_2             = 64467, // I dont need this
    SPELL_EMPOWERING_SHADOWS_HEAL_10            = 64468, // 10plr Heal
    SPELL_EMPOWERING_SHADOWS_HEAL_25            = 64486, // 20plr Heal

    SPELL_LUNATIC_GAZE                          = 64163, // Triggers 4 Times 64164
    SPELL_LUNATIC_GAZE_EFFECT                   = 64164, // Needs Sanity Scripting

    //  Immortal Guardian - under 1% no damage
    SPELL_DRAIN_LIFE_10                         = 64159,
    SPELL_DRAIN_LIFE_25                         = 33988,

    SPELL_WEAKENED                              = 64162, // Dummy on low health for Titan Storm and Shadow Beacon
    SPELL_EMPOWERED                             = 65294, // stacks 9 times ... on 100% hp it have 9 stacks .. but with <10% it havent any
};

enum BossPhase
{
    PHASE_NONE = 0,
    PHASE_SARA = 1,
    PHASE_BRAIN = 2,
    PHASE_YOGG = 3
};

enum TentacleType
{
    CRUSHER_TENTACLE        = 0,
    CORRUPTOR_TENTACLE      = 1,
    CONSTRICTOR_TENTACLE    = 2
};

enum BrainEventPhase
{
    PORTAL_PHASE_KING_LLIANE = 0,
    PORTAL_PHASE_DRAGON_SOUL = 1,
    PORTAL_PHASE_LICH_KING   = 2,
    PORTAL_PHASE_BRAIN_NONE = 3
};

const Position InnerBrainLocation[3] = 
{
    {1944.87f,  37.22f, 239.7f, (0.66f*M_PI)}, //King Lliane
    {2045.97f, -25.45f, 239.8f, 0           }, //Dragon Soul
    {1953.41f, -73.73f, 240.0f, (1.33f*M_PI)}  //Lich King
};

const Position BrainPortalLocation[4] = 
{
    {1970.48f,   -9.75f, 325.5f, 0},
    {1992.76f,  -10.21f, 325.5f, 0},
    {1995.53f,  -39.78f, 325.5f, 0},
    {1969.25f,  -42.00f, 325.5f, 0}
    /*
     ToDo: 6 Weitere Portale f�r 25 Mode
    */
};

const Position KingLlianeTentacleLocation[CONSTANT_MAX_LLIANE_TENTACLE_SPAWNS] = 
{
    {1949.82f,   50.77f, 239.70f, (0.8f*M_PI)},
    {1955.24f,   72.08f, 239.70f, (1.04f*M_PI)},
    {1944.51f,   90.88f, 239.70f, (1.3f*M_PI)},
    {1923.46f,   96.71f, 239.70f, (1.53f*M_PI)},
    {1904.14f,   85.99f, 239.70f, (1.78f*M_PI)},
    {1898.78f,   64.62f, 239.70f, (0.05f*M_PI)},
    {1909.74f,   45.15f, 239.70f, (0.31f*M_PI)},
    {1931.01f,   39.85f, 239.70f, (0.55f*M_PI)},
};

const Position DragonSoulTentacleLocation[CONSTANT_MAX_DRAGONSOUL_TENTACLE_SPAWNS] = 
{
    // ENTRY_RUBY_CONSORT
    {2061.44f,  -11.83f, 239.80f, 0},
    {2059.87f,  -37.77f, 239.80f, 0},
    // ENTRY_AZURE_CONSORT
    {2105.42f,  -71.81f, 239.80f, (0.51f*M_PI)},
    {2131.29f,  -60.90f, 239.80f, (0.68f*M_PI)},
    // ENTRY_OBSIDIAN_CONSORT
    {2147.62f,  -42.06f, 239.80f, M_PI},
    {2147.62f,   -6.91f, 239.80f, M_PI},
    //ENTRY_EMERAL_CONSORT
    {2125.64f,   17.08f, 239.80f, (1.35f*M_PI)},
    {2109.06f,   22.69f, 239.80f, (1.42f*M_PI)}
};

const Position LichKingTentacleLocation[CONSTANT_MAX_LICHKING_TENTACLE_SPAWNS] = 
{
    {1944.20f,  -136.72f, 240.00f, (1.35f*M_PI)},
    {1950.06f,  -139.36f, 240.00f, (1.35f*M_PI)},
    {1948.23f,  -129.44f, 240.00f, (1.35f*M_PI)},

    {1920.34f,  -136.38f, 240.00f, (1.35f*M_PI)},
    {1914.44f,  -132.35f, 240.00f, (1.35f*M_PI)},
    {1919.69f,  -129.47f, 240.00f, (1.35f*M_PI)},

    {1909.49f,  -111.84f, 240.00f, (1.35f*M_PI)},
    {1902.02f,  -107.69f, 240.00f, (1.35f*M_PI)},
    {1910.28f,  -102.96f, 240.00f, (1.35f*M_PI)}
};

const Position BrainLocation = {1980.01f, -25.36f, 260.00f, M_PI};
const Position SaraLocation = {1980.28f, -25.58f, 325.00f, M_PI};

const Position InnerBrainTeleportLocation[3] = 
{
    {2001.40f, -59.66f, 245.07f, 0},
    {1941.61f, -25.88f, 244.98f, 0},
    {2001.18f,  9.409f, 245.24f, 0}
};

const Position KeeperSpawnLocation[4] = 
{
    {1939.15f,  42.47f, 338.46f, 1.7f*M_PI}, // Mimiron
    {2037.09f,  25.43f, 338.46f, 1.3f*M_PI}, // Freya
    {2036.88f, -73.66f, 338.46f, 0.7f*M_PI}, // Thorim
    {1939.94f, -90.49f, 338.46f, 0.3f*M_PI} // Hodir
};

class boss_sara : public CreatureScript
{
public:
    boss_sara() : CreatureScript("boss_sara") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_saraAI (pCreature);
    }

    struct boss_saraAI : public ScriptedAI
    {
        boss_saraAI(Creature *c) : ScriptedAI(c), Summons(me)
        {
            m_pInstance = c->GetInstanceScript();
            me->SetFlying(true);
            SetImmuneToPushPullEffects(true);
        }

        InstanceScript* m_pInstance;
        SummonList Summons;

        BossPhase m_Phase;
        uint32 amountKeeper;

        uint64 guidYogg;
        uint64 guidYoggBrain;
        std::list<uint64> guidEventTentacles;

        // Phase 1
        uint32 uiSarasHelp_Timer;

        uint32 uiGuardianSummon_Timer;
        uint32 uilastGuardianSummon_Timer;
        uint32 uiRandomYell_Timer;

        uint32 NovaHitCounter;
        // Phase 2
        bool IsSpeaking;
        uint32 SpeakingPhase;
        uint32 uiSpeaking_Timer;

        uint32 uiPsychosis_Timer;
        uint32 uiMindSpell_Timer;
        uint32 uiTentacle_Timer;

        uint32 uiEnrage_Timer;
        uint32 uiMadness_Timer;

        BrainEventPhase currentBrainEventPhase;

        // Phase 3
        uint32 uiDeafeningRoar_Timer;
        uint32 uiShadowBeacon_Timer;
        uint32 uiLunaticGaze_Timer;

        void CloudHandling(bool remove)
        {
            std::list<Creature*> CloudList;
            me->GetCreatureListWithEntryInGrid(CloudList,ENTRY_OMINOUS_CLOUD,100.0f);
            if(!CloudList.empty())
            {
                for(std::list<Creature*>::iterator itr = CloudList.begin(); itr != CloudList.end(); itr++)
                {
                    if(remove) (*itr)->AI()->DoAction(ACTION_DEACTIVATE_CLOUDS);
                    else (*itr)->AI()->DoAction(ACTION_ACTIVATE_CLOUDS);
                }
            }
        }

        void Reset()
        {
            Summons.DespawnAll();
            guidEventTentacles = std::list<uint64>();

            me->InterruptNonMeleeSpells(false);
            // Zurueck an Home ... muss nicht sein ist aber besser so
            Position pos = me->GetHomePosition();
            me->NearTeleportTo(pos.m_positionX,pos.m_positionY,pos.m_positionZ,pos.m_orientation);
            me->RemoveAurasDueToSpell(SPELL_SHATTERED_ILLUSIONS);
            me->RemoveAurasDueToSpell(SPELL_SARA_SHADOWY_BARRIER);

            // Remove Random MoveMaster
            me->GetMotionMaster()->Clear(false);
            me->GetMotionMaster()->MoveIdle();

            // Reset Display
            me->setFaction(35);
            me->SetVisible(true);
            me->SetDisplayId(me->GetNativeDisplayId());
            // Reset Health
            me->SetHealth(me->GetMaxHealth());
            // Remove Not Attackable Flags
            //me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            //me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            // Reset Phase
            m_Phase = PHASE_NONE;
            // Respawn Clouds
            CloudHandling(false);
            SetSanityAura(true);
            // Reset HitCounter Phase 1
            NovaHitCounter = CONSTANT_MAX_NOVA_HITS;
            currentBrainEventPhase = PORTAL_PHASE_BRAIN_NONE;

            // Spawn Yoggy if not spawned
            Creature* yogg = me->GetCreature(*me,guidYogg);
            if(!yogg)
                DoSummon(ENTRY_YOGG_SARON,SaraLocation,0,TEMPSUMMON_MANUAL_DESPAWN);
            Creature* yoggbrain = me->GetCreature(*me,guidYoggBrain);
            if(!yoggbrain)
                DoSummon(ENTRY_BRAIN_OF_YOGG_SARON,BrainLocation,0,TEMPSUMMON_MANUAL_DESPAWN);

            if(m_pInstance)
                m_pInstance->SetBossState(TYPE_YOGGSARON,NOT_STARTED);

            uiRandomYell_Timer = urand(10000,20000);
        }

        void DoSpawnKeeperForSupport() // Despawn on Sara Reset
        {
            if(m_pInstance)
            {
                uint32 supportFlag = m_pInstance->GetData(DATA_KEEPER_SUPPORT_YOGG);

                if((supportFlag & MIMIRON_SUPPORT) == MIMIRON_SUPPORT)
                    DoSummon(ENTRY_KEEPER_MIMIRON,KeeperSpawnLocation[0],0,TEMPSUMMON_MANUAL_DESPAWN);
                if((supportFlag & FREYA_SUPPORT) == FREYA_SUPPORT)
                    DoSummon(ENTRY_KEEPER_FREYA,KeeperSpawnLocation[1],0,TEMPSUMMON_MANUAL_DESPAWN);
                if((supportFlag & THORIM_SUPPORT) == THORIM_SUPPORT)
                    DoSummon(ENTRY_KEEPER_THORIM,KeeperSpawnLocation[2],0,TEMPSUMMON_MANUAL_DESPAWN);
                if((supportFlag & HODIR_SUPPORT) == HODIR_SUPPORT)
                    DoSummon(ENTRY_KEEPER_HODIR,KeeperSpawnLocation[3],0,TEMPSUMMON_MANUAL_DESPAWN);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {

            uiSarasHelp_Timer = urand(5000,6000);
            uiGuardianSummon_Timer = 10000;
            uilastGuardianSummon_Timer = 35000;

            uiPsychosis_Timer = urand(5000,5000);
            uiMindSpell_Timer = urand(30000,30000);
            uiTentacle_Timer = urand(3000,5000);
            uiMadness_Timer = 60000;

            uiDeafeningRoar_Timer = urand(30000,60000);
            uiShadowBeacon_Timer = 30000;
            uiLunaticGaze_Timer = 12000;

            uiEnrage_Timer = 900000;

            if(Creature* yogg = me->GetCreature(*me,guidYogg))
                DoZoneInCombat(yogg);

            SetSanityAura();
            DoSpawnKeeperForSupport();

            if(m_pInstance)
                m_pInstance->SetBossState(TYPE_YOGGSARON,IN_PROGRESS);

            // TO DO: Only Debug 
            amountKeeper = 3;
        }

        void ReceiveEmote(Player* pPlayer, uint32 emote)
        {
            if(m_Phase >= PHASE_BRAIN)
            {
                if(emote == TEXTEMOTE_KISS)
                {
                    if(pPlayer->HasAchieved(RAID_MODE(ACHIEVMENT_KISS_AND_MAKE_UP_10,ACHIEVMENT_KILL_AND_MAKE_UP_25)))
                        return;

                    if (me->IsWithinLOS(pPlayer->GetPositionX(),pPlayer->GetPositionY(),pPlayer->GetPositionZ()) && me->IsWithinDistInMap(pPlayer,30.0f))
                    {
                        if(AchievementEntry const *achievKissAndMakeUp = GetAchievementStore()->LookupEntry(RAID_MODE(ACHIEVMENT_KISS_AND_MAKE_UP_10,ACHIEVMENT_KILL_AND_MAKE_UP_25)))
                            pPlayer->CompletedAchievement(achievKissAndMakeUp);
                    }
                }
            }
        }

        //void SpellHit(Unit* caster, const SpellEntry* spell)
        //{
        //    switch(spell->Id)
        //    {
        //    case SPELL_SHADOW_NOVA:
        //        if(m_Phase != PHASE_SARA)
        //            return;

        //        NovaHitCounter--;

        //        if(NovaHitCounter <= 0)
        //            SetPhase(PHASE_BRAIN);

        //        break;
        //    }
        //}

        //FindNearestCreature

        void ModifySanity(Player* target, int8 amount)
        {
            if(target && target->isAlive())
            {
                int32 newamount;
                if(Aura* aur = target->GetAura(SPELL_SANITY, GetGUID()))
                {
                    newamount = aur->GetStackAmount();
                    newamount += amount;
                    if(newamount <= 0)
                        target->RemoveAurasDueToSpell(SPELL_SANITY);
                    else
                        aur->SetStackAmount(newamount);
                }
            }
        }

        void SpellHitTarget(Unit* target, const SpellEntry* spell)
        {
            if(target && target->ToPlayer())
            {
                switch(spell->Id)
                {
                case SPELL_PSYCHOSIS:
                    ModifySanity(target->ToPlayer(),-12);
                    break;
                case SPELL_BRAIN_LINK_DAMAGE:
                    ModifySanity(target->ToPlayer(),-2);
                    break;
                case SPELL_MALADY_OF_MIND:
                    ModifySanity(target->ToPlayer(),-3);
                    break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 i)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if(i == 1)
            {
                me->GetMotionMaster()->Clear(false);
                me->GetMotionMaster()->MoveIdle();
            }
        }

        void DoAction(const int32 action)
        {
            switch(action)
            {
            case ACTION_NOVA_HIT:
                if(m_Phase != PHASE_SARA)
                    return;

                NovaHitCounter--;

                if(NovaHitCounter <= 0)
                    SetPhase(PHASE_BRAIN);
                else me->ModifyHealth(-25000);
                break;
            case ACTION_BRAIN_UNDER_30_PERCENT:
                SetPhase(PHASE_YOGG);
                break;
            }
        }

        void SetPhase(BossPhase newPhase)
        {
            if(m_Phase == newPhase)
                return;

            //Sayings
            switch(newPhase)
            {
            case PHASE_SARA:
                break;
            case PHASE_BRAIN:
                me->SetHealth(me->GetMaxHealth());
                IsSpeaking = true;
                SpeakingPhase = 0;
                uiSpeaking_Timer = 1000;
                //me->SetDisplayId(SARA_TRANSFORM);
                CloudHandling(true);
                uiRandomYell_Timer = 35000;
                break;
            case PHASE_YOGG:
                me->SetVisible(false);
                if(Creature* yogg = me->GetCreature(*me,guidYogg))
                {
                    yogg->SetHealth(yogg->CountPctFromMaxHealth(30));
                    yogg->RemoveAurasDueToSpell(SPELL_SHADOWY_BARRIER);
                    yogg->RemoveAurasDueToSpell(SPELL_SHATTERED_ILLUSIONS);
                    DoScriptText(SAY_PHASE3,yogg);
                }

                // Alle Spieler aus BrainRoom rauswerfen
                if(me->GetMap() && me->GetMap()->IsDungeon())
                {
                    Map::PlayerList const& players = me->GetMap()->GetPlayers();
                    if (!players.isEmpty())
                        for(Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                            if (Player* plr = itr->getSource())
                                if(plr->isAlive() && IsPlayerInBrainRoom(plr))
                                {
                                    plr->NearTeleportTo(SaraLocation.GetPositionX(),SaraLocation.GetPositionY(),SaraLocation.GetPositionZ(),M_PI,false);
                                    plr->JumpTo(30.0f,5.0f,true);
                                }
                }
                uiGuardianSummon_Timer = 20000;
                uilastGuardianSummon_Timer = 35000;
                break;
            }

            m_Phase = newPhase;
        }

        void SaraRandomYell()
        {
            switch(m_Phase)
            {
            case PHASE_NONE: DoScriptText(RAND(SAY_SARA_PREFIGHT_1,SAY_SARA_PREFIGHT_2),me); break;
            case PHASE_SARA: DoScriptText(RAND(SAY_SARA_AGGRO_1,SAY_SARA_AGGRO_2,SAY_SARA_AGGRO_3),me); break;
            case PHASE_BRAIN: DoScriptText(RAND(SAY_SARA_PHASE2_1,SAY_SARA_PHASE2_2,SAY_SARA_AGGRO_3),me); break;
            }
        }

        void MoveInLineOfSight(Unit* target)
        {
            if(m_Phase == PHASE_NONE)
            {
                if(target && me->GetDistance2d(target) <= 100 && target->ToPlayer() && !target->ToPlayer()->isGameMaster() && me->IsWithinLOSInMap(target))
                {
                    SetPhase(PHASE_SARA);
                    EnterCombat(target);
                }
            }
        }

        void JustSummoned(Creature* pSummoned)
        {
            switch(pSummoned->GetEntry())
            {
            case ENTRY_GUARDIAN_OF_YOGG_SARON:
                pSummoned->setFaction(14);
                pSummoned->AI()->AttackStart(SelectPlayerTargetInRange(100.0f));
                break;
            case ENTRY_YOGG_SARON:
                guidYogg = pSummoned->GetGUID();
                pSummoned->SetReactState(REACT_PASSIVE);
                pSummoned->setFaction(14);
                //pSummoned->SetVisible(false);
                pSummoned->SetStandState(UNIT_STAND_STATE_SUBMERGED);
                pSummoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                pSummoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                //pSummoned->SetDisplayId(YOGGSARON_TRANSFORM);
                break;
            case ENTRY_BRAIN_OF_YOGG_SARON:
                guidYoggBrain = pSummoned->GetGUID();
                pSummoned->setActive(true);
                break;
            case ENTRY_RUBY_CONSORT:
            case ENTRY_OBSIDIAN_CONSORT:
            case ENTRY_AZURE_CONSORT:
            case ENTRY_EMERAL_CONSORT:
            case ENTRY_DEATHSWORN_ZEALOT:
            case ENTRY_SUIT_OF_ARMOR:
                pSummoned->SetReactState(REACT_PASSIVE);
                pSummoned->setFaction(4);
                break;
            }

            Summons.Summon(pSummoned);
        }

        bool IsEncounterInProgress()
        {
            if(me->GetMap() && me->GetMap()->IsDungeon())
            {
                Map::PlayerList const& players = me->GetMap()->GetPlayers();
                if (!players.isEmpty())
                    for(Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        if (Player* plr = itr->getSource())
                            if(plr->isAlive() && !plr->isGameMaster() && !plr->HasAura(SPELL_INSANE))
                                return true;
            }
            return false;
        }

        void SetSanityAura(bool remove = false)
        {
            if(me->GetMap() && me->GetMap()->IsDungeon())
            {
                Map::PlayerList const& players = me->GetMap()->GetPlayers();
                if (!players.isEmpty())
                    for(Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        if (Player* plr = itr->getSource())
                            if(plr->isAlive())
                            {
                                if(!remove)
                                {
                                    me->AddAura(SPELL_SANITY,plr);
                                    me->SetAuraStack(SPELL_SANITY,plr,100);
                                }else
                                {
                                    plr->RemoveAurasDueToSpell(SPELL_SANITY);
                                }
                            }
            }
        }

        Player* SelectPlayerTargetInRange(float range)
        {
            Player *target = NULL;
            Trinity::AnyPlayerInObjectRangeCheck u_check(me, range, true);
            Trinity::PlayerSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, target, u_check);
            me->VisitNearbyObject(range, searcher);
            return target;
        }

        Creature* GetRandomEntryTarget(uint32 entry, float range = 100.0f)
        {
            std::list<Creature*> TargetList;
            me->GetCreatureListWithEntryInGrid(TargetList,entry, range);
            if(TargetList.empty())
                return NULL;

            std::list<Creature*>::iterator itr = TargetList.begin();
            advance(itr, urand(0, TargetList.size()-1));
            return (*itr);
        }

        // For Gardian Summon
        Creature* GetRandomCloudTarget(float range = 100.0f)
        {
            return GetRandomEntryTarget(ENTRY_OMINOUS_CLOUD);
        }

        // For Immortal Guardian Heal
        Creature* GetRandomGuardianTarget(float range = 100.0f)
        {
            return GetRandomEntryTarget(ENTRY_IMMORTAL_GUARDIAN);
        }

        bool IsPlayerInBrainRoom(Player* pPlayer)
        {
            return pPlayer->GetPositionZ() < 300;
        }

        bool AllSpawnsDeadOrDespawned(std::list<uint64> GuidListe)
        {
            for(std::list<uint64>::iterator itr = GuidListe.begin(); itr != GuidListe.end(); ++itr)
            {
                Creature* temp = me->GetCreature(*me,*itr);
                if(temp && temp->isAlive())
                    return false;
            }

            return true;
        }

        void DoMadness()
        {
            if(m_pInstance)
            {
                m_pInstance->HandleGameObject(m_pInstance->GetData64(TYPE_BRAIN_DOOR_1),false);
                m_pInstance->HandleGameObject(m_pInstance->GetData64(TYPE_BRAIN_DOOR_2),false);
                m_pInstance->HandleGameObject(m_pInstance->GetData64(TYPE_BRAIN_DOOR_3),false);
            }

            // Random Action - Not Blizzlike?
            Actions tempAction = RAND(ACTION_PORTAL_TO_MADNESS_STORMWIND,ACTION_PORTAL_TO_MADNESS_DRAGON,ACTION_PORTAL_TO_MADNESS_LICHKING);
            // Spawn Portal
            for(int i = 0; i < 4; ++i)
            {
                if(Creature* portal = DoSummon(ENTRY_BRAIN_PORTAL,BrainPortalLocation[i],40000,TEMPSUMMON_TIMED_DESPAWN))
                    portal->AI()->DoAction(tempAction);
            }

            // Spawn Event Tentacle
            switch(tempAction)
            {
            case ACTION_PORTAL_TO_MADNESS_DRAGON:
                currentBrainEventPhase = PORTAL_PHASE_DRAGON_SOUL;
                guidEventTentacles.clear();
                uint32 entry;
                for(int i = 0; i < CONSTANT_MAX_DRAGONSOUL_TENTACLE_SPAWNS; ++i)
                {
                    switch(i)
                    {
                    case 0:
                    case 1: entry = ENTRY_RUBY_CONSORT; break;
                    case 2:
                    case 3: entry = ENTRY_AZURE_CONSORT; break;
                    case 4:
                    case 5: entry = ENTRY_OBSIDIAN_CONSORT; break;
                    case 6:
                    case 7: entry = ENTRY_EMERAL_CONSORT; break;
                    }
                    if(Creature* summon = DoSummon(entry,DragonSoulTentacleLocation[i],60000,TEMPSUMMON_TIMED_DESPAWN))
                        guidEventTentacles.push_back(summon->GetGUID());
                }
                break;
            case ACTION_PORTAL_TO_MADNESS_LICHKING:
                currentBrainEventPhase = PORTAL_PHASE_LICH_KING;
                guidEventTentacles.clear();
                for(int i = 0; i < CONSTANT_MAX_LICHKING_TENTACLE_SPAWNS; ++i)
                {
                    if(Creature* summon = DoSummon(ENTRY_DEATHSWORN_ZEALOT,LichKingTentacleLocation[i],60000,TEMPSUMMON_TIMED_DESPAWN))
                        guidEventTentacles.push_back(summon->GetGUID());
                }
                break;
            case ACTION_PORTAL_TO_MADNESS_STORMWIND:
                currentBrainEventPhase = PORTAL_PHASE_KING_LLIANE;
                guidEventTentacles.clear();
                for(int i = 0; i < CONSTANT_MAX_LLIANE_TENTACLE_SPAWNS; ++i)
                {
                    if(Creature* summon = DoSummon(ENTRY_SUIT_OF_ARMOR,KingLlianeTentacleLocation[i],60000,TEMPSUMMON_TIMED_DESPAWN))
                        guidEventTentacles.push_back(summon->GetGUID());
                }
                break;
            }

            if(Creature* yoggbrain = me->GetCreature(*me,guidYoggBrain))
                yoggbrain->CastSpell(yoggbrain,SPELL_INDUCE_MADNESS,false);
        }

        void UpdateAI(const uint32 diff)
        {
            if(uiRandomYell_Timer <= diff)
            {
                SaraRandomYell();
                uiRandomYell_Timer = urand(20000,30000);
            }else uiRandomYell_Timer -= diff;

            switch(m_Phase)
            {
                case PHASE_SARA:
                    if(uiGuardianSummon_Timer <= diff)
                    {
                        if(Creature* target = GetRandomCloudTarget(500.0f))
                            target->CastSpell(target,SPELL_SUMMON_GUARDIAN,true);

                        uilastGuardianSummon_Timer = uilastGuardianSummon_Timer-5000 <= 10000 ? 10000 : uilastGuardianSummon_Timer - 5000;
                        uiGuardianSummon_Timer = uilastGuardianSummon_Timer;
                    }else uiGuardianSummon_Timer -= diff;

                    if(uiSarasHelp_Timer <= diff)
                    {
                        switch(urand(0,2))
                        {
                        case 0:
                            if(Player* target = SelectPlayerTargetInRange(500.0f))
                                if(!IsPlayerInBrainRoom(target))
                                DoCast(target,SPELL_SARAS_FERVOR,false);
                            break;
                        case 1:
                            if(Player* target = SelectPlayerTargetInRange(500.0f))
                                if(!IsPlayerInBrainRoom(target))
                                    DoCast(target,SPELL_SARAS_BLESSING,false);
                        case 2:
                            if(Unit* target = GetRandomEntryTarget(ENTRY_GUARDIAN_OF_YOGG_SARON,500.0f))
                                DoCast(target, SPELL_SARAS_ANGER, false);
                            break;
                        default: break;
                        }
                        uiSarasHelp_Timer = urand(5000,6000);
                    }else uiSarasHelp_Timer -= diff;

                    break;
                case PHASE_BRAIN:
                    if(IsSpeaking)
                    {
                        if(uiSpeaking_Timer <= diff)
                        {
                            switch(SpeakingPhase)
                            {
                            case 0:
                                //if(Creature* yogg = me->GetCreature(*me,guidYogg))
                                //    yogg->SetVisible(true);

                                DoScriptText(SAY_PHASE2_1,me);
                                uiSpeaking_Timer = 5000;
                                break;
                            case 1:
                                DoScriptText(SAY_PHASE2_2,me);
                                uiSpeaking_Timer = 5000;
                                break;
                            case 2:
                                DoScriptText(SAY_PHASE2_3,me);
                                uiSpeaking_Timer = 5000;
                                break;
                            case 3:
                                DoScriptText(SAY_PHASE2_4,me);
                                uiSpeaking_Timer = 5000;
                                break;
                            case 4:
                                me->SetDisplayId(SARA_TRANSFORM);
                                DoCast(me,SPELL_SARA_SHADOWY_BARRIER,false);
                                me->GetMotionMaster()->MovePoint(1,me->GetPositionX(),me->GetPositionY(),me->GetPositionZ()+15);
                                if(Creature* yogg = me->GetCreature(*me,guidYogg))
                                {
                                    //yogg->SetDisplayId(YOGGSARON_NORMAL);
                                    yogg->CastSpell(yogg,SPELL_SHADOWY_BARRIER,false);
                                    yogg->SetStandState(UNIT_STAND_STATE_STAND);
                                    yogg->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                    yogg->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    DoScriptText(SAY_PHASE2_5,yogg);
                                }
                                me->setFaction(14);
                                //me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                //me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                uiSpeaking_Timer = 5000;
                                IsSpeaking = false;
                                break;
                            }
                            SpeakingPhase++;
                        }else uiSpeaking_Timer -= diff;
                    }else
                    {
                        if(!me->HasAura(SPELL_SHATTERED_ILLUSIONS))
                        {
                            if(uiPsychosis_Timer <= diff)
                            {
                                if(Player* target = SelectPlayerTargetInRange(500.0f))
                                    if(!IsPlayerInBrainRoom(target))
                                        DoCast(target,SPELL_PSYCHOSIS,false);
                                uiPsychosis_Timer = urand(5000,5000);
                            }else uiPsychosis_Timer -= diff;

                            if(uiMindSpell_Timer <= diff)
                            {
                                if(!me->IsNonMeleeSpellCasted(false))
                                {
                                    switch(urand(0,2))
                                    {
                                    case 0:
                                        if(Player* target = SelectPlayerTargetInRange(500.0f))
                                            if(!IsPlayerInBrainRoom(target))
                                                DoCast(target,SPELL_MALADY_OF_MIND,false);
                                        break;
                                    case 1:
                                        break;
                                    case 2:
                                        break;
                                    }
                                    uiMindSpell_Timer = 30000;
                                }
                            }else uiMindSpell_Timer -= diff;

                            if(uiTentacle_Timer <= diff)
                            {
                                if(urand(0,2) == 0)
                                {
                                    if(Player* target = SelectPlayerTargetInRange(500.0f))
                                        if(!IsPlayerInBrainRoom(target))
                                            target->CastSpell(target,SPELL_SUMMON_CONSTRICTOR_TENTACLES,true);
                                }else
                                {
                                    if(Creature* yogg = me->GetCreature(*me,guidYogg))
                                        yogg->CastSpell(yogg,RAND(SPELL_SUMMON_CRUSHER_TENTACLE,SPELL_SUMMON_CURRUPTOR_TENTACLE),true);
                                }
                                uiTentacle_Timer = urand(15000,30000);
                            }else uiTentacle_Timer -= diff;
                        }else
                        {
                            if(Creature* yoggbrain = me->GetCreature(*me,guidYoggBrain))
                                if(!yoggbrain->IsNonMeleeSpellCasted(false))
                                {
                                    if(Creature* yogg = me->GetCreature(*me,guidYogg))
                                        yogg->RemoveAurasDueToSpell(SPELL_SHATTERED_ILLUSIONS);
                                    me->RemoveAurasDueToSpell(SPELL_SHATTERED_ILLUSIONS);
                                }
                        }

                        if(uiMadness_Timer <= diff)
                        {
                            if(Creature* yogg = me->GetCreature(*me,guidYogg))
                            {
                                DoScriptText(SAY_VISION,yogg);
                                DoMadness();
                            }

                            //Say YoggSaron to Open Portals
                            uiMadness_Timer = 80000;
                        }else uiMadness_Timer -= diff;

                        if(!me->HasAura(SPELL_SHATTERED_ILLUSIONS))
                        {
                            if(currentBrainEventPhase != PORTAL_PHASE_BRAIN_NONE)
                            {
                                if(AllSpawnsDeadOrDespawned(guidEventTentacles))
                                {
                                    switch(currentBrainEventPhase)
                                    {
                                    case PORTAL_PHASE_DRAGON_SOUL: if(m_pInstance) m_pInstance->HandleGameObject(m_pInstance->GetData64(TYPE_BRAIN_DOOR_1),true); break;
                                    case PORTAL_PHASE_LICH_KING: if(m_pInstance) m_pInstance->HandleGameObject(m_pInstance->GetData64(TYPE_BRAIN_DOOR_2),true); break;
                                    case PORTAL_PHASE_KING_LLIANE: if(m_pInstance) m_pInstance->HandleGameObject(m_pInstance->GetData64(TYPE_BRAIN_DOOR_3),true); break;
                                    }
                                    currentBrainEventPhase = PORTAL_PHASE_BRAIN_NONE;
                                    if(Creature* yogg = me->GetCreature(*me,guidYogg))
                                        me->AddAura(SPELL_SHATTERED_ILLUSIONS,yogg);
                                    me->AddAura(SPELL_SHATTERED_ILLUSIONS,me);
                                }
                            }
                        }
                    }
                    break;
                case PHASE_YOGG:
                    if(uiGuardianSummon_Timer <= diff)
                    {
                        if(Creature* yogg = me->GetCreature(*me,guidYogg))
                            yogg->CastSpell(yogg,SPELL_SUMMON_IMMORTAL_GUARDIAN,true);

                        uilastGuardianSummon_Timer = uilastGuardianSummon_Timer-5000 <= 10000 ? 10000 : uilastGuardianSummon_Timer - 5000;
                        uiGuardianSummon_Timer = uilastGuardianSummon_Timer;
                    }else uiGuardianSummon_Timer -= diff;

                    if(uiLunaticGaze_Timer <= diff)
                    {
                        if(Creature* yogg = me->GetCreature(*me,guidYogg))
                        {
                            if(yogg->IsNonMeleeSpellCasted(false))
                            {
                                yogg->CastSpell(yogg,SPELL_LUNATIC_GAZE,false);
                                uiLunaticGaze_Timer = 12000;
                            }
                        }
                    }else uiLunaticGaze_Timer -= diff;

                    if(getDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL && amountKeeper < 4)
                        if(uiDeafeningRoar_Timer <= diff)
                        {
                            if(Creature* yogg = me->GetCreature(*me,guidYogg))
                            {
                                if(yogg->IsNonMeleeSpellCasted(false))
                                {
                                    yogg->CastSpell(yogg,SPELL_DEAFENING_ROAR,false);
                                    uiDeafeningRoar_Timer = 60000;
                                }
                            }
                        }else uiDeafeningRoar_Timer -= diff;

                    if(uiShadowBeacon_Timer <= diff)
                    {
                        if(Creature* yogg = me->GetCreature(*me,guidYogg))
                        {
                            if(yogg->IsNonMeleeSpellCasted(false))
                            {
                                if(Creature* guard = GetRandomGuardianTarget())
                                {
                                    if(guard->HasAura(SPELL_WEAKENED))
                                            yogg->CastSpell(guard,SPELL_SHADOW_BEACON,false);
                                }
                                uiShadowBeacon_Timer = 10000;
                            }
                        }
                    }else uiShadowBeacon_Timer -= diff;

                    break;
            }

            if(m_Phase == PHASE_YOGG || m_Phase == PHASE_BRAIN)
            {
                if(uiEnrage_Timer <= diff)
                {
                    if(Creature* yogg = me->GetCreature(*me,guidYogg))
                    {
                        yogg->InterruptNonMeleeSpells(false);
                        yogg->CastSpell(yogg,SPELL_EXTINGUISH_ALL_LIFE,false);
                    }
                    uiEnrage_Timer = 5000;
                }else uiEnrage_Timer -= diff;
            }

            if(m_Phase != PHASE_NONE && !IsEncounterInProgress())
                EnterEvadeMode();
        }
    };
};

class npc_ominous_cloud : public CreatureScript
{
public:
    npc_ominous_cloud() : CreatureScript("npc_ominous_cloud") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ominous_cloudAI (pCreature);
    }

    struct npc_ominous_cloudAI : public ScriptedAI
    {
        npc_ominous_cloudAI(Creature *c) : ScriptedAI(c) 
        {
            SetImmuneToPushPullEffects(true);
        }

        void MoveInLineOfSight(Unit* target)
        {
            if(target && me->GetDistance2d(target) <= 5 && target->ToPlayer() && !target->ToPlayer()->isGameMaster())
                TriggerGuardianSpawn();
        }

        void AttackStart(Unit* /*attacker*/) {}

        void DoAction(const int32 action)
        {
            switch(action)
            {
            case ACTION_DEACTIVATE_CLOUDS:
                me->RemoveAurasDueToSpell(SPELL_SUMMON_GUARDIAN);
                me->RemoveAurasDueToSpell(SPELL_OMINOUS_CLOUD_EFFECT);
                me->SetReactState(REACT_PASSIVE);
                break;
            case ACTION_ACTIVATE_CLOUDS:
                Reset();
                me->SetReactState(REACT_AGGRESSIVE);
                break;
            }
        }

        void TriggerGuardianSpawn()
        {
            if(!me->HasAura(SPELL_SUMMON_GUARDIAN))
                DoCast(me,SPELL_SUMMON_GUARDIAN,true);
        }

        void Reset()
        {
            DoCast(me,SPELL_OMINOUS_CLOUD_EFFECT,true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            //me->SetReactState(REACT_PASSIVE); //Prevent MoveInLineOfSight

            me->GetMotionMaster()->MoveRandom(50.0f);
        }

        void UpdateAI(const uint32 diff) {}
    };
};

class npc_guardian_of_yogg_saron : public CreatureScript
{
public:
    npc_guardian_of_yogg_saron() : CreatureScript("npc_guardian_of_yogg_saron") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_guardian_of_yogg_saronAI (pCreature);
    }

    struct npc_guardian_of_yogg_saronAI : public ScriptedAI
    {
        npc_guardian_of_yogg_saronAI(Creature *c) : ScriptedAI(c)
        {
            m_pInstance = c->GetInstanceScript();
            me->setFaction(14);
        }
        
        InstanceScript* m_pInstance;
        uint32 uiDarkVolley_Timer;

        void SpellHitTarget(Unit* target, const SpellEntry* spell)
        {
            if(target && target->ToPlayer())
            {
                switch(spell->Id)
                {
                case SPELL_DARK_VOLLEY:
                    if(Creature* cSara = me->GetCreature(*me,m_pInstance->GetData64(TYPE_SARA)))
                        CAST_AI(boss_sara::boss_saraAI,cSara->AI())->ModifySanity(target->ToPlayer(),-2);
                    break;
                }
            }
        }

        Unit* SelectPlayerTargetInRange(float range)
        {
            Player *target = NULL;
            Trinity::AnyPlayerInObjectRangeCheck u_check(me, range, true);
            Trinity::PlayerSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, target, u_check);
            me->VisitNearbyObject(range, searcher);
            return target;
        }

        void JustDied(Unit* /*killer*/)
        {
            DoCast(me,SPELL_SHADOW_NOVA,true);

            if(m_pInstance)
            {
                if(Creature* cSara = me->GetCreature(*me,m_pInstance->GetData64(TYPE_SARA)))
                    if(me->GetDistance2d(cSara) <= 15)
                        cSara->AI()->DoAction(ACTION_NOVA_HIT);
            }
        }

        void Reset()
        {
            uiDarkVolley_Timer = urand(20000,30000);
            if(Unit* target = SelectPlayerTargetInRange(100.0f))
                me->AI()->AttackStart(target);
        }

        void UpdateAI(const uint32 diff)
        {
            if(m_pInstance && m_pInstance->GetBossState(TYPE_YOGGSARON) != IN_PROGRESS)
            {
                me->DealDamage(me,me->GetMaxHealth());
                me->RemoveCorpse();
            }

            if (!UpdateVictim())
                return;

            if(uiDarkVolley_Timer <= diff)
            {
                DoCast(SPELL_DARK_VOLLEY);
                uiDarkVolley_Timer = urand(20000,30000);
            }else uiDarkVolley_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_yogg_saron_tentacle : public CreatureScript
{
public:
    npc_yogg_saron_tentacle() : CreatureScript("npc_yogg_saron_tentacle") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_yogg_saron_tentacleAI (pCreature);
    }

    struct npc_yogg_saron_tentacleAI : public ScriptedAI
    {
        npc_yogg_saron_tentacleAI(Creature *c) : ScriptedAI(c)
        {
            m_pInstance = c->GetInstanceScript();
            SetTentacleType(c->GetEntry());
            once = false;
            me->setFaction(14);
            SetImmuneToPushPullEffects(true);
        }

        InstanceScript* m_pInstance;
        TentacleType t_Type;
        bool once;
        uint32 uiTentacleSpell_Timer;

        void SetTentacleType(uint32 entry)
        {
            switch(entry)
            {
            case ENTRY_CRUSHER_TENTACLE : t_Type = CRUSHER_TENTACLE; break;
            case ENTRY_CORRUPTOR_TENTACLE : t_Type = CORRUPTOR_TENTACLE; break;
            case ENTRY_CONSTRICTOR_TENTACLE : t_Type = CONSTRICTOR_TENTACLE; break;
            default: t_Type = CORRUPTOR_TENTACLE; break;
            }
        }

        void MoveInLineOfSight(Unit* target)
        {
            if(target && me->GetDistance2d(target) <= me->GetMeleeReach() && target->ToPlayer() && !target->ToPlayer()->isGameMaster())
                AttackStartNoMove(target);
        }

        void AttackStart(Unit* /*target*/) {}

        Unit* SelectPlayerTargetInRange(float range)
        {
            Player *target = NULL;
            Trinity::AnyPlayerInObjectRangeCheck u_check(me, range, true);
            Trinity::PlayerSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, target, u_check);
            me->VisitNearbyObject(range, searcher);
            return target;
        }

        void Reset()
        {
            if(Unit* target = SelectPlayerTargetInRange(500.0f))
                AttackStartNoMove(target);
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoZoneInCombat();

            uiTentacleSpell_Timer = urand(10000,15000);
            switch(t_Type)
            {
            case CRUSHER_TENTACLE:
                DoCast(me,SPELL_CRUSH,true);
                DoCast(SPELL_FOCUS_ANGER);
                break;
            case CONSTRICTOR_TENTACLE:
                uiTentacleSpell_Timer = urand(20000,30000);
                break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if(m_pInstance && m_pInstance->GetBossState(TYPE_YOGGSARON) != IN_PROGRESS)
            {
                me->DealDamage(me,me->GetMaxHealth());
                me->RemoveCorpse();
            }

            if(!once)
            {
                DoCast(SPELL_ERUPT);
                once = true;
            }

            if (!UpdateVictim())
                return;

            if(uiTentacleSpell_Timer <= diff)
            {
                switch(t_Type)
                {
                case CRUSHER_TENTACLE:
                    if(!me->HasAura(SPELL_DIMISH_POWER))
                        DoCast(SPELL_DIMISH_POWER);
                    break;
                case CORRUPTOR_TENTACLE:
                    if(Unit* target = SelectPlayerTargetInRange(500.0f))
                        DoCast(target,RAND(SPELL_DRAINING_POISON,SPELL_BLACK_PLAGUE,SPELL_APATHY,SPELL_CURSE_OF_DOOM),false);
                    break;
                case CONSTRICTOR_TENTACLE:
                    //if(Unit* target = SelectPlayerTargetInRange(50.0f))
                    //    DoCast(target,SPELL_SQUEEZE,true);
                    break;
                }
                uiTentacleSpell_Timer = urand(5000,7000);
            }else uiTentacleSpell_Timer -= diff;

            if(t_Type == CRUSHER_TENTACLE)
                DoMeleeAttackIfReady();
        }
    };
};

class npc_descend_into_madness : public CreatureScript
{
public:
    npc_descend_into_madness() : CreatureScript("npc_descend_into_madness") { }

    bool OnGossipHello(Player* pPlayer,Creature* pCreature)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        bool AcceptTeleport = false;
        Position posTeleportPosition;
        //pPlayer->NearTeleportTo();
        BrainEventPhase pTemp;
        if(pCreature && pCreature->AI())
            pTemp = CAST_AI(npc_descend_into_madnessAI,pCreature->AI())->bPhase;

        switch(pTemp)
        {
        case PORTAL_PHASE_KING_LLIANE:
        case PORTAL_PHASE_DRAGON_SOUL:
        case PORTAL_PHASE_LICH_KING:
            AcceptTeleport = true;
            posTeleportPosition = InnerBrainLocation[pTemp];
            break;
        default: AcceptTeleport = false; break;
        }

        if(AcceptTeleport)
        {
            if(pPlayer)
            {
                pPlayer->NearTeleportTo(posTeleportPosition.m_positionX,posTeleportPosition.m_positionY,posTeleportPosition.m_positionZ,posTeleportPosition.m_orientation,true);
                //pPlayer->CastSpell(pPlayer,SPELL_TELEPORT,true);
            }
            CAST_AI(npc_descend_into_madnessAI,pCreature->AI())->bPhase = PORTAL_PHASE_BRAIN_NONE;
            AcceptTeleport = false;
        }

        return true;
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_descend_into_madnessAI (pCreature);
    }

    struct npc_descend_into_madnessAI : public Scripted_NoMovementAI
    {
        npc_descend_into_madnessAI(Creature *c) : Scripted_NoMovementAI(c)
        {
            SetImmuneToPushPullEffects(true);
        }

        BrainEventPhase bPhase;

        void DoAction(const int32 action)
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            switch(action)
            {
                case ACTION_PORTAL_TO_MADNESS_STORMWIND:
                    bPhase = PORTAL_PHASE_KING_LLIANE;
                    break;
                case ACTION_PORTAL_TO_MADNESS_DRAGON:
                    bPhase = PORTAL_PHASE_DRAGON_SOUL;
                    break;
                case ACTION_PORTAL_TO_MADNESS_LICHKING:
                    bPhase = PORTAL_PHASE_LICH_KING;
                    break;
            }
        }

        void Reset()
        {
            bPhase = PORTAL_PHASE_BRAIN_NONE;
        }

        void UpdateAI(const uint32 diff) {}
    };
};


class npc_brain_of_yogg_saron : public CreatureScript
{
public:
    npc_brain_of_yogg_saron() : CreatureScript("npc_brain_of_yogg_saron") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_brain_of_yogg_saronAI (pCreature);
    }

    struct npc_brain_of_yogg_saronAI : public Scripted_NoMovementAI
    {
        npc_brain_of_yogg_saronAI(Creature *c) : Scripted_NoMovementAI(c)
        {
            m_pInstance = c->GetInstanceScript();
            me->SetReactState(REACT_PASSIVE);
            me->setFaction(14);
            me->SetFlying(true);
            SetImmuneToPushPullEffects(true);
        }

        InstanceScript* m_pInstance;

        void UpdateAI(const uint32 diff)
        {
            if(HealthBelowPct(30))
                if(Creature* cSara = me->GetCreature(*me,m_pInstance->GetData64(TYPE_SARA)))
                        cSara->AI()->DoAction(ACTION_BRAIN_UNDER_30_PERCENT);
        }
    };
};

class boss_yogg_saron : public CreatureScript
{
public:
    boss_yogg_saron() : CreatureScript("boss_yogg_saron") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_yogg_saronAI (pCreature);
    }

    struct boss_yogg_saronAI : public Scripted_NoMovementAI
    {
        boss_yogg_saronAI(Creature *c) : Scripted_NoMovementAI(c)
        {
            m_pInstance = c->GetInstanceScript();
            me->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* m_pInstance;
        uint32 uiSanityCheck_Timer;

        void Reset()
        {
            uiSanityCheck_Timer = 1000;
        }

        void Update(const uint32 diff)
        {
            if(m_pInstance && m_pInstance->GetBossState(TYPE_YOGGSARON) != IN_PROGRESS)
                return;

            if(uiSanityCheck_Timer <= diff)
            {
                if(me->GetMap() && me->GetMap()->IsDungeon())
                {
                    Map::PlayerList const& players = me->GetMap()->GetPlayers();
                    if (!players.isEmpty())
                        for(Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                            if (Player* plr = itr->getSource())
                                if(plr->isAlive() && !plr->isGameMaster())
                                    if(!plr->HasAura(SPELL_SANITY) && !plr->HasAura(SPELL_INSANE))
                                    {
                                        DoCast(plr,SPELL_INSANE,true);
                                        DoScriptText(RAND(WHISP_INSANITY_1,WHISP_INSANITY_2),me,plr);
                                    }
                }

                uiSanityCheck_Timer = 1000;
            }else uiSanityCheck_Timer -= diff;
        }
    };
};

class npc_influence_tentacle : public CreatureScript
{
public:
    npc_influence_tentacle() : CreatureScript("npc_influence_tentacle") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_influence_tentacleAI (pCreature);
    }

    struct npc_influence_tentacleAI : public Scripted_NoMovementAI
    {
        npc_influence_tentacleAI(Creature *c) : Scripted_NoMovementAI(c)
        {
            me->SetReactState(REACT_DEFENSIVE);
        }

        void EnterCombat(Unit* attacker)
        {
            me->UpdateEntry(ENTRY_INFULENCE_TENTACLE);
            DoCast(SPELL_GRIM_REPRISAL);
        }
    };
};

class npc_immortal_guardian : public CreatureScript
{
public:
    npc_immortal_guardian() : CreatureScript("npc_immortal_guardian") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_immortal_guardianAI (pCreature);
    }

    struct npc_immortal_guardianAI : public ScriptedAI
    {
        npc_immortal_guardianAI(Creature *c) : ScriptedAI(c)
        {
            m_pInstance = c->GetInstanceScript();
            me->setFaction(14);
            SetImmuneToPushPullEffects(true);
        }

        InstanceScript* m_pInstance;

        uint32 uiDrainLife_Timer;

        Unit* SelectPlayerTargetInRange(float range)
        {
            Player *target = NULL;
            Trinity::AnyPlayerInObjectRangeCheck u_check(me, range, true);
            Trinity::PlayerSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, target, u_check);
            me->VisitNearbyObject(range, searcher);
            return target;
        }

        void Reset()
        {
            if(Unit* target = SelectPlayerTargetInRange(100.0f))
                me->AI()->AttackStart(target);

            uint32 uiDrainLife_Timer = 10000;
        }

        void SpellHit(Unit* caster, const SpellEntry* spell)
        {
            if(spell->Id == 64172) // Titanic Storm
            {
                if(me->HasAura(SPELL_WEAKENED))
                    me->DealDamage(me,me->GetHealth());
            }
        }

        void DamageTaken(Unit* dealer, uint32 &damage)
        {
            if(dealer->GetGUID() == me->GetGUID())
                return;

            if(HealthBelowPct(1))
                damage = 0;

            if(me->GetHealth() < damage)
                damage = 0;
        }

        void Update(const uint32 diff)
        {
            if(m_pInstance && m_pInstance->GetBossState(TYPE_YOGGSARON) != IN_PROGRESS)
            {
                me->DealDamage(me,me->GetMaxHealth());
                me->RemoveCorpse();
            }

            if(me->HasAura(SPELL_EMPOWERED))
            {
                int8 stacks = int8(uint32(me->GetHealthPct()) / 10);
                if(stacks > 9) stacks = 9;

                if(stacks > 0)
                {
                    me->RemoveAurasDueToSpell(SPELL_WEAKENED);
                    me->SetAuraStack(SPELL_EMPOWERED,me,stacks);
                }else
                {
                    me->RemoveAurasDueToSpell(SPELL_EMPOWERED);
                    me->AddAura(SPELL_WEAKENED,me);
                }
            }else me->AddAura(SPELL_EMPOWERED,me);

            if(m_pInstance->GetBossState(TYPE_YOGGSARON) != IN_PROGRESS)
                return;

            if (!UpdateVictim())
                return;

            if(uiDrainLife_Timer < diff)
            {
                DoCast(me->getVictim(),RAID_MODE(SPELL_DRAIN_LIFE_10,SPELL_DRAIN_LIFE_25));
                uiDrainLife_Timer = 10000 + (rand()%20000);
            }else uiDrainLife_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_support_keeper : public CreatureScript
{
public:
    npc_support_keeper() : CreatureScript("npc_support_keeper") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_support_keeperAI (pCreature);
    }

    struct npc_support_keeperAI : public Scripted_NoMovementAI
    {
        npc_support_keeperAI(Creature *c) : Scripted_NoMovementAI(c)
        {
            m_pInstance = c->GetInstanceScript();
        }

        InstanceScript* m_pInstance;
        
        void AttackStart(Unit *attacker)
        {
        }

        void Reset()
        {
            uint32 auraspell = 0;
            switch(me->GetEntry())
            {
            case ENTRY_KEEPER_HODIR:
                auraspell = SPELL_FORTITUDE_OF_FROST;
                break;
            case ENTRY_KEEPER_FREYA:
                auraspell = SPELL_RESILIENCE_OF_NATURE;
                break;
            case ENTRY_KEEPER_THORIM:
                auraspell = SPELL_FURY_OF_THE_STORM;
                break;
            case ENTRY_KEEPER_MIMIRON:
                auraspell = SPELL_SPEED_OF_INVENTION;
                break;
            }
            DoCast(auraspell);
        }

        void Update(const uint32 diff)
        {
            switch(me->GetEntry())
            {
            case ENTRY_KEEPER_THORIM:
                if(!me->HasAura(SPELL_TITANIC_STORM))
                    DoCast(SPELL_TITANIC_STORM);
                break;
            }
        }
    };
};

class go_flee_to_surface : public GameObjectScript
{
public:
    go_flee_to_surface() : GameObjectScript("go_flee_to_surface") { }

    bool OnGossipHello(Player *pPlayer, GameObject * /*pGO*/)
    {
        pPlayer->NearTeleportTo(SaraLocation.GetPositionX(),SaraLocation.GetPositionY(),SaraLocation.GetPositionZ(),M_PI,false);
        pPlayer->JumpTo(30.0f,5.0f,true);
        return false;
    }
};
/*
UPDATE creature_template SET scriptname = 'boss_sara' WHERE entry = 33134;
UPDATE script_texts SET npc_entry = 33134 WHERE npc_entry = 33288 AND entry IN (-1603330,-1603331,-1603332,-1603333);
UPDATE script_texts SET content_default = "Help me! Please get them off me!" WHERE npc_entry = 33134 AND entry = -1603310;
UPDATE script_texts SET content_default = "What do you want from me? Leave me alone!" WHERE npc_entry = 33134 AND entry = -1603311;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` = 33134;
UPDATE creature_template SET scriptname = 'npc_ominous_cloud' WHERE entry = 33292;
UPDATE creature_template SET scriptname = 'npc_guardian_of_yogg_saron' WHERE entry = 33136;
UPDATE creature_template SET scriptname = 'npc_yogg_saron_tentacle' WHERE entry in (33966,33985,33983);
UPDATE creature_template SET scriptname = 'npc_descend_into_madness' WHERE entry = 34072;
UPDATE creature_template SET scriptname = 'npc_brain_of_yogg_saron' WHERE entry = 33890;
UPDATE creature_template SET scriptname = 'boss_yogg_saron' WHERE entry = 33288;
UPDATE creature_template SET scriptname = 'npc_influence_tentacle' WHERE entry in (33716,33720,33719,33717,33433,33567);
UPDATE creature_template SET scriptname = 'npc_immortal_guardian' WHERE entry = 33988;
UPDATE creature_template SET scriptname = 'npc_support_keeper' WHERE entry in (33410,33411,33412,33413);
UPDATE gameobject_template SET scriptname = 'go_flee_to_surface' WHERE entry = 194625;

UPDATE creature_template SET RegenHealth = 0 WHERE entry IN (33134,34332,33890,33954);

DELETE FROM gameobject WHERE id = 194625;
INSERT INTO gameobject 
(guid, id, map, spawnMask, phaseMask, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state)
VALUES 
(603001, 194625, 603, 3, 1, 2001.40, -59.66, 245.07, 0, 0, 0, 0, 0, 60, 100, 1),
(603002, 194625, 603, 3, 1, 1941.61, -25.88, 244.98, 0, 0, 0, 0, 0, 60, 100, 1),
(603003, 194625, 603, 3, 1, 2001.18,  9.409, 245.24, 0, 0, 0, 0, 0, 60, 100, 1);
*/

void AddSC_boss_yoggsaron()
{
    new boss_sara();
    new npc_ominous_cloud();
    new npc_guardian_of_yogg_saron();
    new npc_yogg_saron_tentacle();
    new npc_descend_into_madness();
    new npc_influence_tentacle();
    new npc_brain_of_yogg_saron();
    new boss_yogg_saron();
    new npc_immortal_guardian();
    new npc_support_keeper();
    new go_flee_to_surface();
}