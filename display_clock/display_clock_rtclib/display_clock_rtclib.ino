#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32 // Adjusted for 128x32 display

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

void displayDateTime() {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);

  DateTime now = myRTC.now();

  // Format the date as "dd.mm.yyyy"
  display.print(now.day(), DEC);
  display.print(".");
  display.print(now.month(), DEC);
  display.print(".");
  display.print(now.year(), DEC);

  display.print(" ");

  // Print the time
  
  // Print the time with leading zeros
  if (now.hour() < 10) {
    display.print("0");
  }
  display.print(now.hour(), DEC);
  display.print(":");

  if (now.minute() < 10) {
    display.print("0");
  }
  display.print(now.minute(), DEC);
  display.print(":");

  if (now.second() < 10) {
    display.print("0");
  }
  display.print(now.second(), DEC);

  display.display();
}

void loop() {
  delay(1000);

  displayDateTime(); // Update date and time on OLED display
}
