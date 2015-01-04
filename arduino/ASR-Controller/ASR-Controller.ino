/* Laurent Pitoiset 2015

ASR controller
display latest application messages from ASR application

needed: arduino uno / ethernet shield / lcd display
*/

// include

#include <LiquidCrystal.h>
// initialize

#define lcdDisplay  1; // 1 for 2*16 lcd display
boolean newMessage  =  false;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the lcd display
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
// loop
void loop() {
  
    if (newMessage) {
      // clean up the screen before printing a new reply
      lcd.clear();
      // set the cursor to column 0, line 0     
      lcd.setCursor(0, 0);
      // print some text
      lcd.print("ASR update:");
      // move the cursor to the second line
      lcd.setCursor(0, 1);

        lcd.print("Message");
    }
}
