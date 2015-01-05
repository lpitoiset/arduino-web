/*

Laurent Pitoiset 2015

 Parts required:
 220 ohm resistor
 10 kilohm resistor
 10 kilohm potentiometer
 16x2 LCD screen
 tilt switch
 
 
 Created 13 September 2012
 by Scott Fitzgerald
 
 http://arduino.cc/starterKit
 
 This example code is part of the public domain 
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

void setup() {
  // set up the number of columns and rows on the LCD 
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  lcd.print("Line 1");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("Line 2");
}

void loop() {
    if (false) {
      // clean up the screen before printing a new reply
      lcd.clear();
      // set the cursor to column 0, line 0     
      lcd.setCursor(0, 0);
      // print some text
      lcd.print("the ball says:");
      // move the cursor to the second line
      lcd.setCursor(0, 1);

        lcd.print("Message");
  }
}

