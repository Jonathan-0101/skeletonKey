#include <FS.h>
#include <SD.h>
#include <SPI.h>

#include "SubGHzTools.h"

SubGHzTools subGHzTools;  // Create an instance of SubGHzTools

void setup() {
    Serial.begin(115200);
    delay(500);

    // digitalWrite(42, HIGH);

    // delay(500);

    // Create an SPI instance for the CC1101 module
    // SPIClass spiInstance = new SPIClass(HSPI);
    // spiInstance.begin(39, 41, 40, 42);  // Initialize SPI with custom pins

    // Initialize SPI bus and SD card
    // SPI.begin(39, 41, 40, 42);
    // if (!SD.begin(42)) {
        // Serial.println("Card Mount Failed");
        // return;
    // }

    // subGHzTools.init(SD);  // Initialize the CC1101 module with SPI instance and SD card
    subGHzTools.init();

    Serial.println("Jamming started");
    subGHzTools.startJamming();
    // run the action for 10 seconds in a while loop
    unsigned long startTime = millis();
    while(1) {
    // while (millis() - startTime < 10000) {
      subGHzTools.runAction();  // Run the action
    }
    subGHzTools.stopJamming();  // Stop jamming
    Serial.println("Jamming stopped");

    subGHzTools.captureRaw(1);

    Serial.println("Done");

    delay(5000);

    subGHzTools.transmitRaw(1);
}

void loop() {
    // Nothing to do here
}