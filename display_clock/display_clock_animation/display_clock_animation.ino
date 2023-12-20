#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32 // Adjusted for 128x32 display
#define SCROLL_SPEED 1   // Adjust the scroll speed

#define SSD1306_I2C_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
RTC_DS3231 myRTC;

void setup() {
  Wire.begin();

  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();

  // Initialize the RTC
  if (!myRTC.begin()) {
    Serial.println(F("Couldn't find RTC"));
    while (1);
  }

  if (myRTC.lostPower()) {
    Serial.println(F("RTC lost power, let's set the time!"));
    myRTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}



void loop() {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("scroll"));
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(5000);
  display.stopscroll();
}
