#include <FS.h>
#include <SD.h>
#include <SPI.h>

#include <string>
#include <vector>

#include "IRTools.h"

// MOSI=40 CLK=39 MISO=41

void setup() {
    Serial.begin(115200);
    delay(1000);

    digitalWrite(42, HIGH);

    // Initialize SPI bus and SD card
    SPI.begin(39, 41, 40, 42);
    if (!SD.begin(42)) {
        Serial.println("Card Mount Failed");
        return;
    }

    IRTools irTools(SD);

    // IRTools irTools;
    uint16_t rawDataACOn[259] = {3302, 1644, 408, 419, 410, 416, 413, 1233, 405, 423, 406, 1239, 409, 419, 410, 417, 412, 415, 414, 1232, 406, 1241, 407, 419, 410, 417, 412, 416, 413, 1233, 405, 1241, 407, 394, 435, 419, 410, 417, 412, 416, 413, 387, 432, 422, 407, 420, 409, 418, 411, 416, 413, 415, 404, 423, 406, 421, 408, 420, 409, 1237, 411, 416, 413, 413, 406, 422, 407, 420, 409, 418, 411, 417, 412, 415, 414, 1232, 406, 421, 408, 420, 409, 418, 411, 416, 413, 1232, 406, 1240, 408, 1238, 410, 1236, 412, 1234, 414, 1232, 406, 1240, 408, 1238, 410, 417, 412, 416, 413, 1233, 405, 422, 407, 421, 408, 419, 410, 417, 412, 414, 404, 397, 432, 421, 408, 420, 409, 1237, 411, 1234, 414, 387, 432, 422, 407, 1239, 409, 418, 411, 416, 413, 414, 405, 423, 406, 1240, 408, 1237, 411, 417, 412, 415, 414, 414, 405, 422, 407, 421, 408, 418, 411, 416, 413, 414, 405, 423, 406, 421, 408, 419, 410, 417, 412, 416, 413, 414, 405, 422, 407, 421, 408, 419, 410, 416, 413, 414, 405, 423, 406, 421, 408, 419, 410, 417, 412, 416, 413, 414, 404, 423, 406, 421, 408, 419, 410, 417, 412, 414, 405, 423, 406, 421, 408, 419, 410, 417, 412, 416, 413, 414, 404, 423, 406, 421, 408, 419, 410, 417, 412, 416, 413, 413, 406, 422, 407, 420, 409, 418, 411, 416, 413, 1233, 405, 422, 407, 421, 408, 1237, 411, 1235, 413, 1206, 432, 1240, 408, 420, 409, 418, 411, 1235, 413, 415, 414};

    uint16_t rawDataACOff[115] = {3302, 1618, 435, 393, 436, 391, 438, 1207, 431, 396, 433, 1213, 435, 392, 437, 391, 438, 388, 441, 1206, 432, 1214, 434, 392, 437, 389, 440, 388, 431, 1215, 433, 1213, 435, 392, 437, 390, 439, 388, 431, 396, 433, 395, 434, 392, 437, 390, 439, 388, 431, 396, 433, 394, 435, 392, 437, 390, 439, 388, 441, 1205, 433, 395, 434, 392, 437, 389, 440, 388, 431, 396, 433, 394, 435, 392, 437, 1209, 439, 388, 431, 397, 432, 394, 435, 393, 436, 1210, 438, 387, 432, 396, 433, 394, 435, 392, 437, 390, 439, 388, 431, 1215, 433, 394, 435, 1211, 437, 1208, 440, 1205, 433, 1213, 435, 1211, 437, 1209, 439};

    irTools.sendRawIR(rawDataACOn, 259, 38);
    delay(5000);
    irTools.sendRawIR(rawDataACOff, 115, 38);
    delay(5000);

    irTools.getAvaliableDeviceTypes();

    std::vector<String> deviceTypes = irTools.getDeviceTypes();

    for (int i = 0; i < deviceTypes.size(); i++) {
        Serial.printf("%d Device Type : %s\n", i, deviceTypes[i].c_str());
    }

    // get serial input for device type
    int deviceTypeIndex = 0;
    Serial.println("Enter the device type index: ");
    while (Serial.available() == 0) {
    }
    deviceTypeIndex = Serial.parseInt();
    Serial.printf("Device Type Index : %d\n", deviceTypeIndex);

    irTools.getAvaliableDeviceBrands(deviceTypeIndex);

    std::vector<String> deviceBrands = irTools.getDeviceBrands();

    for (int i = 0; i < deviceBrands.size(); i++) {
        Serial.printf("%d Device Brand : %s\n", i, deviceBrands[i].c_str());
    }
}

void loop() {
    // put your main code here, to run repeatedly:
}