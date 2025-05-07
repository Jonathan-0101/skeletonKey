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

#include "SPI.h"

#define RECORDINGBUFFERSIZE 4096
#define CCBUFFERSIZE 64

typedef enum {
    IDLE,
    CAPTURE_RAW,
    TRANSMIT_RAW,
    JAMMER
} SubGHzTools_flag;

class SubGHzTools {
   private:
    ELECHOUSE_CC1101 ELECHOUSE_cc1101;
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

    int CC1101_gdo0 = 11;
    int CC1101_RF_Switch = 12;

    bool CC1101_A_initialised = false;

    // buffer for sending CC1101
    // byte CC1101_A_sendingbuffer[CCBUFFERSIZE] = {0};
    byte CC1101_sendingbuffer[CCBUFFERSIZE] = {0};

    // buffer for receiving  CC1101
    // byte CC1101_A_receivingbuffer[CCBUFFERSIZE] = {0};
    byte CC1101_receivingbuffer[CCBUFFERSIZE] = {0};

    // buffer for recording and replaying of many frames
    // byte CC1101_A_bigrecordingbuffer[RECORDINGBUFFERSIZE] = {0};
    byte CC1101_bigrecordingbuffer[RECORDINGBUFFERSIZE] = {0};

    int jammingMode = 0;
    float defaultFrequency = 433.92;
    float frequency = 433.92;
    int selectedModule = 1;
    int samplingInterval = 1;
    int setting, setting2;
    SubGHzTools_flag currentMode = IDLE;

    /**
     * @brief Function to configure the CC1101 module
     *
     */
    void
    configureModule();

    /**
     * @brief Jamming function for the CC1101 module
     *
     */
    void jammer();

   public:
    /**
     * @brief Construct a new SubGHz Tools object
     *
     */
    SubGHzTools();

    /**
     * @brief Initialisation of the SubGHzTools object
     *
     */
    void init();

    /**
     * @brief Enable jamming with the CC1101 module
     *
     */
    void startJamming();

    /**
     * @brief Disable jamming with the CC1101 module
     *
     */
    void stopJamming();

    /**
     * @brief Run the action based on the current mode (jamming, capturing, or transmitting)
     *
     */
    void runAction();

    /**
     * @brief Set the frequency for the CC1101 module
     *
     * @param freq Frequency in MHz
     */
    void setFrequency(float freq);

    /**
     * @brief Capture raw data from the CC1101 module
     *
     * @param sampleInterval Sampling interval in microseconds
     */
    void captureRaw(int sampleInterval);

    /**
     * @brief Transmit raw data from the CC1101 module
     *
     * @param sampleInterval Sampling interval in microseconds
     */
    void transmitRaw(int sampleInterval);

    /**
     * @brief Set the module to use (A or B)
     *
     * @param module Module number (0 for A, 1 for B)
     */
    void setModule(int module);

    /**
     * @brief Get the Selected Module object
     *
     * @return int Selected module (0 for A, 1 for B)
     */
    int getSelectedModule();
};

#endif  // SUBGHTOOLS_H