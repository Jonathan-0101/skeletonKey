/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("Logitech", "Logitech", 100);

void setup() {
    Serial.begin(115200);
    Serial.println("Starting BLE work!");
    bleKeyboard.begin();

    while (!bleKeyboard.isConnected()) {
        delay(10);
    }

    if (bleKeyboard.isConnected()) {
        bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.press('r');
        delay(100);
        bleKeyboard.releaseAll();
        bleKeyboard.println("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    }
}

void loop() {
    delay(5000);
}
