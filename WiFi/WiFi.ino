// WiFi.ino

/**
 * @file WiFi.ino
 * @author Jonathan Woolf
 * @brief Test program for Wi-Fi attack tools
 * @version 1.0
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <SPI.h>

#include <vector>

#include "SD.h"
#include "WiFiTools.h"

WiFiTools wifiTools;

void setup() {
    Serial.begin(115200);
    delay(100);

    // Start the SPI bus and the SD card
    SPI.begin(39, 41, 40, 42);
    if (!SD.begin(42)) {
        Serial.println("Card Mount Failed");
    }
    Serial.println("SD card initialized successfully");

    // Initialize the WiFiTools object with the SD card instance
    wifiTools.initWiFiTools(SD);

    // Call the rickRollBeaconSpam function
    Serial.println("Starting beacon spam");
    wifiTools.rickRollBeaconSpam(15000);

    // Call the scanWiFiNetworks function
    wifiTools.scanWiFiNetworks();

    // getAvailableNetworks function
    std::vector<wifi_ap_record_t> availableNetworks = wifiTools.getAvailableNetworks();
    for (int i = 0; i < availableNetworks.size(); i++) {
        Serial.printf("Network %d: %s\n", i, availableNetworks[i].ssid);
    }
}

void loop() {
    // Nothing to do here
}