// IRTools.h
#ifndef IRTOOLS_H
#define IRTOOLS_H

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <SD.h>

#include <string>
#include <vector>

class IRTools {
   private:
    uint16_t kIrLed = 20;
    IRsend irsend;
    fs::SDFS *sd;
    std::vector<String> deviceTypes;
    std::vector<String> deviceBrands;
    std::vector<String> devices;
    std::vector<String> deviceCommands;
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
    void getAvaliableDeviceCommands(String device);
    std::vector<String> getDeviceCommands();
};

#endif  // IRTOOLS_H