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
-- Base de données: `wakbox_char`
--

-- --------------------------------------------------------

--
-- Table structure for table `characters`
--

CREATE TABLE IF NOT EXISTS `characters` (
  `guid` int(10) unsigned NOT NULL,
  `account_id` int(10) unsigned NOT NULL,
  `name` varchar(15) COLLATE utf8_unicode_ci NOT NULL,
  `breed` tinyint(3) unsigned NOT NULL,
  `gender` tinyint(3) unsigned NOT NULL,
  `level` smallint(5) unsigned NOT NULL DEFAULT '1',
  `xp` smallint(5) unsigned NOT NULL,
  `skin_color` int(11) NOT NULL,
  `hair_color` int(11) NOT NULL,
  `pupil_color` int(11) NOT NULL,
  `skin_color_factor` int(10) unsigned NOT NULL,
  `hair_color_factor` int(10) unsigned NOT NULL,
  `cloth` int(11) NOT NULL,
  `face` int(11) NOT NULL,
  `title` int(11) NOT NULL,
  `position_x` int(11) NOT NULL DEFAULT '0',
  `position_y` int(11) NOT NULL DEFAULT '0',
  `position_z` mediumint(9) NOT NULL DEFAULT '0',
  `direction` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `instance_id` mediumint(8) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `characters`
--

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
