-- Trail of the champions
-- Faction of Argent Warhorse and Argent Battleworg
UPDATE `creature_template` SET `faction_H`=16 WHERE `entry`=35644;
UPDATE `creature_template` SET `faction_A`=16 WHERE `entry`=36558;
-- Unit flags Battleworg
UPDATE `creature_template` SET `unit_flags`=256 WHERE `entry`=36558;
-- Spells for Battleworg
UPDATE `creature_template` SET `spell1`=68505, `spell2`=62575, `spell3`=68282, `spell4`=66482 WHERE `entry`=36558;
-- Vehicleid of Warhorse
UPDATE `creature_template` SET `VehicleId`=486 WHERE `entry`=35644;
-- Speeds
UPDATE `creature_template` SET `speed_run`=2 WHERE `entry` IN (36558, 35644);
-- Attacktime
UPDATE `creature_template` SET `baseattacktime`=0 WHERE `entry` IN (36558, 35644);
-- Vehicle template accessory for minions
DELETE FROM `vehicle_template_accessory` WHERE `entry` IN (33321, 33323, 33320, 33322, 33316, 33317, 33324, 33217, 33318, 33319);
INSERT INTO `vehicle_template_accessory` (`entry`,`accessory_entry`,`seat_id`,`minion`,`description`) VALUES
(33321,35323,0,1, 'Darkspear Raptor'),
(33323,35326,0,1, 'Silvermoon Hawkstrider'),
(33320,35314,0,1, 'Orgrimmar Wolf'),
(33322,35325,0,1, 'Thunder Bluff Kodo'),
(33316,35329,0,1, 'Ironforge Ram'),
(33317,35331,0,1, 'Gnomeregan Mechanostrider'),
(33324,35327,0,1, 'Forsaken Warhorse'),
(33217,35328,0,1, 'Stormwind Steed'),
(33318,35330,0,1, 'Exodar Elekk'),
(33319,35332,0,1, 'Darnassian Nightsaber');
-- Equipements ids 
UPDATE `creature_template` SET `equipment_id`=2049 WHERE `entry` in (35314,35326,35327,35325,35323,35331,35330,35329,35328,35332);
UPDATE `creature_template` SET `equipment_id`=2025 WHERE `entry` in (35571,36090);
UPDATE `creature_template` SET `equipment_id`=2021 WHERE `entry` in (35569,36085);
UPDATE `creature_template` SET `equipment_id`=2018 WHERE `entry` in (35572,36089);
UPDATE `creature_template` SET `equipment_id`=2020 WHERE `entry` in (35617,36084);
UPDATE `creature_template` SET `equipment_id`=2019 WHERE `entry` in (35570,36091);
UPDATE `creature_template` SET `equipment_id`=2096 WHERE `entry` in (34701,36803);
UPDATE `creature_template` SET `equipment_id`=2093 WHERE `entry` in (34703,36087);
UPDATE `creature_template` SET `equipment_id`=2095 WHERE `entry` in (34657,36086);
UPDATE `creature_template` SET `equipment_id`=2092 WHERE `entry` in (34705,36088);
UPDATE `creature_template` SET `equipment_id`=834 WHERE `entry` in (35119,35518);
UPDATE `creature_template` SET `equipment_id`=235 WHERE `entry` in (34928,35517);
UPDATE `creature_template` SET `equipment_id`=0 WHERE `entry` in (35451,35490);