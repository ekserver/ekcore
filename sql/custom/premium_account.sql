CREATE TABLE IF NOT EXISTS `account_premium` (
        `id` INT(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
        `start_time` TIMESTAMP NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'Absolute start date, the bonus will be granted' ,
        `end_time`  TIMESTAMP NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'Absolute end date, the bonus is expired' ,
        `kill_xp_rate`  INT(10) UNSIGNED NOT NULL DEFAULT 1 COMMENT 'Experience Multiplier' ,
        `quest_xp_rate`  INT(10) UNSIGNED NOT NULL DEFAULT 1 COMMENT 'Experience Multiplier' ,
        `explore_xp_rate`  INT(10) UNSIGNED NOT NULL DEFAULT 1 COMMENT 'Experience Multiplier' ,
        `rest_xp_rate` INT(10) UNSIGNED NOT NULL DEFAULT 1 COMMENT 'Experience Multiplier' ,
PRIMARY KEY  (`id`)
) ENGINE=INNODB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT COMMENT='Premium Accounts';
-- Copy all accounts into premium_account with default VALUES
INSERT IGNORE INTO `premium_account` (`id`) SELECT `id` FROM `account`;