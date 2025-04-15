#include <SPI.h>

#include "SubGHzTools.h"

SubGHzTools subGHzTools;  // Create an instance of SubGHzTools

void setup() {
    Serial.begin(115200);
    delay(500);

    subGHzTools.init();

    // Jam for 10 seconds
    subGHzTools.startJamming();
    Serial.println("Jamming started");
    unsigned long startTime = millis();
    while (millis() - startTime < 10000) {
        subGHzTools.runAction();
    }
    subGHzTools.stopJamming();
    Serial.println("Jamming stopped");

    delay(5000);

    // Listen until raw data is received
    subGHzTools.captureRaw(1);
    Serial.println("Done");

    delay(5000);

    // Transmit the recorded raw data
    subGHzTools.transmitRaw(1);
}

void loop() {
    // Nothing to do here
}