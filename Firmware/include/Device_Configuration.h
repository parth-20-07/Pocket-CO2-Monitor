/**
 * @file DEVICE_CONFIGURATION.h
 * @author Parth Patel (parth.pmech@gmail.com)
 * @brief This file is used to select the device configuration
 * 1. Select the sensor type connected to the unit
 * 2. Select the type of display which is connected
 * 3. Select if the SD Card is supported
 * @version 0.1
 * @date 2021-12-05
 * @copyright Copyright (c) 2021
 * * CHANGE AS PER THE NEED
 */

#ifndef DEVICE_CONFIGURATION_H
#define DEVICE_CONFIGURATION_H
#include "Pin_Connection.h"

//!============================== Sensor Connected =======================================//
#define PRANA_AIR_SENSOR // PranaAir Air Quality Index Sensor
// #define GENERIC_AIR_SENSOR // Generic Air Quality Index Sensor
//!=======================================================================================//

//!============================= Display Connected =======================================//
#define TFT_LCD_DISPLAY // TFT LCD Display
// #define TM1637_4x7_SEGMENT_DISPLAY // 4 x 7 Segment Display with TM1637 LED Driver
//!=======================================================================================//

//!============================= SD Card Connected =======================================//
// #define SD_SUPPORT_ENABLED // If SD Card is supported
//!=======================================================================================//

#endif
