/*
 Navicat Premium Data Transfer

 Source Server         : qt-sql
 Source Server Type    : MySQL
 Source Server Version : 80031
 Source Host           : localhost:3306
 Source Schema         : care_animals

 Target Server Type    : MySQL
 Target Server Version : 80031
 File Encoding         : 65001

 Date: 04/01/2024 21:22:14
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for adopter
-- ----------------------------
DROP TABLE IF EXISTS `adopter`;
CREATE TABLE `adopter`  (
  `名字` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `宠物` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `手机号码` int(0) NULL DEFAULT NULL,
  `家庭地址` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL,
  `生活状况` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL,
  `签订协议` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`名字`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Triggers structure for table adopter
-- ----------------------------
DROP TRIGGER IF EXISTS `after_insert_adopter`;
delimiter ;;
CREATE TRIGGER `after_insert_adopter` AFTER INSERT ON `adopter` FOR EACH ROW BEGIN
    -- 删除被领养的宠物数据
    DELETE FROM pet WHERE `宠物` = NEW.宠物;
    
    -- 增添领养记录
    INSERT INTO history	 (history.`领养者`, history.`宠物`, history.`领养时间`, history.`签订协议`)
    VALUES (NEW.`名字`, NEW.`宠物`, DATE_FORMAT(NOW(), '%Y-%m-%d %H:%i:%s'), NEW.`签订协议`);
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
