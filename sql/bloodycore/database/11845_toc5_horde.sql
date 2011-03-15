DELETE FROM `creature` WHERE `guid` = 230961; -- Despwan an_start
DELETE FROM `creature` WHERE `guid` = 200038; -- despwan announcer
INSERT INTO `creature` VALUES (200038, 35004, 650, 3, 1, 0, 0, 748.309, 619.488, 411.172, 4.71239, 120, 0, 0, 1, 0, 0, 0, 0, 0, 0); -- spawn announcer
-- Modify faction for mounts of players
UPDATE `creature_template` SET `faction_A`=84, `faction_H`=84 WHERE `entry`=35644;
UPDATE `creature_template` SET `faction_A`=83, `faction_H`=83 WHERE `entry`=36558;