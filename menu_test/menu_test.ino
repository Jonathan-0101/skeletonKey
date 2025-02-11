/*
    Project: Pen-testing Device
    File: menu_test.ino
    Author: Jonathan Woolf
    Created: 2025-01-19
    License: MIT

    Description: Design and testing of the menu sytem used in the project.

    Credits:
        - https://github.com/guttih/DisplayMenu/blob/main/examples/Menu/Menu.ino

    Libraries used:
        - Adafruit_GFX.h
        - TFT_eSPI.h
        - SPIFFS.h (for file system storage of configuration files)
        - Preferences.h (for storing states before sleep/reboot)
        - DisplayMenu.h (for creating the menu system)
        - SD.h (for SD card support)

    Hardware:
        - ESP32
        - 4.0" ILI9341 TFT touch screen (480x320)
        - SD card module (design based on Adafruit MicroSD card breakout board+ https://www.adafruit.com/product/254)

    Connections:
        - TFT CS -> ESP GPIO01
        - TFT Reset -> ESP EN/REST
        - TFT DC -> ESP GPIO02
        - TFT SDI (MOSI) -> ESP GPIO40
        - TFT SCK -> ESP GPIO39
        - TFT T_CLK -> ESP39
        - TFT T_CS -> ESP GPIO36
        - TFT T_DIN -> ESP GPIO40
        - TFT T_DO -> ESP GPIO41
        - TFT T_IRQ -> ESP GPIO35

*/

#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <DisplayMenu.h>
#include <FS.h>           // Filesystem support header
#include <Preferences.h>  // Used to store states before sleep/reboot
#include <SD.h>           // SD card support header
#include <SPI.h>
#include <SPIFFS.h>    // Filesystem support header
#include <TFT_eSPI.h>  // The TFT_eSPI library
#include <XPT2046_Touchscreen.h>
#include <pgmspace.h>  // PROGMEM support header

#define touchInterruptPin 35

#define CALIBRATION_FILE "/calibrationData"

#define REPEAT_CAL true

TFT_eSPI tft = TFT_eSPI();

int batteryLevel = 100;

bool vibration = true;

void toggleVibration() {
    // Toggle vibration
    vibration = !vibration;
    Serial.print("Vibration: ");
    Serial.println(vibration);
}

void touch_calibrate();

DisplayMenu menu = DisplayMenu(&tft);
void setup() {
    // Use serial port
    Serial.begin(115200);

    // Define button dimensions
    const uint16_t buttonWidth = 120;
    const uint16_t buttonHeight = 50;
    const uint16_t centerHorizontal = tft.width() / 2;
    const uint16_t centerVertical = tft.height() / 2;

    tft.begin();

    tft.setRotation(0);

    touch_calibrate();

    tft.fillScreen(TFT_WHITE);
    delay(100);
    tft.fillScreen(TFT_BLACK);
    delay(100);

    // Logo is a 256x64 bitmap stored in the SD card in /images/logo.txt as plain bytes
    // Display the logo centered on the screen
    // if (SD.begin()) {
    //     File file = SD.open("/images/logo.txt");
    //     if (file) {
    //         uint8_t logo[256 * 64];
    //         file.read(logo, 256 * 64);
    //         file.close();
    //         tft.drawBitmap((tft.width() - 256) / 2, (tft.height() - 64) / 2, logo, 256, 64, TFT_WHITE, TFT_BLACK);
    //     }
    // }

    delay(500);

    // Create the main menu
    DisplayPage *page_mainMenu, *page_RFID, *page_subGHz, *page_wifi, *page_bluetooth, *page_badUSB, *page_IR, *page_settings;
    DisplayLabel *page_label;

    // Create array of submenus
    DisplayPage *subMenus[] = {page_RFID, page_subGHz, page_wifi, page_bluetooth, page_badUSB, page_IR, page_settings};
    // create a char text array for the submenus
    const char *subMenuNames[] = {"RFID", "Sub-GHz", "WiFi", "Bluetooth", "BadUSB", "IR", "Settings"};

    // Add pages to the menu
    page_mainMenu = menu.addPage();
    page_RFID = menu.addPage();
    page_subGHz = menu.addPage();
    page_wifi = menu.addPage();
    page_bluetooth = menu.addPage();
    page_badUSB = menu.addPage();
    page_IR = menu.addPage();
    page_settings = menu.addPage();

    // Add labels to the main menu
    page_label = page_mainMenu->addPageLabel(centerHorizontal, 0, buttonWidth, buttonHeight, page_mainMenu->getFillColor(), page_mainMenu->getFillColor(), TFT_WHITE, 1, "Main menu");
    page_label->setTextAlign(ALIGN_CENTER, 0, 0);

    // // Add labels to all pages
    // for (int i = 0; i < 7; i++) {
    //     page_label = subMenus[i]->addPageLabel(centerHorizontal, 0, buttonWidth, buttonHeight, subMenus[i]->getFillColor(), subMenus[i]->getFillColor(), TFT_WHITE, 1, subMenuNames[i]);
    //     page_label->setTextAlign(ALIGN_CENTER, 0, 0);
    // }

    // Add buttons to the pages on the main menu
    page_mainMenu->addPageButton(centerHorizontal - (buttonWidth / 2), centerVertical - 50, buttonWidth, buttonHeight, TFT_WHITE, TFT_BLACK, TFT_WHITE, 1, "RFID", page_RFID);
    page_mainMenu->addPageButton(centerHorizontal + (buttonWidth / 2), centerVertical - 50, buttonWidth, buttonHeight, TFT_WHITE, TFT_BLACK, TFT_WHITE, 1, "Sub-GHz", page_subGHz);
    page_mainMenu->addPageButton(centerHorizontal - (buttonWidth / 2), centerVertical, buttonWidth, buttonHeight, TFT_WHITE, TFT_BLACK, TFT_WHITE, 1, "WiFi", page_wifi);
    page_mainMenu->addPageButton(centerHorizontal + (buttonWidth / 2), centerVertical, buttonWidth, buttonHeight, TFT_WHITE, TFT_BLACK, TFT_WHITE, 1, "Bluetooth", page_bluetooth);
    page_mainMenu->addPageButton(centerHorizontal - (buttonWidth / 2), centerVertical + 50, buttonWidth, buttonHeight, TFT_WHITE, TFT_BLACK, TFT_WHITE, 1, "BadUSB", page_badUSB);
    page_mainMenu->addPageButton(centerHorizontal + (buttonWidth / 2), centerVertical + 50, buttonWidth, buttonHeight, TFT_WHITE, TFT_BLACK, TFT_WHITE, 1, "IR", page_IR);
    page_mainMenu->addPageButton(centerHorizontal, centerVertical + 100, buttonWidth, buttonHeight, TFT_WHITE, TFT_BLACK, TFT_WHITE, 1, "Settings", page_settings);

    // // Add open main menu button to all pages
    // for (int i = 0; i < 7; i++) {
    //     subMenus[i]->addPageButton(centerHorizontal, centerVertical + 150, buttonWidth, buttonHeight, TFT_WHITE, TFT_BLACK, TFT_WHITE, 1, "Main menu", menu.getPage(0));
    // }

    // Add buttons to the settings page
    // page_settings->addPageButton(centerHorizontal, centerVertical - 100, buttonWidth, buttonHeight, TFT_WHITE, TFT_BLACK, TFT_WHITE, 1, "Vibration", toggleVibration);

    // Show the main menu
    menu.showPage(0);
}

void loop() {
    menu.update();
}

void touch_calibrate() {
    uint16_t calData[5];
    uint8_t calDataOK = 0;

    // check file system exists
    if (!SPIFFS.begin()) {
        Serial.println("formatting file system");
        SPIFFS.format();
        SPIFFS.begin();
    }

    // check if calibration file exists and size is correct
    if (SPIFFS.exists(CALIBRATION_FILE)) {
        if (REPEAT_CAL) {
            // Delete if we want to re-calibrate
            SPIFFS.remove(CALIBRATION_FILE);
        } else {
            File f = SPIFFS.open(CALIBRATION_FILE, "r");
            if (f) {
                if (f.readBytes((char *)calData, 14) == 14)
                    calDataOK = 1;
                f.close();
            }
        }
    }

    if (calDataOK && !REPEAT_CAL) {
        // calibration data valid
        tft.setTouch(calData);
    } else {
        // data not valid so recalibrate
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(20, 0);
        tft.setTextFont(2);
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);

        tft.println("Touch corners as indicated");

        tft.setTextFont(1);
        tft.println();

        if (REPEAT_CAL) {
            tft.setTextColor(TFT_RED, TFT_BLACK);
            tft.println("Set REPEAT_CAL to false to stop this running again!");
        }

        tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

        tft.setTextColor(TFT_GREEN, TFT_BLACK);
        tft.println("Calibration complete!");

        // store data
        File f = SPIFFS.open(CALIBRATION_FILE, "w");
        if (f) {
            f.write((const unsigned char *)calData, 14);
            f.close();
        }
    }
}