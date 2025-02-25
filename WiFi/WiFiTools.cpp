#include "WiFiTools.h"

#include <WiFi.h>

#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
esp_err_t esp_wifi_set_channel(uint8_t primary, wifi_second_chan_t second);
esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void* buffer, int len, bool en_sys_seq);
esp_err_t esp_wifi_set_storage(wifi_storage_t storage);
esp_err_t esp_wifi_set_mode(wifi_mode_t mode);
esp_err_t esp_wifi_start();
esp_err_t esp_wifi_set_promiscuous(bool en);

// Constructor
WiFiTools::WiFiTools() {
    // Empty constructor
}

void WiFiTools::begin() {
    // Initialize esp_wifi
    esp_err_t err = esp_wifi_init(&cfg);
    if (err != ESP_OK) {
        Serial.printf("Failed to initialize esp_wifi: %d\n", err);
        Serial.printf("Error: %s\n", esp_err_to_name(err));
        return;
    }

    // Set WiFi storage to RAM
    err = esp_wifi_set_storage(WIFI_STORAGE_RAM);
    if (err != ESP_OK) {
        Serial.printf("Failed to set WiFi storage: %d\n", err);
        Serial.printf("Error: %s\n", esp_err_to_name(err));
        return;
    }

    // Set WiFi mode to STA
    err = esp_wifi_set_mode(WIFI_MODE_STA);
    if (err != ESP_OK) {
        Serial.printf("Failed to set WiFi mode: %d\n", err);
        Serial.printf("Error: %s\n", esp_err_to_name(err));
        return;
    }

    // Start WiFi
    err = esp_wifi_start();
    if (err != ESP_OK) {
        Serial.printf("Failed to start WiFi: %d\n", err);
        Serial.printf("Error: %s\n", esp_err_to_name(err));
        return;
    }

    // Set WiFi to promiscuous mode
    err = esp_wifi_set_promiscuous(true);
    if (err != ESP_OK) {
        Serial.printf("Failed to set WiFi to promiscuous mode: %d\n", err);
        Serial.printf("Error: %s\n", esp_err_to_name(err));
        return;
    }

    Serial.println("WiFi initialized successfully");
}

void WiFiTools::nextChannel() {
    // Increment the channel index
    channelIndex = (channelIndex + 1) % 14;  // Assuming 14 channels
    if (channelIndex == 0) {
        channelIndex = 1;
    }
    // Set the WiFi channel
    esp_wifi_set_channel(channelIndex, WIFI_SECOND_CHAN_NONE);
}

void WiFiTools::generateRandomMac() {
    // Generate a random MAC address
    for (int i = 0; i < 6; i++) {
        randomMacAddr[i] = random(0, 255);
    }
}

void WiFiTools::rickRollBeaconSpam() {
    Serial.println("Starting rickRollBeaconSpam");

    // Stop current WiFi connection and transition to AP mode
    WiFi.disconnect();

    // create empty SSID
    for (int i = 0; i < 32; i++)
        emptySSID[i] = ' ';

    // set packetSize
    packetSize = sizeof(beaconPacket);

    if (wpa2) {
        beaconPacket[34] = 0x31;
    } else {
        beaconPacket[34] = 0x21;
        packetSize -= 26;
    }

    // change WiFi mode to AP mode
    WiFi.mode(WIFI_AP);
    Serial.println("WiFi mode set to AP");

    // set channel
    esp_err_t err = esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
    if (err != ESP_OK) {
        Serial.printf("Failed to set channel: %d\n", err);
        return;
    }
    Serial.println("Channel set to 1");

    delay(1000);
    for (int k = 0; k < 10; k++) {
        // loop through all SSIDs
        for (int i = 0; i < 8; i++) {
            // generate random MAC address
            generateRandomMac();

            // debug
            Serial.printf("SSID: %s\n", rickRollSSIDs[i]);
            Serial.printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", randomMacAddr[0], randomMacAddr[1], randomMacAddr[2], randomMacAddr[3], randomMacAddr[4], randomMacAddr[5]);

            // set MAC address in beacon packet
            memcpy(&beaconPacket[10], randomMacAddr, 6);
            memcpy(&beaconPacket[16], randomMacAddr, 6);

            // reset SSID
            memcpy(&beaconPacket[38], emptySSID, 32);

            // get length of SSID
            uint8_t ssidLength = strlen_P(rickRollSSIDs[i]);

            // write new SSID into beacon frame
            memcpy_P(&beaconPacket[38], (const char*)pgm_read_ptr(&rickRollSSIDs[i]), ssidLength);

            // set channel for beacon frame
            beaconPacket[82] = channelIndex;
            Serial.printf("Beacon Packet Channel: %d\n", channelIndex);

            // print the beacon frame
            for (int j = 0; j < packetSize; j++) {
                Serial.printf("%02X ", beaconPacket[j]);
            }

            for (int j = 0; j < 100; j++) {
                // send beacon frame
                err = esp_wifi_80211_tx(WIFI_IF_AP, beaconPacket, packetSize, false);
                if (err != ESP_OK) {
                    Serial.printf("Failed to send beacon: %d\n", err);
                } else {
                    Serial.println("Beacon sent successfully");
                }
                delay(1);
            }

            delay(10);

            nextChannel();
        }
    }

    Serial.println("Finished rickRollBeaconSpam");
}