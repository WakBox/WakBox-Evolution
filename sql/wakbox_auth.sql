-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le: Lun 30 Décembre 2013 à 11:08
-- Version du serveur: 5.5.24-log
-- Version de PHP: 5.4.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `wakbox_auth`
--

-- --------------------------------------------------------

--
-- Structure de la table `accounts`
--

CREATE TABLE IF NOT EXISTS `accounts` (
  `account_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(40) COLLATE utf8_unicode_ci NOT NULL,
  `pseudo` varchar(40) COLLATE utf8_unicode_ci NOT NULL,
  `hash_password` varchar(45) COLLATE utf8_unicode_ci NOT NULL,
  `session_token` varchar(45) COLLATE utf8_unicode_ci NOT NULL,
  `email` varchar(45) COLLATE utf8_unicode_ci NOT NULL,
  `gm_level` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `join_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `last_login` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `last_ip` varchar(15) COLLATE utf8_unicode_ci NOT NULL DEFAULT '127.0.0.1',
  `online` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `banned` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `subscription_time` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`account_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci ;

-- --------------------------------------------------------

--
-- Table structure for table `ip_banned`
--

CREATE TABLE IF NOT EXISTS `ip_banned` (
  `ip` varchar(15) COLLATE utf8_unicode_ci NOT NULL,
  `ban_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `ban_reason` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `banned_by` varchar(40) COLLATE utf8_unicode_ci NOT NULL,
  `unban_date` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`ip`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- --------------------------------------------------------

--
-- Structure de la table `realms`
--

CREATE TABLE IF NOT EXISTS `realms` (
  `realm_id` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `address` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '127.0.0.1',
  `port` smallint(5) unsigned NOT NULL DEFAULT '5556',
  `version` varchar(10) COLLATE utf8_unicode_ci NOT NULL DEFAULT '1.39.6',
  `community` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `player_count` int(10) unsigned NOT NULL DEFAULT '0',
  `player_limit` int(10) unsigned NOT NULL DEFAULT '500',
  `security_access_level` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `locked` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`realm_id`),
  UNIQUE KEY `idx_name` (`name`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci ;

--
-- Contenu de la table `realms`
--

INSERT INTO `realms` (`realm_id`, `name`, `address`, `port`, `version`, `community`, `player_count`, `player_limit`, `security_access_level`, `locked`) VALUES
(1, 'WakBox', '127.0.0.1', 5556, '1.39.6', 0, 0, 500, 0, 0);

--
-- Table structure for table `realm_characters`
--

CREATE TABLE IF NOT EXISTS `realm_characters` (
  `realm_id` int(10) unsigned NOT NULL DEFAULT '0',
  `account_id` int(10) unsigned NOT NULL,
  `num_characters` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`realm_id`,`account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
