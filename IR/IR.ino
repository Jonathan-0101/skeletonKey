#include <FS.h>
#include <SD.h>
#include <SPI.h>

#include <string>
#include <vector>

#include "IRTools.h"

// MOSI=40 CLK=39 MISO=41

IRTools* irTools = nullptr;             // Declare a pointer for irTools
std::vector<IRCommand> deviceCommands;  // Declare deviceCommands globally

void setup() {
    Serial.begin(115200);
    delay(500);

    digitalWrite(42, HIGH);

    delay(500);

    // Initialize SPI bus and SD card
    SPI.begin(39, 41, 40, 42);
    if (!SD.begin(42)) {
        Serial.println("Card Mount Failed");
        return;
    }

    irTools = new IRTools(SD);  // Initialize irTools after SD card is ready

    irTools->getAvaliableDeviceTypes();

    // std::vector<String> deviceTypes = irTools->getDeviceTypes();

    // for (int i = 0; i < deviceTypes.size(); i++) {
    //     Serial.printf("%d Device Type : %s\n", i, deviceTypes[i].c_str());
    // }

    irTools->getAvaliableDeviceBrands(44);

    // std::vector<String> deviceBrands = irTools->getDeviceBrands();

    // for (int i = 0; i < deviceBrands.size(); i++) {
    //     Serial.printf("%d Device Brand : %s\n", i, deviceBrands[i].c_str());
    // }

    irTools->getAvaliableDevices(36);

    std::vector<String> devices = irTools->getDevices();

    // Print the device name
    Serial.printf("Device Name : %s\n", devices[0].c_str());

    irTools->getAvaliableDeviceCommands(0);
    deviceCommands = irTools->getDeviceCommands();

    for (int i = 0; i < deviceCommands.size(); i++) {
        Serial.printf("%d Device Command : %s\n", i, deviceCommands[i].commandName.c_str());
    }
}

void loop() {
    // Get user input for device command
    int deviceCommandIndex = 0;
    Serial.println("Enter the device command index: ");
    while (Serial.available() == 0) {
    }
    deviceCommandIndex = Serial.parseInt();
    Serial.printf("Device Command Index : %d\n", deviceCommandIndex);

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
}
