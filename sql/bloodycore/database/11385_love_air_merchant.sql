DELETE FROM `creature` WHERE `id`=37674;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(140003, 37674, 1, 1, 1, 0, 0, 9923.83, 2526.41, 1319.41, 2.7881, 300, 0, 0, 1716, 0, 0, 0, 0, 0, 0), -- Darnassus
(140004, 37674, 530, 1, 1, 0, 0, -4014.71, -11846.7, 0.0862441, 5.13571, 300, 0, 0, 1782, 0, 0, 0, 0, 0, 0), -- Exodar
(140005, 37674, 0, 1, 1, 0, 0, -8893.84, 578.827, 94.0528, 5.93303, 300, 0, 0, 2215, 0, 0, 0, 0, 0, 0), -- Stormwind
(140006, 37674, 530, 1, 1, 0, 0, 9577.39, -7145.34, 14.2517, 5.81642, 300, 0, 0, 1990, 0, 0, 0, 0, 0, 0), -- Silvermoon City
(140007, 37674, 1, 1, 1, 0, 0, -1274.59, 73.5246, 128.19, 0.921814, 300, 0, 0, 2215, 0, 0, 0, 0, 0, 0), -- Thunder bluff
(140008, 37674, 1, 1, 1, 0, 0, 1613.59, -4399.63, 11.0503, 2.95463, 300, 0, 0, 1585, 0, 0, 0, 0, 0, 0), -- Orgrimarr
(140009, 37674, 0, 1, 1, 0, 0, 1252.89, 327.783, -63.7358, 6.18282, 300, 0, 0, 1651, 0, 0, 0, 0, 0, 0), -- Undercity
(140010, 37674, 0, 1, 1, 0, 0, -4928.03, -985.31, 501.461, 1.81664, 300, 0, 0, 1848, 0, 0, 0, 0, 0, 0); -- Ironforge

DELETE FROM `game_event_creature` WHERE `guid`IN (140003, 140004, 140005, 140006, 140007, 140008, 140009, 140010);
INSERT INTO `game_event_creature` (`eventEntry`,`guid`) VALUES
(8, 140003),
(8, 140004),
(8, 140005),
(8, 140006),
(8, 140007),
(8, 140008),
(8, 140009),
(8, 140010);

