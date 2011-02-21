-- Speed walk-run
UPDATE `creature_template` SET `speed_walk`=0, `speed_run`=0 WHERE `entry`=28366;

-- Spell Fire Cannon
UPDATE `creature_template` SET `spell1`=51421 WHERE `entry`=28366;

-- Rank
UPDATE `creature_template` SET `rank`=1 WHERE `entry`=28366;
