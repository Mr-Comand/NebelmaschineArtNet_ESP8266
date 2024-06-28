#include <ArtnetWiFi.h>
#include <EEPROM.h>

ArtnetWiFiReceiver artnet;
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <cstdint>

#define relayPin 14
#define resetPin 2
#define statusLED LED_BUILTIN
#define artnetTimeout 10000
#define otaPassword ""

long old_time = 0;
int fireduration = 0;
bool fired = false;

bool disableWebFire=false;
bool disableWebSettings=false;
bool dualChenelMode=true;

char ssids[4][33] = { "Ne", "", "", "Fock-Mashine" };
char passwords[4][64]{ "12345678", "", "", "Fock-Mashine" };
char shortname[19] = "ESP-Nebel";
char longname[65] = "Große Nebelmaschine";

uint16_t Address = 0;
uint8_t Univers = 0;

long last_artnet = 0;

unsigned long previousMillis = 0;  // Variable, um die letzte Ausführungszeit zu speichern

WiFiUDP Udp;
WiFiClient client;
const int localPort = 6454;
bool APmode = false;
void callback_artnet(const uint8_t *data, const uint16_t size) {
  if (fireduration <= 0) {
    digitalWrite(relayPin, (data[Address] > 128));
  }
  if(dualChenelMode){
   disableWebFire = (data[Address+1] > 128);
   disableWebSettings = ((data[Address+1] > 192)||((data[Address+1] <= 128)&&(data[Address+1] > 64)));
  }else{
    disableWebFire=false;
    disableWebSettings=false;
  }
  flash();
  last_artnet=millis();
}


void setup() {
  writeDataToEEPROM();
  pinMode(resetPin, INPUT_PULLUP);
  //writeDataToEEPROM();
  if (digitalRead(resetPin) == LOW) {
    writeDataToEEPROM(); // Annahme: nreset ist eine definierte Funktion
  }
  pinMode(relayPin, OUTPUT);
  pinMode(statusLED, OUTPUT);
  digitalWrite(statusLED, 1);

  // setup Ethernet/WiFi...
  Serial.begin(115200);
  readDataFromEEPROM();
  Serial.println("SSIDs:");
  for (int i = 0; i < 4; ++i) {
    Serial.println(ssids[i]);
  }

  Serial.println("Passwords:");
  for (int i = 0; i < 4; ++i) {
    Serial.println(passwords[i]);
  }
  Serial.println("Address: " + String(Address));
  Serial.println("Univers: " + String(Univers));
  Serial.println("shortname: " + String(shortname));
  Serial.println("longname: " + String(longname));
  
  //
  WiFi.hostname(shortname);
  bool connected = false;
  for (int i = 0; i < 3; ++i) {
    connected = connectToWiFi(ssids[i], passwords[i]);
    if (connected) {
      break;
    }
  }
  if (!connected) {
    WiFi.disconnect();
    Serial.println("ap Mode");
    APmode = true;
     setup_web_AP(ssids[3], passwords[3]);
  } else {
    setup_web();
  }
  delay(500);
  artnet.begin();  // waiting for Art-Net in default port
  // artnet.begin(net, subnet); // optionally you can set net and subnet here
  // if Artnet packet comes to this universe(0-15), this function is called
  artnet.shortname(shortname);
  artnet.longname(shortname);
  artnet.subscribe(Univers, callback_artnet);  // you can also use pre-defined callbacks
  
  setup_ota();
}

void loop() {
  artnet.parse();  // check if artnet packet has come and execute callback


  loop_ota();
  loop_web();
  if (fireduration > 0) {
    fireduration = fireduration - (millis() - old_time);
    fired = true;
    digitalWrite(relayPin, 1);
  } else if (fired) {
    digitalWrite(relayPin, 0);
    fired = false;
  }
  if (fireduration<=0 && artnetTimeout < (millis() - last_artnet)){
        digitalWrite(relayPin, 0);

  }
  old_time = millis();
}


bool connectToWiFi(String ssid, String password) {
  if (ssid == "") return false;
  //Connect to WiFi Network
  Serial.println();
  Serial.println();

  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("...");
  WiFi.begin(ssid, password);
  int retries = 0;
  digitalWrite(statusLED, 0);

  while ((WiFi.status() != WL_CONNECTED) && (retries < 30)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  if ((WiFi.status() != WL_CONNECTED)) {
    Serial.println(F("WiFi connection FAILED"));
    delay(100);
    flash();
    delay(100);
    flash();
    delay(500);
    WiFi.disconnect();
    return false;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi connected!"));
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAc address: ");
    Serial.println(WiFi.macAddress());
    digitalWrite(statusLED, 1);
    delay(100);
    digitalWrite(statusLED, 0);
    delay(500);
    digitalWrite(statusLED, 1);
    delay(500);
    return true;
  }
  return false;
}



void flash() {
  digitalWrite(statusLED, 0);
  delay(10);
  digitalWrite(statusLED, 1);
}