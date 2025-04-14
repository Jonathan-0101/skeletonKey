// SubGHzTools.h
#ifndef SUBGHTOOLS_H
#define SUBGHTOOLS_H

/**
 * @file SubGHzTools.h
 * @author Jonathan Woolf
 * @brief Library for Sub-GHz attack tools
 * @version 1.0
 * @date 2025-04-13
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <Arduino.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <SD.h>
#include <SPI.h>

#define RECORDINGBUFFERSIZE 4096
#define CCBUFFERSIZE 64

typedef enum {
    CAPTURE_RAW,
    TRANSMIT_RAW,
    JAMMER
} SubGHzTools_flag;

class SubGHzTools {
   private:
    // CC1101 module instance
    fs::SDFS* sd;
    //  SPIClass* spiInstance;
    //  ELECHOUSE_CC1101 ELECHOUSE_cc1101;
    byte CC1101_A_sck = 39;
    byte CC1101_A_miso = 41;
    byte CC1101_A_mosi = 40;
    byte CC1101_A_ss = 8;
    int CC1101_A_gdo0 = 9;
    int CC1101_A_RF_Switch = 10;
    byte CC1101_B_sck = 17;
    byte CC1101_B_miso = 15;
    byte CC1101_B_mosi = 16;
    byte CC1101_B_ss = 3;
    int CC1101_B_gdo0 = 11;
    int CC1101_B_RF_Switch = 12;

    // buffer for sending CC1101
    byte CC1101_A_sendingbuffer[CCBUFFERSIZE] = {0};
    byte CC1101_B_sendingbuffer[CCBUFFERSIZE] = {0};

    // buffer for receiving  CC1101
    byte CC1101_A_receivingbuffer[CCBUFFERSIZE] = {0};
    byte CC1101_B_receivingbuffer[CCBUFFERSIZE] = {0};

    // buffer for recording and replaying of many frames
    byte CC1101_A_bigrecordingbuffer[RECORDINGBUFFERSIZE] = {0};
    byte CC1101_B_bigrecordingbuffer[RECORDINGBUFFERSIZE] = {0};

    int jammingMode = 0;
    float defaultFrequency = 433.92;
    float frequency = 433.92;
    int samplingInterval = 1;
    int setting, setting2;

    void jammer();
    void configureModule();

   public:
    SubGHzTools();  // Constructor

    //  void init(fs::SDFS& sdInstance);
    void init();
    void startJamming();
    void stopJamming();
    void runAction();
    void setFrequency(float freq);
    void captureRaw(int sampleInterval);
    void transmitRaw(int sampleInterval);
};

#endif  // SUBGHTOOLS_H