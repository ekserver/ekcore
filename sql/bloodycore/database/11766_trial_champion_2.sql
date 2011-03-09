-- Scriptname, hp, damage, level
UPDATE `creature_template` SET 
`ScriptName`='generic_vehicleAI_toc5',
`minlevel`='80', 
`maxlevel`='80', 
`rank`='1',
`mindmg`='420', 
`maxdmg`='630', 
`attackpower`='157', 
`Health_mod`='5,95238' WHERE `entry` IN (33324, 33321, 33322, 33320, 33323, 33319, 33318, 33317, 33316, 33324);

-- Hp, damage and level.. 
UPDATE `creature_template` SET 
`unit_flags`=0 , 
`minlevel`='80', 
`maxlevel`='80', 
`mindmg`='420', 
`rank`='1',
`maxdmg`='630', 
`attackpower`='157', 
`Health_mod`='15' WHERE `entry` IN (35635, 35640, 35634, 35638, 35641, 34658, 35633, 35768, 35636, 35637);

-- Npcs on vehicle should be passive and untargettable 
-- (not blizzlike, but only way to make the event works. On offy players must kill the champions not the vehicles..)
UPDATE `creature_template` SET 
`AIName`='PassiveAI',
`unit_flags`=33554434 
WHERE `entry` IN (SELECT `accessory_entry` FROM `vehicle_template_accessory` WHERE `entry` IN (33324, 33321, 33322, 33320, 33323, 33319, 33318, 33317, 33316, 33324));

-- scale of mokra mount
UPDATE `creature_template` SET `scale`=1.5 WHERE `entry`=35638;