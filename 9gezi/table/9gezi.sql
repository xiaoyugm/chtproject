-- MySQL dump 10.13  Distrib 5.1.39, for Win32 (ia32)
--
-- Host: localhost    Database: 9gezi
-- ------------------------------------------------------
-- Server version	5.1.39-community

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `9gezi_answers`
--

DROP TABLE IF EXISTS `9gezi_answers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_answers` (
  `qid` tinyint(3) unsigned NOT NULL,
  `answer` tinyint(4) NOT NULL,
  `tid` mediumint(8) unsigned NOT NULL,
  PRIMARY KEY (`qid`,`tid`) USING BTREE,
  KEY `fk_ans_que_id` (`qid`),
  KEY `fk_ans_test_id` (`tid`),
  CONSTRAINT `fk_ans_que_id` FOREIGN KEY (`qid`) REFERENCES `9gezi_questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_ans_test_id` FOREIGN KEY (`tid`) REFERENCES `9gezi_test` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_bodytype`
--

DROP TABLE IF EXISTS `9gezi_bodytype`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_bodytype` (
  `id` tinyint(4) NOT NULL AUTO_INCREMENT,
  `type_name` varchar(45) NOT NULL,
  `type_desc` varchar(1000) DEFAULT NULL,
  `stamina` varchar(200) DEFAULT NULL,
  `food` varchar(200) DEFAULT NULL,
  `pe` varchar(200) DEFAULT NULL,
  `medicine` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_diary`
--

DROP TABLE IF EXISTS `9gezi_diary`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_diary` (
  `diaryid` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,
  `uid` mediumint(8) unsigned NOT NULL,
  `dateline` int(10) unsigned NOT NULL,
  `message` mediumtext,
  `breakfast` tinyint(1) unsigned zerofill NOT NULL DEFAULT '0',
  `lunch` tinyint(1) unsigned zerofill NOT NULL DEFAULT '0',
  `supper` tinyint(1) unsigned zerofill NOT NULL DEFAULT '0',
  `friend` tinyint(1) unsigned NOT NULL,
  `password` varchar(45) DEFAULT NULL,
  `noreply` tinyint(1) unsigned NOT NULL,
  `picflag` tinyint(1) unsigned DEFAULT NULL,
  `pic` varchar(45) DEFAULT NULL,
  `sportlow` int(10) unsigned zerofill NOT NULL,
  `sportmid` int(10) unsigned zerofill NOT NULL,
  `sporthigh` int(10) unsigned zerofill NOT NULL,
  `drink` tinyint(1) unsigned zerofill NOT NULL,
  `bigfood` tinyint(1) unsigned zerofill NOT NULL,
  `snack` tinyint(1) unsigned zerofill NOT NULL,
  `night` tinyint(1) unsigned zerofill NOT NULL,
  `weight` int(10) unsigned DEFAULT NULL,
  `mchest` int(10) unsigned DEFAULT NULL,
  `mwaist` int(10) unsigned DEFAULT NULL,
  `mbuttock` int(10) unsigned DEFAULT NULL,
  `marm` int(10) unsigned DEFAULT NULL,
  `mleg` int(10) unsigned DEFAULT NULL,
  `mshank` int(10) unsigned DEFAULT NULL,
  `menses` tinyint(1) unsigned zerofill NOT NULL,
  `shit` varchar(45) DEFAULT NULL,
  `bedtime` varchar(45) DEFAULT NULL,
  `getuptime` varchar(45) DEFAULT NULL,
  `foodtime_1` varchar(45) NOT NULL,
  `foodtime_2` varchar(45) NOT NULL,
  `foodtime_3` varchar(45) NOT NULL,
  PRIMARY KEY (`diaryid`) USING BTREE,
  UNIQUE KEY `UK_9gezi_diary` (`uid`,`dateline`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_diary_rec`
--

DROP TABLE IF EXISTS `9gezi_diary_rec`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_diary_rec` (
  `did` mediumint(8) unsigned NOT NULL,
  `meal` varchar(45) NOT NULL,
  `rid` mediumint(8) unsigned NOT NULL,
  `quantity` mediumint(8) unsigned NOT NULL,
  PRIMARY KEY (`did`,`meal`,`rid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_disease`
--

DROP TABLE IF EXISTS `9gezi_disease`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_disease` (
  `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK_dis_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=86 DEFAULT CHARSET=gbk ROW_FORMAT=FIXED;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_effect`
--

DROP TABLE IF EXISTS `9gezi_effect`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_effect` (
  `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK_eff_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=gbk ROW_FORMAT=FIXED;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_favor`
--

DROP TABLE IF EXISTS `9gezi_favor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_favor` (
  `id` mediumint(8) unsigned NOT NULL,
  `type` varchar(45) NOT NULL,
  `uid` mediumint(8) unsigned NOT NULL,
  `taste` tinyint(1) unsigned DEFAULT NULL,
  `difficult` tinyint(1) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`,`uid`,`type`),
  KEY `FK_9gezi_favor_mem` (`uid`),
  CONSTRAINT `FK_9gezi_favor_mem` FOREIGN KEY (`uid`) REFERENCES `9geziucenter`.`uc_members` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_ingred`
--

DROP TABLE IF EXISTS `9gezi_ingred`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_ingred` (
  `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `alias` varchar(45) DEFAULT NULL,
  `mid` mediumint(8) unsigned DEFAULT NULL,
  `uid` mediumint(8) unsigned DEFAULT NULL,
  `dateline` int(10) unsigned NOT NULL,
  `replynum` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `viewnum` mediumint(8) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK_ing_name` (`name`),
  KEY `FK_9gezi_ing_mem` (`uid`),
  KEY `FK_9gezi_ing_mat` (`mid`),
  CONSTRAINT `FK_9gezi_ing_mat` FOREIGN KEY (`mid`) REFERENCES `9gezi_materials` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_9gezi_ing_mem` FOREIGN KEY (`uid`) REFERENCES `9geziucenter`.`uc_members` (`uid`) ON DELETE SET NULL ON UPDATE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=2387 DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_mat_bt`
--

DROP TABLE IF EXISTS `9gezi_mat_bt`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_mat_bt` (
  `mid` mediumint(8) unsigned NOT NULL,
  `bid` tinyint(4) NOT NULL,
  PRIMARY KEY (`mid`,`bid`),
  KEY `fk_mat_mat_id` (`mid`),
  KEY `fk_mat_bt_id` (`bid`),
  CONSTRAINT `fk_mat_bt_id` FOREIGN KEY (`bid`) REFERENCES `9gezi_bodytype` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_mat_mat_id` FOREIGN KEY (`mid`) REFERENCES `9gezi_materials` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_mat_dis`
--

DROP TABLE IF EXISTS `9gezi_mat_dis`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_mat_dis` (
  `mid` mediumint(8) unsigned NOT NULL,
  `did` mediumint(8) unsigned NOT NULL,
  `forbid` tinyint(4) DEFAULT NULL COMMENT '1 means good, 0 means forbid',
  PRIMARY KEY (`mid`,`did`),
  KEY `fk_matdis_mat_id` (`mid`),
  KEY `fk_matdis_dis_id` (`did`),
  CONSTRAINT `fk_matdis_dis_id` FOREIGN KEY (`did`) REFERENCES `9gezi_disease` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_matdis_mat_id` FOREIGN KEY (`mid`) REFERENCES `9gezi_materials` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_mat_eff`
--

DROP TABLE IF EXISTS `9gezi_mat_eff`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_mat_eff` (
  `m_id` mediumint(8) unsigned NOT NULL,
  `e_id` mediumint(8) unsigned NOT NULL,
  PRIMARY KEY (`m_id`,`e_id`),
  KEY `FK_9gezi_mat_eff_2` (`e_id`),
  CONSTRAINT `FK_9gezi_mat_eff_1` FOREIGN KEY (`m_id`) REFERENCES `9gezi_materials` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_9gezi_mat_eff_2` FOREIGN KEY (`e_id`) REFERENCES `9gezi_effect` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_mat_mat_forbid`
--

DROP TABLE IF EXISTS `9gezi_mat_mat_forbid`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_mat_mat_forbid` (
  `mid` mediumint(8) unsigned NOT NULL,
  `mid2` mediumint(8) unsigned NOT NULL,
  PRIMARY KEY (`mid`,`mid2`),
  KEY `fk_mmf_mat_id1` (`mid`),
  KEY `fk_mmf_mat_id2` (`mid2`),
  CONSTRAINT `fk_mmf_mat_id1` FOREIGN KEY (`mid`) REFERENCES `9gezi_materials` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_mmf_mat_id2` FOREIGN KEY (`mid2`) REFERENCES `9gezi_materials` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_mat_nut`
--

DROP TABLE IF EXISTS `9gezi_mat_nut`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_mat_nut` (
  `mid` mediumint(8) unsigned NOT NULL,
  `nid` mediumint(8) unsigned NOT NULL,
  `quantity` float NOT NULL,
  `unit` varchar(45) NOT NULL,
  PRIMARY KEY (`mid`,`nid`),
  KEY `FK_9gezi_mat_nut_2` (`nid`),
  CONSTRAINT `FK_9gezi_mat_nut_1` FOREIGN KEY (`mid`) REFERENCES `9gezi_materials` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_9gezi_mat_nut_2` FOREIGN KEY (`nid`) REFERENCES `9gezi_nutrition` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_materials`
--

DROP TABLE IF EXISTS `9gezi_materials`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_materials` (
  `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `taste` varchar(45) DEFAULT NULL,
  `belongs` varchar(45) DEFAULT NULL,
  `effect` varchar(500) DEFAULT NULL,
  `notice` varchar(500) DEFAULT NULL,
  `season` varchar(45) DEFAULT NULL,
  `forbidden` varchar(1000) DEFAULT NULL,
  `nutrition` varchar(1000) DEFAULT NULL,
  `uid` mediumint(8) unsigned NOT NULL,
  `aliases` varchar(45) DEFAULT NULL,
  `pic` varchar(120) DEFAULT NULL,
  `picflag` tinyint(1) DEFAULT NULL,
  `dateline` int(10) unsigned NOT NULL,
  `organ` varchar(45) DEFAULT NULL,
  `suit_person` varchar(200) DEFAULT NULL,
  `property` varchar(45) DEFAULT NULL,
  `replynum` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `viewnum` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `category` varchar(45) DEFAULT NULL,
  `description` text,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK_mat_name` (`name`),
  KEY `fk_mat_mem_id` (`uid`),
  CONSTRAINT `fk_mat_mem_id` FOREIGN KEY (`uid`) REFERENCES `9geziucenter`.`uc_members` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=725 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_mem_bt`
--

DROP TABLE IF EXISTS `9gezi_mem_bt`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_mem_bt` (
  `uid` mediumint(8) unsigned NOT NULL,
  `bodytype` tinyint(4) NOT NULL,
  `judgement` tinyint(4) NOT NULL,
  PRIMARY KEY (`uid`,`bodytype`),
  KEY `fk_mem_mem_id` (`uid`),
  KEY `fk_mem_bt_id` (`bodytype`),
  CONSTRAINT `fk_mem_bt_id` FOREIGN KEY (`bodytype`) REFERENCES `9gezi_bodytype` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_mem_mem_id` FOREIGN KEY (`uid`) REFERENCES `9geziucenter`.`uc_members` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_mem_dis`
--

DROP TABLE IF EXISTS `9gezi_mem_dis`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_mem_dis` (
  `uid` mediumint(8) unsigned NOT NULL,
  `did` mediumint(8) unsigned NOT NULL,
  PRIMARY KEY (`uid`,`did`),
  KEY `fk_dis_mem_id` (`uid`),
  KEY `fk_dis_dis_id` (`did`),
  CONSTRAINT `fk_dis_dis_id` FOREIGN KEY (`did`) REFERENCES `9gezi_disease` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_dis_mem_id` FOREIGN KEY (`uid`) REFERENCES `9geziucenter`.`uc_members` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_mem_relation`
--

DROP TABLE IF EXISTS `9gezi_mem_relation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_mem_relation` (
  `uid` mediumint(8) unsigned NOT NULL,
  `uid2` mediumint(8) unsigned NOT NULL,
  `relation` varchar(45) NOT NULL,
  PRIMARY KEY (`uid`,`uid2`),
  KEY `fk_rel_mem_id` (`uid`),
  KEY `fk_rel2_mem_id` (`uid2`),
  CONSTRAINT `fk_rel2_mem_id` FOREIGN KEY (`uid2`) REFERENCES `9geziucenter`.`uc_members` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_rel_mem_id` FOREIGN KEY (`uid`) REFERENCES `9geziucenter`.`uc_members` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_nutrition`
--

DROP TABLE IF EXISTS `9gezi_nutrition`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_nutrition` (
  `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK_nutrition_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_pic_video`
--

DROP TABLE IF EXISTS `9gezi_pic_video`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_pic_video` (
  `urlid` mediumint(8) unsigned NOT NULL,
  `category` varchar(45) NOT NULL,
  `id` mediumint(8) unsigned NOT NULL,
  `pic_vid_url` varchar(500) NOT NULL,
  `pic_or_vid` tinyint(4) NOT NULL,
  PRIMARY KEY (`urlid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_questions`
--

DROP TABLE IF EXISTS `9gezi_questions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_questions` (
  `id` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `question_text` varchar(200) NOT NULL,
  `type` tinyint(4) NOT NULL,
  `reverse` tinyint(1) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_quest_bt_id` (`type`),
  CONSTRAINT `FK_quest_bt_id` FOREIGN KEY (`type`) REFERENCES `9gezi_bodytype` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=68 DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_rec_bt`
--

DROP TABLE IF EXISTS `9gezi_rec_bt`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_rec_bt` (
  `rid` mediumint(8) unsigned NOT NULL,
  `bid` tinyint(4) NOT NULL,
  PRIMARY KEY (`rid`,`bid`),
  KEY `fk_rec_rec_id` (`rid`),
  KEY `fk_rec_bt_id` (`bid`),
  CONSTRAINT `fk_rec_bt_id` FOREIGN KEY (`bid`) REFERENCES `9gezi_bodytype` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_rec_rec_id` FOREIGN KEY (`rid`) REFERENCES `9gezi_recipe` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk ROW_FORMAT=FIXED;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_rec_comments`
--

DROP TABLE IF EXISTS `9gezi_rec_comments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_rec_comments` (
  `uid` mediumint(8) unsigned NOT NULL,
  `rid` mediumint(8) unsigned NOT NULL,
  `score` tinyint(4) DEFAULT NULL,
  `comment` text,
  `comment_date` date DEFAULT NULL,
  PRIMARY KEY (`uid`,`rid`),
  KEY `fk_com_mem_id` (`uid`),
  KEY `fk_com_rec_id` (`rid`),
  CONSTRAINT `fk_com_mem_id` FOREIGN KEY (`uid`) REFERENCES `9geziucenter`.`uc_members` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_com_rec_id` FOREIGN KEY (`rid`) REFERENCES `9gezi_recipe` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk ROW_FORMAT=FIXED;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_rec_dis`
--

DROP TABLE IF EXISTS `9gezi_rec_dis`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_rec_dis` (
  `rid` mediumint(8) unsigned NOT NULL,
  `did` mediumint(8) unsigned NOT NULL,
  `forbid` tinyint(4) DEFAULT NULL,
  PRIMARY KEY (`rid`,`did`),
  KEY `fk_recdis_rec_id` (`rid`),
  KEY `fk_recdis_dis_id` (`did`),
  CONSTRAINT `fk_recdis_dis_id` FOREIGN KEY (`did`) REFERENCES `9gezi_disease` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_recdis_rec_id` FOREIGN KEY (`rid`) REFERENCES `9gezi_recipe` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk ROW_FORMAT=FIXED;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_rec_eff`
--

DROP TABLE IF EXISTS `9gezi_rec_eff`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_rec_eff` (
  `rid` mediumint(8) unsigned NOT NULL,
  `eid` mediumint(8) unsigned NOT NULL,
  PRIMARY KEY (`rid`,`eid`),
  KEY `FK_9gezi_rec_eff_eff_id` (`eid`),
  CONSTRAINT `FK_9gezi_rec_eff_eff_id` FOREIGN KEY (`eid`) REFERENCES `9gezi_effect` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_9gezi_rec_eff_rec_id` FOREIGN KEY (`rid`) REFERENCES `9gezi_recipe` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk ROW_FORMAT=FIXED;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_rec_mat`
--

DROP TABLE IF EXISTS `9gezi_rec_mat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_rec_mat` (
  `rid` mediumint(8) unsigned NOT NULL,
  `mid` mediumint(8) unsigned NOT NULL,
  `quantity` float DEFAULT NULL,
  `unit` varchar(45) DEFAULT NULL,
  `order` tinyint(4) DEFAULT NULL,
  `main` tinyint(1) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`rid`,`mid`),
  KEY `fk_rm_rec_id` (`rid`),
  KEY `fk_rm_mat_id` (`mid`),
  CONSTRAINT `fk_rm_mat_id` FOREIGN KEY (`mid`) REFERENCES `9gezi_ingred` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_rm_rec_id` FOREIGN KEY (`rid`) REFERENCES `9gezi_recipe` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk ROW_FORMAT=FIXED;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_recipe`
--

DROP TABLE IF EXISTS `9gezi_recipe`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_recipe` (
  `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `category` varchar(45) NOT NULL,
  `materials` varchar(500) NOT NULL,
  `method` varchar(1000) NOT NULL,
  `usage` varchar(50) DEFAULT NULL,
  `effect` varchar(500) DEFAULT NULL,
  `uid` mediumint(8) unsigned DEFAULT NULL,
  `difficulty` tinyint(4) NOT NULL,
  `time_prep` varchar(45) DEFAULT NULL,
  `time_make` varchar(45) DEFAULT NULL,
  `dateline` int(10) unsigned NOT NULL,
  `season` varchar(45) DEFAULT NULL,
  `pic` varchar(120) DEFAULT NULL,
  `picflag` tinyint(1) unsigned DEFAULT NULL,
  `suit_person` varchar(200) DEFAULT NULL,
  `replynum` mediumint(8) NOT NULL DEFAULT '0',
  `viewnum` mediumint(8) NOT NULL DEFAULT '0',
  `tiaoliao` varchar(500) DEFAULT NULL,
  `way` varchar(8) DEFAULT NULL,
  `status` tinyint(1) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK_rec_name1` (`name`),
  KEY `fk_rec_mem_id1` (`uid`),
  CONSTRAINT `fk_rec_mem_id1` FOREIGN KEY (`uid`) REFERENCES `9geziucenter`.`uc_members` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6260 DEFAULT CHARSET=gbk ROW_FORMAT=FIXED;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_tag`
--

DROP TABLE IF EXISTS `9gezi_tag`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_tag` (
  `id` mediumint(8) unsigned NOT NULL,
  `uid` mediumint(8) unsigned NOT NULL,
  `type` varchar(45) NOT NULL,
  `tagname` varchar(45) NOT NULL,
  PRIMARY KEY (`id`,`uid`,`type`,`tagname`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `9gezi_test`
--

DROP TABLE IF EXISTS `9gezi_test`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `9gezi_test` (
  `uid` mediumint(8) unsigned NOT NULL,
  `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,
  `test_date` datetime NOT NULL,
  `result` varchar(200) DEFAULT NULL,
  `status` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `bt1` tinyint(1) unsigned DEFAULT NULL,
  `bt2` tinyint(1) unsigned DEFAULT NULL,
  `bt3` tinyint(1) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_test_mem_id` (`uid`),
  CONSTRAINT `fk_test_mem_id` FOREIGN KEY (`uid`) REFERENCES `9geziucenter`.`uc_members` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2852 DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-05-27 18:49:44
