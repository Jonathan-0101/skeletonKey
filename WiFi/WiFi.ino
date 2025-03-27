#include <vector>

#include "WiFiTools.h"

WiFiTools wifiTools;

void setup() {
    Serial.begin(115200);
    delay(100);

    // Call the rickRollBeaconSpam function
    wifiTools.rickRollBeaconSpam();

    // Call the scanWiFiNetworks function
    wifiTools.scanWiFiNetworks();

    // getAvailableNetworks function
    std::vector<wifi_ap_record_t> availableNetworks = wifiTools.getAvailableNetworks();
    for (int i = 0; i < availableNetworks.size(); i++) {
        Serial.printf("Network %d: %s\n", i, availableNetworks[i].ssid);
    }

    // Serial.println("Enter the index of the network to find devices of:");
    // while (Serial.available() == 0) {
    //     delay(100);
    // }

    // int networkIndex = Serial.parseInt();
    // if (networkIndex != -1) {
    //     if (networkIndex < 0 || networkIndex >= availableNetworks.size()) {
    //         Serial.println("Invalid network index");
    //         return;
    //     } else {
    //         wifiTools.handshakeCapture(NULL, NULL, networkIndex, 30000);
    //         // wifiTools.activeHandshakeCapture(NULL, NULL, networkIndex, 30000);
    //         // wifiTools.findClients(NULL, NULL, networkIndex, 15000);
    //     }
    // }

    // // scanForClients function
    // wifiTools.scanForClients();

    // scan for available networks
    // wifiTools.scanWiFiNetworks();

    // get char array of SSID and MACs
    // char* ssidAndMACs = wifiTools.getFoundSSIDandMACs();

    // print the SSID and MACs
    // Serial.println(ssidAndMACs);
}

void loop() {
    // Nothing to do here
}