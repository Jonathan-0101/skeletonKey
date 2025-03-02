#include <vector>

#include "WiFiTools.h"

WiFiTools wifiTools;

void setup() {
    Serial.begin(115200);
    delay(100);

    // Call the rickRollBeaconSpam function
    // wifiTools.rickRollBeaconSpam();

    // Call the scanWiFiNetworks function
    // wifiTools.scanWiFiNetworks();

    // Call the deauthNetwork function with the following parameters:
    // uint8_t* networkSSID = tonyTable
    // uint8_t* networkBSSID = B8:27:EB:33:A2:4E
    // uint8_t channel = 6
    // int numPackets = 10
    // int delayMs = 100
    // uint8_t reasonCode = 2
    // wifiTools.deauthNetwork((uint8_t*)"tonyTable", (uint8_t*)"\xB8\x27\xEB\x33\xA2\x4E", 6, -1, NULL, 1000, 1, 2);
    // wifiTools.deauthNetwork((uint8_t*)"Jonathan's iPhone", (uint8_t*)"\x4E\x8D\x2E\x26\x5F\x36", 6, -1, NULL, 10000, 1, 2);

    // getAvailableNetworks function
    // std::vector<wifi_ap_record_t> availableNetworks = wifiTools.getAvailableNetworks();
    // for (int i = 0; i < availableNetworks.size(); i++) {
    //     Serial.printf("Network %d: %s\n", i, availableNetworks[i].ssid);
    // }

    // Serial.println("Enter the index of the network to deauth:");
    // while (Serial.available() == 0) {
    //     delay(100);
    // }

    // int networkIndex = Serial.parseInt();
    // if (networkIndex != -1) {
    //     if (networkIndex < 0 || networkIndex >= availableNetworks.size()) {
    //         Serial.println("Invalid network index");
    //         return;
    //     } else {
    //         wifiTools.deauthNetwork(NULL, NULL, NULL, networkIndex, NULL, 5000, 1, 2);
    //     }
    // }

    // // scanForClients function
    // wifiTools.scanForClients();

    // scan for available networks
    wifiTools.scanWiFiNetworks();

    // get char array of SSID and MACs
    char* ssidAndMACs = wifiTools.getFoundSSIDandMACs();

    // print the SSID and MACs
    Serial.println(ssidAndMACs);
}

void loop() {
    // Nothing to do here
}