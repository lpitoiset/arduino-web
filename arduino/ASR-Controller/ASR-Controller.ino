/* Laurent Pitoiset 2015
 
 ASR controller
 display latest application messages from ASR application
 
 needed: arduino uno / ethernet shield / lcd display
 
 lcd wiring
 */

// include

#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>
// initialize

int lcdDisplay  = 1; // 1 for 2*16 lcd display
boolean proxyRouting = true; // true for proxy
String reply = "";  // returned by web server

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "proxy.unhcr.local";    // 

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,0,177);

// Initialize the Ethernet client library
EthernetClient client;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

void setup() {
  // set up the lcd display
  // set up the number of columns and rows on the LCD 
  lcd.begin(16, 2); 
  // Print a message to the LCD.
  lcd.print("ASR Controller");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("...");
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
  lcd.setCursor(0, 1);
  lcd.print("connecting");

  // if you get a connection, report back via serial:
  if (client.connect(server, 8080)) {
    Serial.println("connected");
    lcd.setCursor(0, 1);
    lcd.print("connected");
    // Make a HTTP request:
    client.println("GET http://popdata.unhcr.org/ HTTP/1.0");
    client.println("Connection: close");
    lcd.setCursor(0, 1);
    lcd.print("connection closed");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
    lcd.setCursor(0, 1);
    lcd.print("connection failed");
  }
}




// loop
void loop() {

  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
    reply = String(reply + c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    lcd.clear();
    // lcd.print(reply);
    lcd.setCursor(0,0);
    lcd.print("ASR status 0-0-0");
    lcd.setCursor(0,1);
    lcd.print("AFG table1 saved");
    while(true);
  }
}


