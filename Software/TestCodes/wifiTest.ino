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

    Serial.println("Starting beacon spam");
    // Call the rickRollBeaconSpam function
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