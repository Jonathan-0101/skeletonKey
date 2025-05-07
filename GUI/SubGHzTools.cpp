#include "SubGHzTools.h"

#include <Arduino.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <HardwareSerial.h>

#include "SPI.h"

// Constructor
SubGHzTools::SubGHzTools() {
    // Create the CC1101 object
    ELECHOUSE_cc1101 = ELECHOUSE_CC1101();
}

void SubGHzTools::configureModule() {
    // Main part to tune CC1101 with proper frequency, modulation and encoding
    // ELECHOUSE_cc1101.Init();                 // Must be set to initialize the cc1101!
    ELECHOUSE_cc1101.setCCMode(1);           // Set config for internal transmission mode. value 0 is for RAW recording/replaying
    ELECHOUSE_cc1101.setModulation(2);       // Set modulation mode. 0 = 2-FSK, 1 = GFSK, 2 = ASK/OOK, 3 = 4-FSK, 4 = MSK.
    ELECHOUSE_cc1101.setMHZ(433.92);         // Here you can set your basic frequency. The lib calculates the frequency automatically (default = 433.92).The cc1101 can: 300-348 MHZ, 387-464MHZ and 779-928MHZ. Read More info from datasheet.
    ELECHOUSE_cc1101.setDeviation(47.60);    // Set the Frequency deviation in kHz. Value from 1.58 to 380.85. Default is 47.60 kHz.
    ELECHOUSE_cc1101.setChannel(0);          // Set the Channelnumber from 0 to 255. Default is cahnnel 0.
    ELECHOUSE_cc1101.setChsp(199.95);        // The channel spacing is multiplied by the channel number CHAN and added to the base frequency in kHz. Value from 25.39 to 405.45. Default is 199.95 kHz.
    ELECHOUSE_cc1101.setRxBW(812.50);        // Set the Receive Bandwidth in kHz. Value from 58.03 to 812.50. Default is 812.50 kHz.
    ELECHOUSE_cc1101.setDRate(9.6);          // Set the Data Rate in kBaud. Value from 0.02 to 1621.83. Default is 99.97 kBaud!
    ELECHOUSE_cc1101.setPA(10);              // Set TxPower. The following settings are possible depending on the frequency band.  (-30  -20  -15  -10  -6    0    5    7    10   11   12) Default is max!
    ELECHOUSE_cc1101.setSyncMode(2);         // Combined sync-word qualifier mode. 0 = No preamble/sync. 1 = 16 sync word bits detected. 2 = 16/16 sync word bits detected. 3 = 30/32 sync word bits detected. 4 = No preamble/sync, carrier-sense above threshold. 5 = 15/16 + carrier-sense above threshold. 6 = 16/16 + carrier-sense above threshold. 7 = 30/32 + carrier-sense above threshold.
    ELECHOUSE_cc1101.setSyncWord(211, 145);  // Set sync word. Must be the same for the transmitter and receiver. Default is 211,145 (Syncword high, Syncword low)
    ELECHOUSE_cc1101.setAdrChk(0);           // Controls address check configuration of received packages. 0 = No address check. 1 = Address check, no broadcast. 2 = Address check and 0 (0x00) broadcast. 3 = Address check and 0 (0x00) and 255 (0xFF) broadcast.
    ELECHOUSE_cc1101.setAddr(0);             // Address used for packet filtration. Optional broadcast addresses are 0 (0x00) and 255 (0xFF).
    ELECHOUSE_cc1101.setWhiteData(0);        // Turn data whitening on / off. 0 = Whitening off. 1 = Whitening on.
    ELECHOUSE_cc1101.setPktFormat(0);        // Format of RX and TX data. 0 = Normal mode, use FIFOs for RX and TX. 1 = Synchronous serial mode, Data in on GDO0 and data out on either of the GDOx pins. 2 = Random TX mode; sends random data using PN9 generator. Used for test. Works as normal mode, setting 0 (00), in RX. 3 = Asynchronous serial mode, Data in on GDO0 and data out on either of the GDOx pins.
    ELECHOUSE_cc1101.setLengthConfig(1);     // 0 = Fixed packet length mode. 1 = Variable packet length mode. 2 = Infinite packet length mode. 3 = Reserved
    ELECHOUSE_cc1101.setPacketLength(0);     // Indicates the packet length when fixed packet length mode is enabled. If variable packet length mode is used, this value indicates the maximum packet length allowed.
    ELECHOUSE_cc1101.setCrc(0);              // 1 = CRC calculation in TX and CRC check in RX enabled. 0 = CRC disabled for TX and RX.
    ELECHOUSE_cc1101.setCRC_AF(0);           // Enable automatic flush of RX FIFO when CRC is not OK. This requires that only one packet is in the RXIFIFO and that packet length is limited to the RX FIFO size.
    ELECHOUSE_cc1101.setDcFilterOff(0);      // Disable digital DC blocking filter before demodulator. Only for data rates ≤ 250 kBaud The recommended IF frequency changes when the DC blocking is disabled. 1 = Disable (current optimized). 0 = Enable (better sensitivity).
    ELECHOUSE_cc1101.setManchester(0);       // Enables Manchester encoding/decoding. 0 = Disable. 1 = Enable.
    ELECHOUSE_cc1101.setFEC(0);              // Enable Forward Error Correction (FEC) with interleaving for packet payload (Only supported for fixed packet length mode. 0 = Disable. 1 = Enable.
    ELECHOUSE_cc1101.setPRE(0);              // Sets the minimum number of preamble bytes to be transmitted. Values: 0 : 2, 1 : 3, 2 : 4, 3 : 6, 4 : 8, 5 : 12, 6 : 16, 7 : 24
    ELECHOUSE_cc1101.setPQT(0);              // Preamble quality estimator threshold. The preamble quality estimator increases an internal counter by one each time a bit is received that is different from the previous bit, and decreases the counter by 8 each time a bit is received that is the same as the last bit. A threshold of 4∙PQT for this counter is used to gate sync word detection. When PQT=0 a sync word is always accepted.
    ELECHOUSE_cc1101.setAppendStatus(0);     // When enabled, two status bytes will be appended to the payload of the packet. The status bytes contain RSSI and LQI values, as well as CRC OK.
}

// Initialize the CC1101 modules
void SubGHzTools::init() {
    Serial.println("Initializing CC1101 modules");

    // Create the CC1101 objects
    ELECHOUSE_cc1101.addSpiPin(CC1101_A_sck, CC1101_A_miso, CC1101_A_mosi, CC1101_A_ss, 0);
    ELECHOUSE_cc1101.addGDO0(CC1101_A_gdo0, 0);
    Serial.println("CC1101_A added");

    // Add the second CC1101 module with custom pins
    ELECHOUSE_cc1101.addSpiPin(CC1101_B_sck, CC1101_B_miso, CC1101_B_mosi, CC1101_B_ss, 1);
    ELECHOUSE_cc1101.addGDO0(CC1101_B_gdo0, 1);
    Serial.println("CC1101_B added");

    // Set and configure the first CC1101 module (CC1101_A)
    ELECHOUSE_cc1101.setModul(0);
    ELECHOUSE_cc1101.Init();
    configureModule();
    Serial.println("CC1101_A configureModule done");

    // Set and configure the second CC1101 module (CC1101_B)
    ELECHOUSE_cc1101.setModul(1);
    configureModule();
    Serial.println("CC1101_B configureModule done");

    // Set the RF switch pins for both CC1101 modules
    pinMode(CC1101_A_RF_Switch, OUTPUT);
    pinMode(CC1101_B_RF_Switch, OUTPUT);
    digitalWrite(CC1101_A_RF_Switch, LOW);
    digitalWrite(CC1101_B_RF_Switch, LOW);
    Serial.println("RF switch pins set to HIGH");

    // Set CC1101_B as the default module for communication
    ELECHOUSE_cc1101.setModul(0);

    Serial.println("Initialised");
    if (ELECHOUSE_cc1101.getCC1101()) {
        Serial.println("cc1101 initialized. Connection OK");
    } else {
        Serial.println("cc1101 connection error! check the wiring.");
    };
}

void SubGHzTools::jammer() {
    // Populate cc1101 sending buffer with random values
    for (int i = 0; i < 60; i++) {
        CC1101_sendingbuffer[i] = (byte)random(255);
    };

    // Send these data to radio over CC1101
    ELECHOUSE_cc1101.SendData(CC1101_sendingbuffer, 60);
}

void SubGHzTools::startJamming() {
    // Set the required flags for jamming mode
    jammingMode = 1;
    currentMode = JAMMER;

    // Set the power output to maximum
    ELECHOUSE_cc1101.setPA(12);  // Set TxPower to maximum

    // Call the jammer function
    jammer();
}

void SubGHzTools::stopJamming() {
    // Set jamming mode to 0
    jammingMode = 0;
    currentMode = IDLE;
}

void SubGHzTools::runAction() {
    if (currentMode == IDLE) {
        // Do nothing
    } else if (currentMode == JAMMER) {
        jammer();
    } else if (currentMode == CAPTURE_RAW) {
        captureRaw(samplingInterval);
    } else if (currentMode == TRANSMIT_RAW) {
        transmitRaw(samplingInterval);
    }
}

void SubGHzTools::setFrequency(float freq) {
    // Check if the frequency is within the valid ranges (300-348 MHZ, 387-464MHZ and 779-928MHZ)
    if ((freq >= 300 && freq <= 348) || (freq >= 387 && freq <= 464) || (freq >= 779 && freq <= 928)) {
        Serial.println("Frequency is valid");
    } else {
        Serial.println("Frequency is invalid, setting to default frequency");
        freq = defaultFrequency;
    }

    // Set the frequency to the specified value
    frequency = freq;
    ELECHOUSE_cc1101.setMHZ(frequency);
    Serial.printf("Frequency set to: %.2f MHz\n", frequency);
}

void SubGHzTools::captureRaw(int sampleInterval = 1) {
    // Capture raw data from the CC1101 module
    setting = sampleInterval;

    Serial.println("Capturing RAW data from CC1101 module...");

    // Setup async mode on CC1101 with GDO0 pin processing
    ELECHOUSE_cc1101.setCCMode(0);
    ELECHOUSE_cc1101.setPktFormat(3);
    ELECHOUSE_cc1101.SetRx();

    // Start recording to the buffer with bitbanging of GDO0 pin state
    Serial.println("Waiting for radio signal to start RAW recording...");
    pinMode(CC1101_gdo0, INPUT);
    setting2 = digitalRead(CC1101_gdo0);
    delayMicroseconds(1000);

    // Waiting for some data first or serial port signal
    while (digitalRead(CC1101_gdo0) == LOW);

    // Start recording to the buffer with bitbanging of GDO0 pin state
    Serial.println("Starting RAW recording to the buffer...");

    for (int i = 0; i < RECORDINGBUFFERSIZE; i++) {
        byte receivedbyte = 0;
        for (int j = 7; j > -1; j--) {
            bitWrite(receivedbyte, j, digitalRead(CC1101_gdo0));
            delayMicroseconds(setting);
        };

        // Store the output into recording buffer
        CC1101_bigrecordingbuffer[i] = receivedbyte;
    }

    Serial.println("Recording RAW data complete.");

    // Setting normal pkt format again
    ELECHOUSE_cc1101.setCCMode(1);
    ELECHOUSE_cc1101.setPktFormat(0);
    ELECHOUSE_cc1101.SetRx();
}

void SubGHzTools::transmitRaw(int sampleInterval = 1) {
    // Transmit raw data from the CC1101 module
    setting = sampleInterval;

    // Setup async mode on CC1101 and go into TX mode with GDO0 pin processing
    ELECHOUSE_cc1101.setCCMode(0);
    ELECHOUSE_cc1101.setPktFormat(3);
    ELECHOUSE_cc1101.SetTx();

    // Start replaying GDO0 bit state from data in the buffer with bitbanging
    Serial.println("Replaying RAW data from the buffer...");
    pinMode(CC1101_gdo0, OUTPUT);

    for (int i = 1; i < RECORDINGBUFFERSIZE; i++) {
        byte receivedbyte = CC1101_bigrecordingbuffer[i];
        for (int j = 7; j > -1; j--) {
            digitalWrite(CC1101_gdo0, bitRead(receivedbyte, j));
            delayMicroseconds(setting);
        };
    }

    Serial.print("Replaying RAW data complete.");

    // Setting normal pkt format again
    ELECHOUSE_cc1101.setCCMode(1);
    ELECHOUSE_cc1101.setPktFormat(0);
    ELECHOUSE_cc1101.SetTx();
}

void SubGHzTools::setModule(int module) {
    // Set the selected module to use (0 for A, 1 for B)
    if (module == 0) {
        if (CC1101_A_initialised == false) {
            ELECHOUSE_cc1101.setModul(0);
            configureModule();
            CC1101_A_initialised = true;
        }
        selectedModule = module;
        ELECHOUSE_cc1101.setModul(selectedModule);
        CC1101_gdo0 = CC1101_A_gdo0;
        CC1101_RF_Switch = CC1101_A_RF_Switch;
        Serial.printf("Selected module set to: %d\n", selectedModule);

    } else if (module == 1) {
        selectedModule = module;
        ELECHOUSE_cc1101.setModul(selectedModule);
        CC1101_gdo0 = CC1101_B_gdo0;
        CC1101_RF_Switch = CC1101_B_RF_Switch;
        Serial.printf("Selected module set to: %d\n", selectedModule);
    } else {
        Serial.println("Invalid module selection. Please choose 0 or 1.");
    }
}

int SubGHzTools::getSelectedModule() {
    // Return the selected module (0 for A, 1 for B)
    return selectedModule;
}