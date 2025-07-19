#include <FS.h>

#include "SD.h"
#include "SPI.h"

// Create an instance of the SPI class
SPIClass spiBus = SPIClass(HSPI);  // Use HSPI for the SD card

void setup() {
    Serial.begin(115200);
    delay(1000);
    digitalWrite(48, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(36, HIGH);
    delay(250);
    // Start the SPI bus with the specified pins
    spiBus.begin(39, 41, 40, 42);  // SCK, MISO, MOSI, CS pins
    // delay(250);
    // digitalWrite(42, LOW);
    if (!SD.begin(42, spiBus)) {  // Initialize the SD card with the CS pin and SPI bus
        Serial.println("Card Mount Failed");
        return;
    }
    Serial.println("Success");  // Print success message if SD card is initialized

    File root = SD.open("/");  // Open the root directory of the SD card

    // Open the file settings.txt and read the contents
    File file = SD.open("/settings.txt", FILE_READ);
    if (file) {
        Serial.println("File opened successfully");
        while (file.available()) {      // Read the file until the end
            Serial.write(file.read());  // Print the contents to the serial monitor
        }
        file.close();  // Close the file after reading
    } else {
        Serial.println("Failed to open file");  // Print error message if file cannot be opened
    }
}

void loop() {
    // Nothing to do here
}