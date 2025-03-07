// IRTools.h
#ifndef IRTOOLS_H
#define IRTOOLS_H

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <SD.h>

#include <string>
#include <vector>

typedef enum {
    raw,
    parsed
} IRCommandType;

typedef struct {
    String deviceType;
    String deviceBrand;
    String deviceName;
    String IRFile;
} IRDeviceInfo;

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
    uint16_t kIrLed = 20;
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

   public:
    IRTools(fs::SDFS &sdInstance);
    void sendRawIR(uint16_t *data, uint16_t length, uint16_t frequency);
    void getAvaliableDeviceTypes();
    std::vector<String> getDeviceTypes();
    void getAvaliableDeviceBrands(int deviceTypeIndex);
    std::vector<String> getDeviceBrands();
    void getAvaliableDevices(int deviceBrandIndex);
    std::vector<String> getDevices();
    void getAvaliableDeviceCommands(int deviceIndex);
    std::vector<IRCommand> getDeviceCommands();
    void sendIRCommand(IRCommand irCommand);
};

#endif  // IRTOOLS_H