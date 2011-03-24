/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Boss_Moira_Bronzbeard
SD%Complete: 100
SDCategory: Blackrock Depths
EndScriptData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

enum Spells
{
    SPELL_HEAL                                             = 10917,
    SPELL_RENEW                                            = 10929,
    SPELL_SHIELD                                           = 10901,
    SPELL_MINDBLAST                                        = 10947,
    SPELL_SHADOWWORDPAIN                                   = 10894,
    SPELL_SMITE                                            = 15537,

	FACTION_ALLFRIENDLY									   = 35,
};


const Position SpawnPoint[1] = { 1384.64f, -831.486f, -87.5893f};


class boss_moira_bronzebeard : public CreatureScript
{
public:
    boss_moira_bronzebeard() : CreatureScript("boss_moira_bronzebeard") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_moira_bronzebeardAI (pCreature);
    }

    struct boss_moira_bronzebeardAI : public ScriptedAI
    {
        boss_moira_bronzebeardAI(Creature *c) : ScriptedAI(c) {}

        uint32 Heal_Timer;
        uint32 MindBlast_Timer;
        uint32 ShadowWordPain_Timer;
        uint32 Smite_Timer;
		uint32 Renew_Timer;
		uint32 Shield_Timer;
		uint64 m_uiTargetGUID;
		uint32 Faction_Timer;

        void Reset()
        {
            Heal_Timer = 12000;                                 //These times are probably wrong
            MindBlast_Timer = 16000;
            ShadowWordPain_Timer = 2000;
            Smite_Timer = 8000;
			Renew_Timer = 19000;
			Shield_Timer = 21000;
			m_uiTargetGUID = 0;
			Faction_Timer = 180000;
        }


		void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
        {
           m_uiTargetGUID = pDoneBy->GetGUID();
        }

        void EnterCombat(Unit * /*who*/)
        {
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
      //      if (!UpdateVictim())
      //          return;

			if(!me->getVictim())
			{
				if(me->getFaction() == FACTION_ALLFRIENDLY)
				{
					if(Faction_Timer <= diff)
					{
					me->setFaction(54);
					me->Respawn();
					me->SetPosition(1384.64f, -831.486f, -87.5893f, 1,623);
					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					Faction_Timer = 180000;
					
					}else Faction_Timer -= diff;
				}
			}
					
		

		if(me->getVictim())
		{

            //MindBlast_Timer
            if (MindBlast_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_MINDBLAST);
                MindBlast_Timer = 14000;
            } else MindBlast_Timer -= diff;

            //ShadowWordPain_Timer
            if (ShadowWordPain_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHADOWWORDPAIN);
                ShadowWordPain_Timer = 18000;
            } else ShadowWordPain_Timer -= diff;

            //Smite_Timer
            if (Smite_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SMITE);
                Smite_Timer = 10000;
            } else Smite_Timer -= diff;

			if(Heal_Timer <= diff)
			{
				Unit* pTarget = DoSelectLowestHpFriendly(40);
				me->CastSpell(pTarget, SPELL_HEAL, 1);
				Heal_Timer = 12000;
			} else Heal_Timer -= diff;

			if(Renew_Timer <= diff)
			{
				std::list<Creature*> itrTarget = DoFindFriendlyMissingBuff(40, SPELL_RENEW);
				Unit* target = itrTarget.front();
				me->CastSpell(target, SPELL_RENEW, 0);
				Renew_Timer = 19000;
			} else Renew_Timer -= diff;

			if(Shield_Timer <= diff)
			{
				std::list<Creature*> itrTarget = DoFindFriendlyMissingBuff(40, SPELL_SHIELD);
				Unit* target = itrTarget.front();
				me->CastSpell(target, SPELL_SHIELD, 0);
				Shield_Timer = 21000;
			} else Shield_Timer -= diff;


			if (me->HealthBelowPct(25))
            {
			   	if(Player* target = Unit::GetPlayer(*me, m_uiTargetGUID))
				{
					me->setFaction(FACTION_ALLFRIENDLY);

					target->CombatStop();
					me->CombatStop();

					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

					me->Respawn();
					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
					Faction_Timer = 180000;
				}
		   }
		}
        }
    };

};

void AddSC_boss_moira_bronzebeard()
{
    new boss_moira_bronzebeard();
}
