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
-- Structure de la table `account`
--

CREATE TABLE IF NOT EXISTS `account` (
  `account_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(40) COLLATE utf8_unicode_ci NOT NULL,
  `pseudo` varchar(40) COLLATE utf8_unicode_ci NOT NULL,
  `hash_password` varchar(45) COLLATE utf8_unicode_ci NOT NULL,
  `session_key` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
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
-- Structure de la table `world_list`
--

CREATE TABLE IF NOT EXISTS `world_list` (
  `world_id` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `language` varchar(2) COLLATE utf8_unicode_ci NOT NULL,
  `population` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `status` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `security_access_level` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`world_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=2 ;

--
-- Contenu de la table `world_list`
--

INSERT INTO `world_list` (`world_id`, `name`, `language`, `population`, `status`, `security_access_level`) VALUES
(1, 'Wakbox', 'fr', 0, 1, 0);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
