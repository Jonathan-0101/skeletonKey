#include <FS.h>

#include <string>
#include <vector>

#include "IRTools.h"
#include "SD.h"
#include "SPI.h"

std::vector<IRCommand> deviceCommands;  // Declare deviceCommands globally

IRTools *irTools = new IRTools();  // Create an instance of IRTools
SPIClass spiBus = SPIClass(HSPI);  // Use HSPI for the SD card

uint16_t rawDataACOn[259] = {3302, 1644, 408, 419, 410, 416, 413, 1233, 405, 423, 406, 1239, 409, 419, 410, 417, 412, 415, 414, 1232, 406, 1241, 407, 419, 410, 417, 412, 416, 413, 1233, 405, 1241, 407, 394, 435, 419, 410, 417, 412, 416, 413, 387, 432, 422, 407, 420, 409, 418, 411, 416, 413, 415, 404, 423, 406, 421, 408, 420, 409, 1237, 411, 416, 413, 413, 406, 422, 407, 420, 409, 418, 411, 417, 412, 415, 414, 1232, 406, 421, 408, 420, 409, 418, 411, 416, 413, 1232, 406, 1240, 408, 1238, 410, 1236, 412, 1234, 414, 1232, 406, 1240, 408, 1238, 410, 417, 412, 416, 413, 1233, 405, 422, 407, 421, 408, 419, 410, 417, 412, 414, 404, 397, 432, 421, 408, 420, 409, 1237, 411, 1234, 414, 387, 432, 422, 407, 1239, 409, 418, 411, 416, 413, 414, 405, 423, 406, 1240, 408, 1237, 411, 417, 412, 415, 414, 414, 405, 422, 407, 421, 408, 418, 411, 416, 413, 414, 405, 423, 406, 421, 408, 419, 410, 417, 412, 416, 413, 414, 405, 422, 407, 421, 408, 419, 410, 416, 413, 414, 405, 423, 406, 421, 408, 419, 410, 417, 412, 416, 413, 414, 404, 423, 406, 421, 408, 419, 410, 417, 412, 414, 405, 423, 406, 421, 408, 419, 410, 417, 412, 416, 413, 414, 404, 423, 406, 421, 408, 419, 410, 417, 412, 416, 413, 413, 406, 422, 407, 420, 409, 418, 411, 416, 413, 1233, 405, 422, 407, 421, 408, 1237, 411, 1235, 413, 1206, 432, 1240, 408, 420, 409, 418, 411, 1235, 413, 415, 414};

void setup() {
    Serial.begin(115200);
    delay(1000);
    digitalWrite(48, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(36, HIGH);
    // delay(250);
    // Start the SPI bus with the specified pins
    spiBus.begin(39, 41, 40, 42);  // SCK, MISO, MOSI, CS pins
    // delay(250);
    // digitalWrite(42, LOW);
    if (!SD.begin(42, spiBus)) {  // Initialize the SD card with the CS pin and SPI bus
        Serial.println("Card Mount Failed");
        return;
    }

    irTools->init(SD);

    Serial.println("Loading avalible device types:");
    irTools->findDeviceTypes();

    std::vector<String> deviceTypes = irTools->getDeviceTypes();

    for (int i = 0; i < deviceTypes.size(); i++) {
        Serial.printf("%d. Device Type: %s\n", i, deviceTypes[i].c_str());
    }

    Serial.println("\nLoading avalible brands:");
    irTools->findDeviceBrands(44);

    std::vector<String> deviceBrands = irTools->getDeviceBrands();

    for (int i = 0; i < deviceBrands.size(); i++) {
        Serial.printf("%d. Device Brand: %s\n", i, deviceBrands[i].c_str());
    }

    irTools->findDevices(36);

    std::vector<String> devices = irTools->getDevices();

    // Print the device name
    Serial.printf("\nDevice Name: %s\n", devices[0].c_str());

    irTools->findDeviceCommands(0);
    deviceCommands = irTools->getDeviceCommands();

    for (int i = 0; i < deviceCommands.size(); i++) {
        Serial.printf("%d. Device Command: %s\n", i, deviceCommands[i].commandName.c_str());
    }
    Serial.println("");
}

void loop() {
    // Get user input for device command
    int deviceCommandIndex = 0;
    Serial.println("Enter the device command index: ");
    while (Serial.available() == 0) {
    }
    deviceCommandIndex = Serial.parseInt();
    Serial.printf("Device Command Index: %d\n", deviceCommandIndex);

    // Send the IR command
    if (irTools != nullptr) {
        irTools->sendIRCommand(deviceCommands[deviceCommandIndex]);
    } else {
        Serial.println("IRTools instance not initialized.");
    }

    delay(100);

    // Clear the input
    while (Serial.available() > 0) {
        Serial.read();
    }

    // irTools->captureIR(15);
    // irTools->sendRawIR(rawDataACOn, 259, 38);
}
