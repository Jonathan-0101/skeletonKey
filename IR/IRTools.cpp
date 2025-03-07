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
    // Clear the devices vector
    devices.clear();

    // Set the device brand
    deviceBrand = deviceBrands[deviceBrandIndex];

    // Get a list of all the .ir files that exist in the device brand folder
    File root = sd->open("/IR/" + deviceType + "/" + deviceBrand);
    if (!root) {
        Serial.println("Failed to open directory");
        return;
    }

    // List all of the files in the brand directory
    while (File file = root.openNextFile()) {
        if (!file.isDirectory()) {
            // DEBUG
            // Serial.printf("Device : %s\n", file.name().c_str());

            // Add the file name to the devices vector
            devices.push_back(file.name());
        }
        file.close();
    }
}

std::vector<String> IRTools::getDevices() {
    if (devices.empty()) {
        Serial.println("No devices available for this brand");
    }
    return devices;
}

void IRTools::getAvaliableDeviceCommands(int deviceIndex) {
    // Clear the deviceCommands vector
    deviceCommands.clear();

    String device = devices[deviceIndex];

    // Set the device path
    devicePath = "/IR/" + deviceType + "/" + deviceBrand + "/" + device;

    // DEBUG
    // Serial.printf("Device Path : %s\n", devicePath.c_str());

    // Open the device file
    File file = sd->open(devicePath);
    if (!file) {
        Serial.println("Failed to open file");
        return;
    }

    // Create the IRDeviceInfo object
    IRDeviceInfo deviceInfo;
    deviceInfo.deviceType = deviceType;
    deviceInfo.deviceBrand = deviceBrand;
    deviceInfo.deviceName = device;
    deviceInfo.IRFile = devicePath;

    IRCommand irCommand;
    String line;

    while (file.available()) {
        line = file.readStringUntil('\n');

        // Check if the line is a command name
        if (line.startsWith("name: ")) {
            irCommand.commandName = line.substring(6);
        } else if (line.startsWith("type: ")) {
            if (line.substring(6) == "raw") {
                irCommand.commandType = raw;
            } else {
                irCommand.commandType = parsed;
            }
        } else if (line.startsWith("protocol: ")) {
            irCommand.commandProtocol = line.substring(10);
        } else if (line.startsWith("address: ")) {
            irCommand.parsedCommandAddress = line.substring(9).toInt();
        } else if (line.startsWith("command: ")) {
            irCommand.parsedCommandData = line.substring(9).toInt();

            // Add the IRCommand to the deviceCommands vector
            irCommand.deviceInfo = deviceInfo;
            deviceCommands.push_back(irCommand);

            // Clear the irCommand object
            irCommand = IRCommand();
        } else if (line.startsWith("frequency: ")) {
            irCommand.rawCommandFrequency = line.substring(11).toInt();
        } else if (line.startsWith("dutyCycle: ")) {
            irCommand.rawCommandDutyCycle = line.substring(11).toFloat();
        } else if (line.startsWith("length: ")) {
            irCommand.rawCommandLength = line.substring(8).toInt();
        } else if (line.startsWith("data: ")) {
            // Get the raw command data, each value is separated by a space
            String data = line.substring(6);
            int spaceIndex = 0;
            int prevSpaceIndex = 0;
            while (spaceIndex != -1) {
                spaceIndex = data.indexOf(' ', prevSpaceIndex);
                if (spaceIndex != -1) {
                    irCommand.rawCommandData.push_back(data.substring(prevSpaceIndex, spaceIndex).toInt());
                    prevSpaceIndex = spaceIndex + 1;
                } else {
                    irCommand.rawCommandData.push_back(data.substring(prevSpaceIndex).toInt());
                }
            }

            irCommand.rawCommandLength = irCommand.rawCommandData.size();

            // Add the IRCommand to the deviceCommands vector
            irCommand.deviceInfo = deviceInfo;
            deviceCommands.push_back(irCommand);

            // Clear the irCommand object
            irCommand = IRCommand();
        } else {
            // DEBUG
            // Serial.printf("Unknown Line : %s\n", line.c_str());
        }
    }
}

std::vector<IRCommand> IRTools::getDeviceCommands() {
    // Check if the deviceCommands vector is empty
    if (deviceCommands.empty()) {
        Serial.println("No commands available for this device");
    }
    return deviceCommands;
}

void IRTools::sendIRCommand(IRCommand irCommand) {
    // Check the command type
    if (irCommand.commandType == raw) {
        irsend.sendRaw(irCommand.rawCommandData.data(), irCommand.rawCommandLength, irCommand.rawCommandFrequency);
    } else if (irCommand.commandType == parsed) {
        // Check the protocol
        String protocol = irCommand.commandProtocol;
        if (protocol == "NEC") {
            irsend.sendNEC(irCommand.parsedCommandAddress, irCommand.parsedCommandData);
        } else if (protocol == "NECext") {
            // Placeholder for the NEC extended protocol
        } else if (protocol == "NEC42") {
            // Placeholder for the NEC 42 protocol
        } else if (protocol == "NEC42ext") {
            // Placeholder for the NEC 42 extended protocol
        } else if (protocol == "Samsung32") {
            irsend.sendSAMSUNG(irCommand.parsedCommandData, 32);
        } else if (protocol == "RC6") {
            irsend.sendRC6(irCommand.parsedCommandData);
        } else if (protocol == "RC5") {
            irsend.sendRC5(irCommand.parsedCommandData);
        } else if (protocol == "RC5X") {
            // Placeholder for the RC5X protocol
        } else if (protocol == "SIRC") {
            // Placeholder for the SIRC protocol
        } else if (protocol == "SIRC15") {
            // Placeholder for the SIRC 15 protocol
        } else if (protocol == "SIRC20") {
            // Placeholder for the SIRC 20 protocol
        } else if (protocol == "Kaseikyo") {
            // Placeholder for the Kaseikyo protocol
        } else if (protocol == "RCA") {
            // Placeholder for the RCA protocol
        }
    }
}

void IRTools::jamIR(int duration) {
    // Get the current time
    unsigned long startTime = millis();

    while (millis() - startTime < duration * 1000) {
        irsend.sendRaw(jamSignal, 2, 38);
        delay(50);
    }
}