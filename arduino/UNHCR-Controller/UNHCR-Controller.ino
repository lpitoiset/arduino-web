

// UNHCR-controller

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
#include <ArduinoJson.h> 
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
  
//char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
char json[] = "{\"year\":\"2013\",\"country_of_residence\":\"PAK\",\"country_of_residence_en\":\"Pakistan\",\"country_of_origin\":\"AFG\",\"country_of_origin_en\":\"Afghanistan\",\"refugees\":\"1615876\",\"asylum_seekers\":\"5323\",\"returned_refugees\":null,\"idps\":null,\"returned_idps\":null,\"stateless_persons\":null,\"others_of_concern\":null,\"total_population\":\"1621199\"}";
//char json[] = "{\"year\":\"2013\"}";
StaticJsonBuffer<200> jsonBuffer;

JsonObject& root = jsonBuffer.parseObject(json);
//JsonObject& root2 = jsonBuffer.parseArray(root);
/*
const char* sensor = root["sensor"];
long time          = root["time"];
double latitude    = root["data"][0];
double longitude   = root["data"][1];
*/

const char* json_year = root["year"];

    // do nothing forevermore:
    lcd.clear();
    // lcd.print(reply);
    lcd.setCursor(0,0);
    lcd.print("UNHCR API");
    lcd.setCursor(0,1);
    lcd.print(String("year "+String(json_year)));
    while(true);
  
}

