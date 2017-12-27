#include <Wire.h>                   // RTC Stuff
#include "RTClib.h"
#include <Adafruit_GFX.h>           // LED Backpack Stuff
#include "Adafruit_LEDBackpack.h"

// The two components attached to the arduino
RTC_DS1307 rtc;
Adafruit_AlphaNum4 alpha4;

// Constants
long ONE_DAY = 86400;
long DAY_LDR_STARTED = 1501718400;


void setup() {
  Serial.begin(9600);
  alpha4.begin(0x70);
  Serial.println("Starting right now!");
}

void loop() {
  DateTime now = rtc.now();
  long current_time = now.unixtime();
  int days_since_ldr_started = (current_time - DAY_LDR_STARTED) / ONE_DAY;

  displayDaysSince(days_since_ldr_started);
  delay(300);
}

void displayDaysSince(int days_since_ldr_started) {
  char char_buffer[4];
  char * to_print = itoa(days_since_ldr_started, char_buffer, 10);
  int print_length = strlen(to_print);
  int start_screen = 4 - print_length; // Flip alpha4 places

  clearDisplay();

  int current_character = 0;
  for(int current_screen = start_screen; current_screen < 4; current_screen++) {
    alpha4.writeDigitAscii(current_screen, to_print[current_character]);
    current_character += 1;
  }

  // Flush to display
  alpha4.writeDisplay();
}

void clearDisplay() {
  alpha4.writeDigitAscii(0, ' ');
  alpha4.writeDigitAscii(1, ' ');
  alpha4.writeDigitAscii(2, ' ');
  alpha4.writeDigitAscii(3, ' ');
}
