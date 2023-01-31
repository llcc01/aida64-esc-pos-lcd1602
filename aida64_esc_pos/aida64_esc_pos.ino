
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

#define LCD_RS D8
#define LCD_EN D7
#define LCD_D4 D4
#define LCD_D5 D3
#define LCD_D6 D2
#define LCD_D7 D1
#define LCD_LED D6

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  pinMode(LCD_LED, OUTPUT);
  digitalWrite(LCD_LED, HIGH);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  Serial.begin(9600);
}

void loop() {
  // static int pos = 0;
  // static int brightness = 4;
  if (Serial.available()) {
    int ch = Serial.read();
    // lcd.setCursor(0, 1);
    // lcd.printf("%02x", ch);
    if (ch == 0x1b) {
      ch = Serial.read();
      if (ch != 0x40) {
        return;
      }

      lcd.clear();

      char buffer[6] = { 0 };
      Serial.readBytes(buffer, 6);
      return;
    }

    if (ch == 0x1f) {
      while (!Serial.available())
        ;
      ch = Serial.read();
      // lcd.setCursor(2, 1);
      // lcd.printf("%02x", ch);

      if (ch == 0x58) {
        while (!Serial.available())
          ;
        ch = Serial.read();

        // analogWrite(LCD_LED, 256 / 4 * ch - 1);
        return;
      }

      return;
    }

    if (ch == 0x0c) {
      return;
    }


    static char buffer[40] = { 0 };
    buffer[0] = ch;
    Serial.readBytes(buffer + 1, 40 - 1);
    buffer[16] = '\0';
    buffer[20 + 16] = '\0';
    lcd.setCursor(0, 0);
    lcd.print(buffer);
    lcd.setCursor(0, 1);
    lcd.print(buffer + 20);
    return;
  }
}
