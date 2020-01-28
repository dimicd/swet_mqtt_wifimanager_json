void remove_json(){
    unsigned long t = millis();
    while (!digitalRead(BUTTON))
    {
        delay(1);
        if (t + 15000 < millis()) // Нажатие 10 секунд
        {
            SPIFFS.remove("/config.json");
            WiFiManager wifiManager;
            wifiManager.resetSettings();
            ESP.restart();
        }
    }
}