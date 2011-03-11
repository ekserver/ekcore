-- Revert PassiveAI for champions on mount
UPDATE `creature_template` SET 
`AIName`='',
WHERE `entry` IN (SELECT `accessory_entry` FROM `vehicle_template_accessory` WHERE `entry` IN (33324, 33321, 33322, 33320, 33323, 33319, 33318, 33317, 33316, 33324));