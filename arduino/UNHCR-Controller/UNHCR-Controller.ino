/* UNHCR-controller

Laurent Pitoiset 2015

 display latest application messages from UNHCR data portal API
 
 needed: arduino uno / ethernet shield / lcd display
 
 */

// include

#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h> 

// application parameters

boolean apiCall = false;

// init
boolean proxyRouting = true; // true for proxy
String reply = "";  // returned by web server
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char proxyserver[] = "proxy.unhcr.local";    // 

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,0,177);

// Initialize the Ethernet client library
EthernetClient client;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

void setup() {
  // set up the lcd display
  lcd.clear();
  lcd.begin(16, 2); 
  lcd.print("ASR Controller");
  lcd.setCursor(0, 1);
  lcd.print("...");
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  */
  if (apiCall) 
  {
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
    if (client.connect(proxyserver, 8080)) {
      Serial.println("connected");
      lcd.setCursor(0, 1);
      lcd.print("connected");
      // Make a HTTP request:
      client.println("GET http://data.unhcr.org/api/stats/persons_of_concern.json?year=2013&country_of_origin=AFG&country_of_residence=PAK HTTP/1.0");
      client.println("Connection: close");
      lcd.setCursor(0, 1);
      lcd.print("conn. closed");
      client.println();
    } 
    else {
      // kf you didn't get a connection to the server:
      Serial.println("conn. failed");
      lcd.setCursor(0, 1);
      lcd.print("conn. failed");
    }
  }
}




// loop
void loop() {

  if (apiCall) 
  {
    // if there are incoming bytes available 
    // from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
      reply = String(reply + c);
    }
  }
  //char json[] = "[{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}, {\"sensor\":\"gps\",\"time\":1351824140,\"data\":[50.756080,21.302038]}]";
  //char json[] ="{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  //char json[] = "[{\"year\":\"2013\",\"country_of_residence\":\"PAK\",\"country_of_residence_en\":\"Pakistan\",\"country_of_origin\":\"AFG\",\"country_of_origin_en\":\"Afghanistan\",\"refugees\":\"1615876\",\"asylum_seekers\":\"5323\",\"returned_refugees\":null,\"idps\":null,\"returned_idps\":null,\"stateless_persons\":null,\"others_of_concern\":null,\"total_population\":\"1621199\"} , {\"year\":\"2014\",\"country_of_residence\":\"PAK\",\"country_of_residence_en\":\"Pakistan\",\"country_of_origin\":\"AFG\",\"country_of_origin_en\":\"Afghanistan\",\"refugees\":\"1615876\",\"asylum_seekers\":\"5323\",\"returned_refugees\":null,\"idps\":null,\"returned_idps\":null,\"stateless_persons\":null,\"others_of_concern\":null,\"total_population\":\"1621199\"}]";
  char json[] = "[{\"year\":\"2013\",\"country_of_residence\":\"PAK\"}]";
  //char json[] = "[{\"year\":\"2013\"}, {\"year\":\"2014\"}]";

  StaticJsonBuffer<200> jsonBuffer;
  //JsonObject& root = jsonBuffer.parseObject(json);
  JsonArray& root = jsonBuffer.parseArray(json);

  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

  //JsonObject row = root.get(0);

  /*
const char* sensor = root["sensor"];
   long time          = root["time"];
   double latitude    = root["data"][0];
   double longitude   = root["data"][1];
   */

  const char* json_year = root[0]["year"];
  //Serial.println(String(root));
  Serial.println(json_year);
  //const char* json_year2 = root[1]["year"];
  
  const char* json_CoR = root[0]["country_of_residence"];
   //const char* json_CoO = root[0]["country_of_origin"];
   //const char* json_refugees = root[0]["refugees"];
   //const char* json_total = root["total_population"];
   
  lcd.clear();
  // lcd.print(reply);
  lcd.setCursor(0,0);
  //lcd.print(String(json_year)+" "+String(json_CoO)+" -> "+String(json_CoR));
  lcd.setCursor(0,1);
  //lcd.print(String("R "+String(json_refugees)));
  lcd.print(String(json_year));
  // do nothing forevermore:
  while(true);

}





