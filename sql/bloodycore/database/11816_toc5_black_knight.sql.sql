-- Black Knight Gryphon
UPDATE `creature_template` SET 
`faction_A`=35, 
`faction_H`=35, 
`mindmg`=0, 
`maxdmg`=0, 
`attackpower`=0, 
`dmg_multiplier`=0, 
`baseattacktime`=0, 
`unit_flags`=33554432, 
`dynamicflags`=0, 
`minrangedmg`=0, 
`maxrangedmg`=0, 
`rangedattackpower`=0, 
`VehicleId`=486 WHERE `entry`=35491;

-- Boss immune mask
UPDATE `creature_template` SET `mechanic_immune_mask`=805257215 WHERE `entry` IN (35490,35451,35518,35517);

-- Spellids fix for mounts 
UPDATE `creature_template` SET `spell1`=62544, `spell3`=63010 WHERE `entry`IN(35644,36558);