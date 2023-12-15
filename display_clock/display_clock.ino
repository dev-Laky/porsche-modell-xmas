#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DS3231.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32 // Adjusted for 128x32 display

#define SSD1306_I2C_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

DS3231 myRTC;

bool century = false;
bool h12Flag;
bool pmFlag;

void setup() {
  Serial.begin(57600);
  Wire.begin();

  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) { // Adjust the I2C address based on your display
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display(); // Initialize the display with default settings (address 0x3C)

  delay(2000); // Pause for 2 seconds

  display.clearDisplay();
}

void loop() {
  delay(1000);

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print(myRTC.getYear(), DEC);
  display.print("-");
  display.print(myRTC.getMonth(century), DEC);
  display.print("-");
  display.print(myRTC.getDate(), DEC);
  display.print(" ");
  display.print(myRTC.getHour(h12Flag, pmFlag), DEC);
  display.print(":");
  display.print(myRTC.getMinute(), DEC);
  display.print(":");
  display.println(myRTC.getSecond(), DEC);

  display.display();
}
