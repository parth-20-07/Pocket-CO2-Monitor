/**
 * @file main.cpp
 * @author Parth Patel (parth.pmech@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-05
 * @copyright Copyright (c) 2021
 * ! DO NOT CHANGE
 */

//!=============================== BASIC DECLARATION ===============================//
#include <Arduino.h>
#include "Pin_Connection.h"
#include "Variable_Declaration.h"
#include "Sensor_Data_Collection.cpp"
#include <avr/sleep.h>
//!==================================================================================//

//!============================== FUNCTION DEFINITION ==============================//
void boot_screen(void);
void graphic_data_screen(void);
void drawing_battery(void);
void put_device_to_sleep(void);
void change_screen(void);
void stop_device_peripherals(void);

//!==================================================================================//

//!============================== FUNCTION DECLARATION ==============================//
/**
 * @brief Print the Boot Screen on the device startup
 */
void boot_screen(void)
{
  Serial.println("Printing Boot Screen");
  Serial.println("Drawing LOGO");
  screen.background(BLACK_COLOR);
  screen.setTextSize(2);
  screen.stroke(WHITE_COLOR);
  screen.text("ECOLOGIC", 20, (screen_height / 2) - 10);
}

/**
 * @brief Draws the bubble screen for displaying the PM 2.5 Value on the screen
 */
void graphic_data_screen(void)
{
  Serial.println("Starting Device Peripherals");
  digitalWrite(TFT_DISPLAY_LED, HIGH);
  screen.begin();
  screen.setRotation(90);
  screen_width = screen.width();
  screen_height = screen.height();
  screen.background(BLACK_COLOR);
  screen.stroke(WHITE_COLOR);
  boot_screen();

  change_screen_flag = false;
  Serial.println("Drawing Graphic Screen");
  screen.background(BLACK_COLOR);
  // Design variable declaration
  double indicator_height = 4;
  double indicator_bar_width = screen_width - 4;
  double green_indicator = (MAX_SAFETY_LIMIT * indicator_bar_width) / MAX_HAZARDOUS_LIMIT;
  double warning_indicator = ((MAX_WARNING_LIMIT - MAX_SAFETY_LIMIT) * indicator_bar_width) / MAX_HAZARDOUS_LIMIT;
  double severe_indicator = ((MAX_UNHEALTHY_LIMIT - MAX_WARNING_LIMIT) * indicator_bar_width) / MAX_HAZARDOUS_LIMIT;
  double danger_indicator = ((MAX_HAZARDOUS_LIMIT - MAX_UNHEALTHY_LIMIT) * indicator_bar_width) / MAX_HAZARDOUS_LIMIT;
  uint8_t indicator_x_starting_pos = 2;
  uint8_t indicator_y_starting_pos = (screen_height / 2) + 32;
  uint8_t green_indicator_height = (uint8_t)green_indicator;
  uint8_t warning_indicator_height = (uint8_t)warning_indicator;
  uint8_t severe_indicator_height = (uint8_t)severe_indicator;
  uint8_t danger_indicator_height = (uint8_t)danger_indicator;
  uint8_t seperation_line_height = 25;

  // Writing Company Logo
  screen.stroke(WHITE_COLOR);
  screen.setTextSize(2);
  screen.text(company_name, 2, MARGIN_BUFFER);

  // Drawing seperation line
  screen.stroke(GREY_COLOR);
  screen.line(0, seperation_line_height, (screen_width / 2) - 15, seperation_line_height);
  screen.setTextSize(1);
  screen.text("CO2", (screen_width / 2) - 10, seperation_line_height - 3);
  screen.line((screen_width / 2) + 15, seperation_line_height, screen_width, seperation_line_height);

  // Drawing the indicator Bar
  screen.stroke(GREEN_COLOR);
  screen.fill(GREEN_COLOR);
  screen.rect(indicator_x_starting_pos, indicator_y_starting_pos, green_indicator_height, indicator_height);
  screen.stroke(YELLOW_COLOR);
  screen.fill(YELLOW_COLOR);
  screen.rect(indicator_x_starting_pos + green_indicator_height, indicator_y_starting_pos, warning_indicator_height, indicator_height);
  screen.stroke(ORANGE_COLOR);
  screen.fill(ORANGE_COLOR);
  screen.rect(indicator_x_starting_pos + green_indicator_height + warning_indicator_height, indicator_y_starting_pos, severe_indicator_height, indicator_height);
  screen.stroke(RED_COLOR);
  screen.fill(RED_COLOR);
  screen.rect(indicator_x_starting_pos + green_indicator_height + warning_indicator_height + severe_indicator_height, indicator_y_starting_pos, danger_indicator_height, indicator_height);
  bool first_boot = true;
  while (1)
  {
    if ((digitalRead(INT_PIN) == LOW) || change_screen_flag)
    {
      change_screen();
      break;
    }

    if (((millis()) - last_millis > GRAPH_PLOT_TIME) || first_boot)
    {
      first_boot = false;
      Serial.println();
      // Calculating values for the design
      int arrow_x_position = 0;
      collect_co2_values();
      collect_temperature_and_humidity_values();
      Serial.println("Values Fetched");
      String co2_str = (String)CO2;
      strcpy(co2_value, co2_str.c_str());
      String temp_str = (String)temp;
      strcpy(temp_value, temp_str.c_str());
      String humi_str = (String)humd + "%";
      strcpy(humi_value, humi_str.c_str());
      Serial.println("Label CO2: " + (String)co2_value);
      Serial.println("Label Temp: " + (String)temp_value);
      Serial.println("Label Humd: " + (String)humi_value);

      if (CO2 < MAX_HAZARDOUS_LIMIT)
        arrow_x_position = indicator_x_starting_pos + (CO2 * indicator_bar_width / MAX_HAZARDOUS_LIMIT);
      else
        arrow_x_position = indicator_x_starting_pos + indicator_bar_width;
      int arrow_y_position = indicator_y_starting_pos - 5;

      drawing_battery(); // Drawing Header: Battery Percentage
      screen.noStroke();

      // Clearing previous values
      screen.stroke(BLACK_COLOR);
      screen.fill(BLACK_COLOR);
      screen.rect(0, arrow_y_position - 9, screen_width, 10);
      screen.rect(0, indicator_y_starting_pos + indicator_height + 5, screen_width, 8);
      screen.rect(0, screen_height - 20, screen_width, 16);

      // Drawing The circle with latest values
      screen.setTextSize(1);
      if (CO2 < MAX_SAFETY_LIMIT)
      {
        screen.stroke(GREEN_COLOR);
        screen.fill(GREEN_COLOR);
        screen.text("SAFE", indicator_x_starting_pos, indicator_y_starting_pos + indicator_height + 5);
      }
      else if (CO2 < MAX_WARNING_LIMIT)
      {
        screen.stroke(YELLOW_COLOR);
        screen.fill(YELLOW_COLOR);
        screen.text("MODERATE", indicator_x_starting_pos, indicator_y_starting_pos + indicator_height + 5);
      }
      else if (CO2 < MAX_UNHEALTHY_LIMIT)
      {
        screen.stroke(ORANGE_COLOR);
        screen.fill(ORANGE_COLOR);
        screen.text("UNHEALTHY", indicator_x_starting_pos, indicator_y_starting_pos + indicator_height + 5);
      }
      else
      {
        screen.stroke(RED_COLOR);
        screen.fill(RED_COLOR);
        screen.text("HAZARDOUS", indicator_x_starting_pos, indicator_y_starting_pos + indicator_height + 5);
      }
      screen.circle(screen_width / 2, (screen_height / 2) - 15, screen_width / 4);

      // Draw the indicator arrow
      screen.line(arrow_x_position, arrow_y_position, arrow_x_position - 4, arrow_y_position - 8);
      screen.line(arrow_x_position, arrow_y_position, arrow_x_position + 4, arrow_y_position - 8);
      screen.line(arrow_x_position - 4, arrow_y_position - 8, arrow_x_position + 4, arrow_y_position - 8);

      // Writing the text on the circle
      screen.setTextSize(2);
      screen.stroke(BLACK_COLOR);
      screen.text(co2_value, (screen_width / 2) - 20, (screen_height / 2) - 20);
      screen.setTextSize(1);
      screen.text("ppm", (screen_width / 2) - 10, (screen_height / 2) + 2);

      // Writing Temperature and Humidity Values
      screen.setTextSize(1);
      screen.stroke(GREY_COLOR);
      screen.text("T:", (screen_width / 4) - 32, screen_height - 20);
      screen.text(temp_value, (screen_width / 4) - 20, screen_height - 20);
      screen.text(".", (screen_width / 4) - 10, screen_height - 28);
      screen.text("C", (screen_width / 4) - 6, screen_height - 20);
      screen.text("H:", ((3 * screen_width) / 4) - 12, screen_height - 20);
      screen.text(humi_value, ((3 * screen_width) / 4), screen_height - 20);
      last_millis = millis();
    }
  }
}

/**
 * @brief Draws the background to plot the values of PM 2.5
 */
void draw_graph_screen(void)
{
  Serial.println("Draw Graph Background");
  collect_co2_values();

  screen.background(BLACK_COLOR);
  screen.stroke(GREY_COLOR);
  screen.line(GRAPH_BUFFER_SCREEN, GRAPH_BUFFER_SCREEN, GRAPH_BUFFER_SCREEN, screen_height - GRAPH_BUFFER_SCREEN);
  screen.line(GRAPH_BUFFER_SCREEN, screen_height - GRAPH_BUFFER_SCREEN, screen_width - GRAPH_BUFFER_SCREEN, screen_height - GRAPH_BUFFER_SCREEN);
  int x_dots = ((screen_width - (2 * GRAPH_BUFFER_SCREEN)) / GRAPH_BUFFER_SCREEN + 1);
  int y_dots = ((screen_height - (2 * GRAPH_BUFFER_SCREEN)) / GRAPH_BUFFER_SCREEN) + 1;
  for (size_t i = 0; i < y_dots; i++)
    for (size_t j = 0; j < x_dots; j++)
      screen.point((j * GRAPH_BUFFER_SCREEN) + GRAPH_BUFFER_SCREEN, (i * GRAPH_BUFFER_SCREEN) + GRAPH_BUFFER_SCREEN);

  screen.stroke(WHITE_COLOR);
  screen.setTextSize(1);
  screen.text("CO2", screen_width - 40, 10);
  screen.text("500 divs", 1, 1);
  screen.text("5 mins", screen_width - 40, screen_height - 10);
  for (size_t i = 0; i < (y_dots / 2) + 1; i++)
    screen.line(GRAPH_BUFFER_SCREEN, screen_height - (2 * i * GRAPH_BUFFER_SCREEN) - GRAPH_BUFFER_SCREEN, GRAPH_BUFFER_SCREEN / 2, screen_height - (2 * i * GRAPH_BUFFER_SCREEN) - GRAPH_BUFFER_SCREEN);
  for (size_t i = 0; i < (x_dots / 2); i++)
    screen.line((2 * i * GRAPH_BUFFER_SCREEN) + GRAPH_BUFFER_SCREEN, screen_height - GRAPH_BUFFER_SCREEN, (2 * i * GRAPH_BUFFER_SCREEN) + GRAPH_BUFFER_SCREEN, screen_height - (GRAPH_BUFFER_SCREEN / 2));
}

/**
 * @brief Plots the graph bars corresponding to value of PM 2.5 after drawing the graph background
 */
void plot_graph_bar(void)
{
  draw_graph_screen();
  change_screen_flag = false;
  Serial.println("Plot Graph");
  last_millis = millis();
  int x_levels = ((screen_width - (2 * GRAPH_BUFFER_SCREEN)) / GRAPH_BUFFER_SCREEN) / 2;
  int y_levels = ((screen_height - (2 * GRAPH_BUFFER_SCREEN)) / (GRAPH_BUFFER_SCREEN * 2));
  int last_graph_position = 0;
  float graph_divisions = 500;
  float scaling_factor = screen_height / (y_levels * graph_divisions);
  screen.stroke(BLACK_COLOR);

  int x_last_pos, y_last_pos;

  while (last_graph_position <= x_levels)
  {
    if (last_graph_position == x_levels)
    {
      draw_graph_screen();
      last_graph_position = 0;
    }

    if ((digitalRead(INT_PIN) == LOW) || change_screen_flag)
    {
      change_screen();
      break;
    }

    collect_co2_values();

    if ((((millis() - last_millis) > GRAPH_PLOT_TIME) || (last_graph_position == 0)) && (CO2 > 10))
    {
      Serial.println("CO2: " + (String)CO2);
      // Calculating Bar Values
      int scaled_value = 0;
      int height = 0;
      if (CO2 < MAX_HAZARDOUS_LIMIT)
      {
        scaled_value = CO2 * scaling_factor;
        height = scaled_value;
      }
      else
      {
        scaled_value = screen_height - (2 * GRAPH_BUFFER_SCREEN);
        height = screen_height - (2 * GRAPH_BUFFER_SCREEN);
      }
      int x_pos = GRAPH_BUFFER_SCREEN + (2 * GRAPH_BUFFER_SCREEN * last_graph_position) + 1;
      int y_pos = screen_height - GRAPH_BUFFER_SCREEN - scaled_value;
      int width = (2 * GRAPH_BUFFER_SCREEN) - 1;

      if (CO2 < MAX_SAFETY_LIMIT)
        screen.fill(GREEN_COLOR);
      else if (CO2 < MAX_WARNING_LIMIT)
        screen.fill(YELLOW_COLOR);
      else if (CO2 < MAX_UNHEALTHY_LIMIT)
        screen.fill(ORANGE_COLOR);
      else
        screen.fill(RED_COLOR);
      screen.stroke(BLACK_COLOR);
      screen.rect(x_pos, y_pos, width, height);

      if (last_graph_position == 0)
      {
        x_last_pos = x_pos + (width / 2);
        y_last_pos = y_pos;
      }
      else
      {
        x_pos = x_pos + (width / 2);
        screen.fill(WHITE_COLOR);
        screen.stroke(WHITE_COLOR);
        screen.circle(x_last_pos, y_last_pos, 2);
        screen.circle(x_pos, y_pos, 2);
        screen.line(x_last_pos, y_last_pos, x_pos, y_pos);
        x_last_pos = x_pos;
        y_last_pos = y_pos;
      }

      last_millis = millis();
      last_graph_position++;
    }
  }
}

/**
 * @brief Draws the battery level after measuring the battery level on the screen in upper right corner of screen when called.
 */
void drawing_battery(void)
{
  int xStart = screen_width - BATTERY_SYMBOL_WIDTH - MARGIN_BUFFER;
  int yStart = MARGIN_BUFFER;
  // Clearing previous battery value
  screen.noStroke();
  screen.fill(BLACK_COLOR);
  screen.rect(xStart, yStart, BATTERY_SYMBOL_WIDTH, BATTERY_SYMBOL_HEIGHT);
  // Creating battery Outline
  screen.stroke(WHITE_COLOR);
  screen.rect(xStart, yStart, BATTERY_SYMBOL_WIDTH, BATTERY_SYMBOL_HEIGHT);
  screen.fill(WHITE_COLOR);
  screen.rect(xStart + BATTERY_SYMBOL_WIDTH, yStart + MARGIN_BUFFER, MARGIN_BUFFER, (BATTERY_SYMBOL_HEIGHT - (2 * MARGIN_BUFFER)));

  // Creating Battery Fill
  float val1 = (analogRead(BATTERY_INPUT) - MIN_BATTERY_ADC_VALUE);
  float available_battery_percentage = (val1 * 100) / MAX_BATTERY_ADC_VALUE;
  // Serial.println("Raw Battery Analog value:" + (String)analogRead(BATTERY_INPUT));
  // Serial.println("Battery Level: " + (String)available_battery_percentage);
  float bat_bar_width = (available_battery_percentage * BATTERY_SYMBOL_WIDTH) / 100;
  int battery_bar_width = bat_bar_width;
  // Serial.println("Integer Bar Width:" + (String)battery_bar_width);
  screen.noStroke();

  if (available_battery_percentage < LOW_BATTERY_PERCENT)
    screen.fill(RED_COLOR);
  else if (available_battery_percentage < MEDIUM_BATTERY_PERCENT)
    screen.fill(ORANGE_COLOR);
  else
    screen.fill(GREEN_COLOR);
  screen.rect(xStart + 1, yStart + 1, battery_bar_width - 2, BATTERY_SYMBOL_HEIGHT - 2);
  if (analogRead(CONNECTED_SUPPLY_PIN) > SUPPLY_CONNECTED_MIN_ADC_VALUE)
  {
    // Serial.println("Charger Connected");
    int batxStart = screen_width - (BATTERY_SYMBOL_WIDTH / 2) - MARGIN_BUFFER;
    int batyStart = MARGIN_BUFFER + 1;
    int bat_symbol_width = 2;
    screen.stroke(WHITE_COLOR);
    screen.line(batxStart, batyStart, batxStart - bat_symbol_width, batyStart + (BATTERY_SYMBOL_HEIGHT / 2));
    screen.line(batxStart - bat_symbol_width, batyStart + (BATTERY_SYMBOL_HEIGHT / 2) - 1, batxStart + bat_symbol_width, batyStart + (BATTERY_SYMBOL_HEIGHT / 2) - 1);
    screen.line(batxStart + bat_symbol_width, batyStart + (BATTERY_SYMBOL_HEIGHT / 2) - 1, batxStart, batyStart + BATTERY_SYMBOL_HEIGHT - 2);
    screen.line(batxStart, batyStart + BATTERY_SYMBOL_HEIGHT - 2, batxStart, batyStart);
  }
}

void put_device_to_sleep(void)
{
  Serial.println("Entering Sleep mode");
  boot_screen();
  delay(5000);
  stop_device_peripherals();
  screen_counter = 0;
  change_screen_flag = false;
  cli();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  Serial.println("Placing Device in sleep mode");
  Serial.flush();
  attachInterrupt(digitalPinToInterrupt(INT_PIN), change_screen, LOW);
  interrupts();
  sleep_cpu();
}

void change_screen(void)
{
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(INT_PIN));
  Serial.println("Button pressed");
  delay(500);

  change_screen_flag = true;
  uint64_t sleep_timer = millis();
  while (digitalRead(INT_PIN) == LOW)
    if ((millis() - sleep_timer) > 2000)
    {
      screen_counter = 3;
      return;
    }

  if (screen_counter < 2)
    screen_counter++;
  else
    screen_counter = 1;
  return;
}

void stop_device_peripherals(void)
{
  Serial.println("Stopping Device Peripherals");
  digitalWrite(TFT_DISPLAY_LED, LOW);
}
//!==================================================================================//

void setup()
{
  Serial.begin(9600);
  Serial.println("\n\n\n----------------------------------------------------------------------------------------");
  Serial.println("Starting Device");
  setup_sensors();
  setup_peripheral_pin_mode();
  Serial.println("Setup Done");
}

void loop()
{
  switch (screen_counter)
  {
  case 1:
    Serial.println("\n----------------------------------------------------------------------------------------");
    graphic_data_screen();
    break;

  case 2:
    Serial.println("\n----------------------------------------------------------------------------------------");
    plot_graph_bar();
    break;

  case 3:
    Serial.println("\n----------------------------------------------------------------------------------------");
    put_device_to_sleep();
    break;
  }
}