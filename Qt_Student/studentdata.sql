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

 Date: 23/05/2023 14:48:22
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for studentdata
-- ----------------------------
DROP TABLE IF EXISTS `studentdata`;
CREATE TABLE `studentdata`  (
  `学号` bigint(12) NOT NULL AUTO_INCREMENT,
  `姓名` tinytext CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `性别` tinytext CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `年龄` int(4) NULL DEFAULT NULL,
  `语文成绩` int(4) NULL DEFAULT NULL,
  `数学成绩` int(4) NULL DEFAULT NULL,
  `英语成绩` int(4) NULL DEFAULT NULL,
  PRIMARY KEY (`学号`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 2023051819 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of studentdata
-- ----------------------------
INSERT INTO `studentdata` VALUES (2023051801, '黄飞鸿', '男', 29, 89, 67, 58);
INSERT INTO `studentdata` VALUES (2023051802, '霍元甲', '男', 31, 78, 66, 61);
INSERT INTO `studentdata` VALUES (2023051803, '陈真', '男', 25, 91, 88, 83);
INSERT INTO `studentdata` VALUES (2023051804, '叶轻眉', '女', 22, 97, 96, 93);
INSERT INTO `studentdata` VALUES (2023051805, '马永贞', '男', 24, 72, 62, 53);
INSERT INTO `studentdata` VALUES (2023051806, '叶问', '男', 41, 89, 76, 68);
INSERT INTO `studentdata` VALUES (2023051812, '王杰希', '男', 26, 60, 61, 62);

SET FOREIGN_KEY_CHECKS = 1;
