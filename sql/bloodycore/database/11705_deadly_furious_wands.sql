DELETE FROM `npc_vendor` WHERE (`entry` = 33925 AND `item` IN (42519, 42502)) OR (`entry` = 33926 AND `item` IN (42503, 42514, 42520));
INSERT INTO `npc_vendor` VALUES
-- Deadly Wands
(33925, 0, 42519, 0, 0, 386),
(33925, 0, 42502, 0, 0, 386),
-- Furious Wands
(33926, 0, 42503, 0, 0, 2608),
(33926, 0, 42514, 0, 0, 2608),
(33926, 0, 42520, 0, 0, 2608);
