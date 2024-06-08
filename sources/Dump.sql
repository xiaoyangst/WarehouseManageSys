CREATE DATABASE  IF NOT EXISTS `warehouse` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `warehouse`;
-- MySQL dump 10.13  Distrib 8.0.30, for Win64 (x86_64)
--
-- Host: localhost    Database: warehouse
-- ------------------------------------------------------
-- Server version	8.0.30

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `goodsinfo`
--

DROP TABLE IF EXISTS `goodsinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `goodsinfo` (
  `goods_id` int NOT NULL COMMENT '商品编号',
  `goods_name` varchar(30) DEFAULT NULL COMMENT '商品名称',
  `goods_amount` int DEFAULT '0' COMMENT '商品数量',
  `goods_price` double DEFAULT '0' COMMENT '商品单价',
  `supplier` varchar(40) DEFAULT NULL COMMENT '供应商家',
  `director` varchar(10) DEFAULT NULL COMMENT '负责人',
  `warehousetime` datetime DEFAULT NULL COMMENT '入库时间',
  `deliverytime` datetime DEFAULT NULL COMMENT '出库时间',
  `remark` varchar(255) DEFAULT NULL COMMENT '备注',
  PRIMARY KEY (`goods_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `goodsinfo`
--

LOCK TABLES `goodsinfo` WRITE;
/*!40000 ALTER TABLE `goodsinfo` DISABLE KEYS */;
INSERT INTO `goodsinfo` VALUES (37129,'华为手机',2900,4999,'华为','任正非','2024-06-08 21:21:38','2024-06-08 21:21:45','国产手机');
/*!40000 ALTER TABLE `goodsinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `goodsininfo`
--

DROP TABLE IF EXISTS `goodsininfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `goodsininfo` (
  `id` int NOT NULL AUTO_INCREMENT,
  `goods_id` int NOT NULL,
  `in_count` int NOT NULL COMMENT '一次入库数量记录',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `goodsininfo`
--

LOCK TABLES `goodsininfo` WRITE;
/*!40000 ALTER TABLE `goodsininfo` DISABLE KEYS */;
INSERT INTO `goodsininfo` VALUES (6,37129,3300),(7,2138,40);
/*!40000 ALTER TABLE `goodsininfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `goodsoutinfo`
--

DROP TABLE IF EXISTS `goodsoutinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `goodsoutinfo` (
  `id` int NOT NULL AUTO_INCREMENT,
  `goods_id` int NOT NULL,
  `out_count` int NOT NULL COMMENT '一次出库数量记录',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `goodsoutinfo`
--

LOCK TABLES `goodsoutinfo` WRITE;
/*!40000 ALTER TABLE `goodsoutinfo` DISABLE KEYS */;
INSERT INTO `goodsoutinfo` VALUES (4,37129,400),(5,2138,20);
/*!40000 ALTER TABLE `goodsoutinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `totalprice`
--

DROP TABLE IF EXISTS `totalprice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `totalprice` (
  `id` int NOT NULL AUTO_INCREMENT,
  `goods_id` int NOT NULL COMMENT 'goodsinfo的主键，商品id',
  `total_price` double NOT NULL COMMENT '总价',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `totalprice`
--

LOCK TABLES `totalprice` WRITE;
/*!40000 ALTER TABLE `totalprice` DISABLE KEYS */;
INSERT INTO `totalprice` VALUES (3,37129,14497100),(4,2138,200);
/*!40000 ALTER TABLE `totalprice` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-06-08 21:51:09
