#include <string>
#include <vector>
#include <FS.h>
#include "IRTools.h"
#include "SD.h"
#include "SPI.h"

std::vector<IRCommand> deviceCommands;  // Declare deviceCommands globally

IRTools *irTools = new IRTools();  // Create an instance of IRTools

void setup() {
    Serial.begin(115200);
    delay(1000);

    // digitalWrite(42, HIGH);
    digitalWrite(48, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(36, HIGH);
    delay(250);
    SPI.begin(39, 41, 40, 42);
    // delay(250);
    // digitalWrite(42, LOW);
    if (!SD.begin(42)) {
        Serial.println("Card Mount Failed");
        return;
    }

    irTools->init(SD);

    Serial.println("Loading avalible device types:");
    irTools->findDeviceTypes();

    std::vector<String> deviceTypes = irTools->getDeviceTypes();

    for (int i = 0; i < 5; i++) {
        Serial.printf("%d. Device Type: %s\n", i, deviceTypes[i].c_str());
    }

    Serial.println("\nLoading avalible brands:");
    irTools->findDeviceBrands(44);

    std::vector<String> deviceBrands = irTools->getDeviceBrands();

    for (int i = 0; i < 5; i++) {
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
}
