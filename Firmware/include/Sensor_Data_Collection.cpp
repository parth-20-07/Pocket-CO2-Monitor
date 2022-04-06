#ifndef Sensor_Data_Collection_cpp
#define Sensor_Data_Collection_cpp

#include "Arduino.h"
#include "Pin_Connection.h"
#include "Variable_Declaration.h"

/* -------------------------------------------------------------------------- */
/*                              BASIC DEFINITION                              */
/* -------------------------------------------------------------------------- */
#define VALUE_LENGTH 5
#define MINIMUM_WIDTH 1
#define NUM_AFTER_DECIMAL 0

#include <Wire.h>
#include "HTU21D.h"
HTU21D temperature_and_humidity_sensor; // Create an instance of the object
uint8_t humd, temp;
char temp_value[VALUE_LENGTH], humi_value[VALUE_LENGTH]; // Variable to store values

#include "MHZ19.h"
#include "SoftwareSerial.h"
MHZ19 carbondioxide_sensor; // Constructor for library
SoftwareSerial MHZ19CSerial(MHZ_TX, MHZ_RX);
uint16_t CO2;
char co2_value[VALUE_LENGTH]; // Variable to store CO2

/* -------------------------------------------------------------------------- */
/*                             FUNCTION DEFINITION                            */
/* -------------------------------------------------------------------------- */
void setup_sensors(void)
{
    Serial.println("Setting up Sensors");
    Serial.println("Setting up Temperature and Humidity Sensor");
    temperature_and_humidity_sensor.begin();

    Serial.println("Setting up CO2 Sensor");
    MHZ19CSerial.begin(9600);
    carbondioxide_sensor.begin(MHZ19CSerial);
    carbondioxide_sensor.autoCalibration();
}

void collect_temperature_and_humidity_values(void)
{
    // Serial.println("Reading HTU21D");
    humd = temperature_and_humidity_sensor.readHumidity();
    temp = temperature_and_humidity_sensor.readTemperature();
    // Serial.println("Temperature: " + (String)temp + "C");
    // Serial.println("Humidity: " + (String)humd + "%");
}

void collect_co2_values(void)
{
    // Serial.println("Reading MHZ19C");
    CO2 = carbondioxide_sensor.getCO2();
    // Serial.println("CO2: " + (String)CO2 + "ppm");
}

#endif