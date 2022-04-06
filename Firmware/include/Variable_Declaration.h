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

//!============================== Sensor Variables =======================================//
#define MAX_SAFETY_LIMIT 799
#define MAX_WARNING_LIMIT 1199
#define MAX_UNHEALTHY_LIMIT 1599
#define MAX_HAZARDOUS_LIMIT 10000
//!=======================================================================================//

//!============================= Display Variables =======================================//
int screen_counter = 1;          // Counts on which screen the user is at
bool change_screen_flag = false; // Checks if the screen needs to be changed
const char company_name[] = "Ecologic";
#define BATTERY_SYMBOL_HEIGHT 15
#define BATTERY_SYMBOL_WIDTH 25
#define MARGIN_BUFFER 3
#define GRAPH_BUFFER_SCREEN 10 // Margin space between screen border and graph
#define GRAPH_PLOT_TIME 300000 // 5 mins plotter
// #define GRAPH_PLOT_TIME 10000 // 10 secs plotter
uint32_t last_millis;
int screen_width = 0;
int screen_height = 0;

#include <SPI.h>
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
//!=======================================================================================//

//!============================= Battery Variables =======================================//
#define MAX_BATTERY_ADC_VALUE 1023
#define MIN_BATTERY_ADC_VALUE 30
#define MEDIUM_BATTERY_PERCENT 50
#define LOW_BATTERY_PERCENT 20
#define SUPPLY_CONNECTED_MIN_ADC_VALUE 100
//!=======================================================================================//
#endif