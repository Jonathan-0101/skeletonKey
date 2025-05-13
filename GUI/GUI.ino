//<App !Start!>
// FILE: [GUI.ino]
// Created by GUIslice Builder version: [0.17.b40]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include <Arduino.h>
#include <FS.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <VibrationMotor.h>

#include <array>
#include <vector>

#include "GUI_GSLC.h"
#include "SD.h"
#include "SubGHzTools.h"
#include "TFT_eSPI.h"
#include "WiFiTools.h"

// ------------------------------------------------
// Program Globals
// ------------------------------------------------
bool bootScreen = true;
bool vibrationEnabled;
bool batteryConnected = true;
int deauthStatus = 0;
long bootScreenDelay = 1500;
long bootScreenStart;
const int motorPin = 18;
const int batteryPin = 4;
int batteryVoltageADC = 0;
float batteryVoltage = 0;
float batteryPercent = 0;

pageOptions currentPage = mainMenu;

VibrationMotor vibro(motorPin);
WiFiTools wifiTools;

SPIClass& tftSPIInstance = SPI;

std::vector<wifi_ap_record_t> foundWiFiNetworks;
int numberOfNetworks = 0;

SubGHzTools subGHzTools;

SubGHzTools_flag currentSubGHzAppMode = IDLE;

#define DEBUG true  // set to true for debug output, false for no debug output
#define DEBUG_SERIAL \
    if (DEBUG) Serial

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* batteryChrgTxt = NULL;
gslc_tsElemRef* m_pElemBtn10 = NULL;
gslc_tsElemRef* m_pElemListbox_SubGHz = NULL;
gslc_tsElemRef* m_pElemListbox_WiFi = NULL;
gslc_tsElemRef* m_pElemOutTxt1 = NULL;
gslc_tsElemRef* m_pListSlider_SubGHz = NULL;
gslc_tsElemRef* m_pListSlider_WiFi = NULL;
gslc_tsElemRef* m_pSettingsVibroButtonTxt = NULL;
gslc_tsElemRef* m_pSubGHzJammingButton = NULL;
gslc_tsElemRef* m_pWiFiDeauthButtonTxt = NULL;
gslc_tsElemRef* m_pWiFiDeauthButtonTxt16_18 = NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) {
    if (ch == (char)'\n')
        Serial.println("");
    else
        Serial.write(ch);
    return 0;
}

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui, void* pvElemRef, gslc_teTouch eTouch, int16_t nX, int16_t nY) {
    // Typecast the parameters to match the GUI and element types
    gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
    gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
    gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);

    if (eTouch == GSLC_TOUCH_UP_IN) {
        // From the element's ID we can determine which button was pressed.
        switch (pElem->nId) {
                //<Button Enums !Start!>
            case Base_Button_home:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "Main Menu");
                gslc_SetPageCur(&m_gui, E_PG_MAIN);
                currentPage = mainMenu;
                break;
            case Base_Button_settings:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "Settings");
                gslc_SetPageCur(&m_gui, E_PG_Settings);
                currentPage = settingsMenu;
                break;
            case Main_Button_RFID:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "RFID");
                gslc_SetPageCur(&m_gui, E_PG_RFID);
                currentPage = rfidMenu;
                break;
            case Main_Button_SubGHz:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "Sub-GHz");
                gslc_SetPageCur(&m_gui, E_PG_SubGHz);
                currentPage = subGHzMenu;
                subGHzTools.init();
                break;
            case Main_Button_WIFI:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "WiFi");
                gslc_SetPageCur(&m_gui, E_PG_WIFI);
                currentPage = wifiMenu;
                wifiTools.initWiFiTools(SD);
                break;
            case Main_Button_BadUSB:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "Bad USB");
                gslc_SetPageCur(&m_gui, E_PG_USB);
                currentPage = usbMenu;
                break;
            case Main_Button_BLE:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "Bluetooth");
                gslc_SetPageCur(&m_gui, E_PG_BLE);
                currentPage = bleMenu;
                break;
            case Main_Button_IR:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "IR");
                gslc_SetPageCur(&m_gui, E_PG_IR);
                currentPage = irMenu;
                break;
            case Settings_Button_calibrateTouch:
                break;
            case Settings_Button_vibrationToggle:
                if (vibrationEnabled == 0) {
                    vibrationEnabled = 1;
                    // Set the button text to "Vibration Enabled"
                    gslc_ElemSetTxtStr(&m_gui, m_pSettingsVibroButtonTxt, "Vibration Enabled");
                    // Set the button color to green
                    gslc_ElemSetCol(&m_gui, m_pSettingsVibroButtonTxt, GSLC_COL_BLUE_DK2, GSLC_COL_GREEN_DK3, GSLC_COL_BLUE_DK1);
                    // Write to the SD card to enable vibration replacing the contents of the first line
                    File settingsFile = SD.open("/settings.txt", FILE_WRITE);
                    if (settingsFile) {
                        settingsFile.println("vibration:enabled");
                        settingsFile.close();
                        DEBUG_SERIAL.println("Vibration enabled in settings file.");
                    } else {
                        DEBUG_SERIAL.println("Failed to open settings file for writing!");
                    }
                } else {
                    vibrationEnabled = 0;
                    // Set the button text to "Vibration Disabled"
                    gslc_ElemSetTxtStr(&m_gui, m_pSettingsVibroButtonTxt, "Vibration Disabled");
                    // Set the button color to red
                    gslc_ElemSetCol(&m_gui, m_pSettingsVibroButtonTxt, GSLC_COL_BLUE_DK2, GSLC_COL_RED_DK2, GSLC_COL_BLUE_DK1);
                    // Write to the SD card to disable vibration replacing the contents of the first line
                    File settingsFile = SD.open("/settings.txt", FILE_WRITE);
                    if (settingsFile) {
                        settingsFile.println("vibration:disabled");
                        settingsFile.close();
                        DEBUG_SERIAL.println("Vibration disabled in settings file.");
                    } else {
                        DEBUG_SERIAL.println("Failed to open settings file for writing!");
                    }
                }
                break;
            case SubGHz_Button_jaming:
                if (currentSubGHzAppMode == IDLE) {
                    // Set the button text to "Jamming Enabled"
                    gslc_ElemSetTxtStr(&m_gui, m_pSubGHzJammingButton, "Jamming Enabled");
                    // Set the button color to green
                    gslc_ElemSetCol(&m_gui, m_pSubGHzJammingButton, GSLC_COL_BLUE_DK2, GSLC_COL_GREEN_DK3, GSLC_COL_BLUE_DK1);
                    // Start the jamming attack
                    subGHzTools.startJamming();
                    // Set the current mode to jamming
                    currentSubGHzAppMode = JAMMER;
                } else {
                    // Set the button text to "Jamming Disabled"
                    gslc_ElemSetTxtStr(&m_gui, m_pSubGHzJammingButton, "Jamming Disabled");
                    // Set the button color to red
                    gslc_ElemSetCol(&m_gui, m_pSubGHzJammingButton, GSLC_COL_BLUE_DK2, GSLC_COL_RED_DK2, GSLC_COL_BLUE_DK1);
                    // Stop the jamming attack
                    subGHzTools.stopJamming();
                    // Set the current mode to idle
                    currentSubGHzAppMode = IDLE;
                }
                break;
            case SubGHz_Button_capture:
                subGHzTools.captureRaw(1);
                break;
            case SubGHz_Button_frequency:
                break;
            case SubGHz_Button_transmit:
                subGHzTools.transmitRaw(1);
                break;
            case WiFi_Button_rickRollBeacon:
                // Start the Rick Roll beacon attack
                wifiTools.rickRollBeaconSpam(15000);  // 15 seconds duration
                break;
            case WiFi_Button_scanNetworks:
                // Start the WiFi network scan
                wifiTools.scanWiFiNetworks();
                // // Get the available networks and update the listbox
                gslc_ElemXListboxReset(&m_gui, m_pElemListbox_WiFi);
                foundWiFiNetworks = wifiTools.getAvailableNetworks();
                numberOfNetworks = foundWiFiNetworks.size();
                for (int i = 0; i < numberOfNetworks; i++) {
                    char ssid[34];  // Increase size to 65 to accommodate longer SSIDs
                    strncpy(ssid, (const char*)foundWiFiNetworks[i].ssid, 33);
                    ssid[33] = '\0';  // Ensure null termination
                    gslc_ElemXListboxAddItem(&m_gui, m_pElemListbox_WiFi, ssid);
                    memset(ssid, 0, sizeof(ssid));
                }
                break;
            case WiFi_Button_deauth:
                if (deauthStatus == 0) {
                    deauthStatus = 1;
                    // Set the button text to "Deauthentication Enabled"
                    gslc_ElemSetTxtStr(&m_gui, m_pWiFiDeauthButtonTxt, "Deauthentication Enabled");
                    // Set the button color to green
                    gslc_ElemSetCol(&m_gui, m_pWiFiDeauthButtonTxt, GSLC_COL_BLUE_DK2, GSLC_COL_GREEN_DK3, GSLC_COL_BLUE_DK1);
                    // // get the selected item from the listbox
                    int16_t nSelId = gslc_ElemXListboxGetSel(&m_gui, m_pElemListbox_WiFi);
                    char ssid[34];  // Increase size to 65 to accommodate longer SSIDs
                    strncpy(ssid, (const char*)foundWiFiNetworks[nSelId].ssid, 33);
                    DEBUG_SERIAL.printf("Selected SSID: %s\n", ssid);
                    // // convet nSelId to an int
                    int networkIndex = nSelId;
                    wifiTools.deauthNetwork(NULL, NULL, NULL, networkIndex, NULL, 5000, 1, 2);
                } else {
                    deauthStatus = 0;
                    // Set the button text to "Deauthentication Disabled"
                    gslc_ElemSetTxtStr(&m_gui, m_pWiFiDeauthButtonTxt, "Deauthentication Disabled");
                    // Set the button color to red
                    gslc_ElemSetCol(&m_gui, m_pWiFiDeauthButtonTxt, GSLC_COL_BLUE_DK2, GSLC_COL_RED_DK2, GSLC_COL_BLUE_DK1);
                }
                break;
            case WiFi_Button_handshake:
                gslc_PopupShow(&m_gui, E_Popup_HandshakeCapture, true);
                break;
            case HandshakeCapture_Button_passive:
                gslc_PopupHide(&m_gui);
                break;
            case HandshakeCapture_Button_active:
                gslc_PopupHide(&m_gui);
                break;
            case HandshakeCapture_Button_exit:
                gslc_PopupHide(&m_gui);
                break;
                //<Button Enums !End!>
            default:
                break;
        }
    }
    return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId) {
    gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
    gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
    gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
    char acTxt[MAX_STR + 1];

    if (pElemRef == NULL) {
        return false;
    }

    // From the element's ID we can determine which listbox was active.
    switch (pElem->nId) {
            //<Listbox Enums !Start!>

        case WiFi_Listbox_networks:
            if (nSelId != XLISTBOX_SEL_NONE) {
                gslc_ElemXListboxGetItem(&m_gui, pElemRef, nSelId, acTxt, MAX_STR);
            }
            break;
        case SubGHz_Listbox_signals:
            if (nSelId != XLISTBOX_SEL_NONE) {
                gslc_ElemXListboxGetItem(&m_gui, pElemRef, nSelId, acTxt, MAX_STR);
            }
            break;
            //<Listbox Enums !End!>
        default:
            break;
    }
    return true;
}
//<Draw Callback !Start!>
//<Draw Callback !End!>

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui, void* pvElemRef, int16_t nPos) {
    gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
    gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
    gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
    int16_t nVal;

    // From the element's ID we can determine which slider was updated.
    switch (pElem->nId) {
            //<Slider Enums !Start!>

        case WiFi_Listscroll_networks:
            // Fetch the slider position
            nVal = gslc_ElemXSliderGetPos(pGui, m_pListSlider_WiFi);
            break;
        case SubGHz_Listscroll_signals:
            // Fetch the slider position
            nVal = gslc_ElemXSliderGetPos(pGui, m_pListSlider_SubGHz);
            break;
            //<Slider Enums !End!>
        default:
            break;
    }

    return true;
}
//<Tick Callback !Start!>
//<Tick Callback !End!>

void successVibration() {
    if (vibrationEnabled) {
        vibro.pulseFor(75);
        delay(25);
        vibro.pulse(2);
    }
}
void failureVibration() {
    if (vibrationEnabled) {
        vibro.pulseFor(100);
        delay(250);
        vibro.pulseFor(100);
    }
}

void calculateBatteryCharge() {
    if (batteryConnected) {
        batteryVoltageADC = analogRead(batteryPin);
        batteryVoltage = batteryVoltageADC * (11.0 / 6825.0);
        batteryPercent = ((batteryVoltage - 3.0) / 1.2) * 100.0;

        // Set the value of batteryChrgTxt to the battery percentage
        String batteryText = String(batteryPercent, 0) + "%";
        gslc_ElemSetTxtStr(&m_gui, batteryChrgTxt, batteryText.c_str());
    }
}

void setup() {
    // ------------------------------------------------
    // Initialize
    // ------------------------------------------------
    delay(100);

    Serial.begin(115200);

    gslc_InitDebug(&DebugOut);

    delay(250);

    // ------------------------------------------------
    // Create graphic elements
    // ------------------------------------------------
    InitGUIslice_gen();

    // Show popup page for 1.5 seconds
    if (bootScreen) {
        bootScreenStart = millis();
        gslc_PopupShow(&m_gui, E_Popup_Boot, true);
    }

    gslc_Update(&m_gui);

    delay(50);

    // Get the SPI instance from the display
    TFT_eSPI& display = *(TFT_eSPI*)gslc_DrvGetDriverDisp(&m_gui);
    tftSPIInstance = display.getSPIinstance();

    float bootBattVoltage[5];

    // Calculate battery charge 5 times and if the voltage is less than 3.0 set the batteryConnected to false
    for (int i = 0; i < 5; i++) {
        calculateBatteryCharge();
        // DEBUG_SERIAL.printf("Bat value: %d = %f", i, batteryVoltage);
        bootBattVoltage[i] = batteryVoltage;
        if (batteryVoltage < 3.0 || batteryVoltage > 4.2) {
            batteryConnected = false;
            // Set the lable to "XX%"
            gslc_ElemSetTxtStr(&m_gui, batteryChrgTxt, "XX%");
            break;
        }
        delay(5);
    }

    // Find the range of the battery voltage
    if (batteryConnected) {
        float minVoltage = bootBattVoltage[0];
        float maxVoltage = bootBattVoltage[0];
        for (int i = 1; i < 5; i++) {
            if (bootBattVoltage[i] < minVoltage) {
                minVoltage = bootBattVoltage[i];
            }
            if (bootBattVoltage[i] > maxVoltage) {
                maxVoltage = bootBattVoltage[i];
            }
        }

        float range = maxVoltage - minVoltage;
        // DEBUG_SERIAL.printf("Battery voltage range: %f\n", range);

        if (range > 0.25) {
            // Set the batteryConnected to false
            batteryConnected = false;
            // Set the lable to "XX%"
            gslc_ElemSetTxtStr(&m_gui, batteryChrgTxt, "XX%");
        }
    }

    // Initialize the SD card sharing the SPI instance
    pinMode(42, OUTPUT);
    digitalWrite(42, HIGH);

    int sdInitAttempts = 0;
    const int maxSdInitAttempts = 5;
    bool sdInitialized = false;

    while (sdInitAttempts < maxSdInitAttempts && !sdInitialized) {
        if (SD.begin(42, tftSPIInstance)) {
            sdInitialized = true;
            DEBUG_SERIAL.println("SD card initialized successfully!");

            // Open the file "/settings.txt" for reading
            File settingsFile = SD.open("/settings.txt", FILE_READ);

            // Check if the file is available and get the contents of the first line
            if (settingsFile) {
                String line = settingsFile.readStringUntil('\n');
                DEBUG_SERIAL.println("Settings file contents: " + line);

                // Check if the first line contains "vibration=on"
                if (line.indexOf("vibration:enabled") != -1) {
                    vibrationEnabled = true;
                    DEBUG_SERIAL.println("Vibration is enabled.");
                    // Set the button text to "Vibration Enabled"
                    gslc_ElemSetTxtStr(&m_gui, m_pSettingsVibroButtonTxt, "Vibration Enabled");
                    gslc_ElemSetCol(&m_gui, m_pSettingsVibroButtonTxt, GSLC_COL_BLUE_DK2, GSLC_COL_GREEN_DK3, GSLC_COL_BLUE_DK1);
                } else {
                    vibrationEnabled = false;
                    DEBUG_SERIAL.println("Vibration is disabled.");
                    // Set the button text to "Vibration Disabled"
                    gslc_ElemSetTxtStr(&m_gui, m_pSettingsVibroButtonTxt, "Vibration Disabled");
                    gslc_ElemSetCol(&m_gui, m_pSettingsVibroButtonTxt, GSLC_COL_BLUE_DK2, GSLC_COL_RED_DK2, GSLC_COL_BLUE_DK1);
                }
                // Close the file
                settingsFile.close();

                successVibration();
            } else {
                DEBUG_SERIAL.println("Failed to open settings file!");
            }
        } else {
            sdInitAttempts++;
            DEBUG_SERIAL.printf("SD card initialization failed! Attempt %d of %d\n", sdInitAttempts, maxSdInitAttempts);
            delay(25);  // Wait before retrying
        }
    }

    if (!sdInitialized) {
        DEBUG_SERIAL.println("SD card initialization failed after maximum attempts!");
        failureVibration();
    }
}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop() {
    // ------------------------------------------------
    // Update GUI Elements
    // ------------------------------------------------
    // Check if the boot screen should be displayed
    if (bootScreen) {
        if (millis() - bootScreenStart >= bootScreenDelay) {
            // Hide the boot screen and set the current page to the main page
            bootScreen = false;
            gslc_PopupHide(&m_gui);
        }
    }

    // TODO - Add update code for any text, gauges, or sliders
    // Check what page is currently active
    if (currentPage == mainMenu) {
        // Update the main menu page
    } else if (currentPage == settingsMenu) {
        // Update the settings menu page
    } else if (currentPage == rfidMenu) {
        // Update the RFID menu page
    } else if (currentPage == subGHzMenu) {
        // Update the Sub-GHz menu page
        subGHzTools.runAction();
    } else if (currentPage == wifiMenu) {
        // Update the WiFi menu page

    } else if (currentPage == usbMenu) {
        // Update the USB menu page

    } else if (currentPage == bleMenu) {
        // Update the BLE menu page

    } else if (currentPage == irMenu) {
        // Update the IR menu page
    }

    // ------------------------------------------------
    // Periodically call GUIslice update function
    // ------------------------------------------------
    gslc_Update(&m_gui);
}
