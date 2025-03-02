/*
    Project: Pen-testing Device
    File: cc1101_test.ino
    Author: Jonathan Woolf
    Created: 2025-02-11
    License: MIT

    Description: Design and testing of the Sub-GHz system.

    Libraries used:
        - ELECHOUSE_CC1101_SRC_DRV.h

    Hardware:


    Connections:
        - CC1101_A_CS -> ESP GPIO08
        - CC1101_A_MISO -> ESP GPIO41
        - CC1101_A_MOSI -> ESP GPIO40
        - CC1101_A_SCK -> ESP GPIO39
        - CC1101_A_GDO0 -> ESP GPIO09
        - CC1101_A_RF_Switch -> ESP GPIO10

*/

#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <SPI.h>

byte CC1101_A_sck = 17;
byte CC1101_A_miso = 15;
byte CC1101_A_mosi = 16;
byte CC1101_A_ss = 3;
int CC1101_A_gdo0 = 11;

int CC1101_A_RF_Switch = 12;

byte transmitt_byte[11] = {72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100};
char *transmitt_char = "Hello World";

void setup() {
    Serial.begin(115200);

    //pinMode(CC1101_A_RF_Switch, OUTPUT);
    //digitalWrite(CC1101_A_RF_Switch, HIGH);

    // Set up the CC1101
    //ELECHOUSE_cc1101.Init();

    if (ELECHOUSE_cc1101.getCC1101()) {  // Check the CC1101 Spi connection.
        Serial.println("Connection OK");
    } else {
        Serial.println("Connection Error");
    }

    ELECHOUSE_cc1101.Init();
    ELECHOUSE_cc1101.setSpiPin(CC1101_A_sck, CC1101_A_miso, CC1101_A_mosi, CC1101_A_ss);
    //ELECHOUSE_cc1101.setGDO0(CC1101_A_gdo0);
    ELECHOUSE_cc1101.setCCMode(1);
    ELECHOUSE_cc1101.setModulation(0);
    ELECHOUSE_cc1101.setMHZ(433.92);
    ELECHOUSE_cc1101.setDeviation(47.60);
    ELECHOUSE_cc1101.setChannel(0);
    ELECHOUSE_cc1101.setChsp(199.95);
    ELECHOUSE_cc1101.setRxBW(812.50);
    ELECHOUSE_cc1101.setDRate(99.97);
    ELECHOUSE_cc1101.setPA(10);
    ELECHOUSE_cc1101.setSyncMode(2);
    ELECHOUSE_cc1101.setSyncWord(211, 145);
    ELECHOUSE_cc1101.setAdrChk(0);
    ELECHOUSE_cc1101.setAddr(0);
    ELECHOUSE_cc1101.setWhiteData(0);
    ELECHOUSE_cc1101.setPktFormat(0);
    ELECHOUSE_cc1101.setLengthConfig(1);
    ELECHOUSE_cc1101.setPacketLength(0);
    ELECHOUSE_cc1101.setCrc(1);
    ELECHOUSE_cc1101.setCRC_AF(0);
    ELECHOUSE_cc1101.setDcFilterOff(0);
    ELECHOUSE_cc1101.setManchester(0);
    ELECHOUSE_cc1101.setFEC(0);
    ELECHOUSE_cc1101.setPRE(0);
    ELECHOUSE_cc1101.setPQT(0);
    ELECHOUSE_cc1101.setAppendStatus(0);

    Serial.println("Tx Mode");
}

void loop() {
    // 3 different methods to send data

    // Transmitt "Hello World" from byte format.
    ELECHOUSE_cc1101.SendData(transmitt_byte, 11);
    delay(2000);

    // Transmitt "Hello World" from char format.
    ELECHOUSE_cc1101.SendData(transmitt_char);
    delay(2000);

    // Transmitt "Hello World" from char format directly.
    ELECHOUSE_cc1101.SendData("Hello World");
    delay(2000);
}