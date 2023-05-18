#include <Arduino.h>
#include <FS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define led 13
#define ldr A0

int vlrd = 0;

const char* ssid = "A&MLuans";
const char* password = "a&mluans000408";
 
String webPage = "";
String stylePage = "";
String scriptPage = "";
 
ESP8266WebServer server(80);
 
void handleRoot() {
  server.send(200, "text/html", webPage);
}

void handle_ldr(){
  vlrd = analogRead(ldr);
  if(vlrd > 50){
    digitalWrite(led, LOW);
  }else{
    digitalWrite(led, HIGH);
  }
}

void handle_led_on(){
  digitalWrite(led, HIGH);
}

void handle_led_off(){
  digitalWrite(led, LOW);
}

void handleRootS(){
  server.send(200, "text/css", stylePage);
}

void handleRootJS(){
  server.send(200, "text/javascript", scriptPage);
}
 
void readFile(void) {
  //Faz a leitura do arquivo HTML
  File rFile = SPIFFS.open("/index.html","r");
  Serial.println("Lendo arquivo HTML...");
  webPage = rFile.readString();
  Serial.println(webPage);
  rFile.close();  
}

void readFileS(void){
  File rFile = SPIFFS.open("/style.css","r");
  Serial.println("Lendo arquivo css...");
  stylePage = rFile.readString();
  Serial.println(stylePage);
  rFile.close();
}

void readFileJS(void){
  File rFile = SPIFFS.open("/script.js","r");
  Serial.println("Lendo arquivo script...");
  scriptPage = rFile.readString();
  Serial.println(scriptPage);
  rFile.close();
}
 
void setup() {
  Serial.begin(9600);
  SPIFFS.begin();

  pinMode(led, OUTPUT);

  digitalWrite(led, HIGH);
 
  if(SPIFFS.exists("/index.html")){
    Serial.println("\n\nfile exists!");
  }else {
    Serial.println("\n\nNo File :(");
  }
 
  readFile();
  readFileS();
  readFileJS();
  
  WiFi.begin(ssid, password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRoot);
  server.on("/style.css", handleRootS);
  server.on("/script.js", handleRootJS);
  server.on("/led5_on", handle_led_on);
  server.on("/led5_off", handle_led_off);
  server.on("/ldr", handle_ldr);

  server.begin();
}
 
void loop() {
    server.handleClient();
    //Serial.println(analogRead(ldr));
}
