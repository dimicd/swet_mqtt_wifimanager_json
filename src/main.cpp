#include <FS.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <Adafruit_MCP23017.h>
#include <ESP8266Ping.h>

Adafruit_MCP23017 mcp;

WiFiClient espClient;
PubSubClient client(espClient);

#define BUFFER_SIZE 100
#define BUTTON 0 
long last_mls = millis();                    //функция времени в милисекундах

int32 bs[]={8,9,10,11,12,13,14,15};
int32 relay[]={0,1,2,3,4,5,6,7};

boolean oldState[]= {false,false,false,false,false,false,false,false};
boolean bstatek[] =  {false,false,false,false,false,false,false,false};
boolean lastbtnStat[]=  {false,false,false,false,false,false,false,false};

#define relays_topic "ESP01/#"
#define relays_topic1 "ESP01/r_1"
#define relays_topic2 "ESP01/r_2"
#define relays_topic3 "ESP01/r_3"
#define relays_topic4 "ESP01/r_4"
#define relays_topic5 "ESP01/r_5"
#define relays_topic6 "ESP01/r_6"
#define relays_topic7 "ESP01/r_7"
#define relays_topic8 "ESP01/r_8"
bool pigstate;
bool shouldSaveConfig = false;
char mqtt_server[40];// Имя сервера MQTT
char mqtt_port[6];// Порт для подключения к серверу MQTT
char mqtt_user[30]; // Порт для подключения к серверу MQTT
char mqtt_pass[30]; // Пароль от сервера
const char *id = "ESP01Client"; // пофиг что будет написано
#include "gpio.h"
#include "mcp23017.h"
#include "manager.h"

void setup(){
  Serial.begin(115200);
  setup_mcp();
  setup_wifi();
  delay(10);
}

void loop(){
  button1(); // Функция проходного выключателя и публикация статуса реле на брокер
  button2();
  button3();
  button4();
  button5();
  button6();
  button7();
  button8();
  remove_json();
  client.loop();
    // 60 секунд периодичность проверки переподключения
  if (millis() - last_mls > 60000) {
    last_mls = millis();
     while (WiFi.status() != WL_CONNECTED){
       shouldSaveConfig = true;
       setup_wifi();
     }
     reconnect_server();
  }
}