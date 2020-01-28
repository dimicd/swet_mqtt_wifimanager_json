void saveConfigCallback(){
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void callback(char* topic, uint8_t* payload, unsigned int length){
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("  ");
  String strTopic = String(topic);
  String strPayload = String((char*)payload);
   for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
   }
   Serial.println();
   if (strTopic == "ESP01/r_1") {
     if ((char)payload[0] == '0') {
       oldState[0] = false;
       mcp.digitalWrite(relay[0], oldState[0]);
      }
     else if ((char)payload[0] == '1') {
      oldState[0] = true;
      mcp.digitalWrite(relay[0], oldState[0]);
      }
     }
  if (strTopic == "ESP01/r_2") {
    if ((char)payload[0] == '0') {
      oldState[1] = false;
      mcp.digitalWrite(relay[1], oldState[1]);
      }
    else if ((char)payload[0] == '1') {
      oldState[1] = true;
      mcp.digitalWrite(relay[1], oldState[1]);
      }
  }
  if (strTopic == "ESP01/r_3") {
    if ((char)payload[0] == '0') {
      oldState[2] = false;
      mcp.digitalWrite(relay[2], oldState[2]);
      }
    else if ((char)payload[0] == '1') {
      oldState[2] = true;
      mcp.digitalWrite(relay[2], oldState[2]);
      }
  }
  if (strTopic == "ESP01/r_4") {
    if ((char)payload[0] == '0') {
      oldState[3] = false;
      mcp.digitalWrite(relay[3], oldState[3]);
      }
    else if ((char)payload[0] == '1') {
      oldState[3]=  true;
      mcp.digitalWrite(relay[3], oldState[3]);
      }
  }
  if (strTopic == "ESP01/r_5") {
    if ((char)payload[0] == '0') {
      oldState[4] = false;
      mcp.digitalWrite(relay[4], oldState[4]);
      }
    else if ((char)payload[0] == '1') {
      oldState[4] = true;
      mcp.digitalWrite(relay[4], oldState[4]);
      }
  }
  if (strTopic == "ESP01/r_6") {
    if ((char)payload[0] == '0') {
      oldState[5] = false;
      mcp.digitalWrite(relay[5], oldState[5]);
          }
    else if ((char)payload[0] == '1') {
      oldState[5] = true;
      mcp.digitalWrite(relay[5], oldState[5]);
      }
  }
  if (strTopic == "ESP01/r_7") {
    if ((char)payload[0] == '0') {
      oldState[6] = false;
      mcp.digitalWrite(relay[6], oldState[6]);
    }
    else if ((char)payload[0] == '1') {
      oldState[6] = true;
      mcp.digitalWrite(relay[6], oldState[6]);
    }
  }
  if (strTopic == "ESP01/r_8") {
    if ((char)payload[0] == '0') {
      oldState[7] = false;
      mcp.digitalWrite(relay[7], oldState[7]);
      }
    else if ((char)payload[0] == '1') {
      oldState[7] = true;
      mcp.digitalWrite(relay[7], oldState[7]);
      }
  }
//  client.loop();
}



void setup_wifi(){
// initialize serial communication
  
  Serial.println();
  
  // format flash storage, used when testing to not store the config between reboots
  // SPIFFS.format();


  Serial.println("mounting FS...");
  // reads the contents of config.json if exists and populates the global variables mentioned above
  if (SPIFFS.begin()) { // open flash storage
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) { // check if config.json exists
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r"); // read contents of config.json
      if (configFile) { /// check if file not empty
        Serial.println("opened config file");
        // -- begin conversion of json to array --
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        // -- end conversion --
        if (json.success()) { // check if conversion was successful
          Serial.println("\nparsed json");

          strcpy(mqtt_server, json["mqtt_server"]); // populate mqtt_server from config
          strcpy(mqtt_port, json["mqtt_port"]); // populate mqtt_port from config
          strcpy(mqtt_user, json["mqtt_user"]); // populate mqtt_user from config
          strcpy(mqtt_pass, json["mqtt_pass"]); // populate mqtt_pass from config
         
        } else { // json conversion failed
          Serial.println("failed to load json config");
        }
      }
    }
  } else { // failed to mount flash storage
    Serial.println("failed to mount FS");
  }

  // -- begin configuration of the portal --

  // create custom parameters for the portal
  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 6);
  WiFiManagerParameter custom_mqtt_user("user", "mqtt user", mqtt_port, 30);
  WiFiManagerParameter custom_mqtt_pass("pass", "mqtt password", mqtt_pass, 30);

  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  // set the callback used for notifying if there was a change
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  // add custom parameters to portal§
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_user);
  wifiManager.addParameter(&custom_mqtt_pass);

  // reset portal settings. used for testing only. to force opening the portal on each boot.
  //  wifiManager.resetSettings();

  // if the board could not connect to wifi on the first boot.
  // an access point called Configure Device would be created
  // when connecting to this access point a configuration portal would be displayed
  // where the user can set a new SSID and password for connecting to wifi
  // and the required credentials for mqtt.
  // this will run in a blocking loop so the boot process would stay here as long
  // as the board is not connected to wifi.
  if (!wifiManager.autoConnect("AutoConnectAP", "password")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }

  // -- end configuration --

  //if you get here you have connected to the WiFi
  Serial.println("connected!");

  // if a new config was set in the portal, it will get saved as json on the flash storage.
  if (shouldSaveConfig) {

    // populate mqtt_server, mqtt_port, mqtt_user, mqtt_pass with the information provided by the user.
    strcpy(mqtt_server, custom_mqtt_server.getValue());
    strcpy(mqtt_port, custom_mqtt_port.getValue());
    strcpy(mqtt_user, custom_mqtt_user.getValue());
    strcpy(mqtt_pass, custom_mqtt_pass.getValue());

    // -- begin conversion of parameters to json and save them to flash storage --
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"] = mqtt_server;
    json["mqtt_port"] = mqtt_port;
    json["mqtt_user"] = mqtt_user;
    json["mqtt_pass"] = mqtt_pass;



    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();

    // -- end conversion --
  }

  Serial.println("local ip");
  Serial.println(WiFi.localIP());


  // -- begin mqtt configuration --
  client.setServer(mqtt_server, atoi(mqtt_port)); // connect to host and port
   client.connect(id, mqtt_user, mqtt_pass);
  client.setCallback(callback);
    delay(100);
  client.connect("ESP01Client");
  delay (100);//конектимся с брокером как клиент
  client.subscribe(relays_topic);
}
void reconnect_server() //функция проверки подключения
{ //bool pigstate;
  if(!Ping.ping(mqtt_server)) {
  Serial.println("connectednotping");
  pigstate=true;
} 
  if(Ping.ping(mqtt_server)) {
   Serial.println("connectedping");
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect(id, mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      if (pigstate==true){
         client.publish(relays_topic1, String(oldState[0]).c_str(), true);
         client.publish(relays_topic2, String(oldState[1]).c_str(), true);
         client.publish(relays_topic3, String(oldState[2]).c_str(), true);
         client.publish(relays_topic4, String(oldState[3]).c_str(), true);
         client.publish(relays_topic5, String(oldState[4]).c_str(), true);
         client.publish(relays_topic6, String(oldState[5]).c_str(), true);
         client.publish(relays_topic7, String(oldState[6]).c_str(), true);
         client.publish(relays_topic8, String(oldState[7]).c_str(), true);
         pigstate=false;
      }
      client.setCallback(callback);
       // подписываемся под топики
      client.subscribe(relays_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
           // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
}