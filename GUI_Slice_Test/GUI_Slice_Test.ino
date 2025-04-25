//<App !Start!>
// FILE: [GUI_Slice_Test.ino]
// Created by GUIslice Builder version: [0.17.b38]
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
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <DisplayMenu.h>
#include <FS.h>  // Filesystem support header
#include <SD.h>  // SD card support header
#include <SPI.h>
#include <TFT_eSPI.h>  // The TFT_eSPI library
#include <XPT2046_Touchscreen.h>
#include <pgmspace.h>  // PROGMEM support header

#include <vector>

#include "GUI_Slice_Test_GSLC.h"
#include "GUIslice.h"
#include "GUIslice_drv.h"
#include "SPIFFS.h"  // SPIFFS support header
#include "WiFiTools.h"
#include "elem/XListbox.h"
#include "elem/XSlider.h"

WiFiTools wifiTools;

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pElemListbox1 = NULL;
gslc_tsElemRef* m_pListSlider1 = NULL;
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
            case E_Main_Button_Home:
                break;
            case E_Main_Button_Settings:
                break;
            case E_Main_Button_RFID:
                gslc_SetPageCur(&m_gui, E_PG_RFID);
                break;
            case E_Main_Button_SubGHz:
                break;
            case E_Main_Button_WiFi:
                gslc_SetPageCur(&m_gui, E_PG_WIFI);
                break;
            case E_Main_Button_BLE:
                break;
            case E_Main_Button_USB:
                break;
            case E_Main_Button_IR:
                break;
            case E_RFID_Button_Home:
                gslc_SetPageCur(&m_gui, E_PG_MAIN);
                break;
            case E_RFID_Button_Settings:
                break;
            case E_WIFI_Button_Home:
                gslc_SetPageCur(&m_gui, E_PG_MAIN);
                break;
            case E_WIFI_Button_Settings:
                break;
            case E_ELEM_BTN3:
                wifiTools.rickRollBeaconSpam();
                break;
            case E_ELEM_BTN4: {
                wifiTools.scanWiFiNetworks();
                std::vector<wifi_ap_record_t> foundWiFiNetworks = wifiTools.getAvailableNetworks();
                int numberOfNetworks = foundWiFiNetworks.size();
                gslc_ElemXListboxReset(&m_gui, m_pElemListbox1);  // Clear the listbox before adding new items
                for (int i = 0; i < numberOfNetworks; i++) {
                    // get the SSID and add it to the listbox
                    char ssid[34];  // Increase size to 65 to accommodate longer SSIDs
                    strncpy(ssid, (const char*)foundWiFiNetworks[i].ssid, 33);
                    ssid[33] = '\0';  // Ensure null termination
                    // add the SSID to the listbox
                    gslc_ElemXListboxAddItem(&m_gui, m_pElemListbox1, ssid);
                    Serial.printf("SSID: %s\n", ssid);
                    // clear the ssid buffer
                    memset(ssid, 0, sizeof(ssid));
                }
                break;
            }
            case E_ELEM_BTN5: {
                // get the selected item from the listbox
                int16_t nSelId = gslc_ElemXListboxGetSel(&m_gui, m_pElemListbox1);
                std::vector<wifi_ap_record_t> foundWiFiNetworks = wifiTools.getAvailableNetworks();
                // get the selected SSID
                char ssid[34];  // Increase size to 65 to accommodate longer SSIDs
                strncpy(ssid, (const char*)foundWiFiNetworks[nSelId].ssid, 33);
                Serial.printf("Selected SSID: %s\n", ssid);
                // convet nSelId to an int
                int networkIndex = nSelId;
                wifiTools.deauthNetwork(NULL, NULL, NULL, networkIndex, NULL, 5000, 1, 2);
                break;
            }
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
        case E_ELEM_LISTBOX1:
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
        case E_LISTSCROLL1:
            // Fetch the slider position
            nVal = gslc_ElemXSliderGetPos(pGui, m_pListSlider1);
            break;

            //<Slider Enums !End!>
        default:
            break;
    }

    return true;
}
//<Tick Callback !Start!>
//<Tick Callback !End!>

void setup() {
    // ------------------------------------------------
    // Initialize
    // ------------------------------------------------
    Serial.begin(115200);
    // Wait for USB Serial
    delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

    digitalWrite(42, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(36, HIGH);

    delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

    gslc_InitDebug(&DebugOut);

    // ------------------------------------------------
    // Create graphic elements
    // ------------------------------------------------
    InitGUIslice_gen();
}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop() {
    // ------------------------------------------------
    // Update GUI Elements
    // ------------------------------------------------

    // TODO - Add update code for any text, gauges, or sliders

    // ------------------------------------------------
    // Periodically call GUIslice update function
    // ------------------------------------------------
    gslc_Update(&m_gui);
}
