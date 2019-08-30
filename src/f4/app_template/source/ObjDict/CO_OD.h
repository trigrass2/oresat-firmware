/*
 * CANopen Object Dictionary.
 *
 * This file was automatically generated with CANopenNode Object
 * Dictionary Editor. DON'T EDIT THIS FILE MANUALLY !!!!
 * Object Dictionary Editor is currently an older, but functional web
 * application. For more info see See 'Object_Dictionary_Editor/about.html' in
 * <http://sourceforge.net/p/canopennode/code_complete/ci/master/tree/>
 * For more information on CANopen Object Dictionary see <CO_SDO.h>.
 *
 * @file        CO_OD.c/CO_OD.h
 * @author      Janez Paternoster
 * @copyright   2010 - 2016 Janez Paternoster
 *
 * This file is part of CANopenNode, an opensource CANopen Stack.
 * Project home page is <https://github.com/CANopenNode/CANopenNode>.
 * For more information on CANopen see <http://www.can-cia.org/>.
 *
 * CANopenNode is free and open source software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Following clarification and special exception to the GNU General Public
 * License is included to the distribution terms of CANopenNode:
 *
 * Linking this library statically or dynamically with other modules is
 * making a combined work based on this library. Thus, the terms and
 * conditions of the GNU General Public License cover the whole combination.
 *
 * As a special exception, the copyright holders of this library give
 * you permission to link this library with independent modules to
 * produce an executable, regardless of the license terms of these
 * independent modules, and to copy and distribute the resulting
 * executable under terms of your choice, provided that you also meet,
 * for each linked independent module, the terms and conditions of the
 * license of that module. An independent module is a module which is
 * not derived from or based on this library. If you modify this
 * library, you may extend this exception to your version of the
 * library, but you are not obliged to do so. If you do not wish
 * to do so, delete this exception statement from your version.
 * Dictionary Editor v0.7-12-g6a8ebda * DON'T EDIT THIS FILE MANUALLY !!!!
 */


#pragma once

/*******************************************************************************
   CANopen DATA TYPES
*******************************************************************************/
   typedef bool_t       BOOLEAN;
   typedef uint8_t      UNSIGNED8;
   typedef uint16_t     UNSIGNED16;
   typedef uint32_t     UNSIGNED32;
   typedef uint64_t     UNSIGNED64;
   typedef int8_t       INTEGER8;
   typedef int16_t      INTEGER16;
   typedef int32_t      INTEGER32;
   typedef int64_t      INTEGER64;
   typedef float32_t    REAL32;
   typedef float64_t    REAL64;
   typedef char_t       VISIBLE_STRING;
   typedef oChar_t      OCTET_STRING;

   #ifdef DOMAIN
   #undef DOMAIN
   #endif

   typedef domain_t     DOMAIN;

#ifndef timeOfDay_t
    typedef union {
        unsigned long long ullValue;
        struct {
            unsigned long ms:28;
            unsigned reserved:4;
            unsigned days:16;
            unsigned reserved2:16;
        };
    }timeOfDay_t;
#endif

    typedef timeOfDay_t TIME_OF_DAY;
    typedef timeOfDay_t TIME_DIFFERENCE;


/*******************************************************************************
   FILE INFO:
      FileName:     app_master.eds
      FileVersion:  0
      CreationTime: 12:18PM
      CreationDate: 08-30-2019
      CreatedBy:    Miles Simpson
*******************************************************************************/


/*******************************************************************************
   DEVICE INFO:
      VendorName:     Portland State Aerospace Society
      VendorNumber:   0
      ProductName:    OreSat Master Template
      ProductNumber:  0
*******************************************************************************/


/*******************************************************************************
   FEATURES
*******************************************************************************/
  #define CO_NO_SYNC                     1   //Associated objects: 1005-1007
  #define CO_NO_EMERGENCY                1   //Associated objects: 1014, 1015
  #define CO_NO_SDO_SERVER               1   //Associated objects: 1200-127F
  #define CO_NO_SDO_CLIENT               1   //Associated objects: 1280-12FF
  #define CO_NO_LSS_SERVER               0   //LSS Slave
  #define CO_NO_LSS_CLIENT               0   //LSS Master
  #define CO_NO_RPDO                     16   //Associated objects: 14xx, 16xx
  #define CO_NO_TPDO                     16   //Associated objects: 18xx, 1Axx
  #define CO_NO_NMT_MASTER               0
  #define CO_NO_TRACE                    0


/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
   #define CO_OD_NoOfElements             96


/*******************************************************************************
   TYPE DEFINITIONS FOR RECORDS
*******************************************************************************/
/*1018      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     vendorID;
               UNSIGNED32     productCode;
               UNSIGNED32     revisionNumber;
               UNSIGNED32     serialNumber;
               }              OD_identity_t;
/*1200      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               }              OD_SDOServerParameter_t;
/*1280      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               UNSIGNED8      nodeIDOfTheSDOServer;
               }              OD_SDOClientParameter_t;
/*1400      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByRPDO;
               UNSIGNED8      transmissionType;
               }              OD_RPDOCommunicationParameter_t;
/*1600      */ typedef struct {
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_RPDOMappingParameter_t;
/*1800      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByTPDO;
               UNSIGNED8      transmissionType;
               UNSIGNED16     inhibitTime;
               UNSIGNED8      compatibilityEntry;
               UNSIGNED16     eventTimer;
               UNSIGNED8      SYNCStartValue;
               }              OD_TPDOCommunicationParameter_t;
/*1A00      */ typedef struct {
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_TPDOMappingParameter_t;
/*2130      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               VISIBLE_STRING string[30];
               UNSIGNED64     epochTimeBaseMs;
               UNSIGNED32     epochTimeOffsetMs;
               }              OD_time_t;

/*******************************************************************************
   TYPE DEFINITIONS FOR OBJECT DICTIONARY INDEXES

   some of those are redundant with CO_SDO.h CO_ObjDicId_t <Common CiA301 object
   dictionary entries>
*******************************************************************************/
/*1000 */
        #define OD_1000_deviceType                                  0x1000

/*1001 */
        #define OD_1001_errorRegister                               0x1001

/*1002 */
        #define OD_1002_manufacturerStatusRegister                  0x1002

/*1003 */
        #define OD_1003_preDefinedErrorField                        0x1003

        #define OD_1003_0_preDefinedErrorField_maxSubIndex          0
        #define OD_1003_1_preDefinedErrorField_standardErrorField   1
        #define OD_1003_2_preDefinedErrorField_standardErrorField   2
        #define OD_1003_3_preDefinedErrorField_standardErrorField   3
        #define OD_1003_4_preDefinedErrorField_standardErrorField   4
        #define OD_1003_5_preDefinedErrorField_standardErrorField   5
        #define OD_1003_6_preDefinedErrorField_standardErrorField   6
        #define OD_1003_7_preDefinedErrorField_standardErrorField   7
        #define OD_1003_8_preDefinedErrorField_standardErrorField   8

/*1005 */
        #define OD_1005_COB_ID_SYNCMessage                          0x1005

/*1006 */
        #define OD_1006_communicationCyclePeriod                    0x1006

/*1007 */
        #define OD_1007_synchronousWindowLength                     0x1007

/*1008 */
        #define OD_1008_manufacturerDeviceName                      0x1008

/*1009 */
        #define OD_1009_manufacturerHardwareVersion                 0x1009

/*100A */
        #define OD_100A_manufacturerSoftwareVersion                 0x100A

/*1010 */
        #define OD_1010_storeParameters                             0x1010

        #define OD_1010_0_storeParameters_maxSubIndex               0
        #define OD_1010_1_storeParameters_saveAllParameters         1

/*1011 */
        #define OD_1011_restoreDefaultParameters                    0x1011

        #define OD_1011_0_restoreDefaultParameters_maxSubIndex      0
        #define OD_1011_1_restoreDefaultParameters_restoreAllDefaultParameters 1

/*1014 */
        #define OD_1014_COB_ID_EMCY                                 0x1014

/*1015 */
        #define OD_1015_inhibitTimeEMCY                             0x1015

/*1016 */
        #define OD_1016_consumerHeartbeatTime                       0x1016

        #define OD_1016_0_consumerHeartbeatTime_maxSubIndex         0
        #define OD_1016_1_consumerHeartbeatTime_consumerHeartbeatTime 1
        #define OD_1016_2_consumerHeartbeatTime_consumerHeartbeatTime 2
        #define OD_1016_3_consumerHeartbeatTime_consumerHeartbeatTime 3
        #define OD_1016_4_consumerHeartbeatTime_consumerHeartbeatTime 4

/*1017 */
        #define OD_1017_producerHeartbeatTime                       0x1017

/*1018 */
        #define OD_1018_identity                                    0x1018

        #define OD_1018_0_identity_maxSubIndex                      0
        #define OD_1018_1_identity_vendorID                         1
        #define OD_1018_2_identity_productCode                      2
        #define OD_1018_3_identity_revisionNumber                   3
        #define OD_1018_4_identity_serialNumber                     4

/*1019 */
        #define OD_1019_synchronousCounterOverflowValue             0x1019

/*1029 */
        #define OD_1029_errorBehavior                               0x1029

        #define OD_1029_0_errorBehavior_maxSubIndex                 0
        #define OD_1029_1_errorBehavior_communication               1
        #define OD_1029_2_errorBehavior_communicationOther          2
        #define OD_1029_3_errorBehavior_communicationPassive        3
        #define OD_1029_4_errorBehavior_generic                     4
        #define OD_1029_5_errorBehavior_deviceProfile               5
        #define OD_1029_6_errorBehavior_manufacturerSpecific        6

/*1200 */
        #define OD_1200_SDOServerParameter                          0x1200

        #define OD_1200_0_SDOServerParameter_maxSubIndex            0
        #define OD_1200_1_SDOServerParameter_COB_IDClientToServer   1
        #define OD_1200_2_SDOServerParameter_COB_IDServerToClient   2

/*1280 */
        #define OD_1280_SDOClientParameter                          0x1280

        #define OD_1280_0_SDOClientParameter_maxSubIndex            0
        #define OD_1280_1_SDOClientParameter_COB_IDClientToServer   1
        #define OD_1280_2_SDOClientParameter_COB_IDServerToClient   2
        #define OD_1280_3_SDOClientParameter_nodeIDOfTheSDOServer   3

/*1400 */
        #define OD_1400_RPDOCommunicationParameter                  0x1400

        #define OD_1400_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1400_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1400_2_RPDOCommunicationParameter_transmissionType 2

/*1401 */
        #define OD_1401_RPDOCommunicationParameter                  0x1401

        #define OD_1401_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1401_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1401_2_RPDOCommunicationParameter_transmissionType 2

/*1402 */
        #define OD_1402_RPDOCommunicationParameter                  0x1402

        #define OD_1402_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1402_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1402_2_RPDOCommunicationParameter_transmissionType 2

/*1403 */
        #define OD_1403_RPDOCommunicationParameter                  0x1403

        #define OD_1403_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1403_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1403_2_RPDOCommunicationParameter_transmissionType 2

/*1404 */
        #define OD_1404_RPDOCommunicationParameter                  0x1404

        #define OD_1404_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1404_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1404_2_RPDOCommunicationParameter_transmissionType 2

/*1405 */
        #define OD_1405_RPDOCommunicationParameter                  0x1405

        #define OD_1405_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1405_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1405_2_RPDOCommunicationParameter_transmissionType 2

/*1406 */
        #define OD_1406_RPDOCommunicationParameter                  0x1406

        #define OD_1406_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1406_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1406_2_RPDOCommunicationParameter_transmissionType 2

/*1407 */
        #define OD_1407_RPDOCommunicationParameter                  0x1407

        #define OD_1407_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1407_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1407_2_RPDOCommunicationParameter_transmissionType 2

/*1408 */
        #define OD_1408_RPDOCommunicationParameter                  0x1408

        #define OD_1408_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1408_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1408_2_RPDOCommunicationParameter_transmissionType 2

/*1409 */
        #define OD_1409_RPDOCommunicationParameter                  0x1409

        #define OD_1409_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1409_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1409_2_RPDOCommunicationParameter_transmissionType 2

/*140A */
        #define OD_140A_RPDOCommunicationParameter                  0x140A

        #define OD_140A_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140A_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140A_2_RPDOCommunicationParameter_transmissionType 2

/*140B */
        #define OD_140B_RPDOCommunicationParameter                  0x140B

        #define OD_140B_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140B_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140B_2_RPDOCommunicationParameter_transmissionType 2

/*140C */
        #define OD_140C_RPDOCommunicationParameter                  0x140C

        #define OD_140C_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140C_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140C_2_RPDOCommunicationParameter_transmissionType 2

/*140D */
        #define OD_140D_RPDOCommunicationParameter                  0x140D

        #define OD_140D_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140D_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140D_2_RPDOCommunicationParameter_transmissionType 2

/*140E */
        #define OD_140E_RPDOCommunicationParameter                  0x140E

        #define OD_140E_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140E_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140E_2_RPDOCommunicationParameter_transmissionType 2

/*140F */
        #define OD_140F_RPDOCommunicationParameter                  0x140F

        #define OD_140F_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140F_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140F_2_RPDOCommunicationParameter_transmissionType 2

/*1600 */
        #define OD_1600_RPDOMappingParameter                        0x1600

        #define OD_1600_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1600_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1600_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1600_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1600_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1600_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1600_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1600_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1600_8_RPDOMappingParameter_mappedObject8        8

/*1601 */
        #define OD_1601_RPDOMappingParameter                        0x1601

        #define OD_1601_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1601_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1601_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1601_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1601_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1601_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1601_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1601_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1601_8_RPDOMappingParameter_mappedObject8        8

/*1602 */
        #define OD_1602_RPDOMappingParameter                        0x1602

        #define OD_1602_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1602_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1602_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1602_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1602_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1602_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1602_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1602_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1602_8_RPDOMappingParameter_mappedObject8        8

/*1603 */
        #define OD_1603_RPDOMappingParameter                        0x1603

        #define OD_1603_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1603_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1603_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1603_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1603_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1603_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1603_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1603_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1603_8_RPDOMappingParameter_mappedObject8        8

/*1604 */
        #define OD_1604_RPDOMappingParameter                        0x1604

        #define OD_1604_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1604_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1604_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1604_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1604_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1604_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1604_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1604_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1604_8_RPDOMappingParameter_mappedObject8        8

/*1605 */
        #define OD_1605_RPDOMappingParameter                        0x1605

        #define OD_1605_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1605_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1605_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1605_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1605_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1605_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1605_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1605_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1605_8_RPDOMappingParameter_mappedObject8        8

/*1606 */
        #define OD_1606_RPDOMappingParameter                        0x1606

        #define OD_1606_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1606_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1606_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1606_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1606_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1606_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1606_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1606_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1606_8_RPDOMappingParameter_mappedObject8        8

/*1607 */
        #define OD_1607_RPDOMappingParameter                        0x1607

        #define OD_1607_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1607_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1607_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1607_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1607_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1607_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1607_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1607_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1607_8_RPDOMappingParameter_mappedObject8        8

/*1608 */
        #define OD_1608_RPDOMappingParameter                        0x1608

        #define OD_1608_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1608_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1608_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1608_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1608_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1608_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1608_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1608_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1608_8_RPDOMappingParameter_mappedObject8        8

/*1609 */
        #define OD_1609_RPDOMappingParameter                        0x1609

        #define OD_1609_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1609_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1609_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1609_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1609_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1609_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1609_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1609_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1609_8_RPDOMappingParameter_mappedObject8        8

/*160A */
        #define OD_160A_RPDOMappingParameter                        0x160A

        #define OD_160A_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160A_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160A_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160A_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160A_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160A_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160A_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160A_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160A_8_RPDOMappingParameter_mappedObject8        8

/*160B */
        #define OD_160B_RPDOMappingParameter                        0x160B

        #define OD_160B_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160B_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160B_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160B_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160B_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160B_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160B_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160B_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160B_8_RPDOMappingParameter_mappedObject8        8

/*160C */
        #define OD_160C_RPDOMappingParameter                        0x160C

        #define OD_160C_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160C_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160C_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160C_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160C_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160C_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160C_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160C_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160C_8_RPDOMappingParameter_mappedObject8        8

/*160D */
        #define OD_160D_RPDOMappingParameter                        0x160D

        #define OD_160D_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160D_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160D_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160D_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160D_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160D_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160D_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160D_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160D_8_RPDOMappingParameter_mappedObject8        8

/*160E */
        #define OD_160E_RPDOMappingParameter                        0x160E

        #define OD_160E_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160E_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160E_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160E_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160E_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160E_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160E_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160E_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160E_8_RPDOMappingParameter_mappedObject8        8

/*160F */
        #define OD_160F_RPDOMappingParameter                        0x160F

        #define OD_160F_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160F_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160F_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160F_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160F_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160F_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160F_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160F_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160F_8_RPDOMappingParameter_mappedObject8        8

/*1800 */
        #define OD_1800_TPDOCommunicationParameter                  0x1800

        #define OD_1800_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1800_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1800_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1800_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1800_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1800_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1800_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1801 */
        #define OD_1801_TPDOCommunicationParameter                  0x1801

        #define OD_1801_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1801_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1801_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1801_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1801_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1801_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1801_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1802 */
        #define OD_1802_TPDOCommunicationParameter                  0x1802

        #define OD_1802_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1802_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1802_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1802_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1802_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1802_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1802_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1803 */
        #define OD_1803_TPDOCommunicationParameter                  0x1803

        #define OD_1803_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1803_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1803_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1803_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1803_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1803_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1803_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1804 */
        #define OD_1804_TPDOCommunicationParameter                  0x1804

        #define OD_1804_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1804_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1804_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1804_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1804_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1804_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1804_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1805 */
        #define OD_1805_TPDOCommunicationParameter                  0x1805

        #define OD_1805_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1805_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1805_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1805_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1805_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1805_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1805_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1806 */
        #define OD_1806_TPDOCommunicationParameter                  0x1806

        #define OD_1806_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1806_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1806_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1806_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1806_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1806_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1806_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1807 */
        #define OD_1807_TPDOCommunicationParameter                  0x1807

        #define OD_1807_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1807_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1807_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1807_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1807_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1807_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1807_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1808 */
        #define OD_1808_TPDOCommunicationParameter                  0x1808

        #define OD_1808_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1808_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1808_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1808_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1808_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1808_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1808_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1809 */
        #define OD_1809_TPDOCommunicationParameter                  0x1809

        #define OD_1809_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1809_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1809_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1809_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1809_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1809_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1809_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180A */
        #define OD_180A_TPDOCommunicationParameter                  0x180A

        #define OD_180A_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180A_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180A_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180A_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180A_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180A_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180A_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180B */
        #define OD_180B_TPDOCommunicationParameter                  0x180B

        #define OD_180B_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180B_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180B_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180B_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180B_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180B_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180B_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180C */
        #define OD_180C_TPDOCommunicationParameter                  0x180C

        #define OD_180C_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180C_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180C_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180C_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180C_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180C_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180C_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180D */
        #define OD_180D_TPDOCommunicationParameter                  0x180D

        #define OD_180D_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180D_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180D_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180D_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180D_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180D_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180D_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180E */
        #define OD_180E_TPDOCommunicationParameter                  0x180E

        #define OD_180E_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180E_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180E_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180E_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180E_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180E_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180E_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180F */
        #define OD_180F_TPDOCommunicationParameter                  0x180F

        #define OD_180F_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180F_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180F_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180F_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180F_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180F_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180F_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1A00 */
        #define OD_1A00_TPDOMappingParameter                        0x1A00

        #define OD_1A00_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A00_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A00_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A00_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A00_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A00_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A00_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A00_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A00_8_TPDOMappingParameter_mappedObject8        8

/*1A01 */
        #define OD_1A01_TPDOMappingParameter                        0x1A01

        #define OD_1A01_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A01_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A01_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A01_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A01_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A01_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A01_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A01_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A01_8_TPDOMappingParameter_mappedObject8        8

/*1A02 */
        #define OD_1A02_TPDOMappingParameter                        0x1A02

        #define OD_1A02_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A02_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A02_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A02_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A02_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A02_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A02_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A02_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A02_8_TPDOMappingParameter_mappedObject8        8

/*1A03 */
        #define OD_1A03_TPDOMappingParameter                        0x1A03

        #define OD_1A03_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A03_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A03_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A03_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A03_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A03_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A03_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A03_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A03_8_TPDOMappingParameter_mappedObject8        8

/*1A04 */
        #define OD_1A04_TPDOMappingParameter                        0x1A04

        #define OD_1A04_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A04_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A04_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A04_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A04_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A04_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A04_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A04_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A04_8_TPDOMappingParameter_mappedObject8        8

/*1A05 */
        #define OD_1A05_TPDOMappingParameter                        0x1A05

        #define OD_1A05_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A05_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A05_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A05_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A05_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A05_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A05_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A05_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A05_8_TPDOMappingParameter_mappedObject8        8

/*1A06 */
        #define OD_1A06_TPDOMappingParameter                        0x1A06

        #define OD_1A06_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A06_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A06_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A06_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A06_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A06_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A06_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A06_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A06_8_TPDOMappingParameter_mappedObject8        8

/*1A07 */
        #define OD_1A07_TPDOMappingParameter                        0x1A07

        #define OD_1A07_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A07_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A07_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A07_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A07_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A07_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A07_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A07_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A07_8_TPDOMappingParameter_mappedObject8        8

/*1A08 */
        #define OD_1A08_TPDOMappingParameter                        0x1A08

        #define OD_1A08_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A08_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A08_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A08_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A08_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A08_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A08_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A08_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A08_8_TPDOMappingParameter_mappedObject8        8

/*1A09 */
        #define OD_1A09_TPDOMappingParameter                        0x1A09

        #define OD_1A09_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A09_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A09_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A09_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A09_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A09_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A09_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A09_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A09_8_TPDOMappingParameter_mappedObject8        8

/*1A0A */
        #define OD_1A0A_TPDOMappingParameter                        0x1A0A

        #define OD_1A0A_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0A_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0A_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0A_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0A_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0A_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0A_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0A_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0A_8_TPDOMappingParameter_mappedObject8        8

/*1A0B */
        #define OD_1A0B_TPDOMappingParameter                        0x1A0B

        #define OD_1A0B_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0B_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0B_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0B_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0B_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0B_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0B_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0B_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0B_8_TPDOMappingParameter_mappedObject8        8

/*1A0C */
        #define OD_1A0C_TPDOMappingParameter                        0x1A0C

        #define OD_1A0C_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0C_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0C_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0C_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0C_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0C_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0C_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0C_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0C_8_TPDOMappingParameter_mappedObject8        8

/*1A0D */
        #define OD_1A0D_TPDOMappingParameter                        0x1A0D

        #define OD_1A0D_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0D_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0D_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0D_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0D_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0D_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0D_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0D_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0D_8_TPDOMappingParameter_mappedObject8        8

/*1A0E */
        #define OD_1A0E_TPDOMappingParameter                        0x1A0E

        #define OD_1A0E_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0E_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0E_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0E_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0E_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0E_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0E_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0E_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0E_8_TPDOMappingParameter_mappedObject8        8

/*1A0F */
        #define OD_1A0F_TPDOMappingParameter                        0x1A0F

        #define OD_1A0F_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0F_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0F_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0F_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0F_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0F_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0F_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0F_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0F_8_TPDOMappingParameter_mappedObject8        8

/*1F80 */
        #define OD_1F80_NMTStartup                                  0x1F80

/*2100 */
        #define OD_2100_errorStatusBits                             0x2100

/*2101 */
        #define OD_2101_CANNodeID                                   0x2101

/*2102 */
        #define OD_2102_CANBitRate                                  0x2102

/*2103 */
        #define OD_2103_SYNCCounter                                 0x2103

/*2104 */
        #define OD_2104_SYNCTime                                    0x2104

/*2106 */
        #define OD_2106_powerOnCounter                              0x2106

/*2107 */
        #define OD_2107_performance                                 0x2107

        #define OD_2107_0_performance_maxSubIndex                   0
        #define OD_2107_1_performance_cyclesPerSecond               1
        #define OD_2107_2_performance_timerCycleTime                2
        #define OD_2107_3_performance_timerCycleMaxTime             3
        #define OD_2107_4_performance_mainCycleTime                 4
        #define OD_2107_5_performance_mainCycleMaxTime              5

/*2108 */
        #define OD_2108_temperature                                 0x2108

        #define OD_2108_0_temperature_maxSubIndex                   0
        #define OD_2108_1_temperature_mainPCB                       1

/*2109 */
        #define OD_2109_voltage                                     0x2109

        #define OD_2109_0_voltage_maxSubIndex                       0
        #define OD_2109_1_voltage_mainPCBSupply                     1

/*2130 */
        #define OD_2130_time                                        0x2130

        #define OD_2130_0_time_maxSubIndex                          0
        #define OD_2130_1_time_string                               1
        #define OD_2130_2_time_epochTimeBaseMs                      2
        #define OD_2130_3_time_epochTimeOffsetMs                    3

/*******************************************************************************
   STRUCTURES FOR VARIABLES IN DIFFERENT MEMORY LOCATIONS
*******************************************************************************/
#define  CO_OD_FIRST_LAST_WORD     0x55 //Any value from 0x01 to 0xFE. If changed, EEPROM will be reinitialized.

/***** Structure for ROM variables ********************************************/
struct sCO_OD_ROM{
               UNSIGNED32     FirstWord;

/*1000      */ UNSIGNED32     deviceType;
/*1005      */ UNSIGNED32     COB_ID_SYNCMessage;
/*1006      */ UNSIGNED32     communicationCyclePeriod;
/*1007      */ UNSIGNED32     synchronousWindowLength;
/*1008      */ VISIBLE_STRING manufacturerDeviceName[11];
/*1009      */ VISIBLE_STRING manufacturerHardwareVersion[4];
/*100A      */ VISIBLE_STRING manufacturerSoftwareVersion[4];
/*1014      */ UNSIGNED32     COB_ID_EMCY;
/*1015      */ UNSIGNED16     inhibitTimeEMCY;
/*1016      */ UNSIGNED32      consumerHeartbeatTime[4];
/*1017      */ UNSIGNED16     producerHeartbeatTime;
/*1018      */ OD_identity_t   identity;
/*1019      */ UNSIGNED8      synchronousCounterOverflowValue;
/*1029      */ UNSIGNED8       errorBehavior[6];
/*1200      */ OD_SDOServerParameter_t SDOServerParameter[1];
/*1400      */ OD_RPDOCommunicationParameter_t RPDOCommunicationParameter[16];
/*1600      */ OD_RPDOMappingParameter_t RPDOMappingParameter[16];
/*1800      */ OD_TPDOCommunicationParameter_t TPDOCommunicationParameter[16];
/*1A00      */ OD_TPDOMappingParameter_t TPDOMappingParameter[16];
/*1F80      */ UNSIGNED32     NMTStartup;
/*2101      */ UNSIGNED8      CANNodeID;
/*2102      */ UNSIGNED16     CANBitRate;

               UNSIGNED32     LastWord;
};

/***** Structure for RAM variables ********************************************/
struct sCO_OD_RAM{
               UNSIGNED32     FirstWord;

/*1001      */ UNSIGNED8      errorRegister;
/*1002      */ UNSIGNED32     manufacturerStatusRegister;
/*1003      */ UNSIGNED32      preDefinedErrorField[8];
/*1010      */ UNSIGNED32      storeParameters[1];
/*1011      */ UNSIGNED32      restoreDefaultParameters[1];
/*1280      */ OD_SDOClientParameter_t SDOClientParameter[1];
/*2100      */ OCTET_STRING   errorStatusBits[10];
/*2103      */ UNSIGNED16     SYNCCounter;
/*2104      */ UNSIGNED16     SYNCTime;
/*2107      */ UNSIGNED16      performance[5];
/*2108      */ INTEGER16       temperature[1];
/*2109      */ INTEGER16       voltage[1];
/*2130      */ OD_time_t       time;

               UNSIGNED32     LastWord;
};

/***** Structure for EEPROM variables ********************************************/
struct sCO_OD_EEPROM{
               UNSIGNED32     FirstWord;

/*2106      */ UNSIGNED32     powerOnCounter;

               UNSIGNED32     LastWord;
};

/***** Declaration of Object Dictionary variables *****************************/
extern struct sCO_OD_ROM CO_OD_ROM;

extern struct sCO_OD_RAM CO_OD_RAM;

extern struct sCO_OD_EEPROM CO_OD_EEPROM;

/*******************************************************************************
   ALIASES FOR OBJECT DICTIONARY VARIABLES
*******************************************************************************/
/*1000, Data Type: UNSIGNED32 */
        #define OD_deviceType                                       CO_OD_ROM.deviceType

/*1001, Data Type: UNSIGNED8 */
        #define OD_errorRegister                                    CO_OD_RAM.errorRegister

/*1002, Data Type: UNSIGNED32 */
        #define OD_manufacturerStatusRegister                       CO_OD_RAM.manufacturerStatusRegister

/*1003, Data Type: UNSIGNED32, Array[8] */
        #define OD_preDefinedErrorField                             CO_OD_RAM.preDefinedErrorField
        #define ODL_preDefinedErrorField_arrayLength                8
        #define ODA_preDefinedErrorField_standardErrorField         0

/*1005, Data Type: UNSIGNED32 */
        #define OD_COB_ID_SYNCMessage                               CO_OD_ROM.COB_ID_SYNCMessage

/*1006, Data Type: UNSIGNED32 */
        #define OD_communicationCyclePeriod                         CO_OD_ROM.communicationCyclePeriod

/*1007, Data Type: UNSIGNED32 */
        #define OD_synchronousWindowLength                          CO_OD_ROM.synchronousWindowLength

/*1008, Data Type: VISIBLE_STRING */
        #define OD_manufacturerDeviceName                           CO_OD_ROM.manufacturerDeviceName
        #define ODL_manufacturerDeviceName_stringLength             11

/*1009, Data Type: VISIBLE_STRING */
        #define OD_manufacturerHardwareVersion                      CO_OD_ROM.manufacturerHardwareVersion
        #define ODL_manufacturerHardwareVersion_stringLength        4

/*100A, Data Type: VISIBLE_STRING */
        #define OD_manufacturerSoftwareVersion                      CO_OD_ROM.manufacturerSoftwareVersion
        #define ODL_manufacturerSoftwareVersion_stringLength        4

/*1010, Data Type: UNSIGNED32, Array[1] */
        #define OD_storeParameters                                  CO_OD_RAM.storeParameters
        #define ODL_storeParameters_arrayLength                     1
        #define ODA_storeParameters_saveAllParameters               0

/*1011, Data Type: UNSIGNED32, Array[1] */
        #define OD_restoreDefaultParameters                         CO_OD_RAM.restoreDefaultParameters
        #define ODL_restoreDefaultParameters_arrayLength            1
        #define ODA_restoreDefaultParameters_restoreAllDefaultParameters 0

/*1014, Data Type: UNSIGNED32 */
        #define OD_COB_ID_EMCY                                      CO_OD_ROM.COB_ID_EMCY

/*1015, Data Type: UNSIGNED16 */
        #define OD_inhibitTimeEMCY                                  CO_OD_ROM.inhibitTimeEMCY

/*1016, Data Type: UNSIGNED32, Array[4] */
        #define OD_consumerHeartbeatTime                            CO_OD_ROM.consumerHeartbeatTime
        #define ODL_consumerHeartbeatTime_arrayLength               4
        #define ODA_consumerHeartbeatTime_consumerHeartbeatTime     0

/*1017, Data Type: UNSIGNED16 */
        #define OD_producerHeartbeatTime                            CO_OD_ROM.producerHeartbeatTime

/*1018, Data Type: identity_t */
        #define OD_identity                                         CO_OD_ROM.identity

/*1019, Data Type: UNSIGNED8 */
        #define OD_synchronousCounterOverflowValue                  CO_OD_ROM.synchronousCounterOverflowValue

/*1029, Data Type: UNSIGNED8, Array[6] */
        #define OD_errorBehavior                                    CO_OD_ROM.errorBehavior
        #define ODL_errorBehavior_arrayLength                       6
        #define ODA_errorBehavior_communication                     0
        #define ODA_errorBehavior_communicationOther                1
        #define ODA_errorBehavior_communicationPassive              2
        #define ODA_errorBehavior_generic                           3
        #define ODA_errorBehavior_deviceProfile                     4
        #define ODA_errorBehavior_manufacturerSpecific              5

/*1200, Data Type: SDOServerParameter_t */
        #define OD_SDOServerParameter                               CO_OD_ROM.SDOServerParameter

/*1280, Data Type: SDOClientParameter_t */
        #define OD_SDOClientParameter                               CO_OD_RAM.SDOClientParameter

/*1400, Data Type: RPDOCommunicationParameter_t */
        #define OD_RPDOCommunicationParameter                       CO_OD_ROM.RPDOCommunicationParameter

/*1600, Data Type: RPDOMappingParameter_t */
        #define OD_RPDOMappingParameter                             CO_OD_ROM.RPDOMappingParameter

/*1800, Data Type: TPDOCommunicationParameter_t */
        #define OD_TPDOCommunicationParameter                       CO_OD_ROM.TPDOCommunicationParameter

/*1A00, Data Type: TPDOMappingParameter_t */
        #define OD_TPDOMappingParameter                             CO_OD_ROM.TPDOMappingParameter

/*1F80, Data Type: UNSIGNED32 */
        #define OD_NMTStartup                                       CO_OD_ROM.NMTStartup

/*2100, Data Type: OCTET_STRING */
        #define OD_errorStatusBits                                  CO_OD_RAM.errorStatusBits
        #define ODL_errorStatusBits_stringLength                    10

/*2101, Data Type: UNSIGNED8 */
        #define OD_CANNodeID                                        CO_OD_ROM.CANNodeID

/*2102, Data Type: UNSIGNED16 */
        #define OD_CANBitRate                                       CO_OD_ROM.CANBitRate

/*2103, Data Type: UNSIGNED16 */
        #define OD_SYNCCounter                                      CO_OD_RAM.SYNCCounter

/*2104, Data Type: UNSIGNED16 */
        #define OD_SYNCTime                                         CO_OD_RAM.SYNCTime

/*2106, Data Type: UNSIGNED32 */
        #define OD_powerOnCounter                                   CO_OD_EEPROM.powerOnCounter

/*2107, Data Type: UNSIGNED16, Array[5] */
        #define OD_performance                                      CO_OD_RAM.performance
        #define ODL_performance_arrayLength                         5
        #define ODA_performance_cyclesPerSecond                     0
        #define ODA_performance_timerCycleTime                      1
        #define ODA_performance_timerCycleMaxTime                   2
        #define ODA_performance_mainCycleTime                       3
        #define ODA_performance_mainCycleMaxTime                    4

/*2108, Data Type: INTEGER16, Array[1] */
        #define OD_temperature                                      CO_OD_RAM.temperature
        #define ODL_temperature_arrayLength                         1
        #define ODA_temperature_mainPCB                             0

/*2109, Data Type: INTEGER16, Array[1] */
        #define OD_voltage                                          CO_OD_RAM.voltage
        #define ODL_voltage_arrayLength                             1
        #define ODA_voltage_mainPCBSupply                           0

/*2130, Data Type: time_t */
        #define OD_time                                             CO_OD_RAM.time

