-- Faction of vehicles
UPDATE `creature_template` SET 
`Faction_A`=16,
`Faction_H`=16
WHERE `entry` IN (33324, 33321, 33322, 33320, 33323, 33319, 33318, 33317, 33316, 33324);

-- Scriptname of all Memories of boss "Argent Confessor Paletress"
UPDATE `creature_template` SET `scriptname`='npc_memory' WHERE `name` LIKE 'Memory of %';

-- Vehicle for black knight
DELETE FROM `vehicle_template_accessory` WHERE `entry` = 35491;
INSERT INTO `vehicle_template_accessory` (`entry`,`accessory_entry`,`seat_id`,`minion`,`description`) VALUES
(35491,35451,0,0, 'Trial of the Champion - Black Knight on his gryphon');