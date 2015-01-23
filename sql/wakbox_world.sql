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
-- Table structure for table `creature_template`
--

CREATE TABLE IF NOT EXISTS `creature_template` (
  `id` int(10) unsigned NOT NULL,
  `name` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `level` smallint(5) unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `creature_template`
--

INSERT INTO `creature_template` (`id`, `name`, `level`) VALUES
(2644, 'Ti Wapin', 1);

-- --------------------------------------------------------

--
-- Table structure for table `interactive_elements`
--

CREATE TABLE IF NOT EXISTS `interactive_elements` (
  `interactive_element_id` int(10) unsigned NOT NULL,
  `script_name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`interactive_element_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `interactive_elements`
--

INSERT INTO `interactive_elements` (`interactive_element_id`, `script_name`) VALUES
(20114, 'InteractiveElement_Tutorial_FirstFight');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
