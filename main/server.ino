
#include <ESP8266WiFi.h>
#include <DNSServer.h> 
#include <ESP8266WebServer.h>
#include "index_html.h"
#include "main_css.h"
#include "main_js.h"


const byte HTTP_CODE = 200;
const byte DNS_PORT = 53;

IPAddress APIP(10, 70, 79, 71); // Gateway ip
DNSServer dnsServer; ESP8266WebServer webServer(80);

unsigned long bootTime=0, lastActivity=0, tickCtr=0;

void setup_web_AP(String SSID_NAME, String password)
{
    bootTime = lastActivity = millis();
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(APIP, APIP, IPAddress(255, 0, 0, 0));
    WiFi.softAP(SSID_NAME, password);

    dnsServer.start(DNS_PORT, "*", APIP); // DNS spoofing (Only HTTP)
    setup_web();
}


void loop_web()
{
  
    dnsServer.processNextRequest();
    webServer.handleClient();
}


String input(String argName) {
    String a=webServer.arg(argName);
    a.replace("<","&lt;");a.replace(">","&gt;");
    a.substring(0,200); return a; 
  }
String wlan(int id) {
    strcpy(ssids[id], input("ssid").c_str());
    strcpy(passwords[id], input("pwd").c_str());
    writeDataToEEPROM();
    return "\"OK\"";
}
String ap() {
    strcpy(ssids[3], input("ssid").c_str());
    strcpy(passwords[3], input("pwd").c_str());
    writeDataToEEPROM();
    return "\"OK\"";
}

String getData() {
  
  return "[\""+String(ssids[0])+"\",\""+String(ssids[1])+"\",\""+String(ssids[2])+"\",\""+String(ssids[3])+"\"]";
}
String getPwd() {
  
  return "[\""+String(passwords[0])+"\",\""+String(passwords[1])+"\",\""+String(passwords[2])+"\",\""+String(passwords[3])+"\"]";
}

String fire(){
  if(disableWebFire) return "\"disabled\"";
  fireduration = input("time").toInt();
  fired=true;
  return "\"OK\"";
}

String getArtnet(){
  return "[\""+String(Address)+"\",\""+String(Univers)+"\",\""+String(shortname)+"\",\""+String(longname)+"\",\""+String(channelMode)+"\"]";
}
String putArtnet(){
  if (disableWebSettings) return "\"disabled\"";
  int univers_new = input("univers").toInt();
  if(univers_new != Univers){
    artnet.unsubscribe(Univers);
    digitalWrite(relayPin, 0);

    Univers = univers_new;
    artnet.subscribe(Univers, callback_artnet);
  } else{
    Univers = univers_new;
  }
  Address =  input("address").toInt();
  strcpy(shortname, input("shortname").c_str());
  strcpy(longname, input("longname").c_str());
  artnet.shortname(shortname);
  artnet.longname(shortname);
  channelMode = input("channelMode").toInt();
  writeDataToEEPROM();
  return "\"OK\"";
}

String ping(){
    return "[\""+String(disableWebSettings)+"\",\""+String(disableWebFire)+"\",\""+String(intervalActive)+"\","+period+","+dutyCycle+"]";
}
  
String interval(){
  if(disableWebFire) return "\"disabled\"";
  period = input("period").toInt();
  dutyCycle = input("dutyCycle").toInt();
  bool newIntervalActive = (input("active").toInt()==1);
  if (intervalActive && !newIntervalActive){
    digitalWrite(relayPin, 0);
  }
  intervalActive = newIntervalActive;
  return String(intervalActive);
}



void setup_web()
{
    webServer.onNotFound([]() { lastActivity=millis(); webServer.send(HTTP_CODE, "text/html", index_html_code); flash();});
    webServer.on("/main.css",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(HTTP_CODE, "text/css", main_css_code); flash();});
    webServer.on("/main.js",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(HTTP_CODE, "application/javascript", main_js_code); flash();});
    webServer.on("/wlan1",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(HTTP_CODE, "text/html", wlan(0)); flash();});
    webServer.on("/wlan2",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(HTTP_CODE, "text/html", wlan(1)); flash();});
    webServer.on("/wlan3",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(HTTP_CODE, "text/html", wlan(2)); flash();});
    webServer.on("/ap",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(HTTP_CODE, "text/html", ap()); flash();});
    
    webServer.on("/getData",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(HTTP_CODE, "application/json", getData()); flash();});
    webServer.on("/getPwd",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(HTTP_CODE, "application/json", getPwd()); flash();});
    webServer.on("/getArtnet",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(HTTP_CODE, "application/json", getArtnet()); flash();});

    webServer.on("/fire",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(disableWebFire ? 423 : 200, "application/json", fire()); flash();});
    webServer.on("/putArtnet",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(disableWebSettings? 423 : 200, "application/json", putArtnet()); flash();});
    webServer.on("/ping",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(HTTP_CODE, "application/json", ping());flash();});
    webServer.on("/interval",[]() { webServer.sendHeader("Access-Control-Allow-Origin", "*"); webServer.send(disableWebFire ? 423 : 200, "application/json", interval()); flash();});

    webServer.begin();
}


