#include "IRTools.h"

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <SD.h>

#include <string>
#include <vector>

IRTools::IRTools(fs::SDFS& sdInstance) : irsend(kIrLed) {
    irsend.begin();
    sd = &sdInstance;
}

void IRTools::sendRawIR(uint16_t* data, uint16_t length, uint16_t frequency) {
    irsend.sendRaw(data, length, frequency);
}

void IRTools::getAvaliableDeviceTypes() {
    // Clear the deviceTypes and deviceBrands vectors
    deviceTypes.clear();
    deviceBrands.clear();

    // Get a list of all the device types available which are stored as folders in the SD card in the IR folder
    File root = sd->open("/IR");
    if (!root) {
        Serial.println("Failed to open directory");
        return;
    }

    // List all of the folders in the IR directory
    while (File file = root.openNextFile()) {
        if (file.isDirectory()) {
            // DEBUG
            // Serial.printf("Device Type : %s\n", file.name().c_str());

            // Add the folder name to the deviceTypes vector
            deviceTypes.push_back(file.name());
        }
        file.close();
    }
}

std::vector<String> IRTools::getDeviceTypes() {
    return deviceTypes;
}

void IRTools::getAvaliableDeviceBrands(int deviceTypeIndex) {
    // Clear the deviceBrands vector
    deviceBrands.clear();

    // Set the device type
    deviceType = deviceTypes[deviceTypeIndex];

    // Get a list of all the device brands available which are stored as folders in the SD card in the IR folder
    File root = sd->open("/IR/" + deviceType);
    if (!root) {
        Serial.println("Failed to open directory");
        return;
    }

    // List all of the folders in the brand directory
    while (File file = root.openNextFile()) {
        if (file.isDirectory()) {
            // DEBUG
            // Serial.printf("Device Brand : %s\n", file.name().c_str());

            // Add the folder name to the deviceBrands vector
            deviceBrands.push_back(file.name());
        }
        file.close();
    }
}

std::vector<String> IRTools::getDeviceBrands() {
    return deviceBrands;
}

void IRTools::getAvaliableDevices(int deviceBrandIndex) {
    // // Clear the deviceCommands vector
    // devices.clear();

    // // Set the device brand
    // device = deviceBrands[deviceBrandIndex];

    // // Search the for all .ir files within the device brand folder
    // File root = sd->open("/IR/" + deviceType + "/" + deviceBrand);
    // if (!root) {
    //     Serial.println("Failed to open directory");
    //     return;
    // }

    // // List all of the .ir files in the brand directory and subdirectories
    // while (File file = root.openNextFile()) {
    //     if (!file.isDirectory() && file.name().endsWith(".ir")) {
    //         // DEBUG
    //         // Serial.printf("Device : %s\n", file.name().c_str());

    //         // Add the file name to the devices vector
    //         devices.push_back(file.name());
    //     }
    //     file.close();
    // }
}

std::vector<String> IRTools::getDevices() {
    return devices;
}

void IRTools::getAvaliableDeviceCommands(String device) {
    // // Clear the deviceCommands vector
    // deviceCommands.clear();

    // // Set the device path
    // devicePath = "/IR/" + deviceType + "/" + deviceBrand + "/" + device + ".ir";

    // // Open the device file
    // File file = sd->open(devicePath);
    // if (!file) {
    //     Serial.println("Failed to open file");
    //     return;
    // }

    // Get each command from the file which is stored on a new line begining with
}