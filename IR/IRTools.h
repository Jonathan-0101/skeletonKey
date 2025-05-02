// IRTools.h
#ifndef IRTOOLS_H
#define IRTOOLS_H

/**
 * @file IRTools.h
 * @author Jonathan Woolf
 * @brief Library for IR attack tools
 * @version 1.0
 * @date 2025-03-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <SD.h>

#include <string>
#include <vector>

/**
 * @brief Enum to store the type of IR command
 *
 */
typedef enum {
    raw,
    parsed
} IRCommandType;

/**
 * @brief Struct to store IR device information
 *
 */
typedef struct {
    String deviceType;
    String deviceBrand;
    String deviceName;
    String IRFile;
} IRDeviceInfo;

/**
 * @brief Struct to store IR command information
 *
 */
typedef struct {
    IRDeviceInfo deviceInfo;
    String commandName;
    IRCommandType commandType;
    String commandProtocol;
    uint32_t parsedCommandAddress;
    uint32_t parsedCommandData;
    uint32_t rawCommandFrequency;
    float rawCommandDutyCycle;
    uint16_t rawCommandLength;
    std::vector<uint16_t> rawCommandData;
} IRCommand;

class IRTools {
   private:
    uint16_t kIrLed = 38;
    IRsend irsend;
    fs::SDFS *sd;
    std::vector<String> deviceTypes;
    std::vector<String> deviceBrands;
    std::vector<String> devices;
    std::vector<IRCommand> deviceCommands;
    String deviceType;
    String deviceBrand;
    String devicePath;
    String device;

    uint16_t jamSignal[2] = {65535, 0};

   public:
    /**
     * @brief Construct a new IRTools object
     *
     * @param sdInstance SD instance
     */
    IRTools(fs::SDFS &sdInstance);

    /**
     * @brief Function to send a custom raw IR command
     *
     * @param data Command data
     * @param length Command length
     * @param frequency Command frequency
     */
    void sendRawIR(uint16_t *data, uint16_t length, uint16_t frequency);

    /**
     * @brief Find the Avaliable Device Types
     *
     */
    void findDeviceTypes();

    /**
     * @brief Get the Device Types object
     *
     * @return std::vector<String>
     */
    std::vector<String> getDeviceTypes();

    /**
     * @brief Find the Avaliable Device Brands
     *
     * @param deviceTypeIndex Index of the device type
     */
    void findDeviceBrands(int deviceTypeIndex);

    /**
     * @brief Get the Device Brands object
     *
     * @return std::vector<String>
     */
    std::vector<String> getDeviceBrands();

    /**
     * @brief Find the Avaliable Devices
     *
     * @param deviceBrandIndex Index of the device brand
     */
    void findDevices(int deviceBrandIndex);

    /**
     * @brief Get the Devices object
     *
     * @return std::vector<String>
     */
    std::vector<String> getDevices();

    /**
     * @brief Get the Avaliable Device Commands object
     *
     * @param deviceIndex Index of the device
     */
    void findDeviceCommands(int deviceIndex);

    /**
     * @brief Get the Device Commands object
     *
     * @return std::vector<IRCommand>
     */
    std::vector<IRCommand> getDeviceCommands();

    /**
     * @brief Function to send an IR command
     *
     * @param irCommand
     */
    void sendIRCommand(IRCommand irCommand);

    /**
     * @brief Function to jam IR signals
     *
     * @param duration Duration to jam IR signals
     */
    void jamIR(int duration);
};

#endif  // IRTOOLS_H