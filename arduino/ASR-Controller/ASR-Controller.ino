/* Laurent Pitoiset 2015
 
 ASR controller
 display latest application messages from ASR application
 
 needed: arduino uno / ethernet shield / lcd display
 */

// include

#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>
// initialize

#define lcdDisplay  1; // 1 for 2*16 lcd display
boolean newMessage  =  false;


// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "proxy.unhcr.local";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,0,177);

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
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
  lcd.print("AFG table1 saved");
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

  // if you get a connection, report back via serial:
  if (client.connect(server, 8080)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}




// loop
void loop() {

  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while(true);
  }

  delay(5000);


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

