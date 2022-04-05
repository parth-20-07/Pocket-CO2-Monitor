/**
 * @file PIN_CONNECTION.h
 * @author Parth Patel (parth.pmech@gmail.com)
 * @brief Check the Pin Connection on this page as per the connection
 * @version 0.1
 * @date 2021-12-27
 * @copyright Copyright (c) 2021
 * ! DO NOT CHANGE
 */

#ifndef PIN_CONNECTION_H
#define PIN_CONNECTION_H

// GPIO PINS
#define NANO_GPIO_2 2
#define NANO_GPIO_3 3
#define NANO_GPIO_4 4
#define NANO_GPIO_5 5
#define NANO_GPIO_6 6
#define NANO_GPIO_7 7
#define NANO_GPIO_8 8
#define NANO_GPIO_9 9
#define NANO_GPIO_10 10
#define NANO_AI_0 A0
#define NANO_AI_1 A1
#define NANO_AI_2 A2
#define NANO_AI_3 A3
#define NANO_AI_6 A6
#define NANO_AI_7 A7

// COMMUNICATION PINS
#define SERIAL_TX 0
#define SERIAL_RX 1
#define SPI_MOSI 11
#define SPI_MISO 12
#define SPI_SCK 13
#define I2C_SDA A4
#define I2C_SCL A5

/* -------------------------- INTERRUPT CONNECTION -------------------------- */
#define INT_PIN NANO_GPIO_2 // Push Button to change the screens

/* -------------------------- MHZ - 19C CONNECTION -------------------------- */
#define MHZ_RX NANO_GPIO_7 // Serial RX Pin for the MHZ-19C Sensor
#define MHZ_TX NANO_GPIO_6 // Serial TX Pin for the MHZ-19C Sensor

/* ---------------------------- SUPPLY CONNECTION --------------------------- */
#define BATTERY_INPUT NANO_AI_0        // Battery connection input to the Arduino to read the battery level
#define CONNECTED_SUPPLY_PIN NANO_AI_1 // Suppply connection input to the Arduino to read the Charger connection state

/* --------------------------- DISPLAY CONNECTION --------------------------- */
#define TFT_DISPLAY_CS NANO_GPIO_10
#define TFT_DISPLAY_DC NANO_GPIO_9
#define TFT_DISPLAY_RST NANO_GPIO_8
#define TFT_DISPLAY_LED NANO_GPIO_4

void setup_peripheral_pin_mode(void)
{
    pinMode(TFT_DISPLAY_LED, OUTPUT);
    pinMode(INT_PIN, INPUT);
    pinMode(CONNECTED_SUPPLY_PIN, INPUT);
    pinMode(BATTERY_INPUT, INPUT);
}

#endif