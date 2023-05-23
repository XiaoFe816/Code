/*
 Navicat Premium Data Transfer

 Source Server         : hostFe
 Source Server Type    : MySQL
 Source Server Version : 80013
 Source Host           : localhost:3306
 Source Schema         : demo

 Target Server Type    : MySQL
 Target Server Version : 80013
 File Encoding         : 65001

 Date: 23/05/2023 14:51:05
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for userdata
-- ----------------------------
DROP TABLE IF EXISTS `userdata`;
CREATE TABLE `userdata`  (
  `uid` int(11) NOT NULL AUTO_INCREMENT,
  `userName` char(100) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `passWord` char(100) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`uid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of userdata
-- ----------------------------
INSERT INTO `userdata` VALUES (1999001, '张三', 'ZhangSan123');
INSERT INTO `userdata` VALUES (1999002, '李四', 'LLL');
INSERT INTO `userdata` VALUES (1999003, '王五', 'WWW');
INSERT INTO `userdata` VALUES (1999004, '赵云', 'Z');

SET FOREIGN_KEY_CHECKS = 1;
