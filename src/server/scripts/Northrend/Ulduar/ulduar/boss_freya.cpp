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

enum Yells
{
    SAY_AGGRO                                   = -1603180,
    SAY_AGGRO_WITH_ELDER                        = -1603181,
    SAY_SLAY_1                                  = -1603182,
    SAY_SLAY_2                                  = -1603183,
    SAY_DEATH                                   = -1603184,
    SAY_BERSERK                                 = -1603185,
    SAY_SUMMON_CONSERVATOR                      = -1603186,
    SAY_SUMMON_TRIO                             = -1603187,
    SAY_SUMMON_LASHERS                          = -1603188,
    SAY_YS_HELP                                 = -1603189,

    // Elder Brightleaf
    SAY_BRIGHTLEAF_AGGRO                        = -1603190,
    SAY_BRIGHTLEAF_SLAY_1                       = -1603191,
    SAY_BRIGHTLEAF_SLAY_2                       = -1603192,
    SAY_BRIGHTLEAF_DEATH                        = -1603193,

    // Elder Ironbranch
    SAY_IRONBRANCH_AGGRO                        = -1603194,
    SAY_IRONBRANCH_SLAY_1                       = -1603195,
    SAY_IRONBRANCH_SLAY_2                       = -1603196,
    SAY_IRONBRANCH_DEATH                        = -1603197,

    // Elder Stonebark
    SAY_STONEBARK_AGGRO                         = -1603198,
    SAY_STONEBARK_SLAY_1                        = -1603199,
    SAY_STONEBARK_SLAY_2                        = -1603200,
    SAY_STONEBARK_DEATH                         = -1603201,
};

enum Events
{
    // Con-speed-atory timed achievement.
    // TODO Should be started when 1st trash is killed.
    ACHIEV_CON_SPEED_ATORY_START_EVENT              = 21597,
    SPELL_ACHIEVEMENT_CHECK                         = 65074,

    // Lumberjacked timed achievement.
    // TODO should be started when 1st elder is killed.
    // Spell should be casted when 3rd elder is killed.
    ACHIEV_LUMBERJACKED                           = 21686,
    SPELL_LUMBERJACKED_ACHIEVEMENT_CHECK          = 65296,
};

enum Archievments
{
    ACHIEVMENT_CON_SPEED_ATORY_10                       = 2980,
    ACHIEVMENT_CON_SPEED_ATORY_25                       = 2981,

    ACHIEVMENT_GETTING_BACK_TO_NATURE_10                = 2982,
    ACHIEVMENT_GETTING_BACK_TO_NATURE_25                = 2983,

    ACHIEVMENT_KNOCK_ON_THE_WOOD_10                     = 3177, // Defeat Freya while leaving at least 1 Elder alive
    ACHIEVMENT_KNOCK_ON_THE_WOOD_25                     = 3185,
    ACHIEVMENT_KNOCK_KNOCK_ON_THE_WOOD_10               = 3178, // Defeat Freya while leaving at least 2 Elder alive
    ACHIEVMENT_KNOCK_KNOCK_ON_THE_WOOD_25               = 3186,
    ACHIEVMENT_KNOCK_KNOCK_KNOCK_ON_THE_WOOD_10         = 3179, // Defeat Freya while leaving at least 3 Elder alive
    ACHIEVMENT_KNOCK_KNOCK_KNOCK_ON_THE_WOOD_25         = 3187,

    ACHIEVMENT_LUMBERJACKED_10                          = 2979,
    ACHIEVMENT_LUMBERJACKED_25                          = 3118,
};

enum Spells
{
    // Freya
    SPELL_TOUCH_OF_EONAR                                = 62528,
    SPELL_TOUCH_OF_EONAR_H                              = 62892,
    SPELL_ATTUNED_TO_NATURE                             = 62519,
    SPELL_SUNBEAM                                       = 62623,
    SPELL_SUNBEAM_H                                     = 62872,

    SPELL_NATURE_BOMB_VISUAL                            = 64648, // Projectile Visual ... Dummy
    SPELL_NATURE_BOMB_SUMMON                            = 64606, // castet from player ... 

    SPELL_SUMMON_WAVE_10                                = 62688, // Trigger 62687 in Spell Effekt
    SPELL_SUMMON_WAVE_10_SUMMON                         = 62687,
    SPELL_SUMMON_WAVE_3                                 = 62686,
    SPELL_SUMMON_WAVE_1                                 = 62685,

    SPELL_LIFEBINDERS_GIFT_TRIGGER_MISSILE_1            = 62572, // works
    SPELL_LIFEBINDERS_GIFT_SUMMON_1                     = 62568,
    SPELL_LIFEBINDERS_GIFT_TRIGGER_MISSILE_2            = 62870, // works
    SPELL_LIFEBINDERS_GIFT_SUMMON_2                     = 62869,
    SPELL_LIFEBINDERS_GIFT_VISUAL                       = 62579,

    //Nature Bomb
    SPELL_NATURE_BOMB_VISUAL_OBJECT                     = 64600, // Gameobjectspawn 194902
    SPELL_NATURE_BOMB_EXPLOSION                         = 64587,
    SPELL_NATURE_BOMB_EXPLOSION_H                       = 64650,

    // Freya Adds
    SPELL_ATTUNED_TO_NATURE_REMOVE_2                    = 62524,
    SPELL_ATTUNED_TO_NATURE_REMOVE_10                   = 62525,
    SPELL_ATTUNED_TO_NATURE_REMOVE_25                   = 62521,
    // Eonar's Gift
    SPELL_LIFEBINDERS_GIFT_10                           = 62584,
    SPELL_LIFEBINDERS_GIFT_25                           = 64185,

    // Test

    SPELL_PHEROMONES                                    = 62619,


    // ???
    SUMMON_FREYA_CHEST                                  = 62950, // 62952-62958

    SPELL_SUMMON_HEALTHY_SPORE_NE                       = 62591,
    SPELL_SUMMON_HEALTHY_SPORE_SE                       = 62592,
    SPELL_SUMMON_HEALTHY_SPORE_SW                       = 62593,
    SPELL_SUMMON_HEALTHY_SPORE_NW                       = 62582,
};

enum Entrys
{
    ENTRY_GAMEOBJECT_NATURE_BOMB                        = 194902,
};

enum Phase
{
    PHASE_SPAWNING,
    PHASE_NOT_SPAWNING
};

const uint32 WaveSpells[3] = 
{
    SPELL_SUMMON_WAVE_10,
    SPELL_SUMMON_WAVE_3,
    SPELL_SUMMON_WAVE_1
};

class boss_freya : public CreatureScript
{
public:
    boss_freya() : CreatureScript("boss_freya") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_freyaAI(pCreature);
    }

    struct boss_freyaAI : public ScriptedAI
    {
        boss_freyaAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            instance = pCreature->GetInstanceScript();
            if(instance)
                EncounterFinished = (instance->GetData(TYPE_FREYA) == DONE);
        }

        InstanceScript* instance;
        bool EncounterFinished;

        uint32 SpawnWaves[3];
        uint32 WaveCount;

        uint32 uiWave_Timer;

        // Dont know yet if needet
        //Phase m_Phase;

        void Reset()
        {
            instance->SetData(TYPE_FREYA,NOT_STARTED);

            if(EncounterFinished)
            {
                me->setFaction(35);
            }else
            {
                //m_Phase = PHASE_SPAWNING;
                InitSpawnWaves();
                WaveCount = 0;
                uiWave_Timer = 60000;
            }
        }

        void KilledUnit(Unit * /*victim*/)
        {
            DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2), me);
        }

        void DamageTaken(Unit* attacker, uint32 &amount)
        {
            if(amount > me->GetHealth())
            {
                amount = 0;
                EncounterIsDone();
            }
        }

        void InitSpawnWaves()
        {
             memset(&SpawnWaves, 0, sizeof(SpawnWaves));
             uint32 i_rand = urand(0,2);
             switch(i_rand)
             {
             case 0:
                 SpawnWaves[0] = i_rand;
                 if(urand(0,1) == 0)
                 {
                     SpawnWaves[1] = 1;
                     SpawnWaves[2] = 2;
                 }else
                 {
                     SpawnWaves[1] = 2;
                     SpawnWaves[2] = 1;
                 }
                 break;
             case 1:
                 SpawnWaves[0] = i_rand;
                 if(urand(0,1) == 0)
                 {
                      SpawnWaves[1] = 0;
                      SpawnWaves[2] = 2;
                 }else
                 {
                      SpawnWaves[1] = 2;
                      SpawnWaves[2] = 0;
                 }
                 break;
             case 2:
                 SpawnWaves[0] = i_rand;
                 if(urand(0,1) == 0)
                 {
                      SpawnWaves[1] = 0;
                      SpawnWaves[2] = 1;
                 }else
                 {
                      SpawnWaves[1] = 1;
                      SpawnWaves[2] = 0;
                 }
                 break;
             }
        }

        void DoSummonWave()
        {
            uint32 spawntype = WaveCount > 3 ? WaveCount-3 : WaveCount;
            DoCast(WaveSpells[SpawnWaves[spawntype]]);
            WaveCount++;
        }

        void EncounterIsDone()
        {
            EncounterFinished = true;
            DoScriptText(SAY_DEATH, me);
            instance->SetData(TYPE_FREYA,DONE);
            me->AI()->EnterEvadeMode();
            // cast is not rewarding the achievement.
            // DoCast(SPELL_ACHIEVEMENT_CHECK);
            //instance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_ACHIEVEMENT_CHECK);
        }

        void SetAttunedToNatureAura()
        {
            DoCast(RAID_MODE(SPELL_TOUCH_OF_EONAR,SPELL_TOUCH_OF_EONAR_H));
            me->AddAura(SPELL_ATTUNED_TO_NATURE,me);
            me->SetAuraStack(SPELL_ATTUNED_TO_NATURE,me,150);
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            DoScriptText(SAY_AGGRO, me);

            SetAttunedToNatureAura();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if(WaveCount < 6)
                if(uiWave_Timer < diff)
                {
                    if(!me->IsNonMeleeSpellCasted(false))
                    {
                        DoSummonWave();
                        uiWave_Timer = 60000;
                    }
                }else uiWave_Timer -= diff;

            DoMeleeAttackIfReady();

            EnterEvadeIfOutOfCombatArea(diff);
        }
    };
};

class mob_natural_bomb : public CreatureScript
{
public:
    mob_natural_bomb() : CreatureScript("mob_natural_bomb") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_natural_bombAI(pCreature);
    }

    struct mob_natural_bombAI : public ScriptedAI
    {
        mob_natural_bombAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
        }

        uint32 uiExplosion_Timer;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->setFaction(14);
            DoCast(SPELL_NATURE_BOMB_VISUAL_OBJECT);
            uiExplosion_Timer = 10000;
        }

        void UpdateAI(const uint32 diff)
        {
            if(uiExplosion_Timer < diff)
            {
                if (GameObject *go_bomb = me->FindNearestGameObject(ENTRY_GAMEOBJECT_NATURE_BOMB, 20.0f))
                    go_bomb->Use(me);

                    DoCast(RAID_MODE(SPELL_NATURE_BOMB_EXPLOSION,SPELL_NATURE_BOMB_EXPLOSION_H));
                    me->DealDamage(me,me->GetHealth());
                    me->RemoveCorpse();
                uiExplosion_Timer = 10000;
            }else uiExplosion_Timer -= diff;
        }
    };
};

class spell_freya_natural_bomb_spell : public SpellScriptLoader
{
public:
    spell_freya_natural_bomb_spell() : SpellScriptLoader("spell_freya_natural_bomb_spell") { }

    class spell_freya_natural_bomb_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_freya_natural_bomb_SpellScript);

        void OnHitEffect()
        {
            if (Player* target = GetHitPlayer())
            {
                target->CastSpell(target,SPELL_NATURE_BOMB_SUMMON,true);
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_freya_natural_bomb_SpellScript::OnHitEffect);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_freya_natural_bomb_SpellScript();
    }
};

void AddSC_boss_freya()
{
    new boss_freya();
    new mob_natural_bomb();
    new spell_freya_natural_bomb_spell();
}
