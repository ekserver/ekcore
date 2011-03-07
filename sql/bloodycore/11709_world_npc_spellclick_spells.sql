-- Emerald Drake, Amber Drake, Ruby Drake Ride Vehicle Hardcoded
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (27692, 27756, 27755);
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`quest_start`,`quest_start_active`,`quest_end`,`cast_flags`,`aura_required`,`aura_forbidden`,`user_type`) VALUES
(27692,46598,0,0,0,1,0,0,0), 
(27756,46598,0,0,0,1,0,0,0),
(27755,46598,0,0,0,1,0,0,0);