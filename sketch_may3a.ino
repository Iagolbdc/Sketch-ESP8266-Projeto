
#include <Arduino.h>
#include <FS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define led 2 //LED_BUILTIN

const char* ssid = "Rede01";
const char* password = "12345678";
 
String webPage = "";
String stylePage = "";
String scriptPage = "";
 
ESP8266WebServer server(80);
 
void handleRoot() {
  server.send(200, "text/html", webPage);
}

void handle_led_on(){
  digitalWrite(led, LOW);
}

void handle_led_off(){
  digitalWrite(led, HIGH);
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
 
  if(SPIFFS.exists("/index.html"))
  {
    Serial.println("\n\nfile exists!");
  }
  else Serial.println("\n\nNo File :(");
 
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

  server.begin();
}
 
void loop() {
    server.handleClient();
}


/*
#include <ESP8266WiFi.h>

// Nome do seu wifi
const char* ssid = "A&MLuans"; 

// Senha do seu wifi
const char* password = "a&mluans000408"; 

// Porta de comunicacao (normalmente se utiliza a 80 ou 8080)
WiFiServer server(80); 

void setup() {
  // Para o node mcu esp8266 a velocidade do monitor serial e 115200
  Serial.begin(9600); 
  delay(10);
  
  pinMode(2, OUTPUT); 
  digitalWrite(2, 1); 

  // Mostra no monitor serial informacoes de conexao da rede
  Serial.println();
  Serial.println();
  Serial.print("conectando em ");
  Serial.println(ssid);
  
  // Inicializando a conexao
  WiFi.begin(ssid, password); 
  
   Enquanto nao conseguir conectar
    imprime um ponto na tela (dá a ideia de que esta carregando) 
  
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print("."); 
  }

  Serial.println("");
  Serial.println("WiFi connectado");

  // Inicializa o servidor (nesse caso o proprio esp8266)
  server.begin();
  Serial.println("Servidor inicializado");
  
  // Mostra o IP do servidor
  Serial.println(WiFi.localIP()); 
}

void loop() {
  
  // Guarda o status do servidor
  WiFiClient client = server.available(); 
  if ( ! client) {
    return;
  }
  
  // Quando estiver alguem acessando 
  Serial.println("novo cliente"); 
  
  // Enquanto nao tiver cliente
  while ( ! client.available()) { 
    delay(1);
  }
  
  // Lê caracteres do buffer serial
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Verifica se existe a substring led5_on
  if (req.indexOf("led5_on") != -1) {
    digitalWrite(2, 0);
    Serial.println(req.indexOf("led5_on"));
    
  } else if (req.indexOf("led5_off") != -1) {
    digitalWrite(2, 1);
    Serial.println(req.indexOf("led5_off"));
  } 

  Serial.println("Cliente desconectado");
}



#include <FS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define led 2

int teste = 2;

const char* ssid = "A&MLuans";
const char* password = "a&mluans000408";
 
String webPage = "";
String stylePage = "";
 
ESP8266WebServer server(80);
 
void handleRoot() {
  teste++;
  char body[webPage.length() + 1];
  strcpy(body, webPage.c_str());
  sprintf(body, body, teste);
  server.send(200, "text/html", body);
}

void handle_led_on(){
  digitalWrite(led, LOW);
}

void handle_led_off(){
  digitalWrite(led, HIGH);
}

void handleRootS(){
  server.send(200, "text/css", stylePage);
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
 
void setup() {
  Serial.begin(9600);
  SPIFFS.begin();

  pinMode(led, OUTPUT);
 
  if(SPIFFS.exists("/index.html"))
  {
    Serial.println("\n\nfile exists!");
  }
  else Serial.println("\n\nNo File :(");
 
  readFile();
  readFileS();
  
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
  server.on("/led/on", handle_led_on);
  server.on("/led/off", handle_led_off);

  server.begin();
}
 
void loop() {
  while(true){
    server.handleClient();
    delay(1000);  
  }
}

*******************************************************
 * CANAL INTERNET E COISAS
 * ESP8266 - Utilizacao do SPIFFS
 * 03/2018 - Andre Michelon
 

// Bibliotecas
#include <FS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "A&MLuans";
const char* password = "a&mluans000408";

String webPage = "";

ESP8266WebServer server(80);

void handleRoot(){
  server.send(200, "text/html", webPage);    
}

void readFile(void){
  //Faz a leitura do html
  File rFile = SPIFFS.open("/index.html", "r");
  Serial.println("Lendo arquivo HTML...");
  webPage = rFile.readString();    
  Serial.println(webPage);
  rFile.close();
}

void setup(){
  Serial.begin(115200);

  // --- Inicializando SPIFSS ---
  Serial.println("\nInicializando SPIFSS ---------------------");
  if (SPIFFS.begin()) {
    Serial.println("Ok");
  } else {
    Serial.println("Falha");
    while(true);
  }

  if(SPIFFS.exists("/index.html")){
    Serial.println("\n\nArquivo existente!");   

  }else{
     Serial.println("\n\nArquivo não existente!");    
  }    
  
  readFile();

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a: ");
  Serial.print(ssid);
  Serial.println("Endereço Ip: ");
  Serial.print(WiFi.localIP());
  
  server.on("/", handleRoot);
  server.begin();
  
}

void loop() {
  server.handleClient();
}

*/
