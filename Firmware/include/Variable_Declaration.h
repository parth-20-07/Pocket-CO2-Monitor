/**
 * @file VARIABLE_DECLARATION.h
 * @author Parth Patel (parth.pmech@gmail.com)
 * @brief This page is used to declare the Variables used throughout the page
 * @version 0.1
 * @date 2021-12-27
 * @copyright Copyright (c) 2021
 * ! DO NOT CHANGE
 */
#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H
#include "Pin_Connection.h"
#include "Device_Configuration.h"

//!============================== Sensor Variables =======================================//
#define MAX_SAFETY_LIMIT 50
#define MAX_WARNING_LIMIT 100
#define MAX_UNHEALTHY_LIMIT 300
#define MAX_HAZARDOUS_LIMIT 500
//!=======================================================================================//

//!============================= Display Variables =======================================//
#define SCREEN_REFRESH_TIME 10000 // Time to wait before screen update (time in ms)
int screen_counter = 1;           // Counts on which screen the user is at
bool first_boot = true;           // Checks if the device is just starting up
bool change_screen_flag = false;  // Checks if the screen needs to be changed
const char company_name[] = "Ecologic";
#define boot_screen_timer 5000 // The timer in ms for which the bootscreen is being displayed
#define BATTERY_SYMBOL_HEIGHT 15
#define BATTERY_SYMBOL_WIDTH 30
#define MARGIN_BUFFER 3
#define GRAPH_BUFFER_SCREEN 10 // Margin space between screen border and graph
// #define GRAPH_PLOT_TIME 300000 // 5 mins plotter
#define GRAPH_PLOT_TIME 10000 // 10 secs plotter
uint32_t last_millis;
int screen_height = 0;
int screen_width = 0;

#ifdef TFT_LCD_DISPLAY
#include <SPI.h>
#ifdef SD_SUPPORT_ENABLED
#include <SD.h>
#endif

#include <TFT.h>
TFT screen = TFT(TFT_DISPLAY_CS, TFT_DISPLAY_DC, TFT_DISPLAY_RST);

// Color Codes in format B,G,R for the TFT Display
#define BLACK_COLOR 0, 0, 0
#define WHITE_COLOR 255, 255, 255
#define GREY_COLOR 100, 100, 100
#define YELLOW_COLOR 0, 255, 255
#define RED_COLOR 0, 0, 255
#define GREEN_COLOR 0, 255, 0
#define ORANGE_COLOR 0, 50, 255
#define PINK_COLOR 182, 193, 255

#endif

#ifdef TM1637_4x7_SEGMENT_DISPLAY
#include <TM1637Display.h>
TM1637Display display = TM1637Display(SEGMENT_CLK, SEGMENT_DIO);
#define TM1637_DISPLAY_BRIGHTNESS 7               // Set the brightness to 5 (0=dimmest 7=brightest)
const uint8_t allON[] = {0xff, 0xff, 0xff, 0xff}; // Create an array that turns all segments ON
#endif

//!=======================================================================================//

//!============================= Battery Variables =======================================//
#define MAX_BATTERY_ADC_VALUE 1023
#define MIN_BATTERY_ADC_VALUE 30
#define MEDIUM_BATTERY_PERCENT 50
#define LOW_BATTERY_PERCENT 20
#define SUPPLY_CONNECTED_MIN_ADC_VALUE 100
//!=======================================================================================//
#endif