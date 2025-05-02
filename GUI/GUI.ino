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

#include "GUI_GSLC.h"
#include "SD.h"
#include "TFT_eSPI.h"

// ------------------------------------------------
// Program Globals
// ------------------------------------------------
bool bootScreen = true;
bool vibrationEnabled = true;
int deauthStatus = 0;
long bootScreenDelay = 1500;
long bootScreenStart;

const int motorPin = 18;
VibrationMotor vibro(motorPin);

SPIClass& tftSPIInstance = SPI;

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pElemBtn10      = NULL;
gslc_tsElemRef* m_pElemBtn12      = NULL;
gslc_tsElemRef* m_pElemListbox_SubGHz= NULL;
gslc_tsElemRef* m_pElemListbox_WiFi= NULL;
gslc_tsElemRef* m_pElemOutTxt1    = NULL;
gslc_tsElemRef* m_pElemOutTxt2    = NULL;
gslc_tsElemRef* m_pListSlider_SubGHz= NULL;
gslc_tsElemRef* m_pListSlider_WiFi= NULL;
gslc_tsElemRef* m_pWiFiDeauthButtonTxt= NULL;
gslc_tsElemRef* m_pWiFiDeauthButtonTxt16= NULL;
gslc_tsElemRef* m_pWiFiDeauthButtonTxt16_18= NULL;
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
                break;
            case Base_Button_settings:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "Settings");
                gslc_SetPageCur(&m_gui, E_PG_Settings);
                break;
            case Main_Button_RFID:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "RFID");
                gslc_SetPageCur(&m_gui, E_PG_RFID);
                break;
            case Main_Button_SubGHz:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "Sub GHz");
                gslc_SetPageCur(&m_gui, E_PG_SubGHz);
                break;
            case Main_Button_WIFI:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "WiFi");
                gslc_SetPageCur(&m_gui, E_PG_WIFI);
                break;
            case Main_Button_BadUSB:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "Bad USB");
                gslc_SetPageCur(&m_gui, E_PG_USB);
                break;
            case Main_Button_BLE:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "Bluetooth");
                gslc_SetPageCur(&m_gui, E_PG_BLE);
                break;
            case Main_Button_IR:
                gslc_ElemSetTxtStr(&m_gui, m_pElemOutTxt1, "IR");
                gslc_SetPageCur(&m_gui, E_PG_IR);
                break;
            case Settings_Button_calibrateTouch:
                break;
            case Settings_Button_vibrationToggle:
                break;
      case SubGHz_Button_jaming:
if (deauthStatus == 0) {
    deauthStatus = 1;
    // Set the button text to "Deauthentication Enabled"
    gslc_ElemSetTxtStr(&m_gui, m_pWiFiDeauthButtonTxt, "Deauthentication Enabled");
    // Set the button color to green
    gslc_ElemSetCol(&m_gui, m_pWiFiDeauthButtonTxt, GSLC_COL_BLUE_DK2, GSLC_COL_GREEN_DK3, GSLC_COL_BLUE_DK1);
} else {
    deauthStatus = 0;
    // Set the button text to "Deauthentication Disabled"
    gslc_ElemSetTxtStr(&m_gui, m_pWiFiDeauthButtonTxt, "Deauthentication Disabled");
    // Set the button color to red
    gslc_ElemSetCol(&m_gui, m_pWiFiDeauthButtonTxt, GSLC_COL_BLUE_DK2, GSLC_COL_RED_DK2, GSLC_COL_BLUE_DK1);
}

        break;
      case SubGHz_Button_capture:
        break;
      case SubGHz_Button_frequency:
if (deauthStatus == 0) {
    deauthStatus = 1;
    // Set the button text to "Deauthentication Enabled"
    gslc_ElemSetTxtStr(&m_gui, m_pWiFiDeauthButtonTxt, "Deauthentication Enabled");
    // Set the button color to green
    gslc_ElemSetCol(&m_gui, m_pWiFiDeauthButtonTxt, GSLC_COL_BLUE_DK2, GSLC_COL_GREEN_DK3, GSLC_COL_BLUE_DK1);
} else {
    deauthStatus = 0;
    // Set the button text to "Deauthentication Disabled"
    gslc_ElemSetTxtStr(&m_gui, m_pWiFiDeauthButtonTxt, "Deauthentication Disabled");
    // Set the button color to red
    gslc_ElemSetCol(&m_gui, m_pWiFiDeauthButtonTxt, GSLC_COL_BLUE_DK2, GSLC_COL_RED_DK2, GSLC_COL_BLUE_DK1);
}

        break;
      case SubGHz_Button_transmit:
        break;
            case WiFi_Button_rickRollBeacon:
                break;
            case WiFi_Button_scanNetworks:
                break;
            case WiFi_Button_deauth:
                if (deauthStatus == 0) {
                    deauthStatus = 1;
                    // Set the button text to "Deauthentication Enabled"
                    gslc_ElemSetTxtStr(&m_gui, m_pWiFiDeauthButtonTxt, "Deauthentication Enabled");
                    // Set the button color to green
                    gslc_ElemSetCol(&m_gui, m_pWiFiDeauthButtonTxt, GSLC_COL_BLUE_DK2, GSLC_COL_GREEN_DK3, GSLC_COL_BLUE_DK1);
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
      nVal = gslc_ElemXSliderGetPos(pGui,m_pListSlider_SubGHz);
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

    delay(100);

    // Get the SPI instance from the display
    TFT_eSPI& display = *(TFT_eSPI*)gslc_DrvGetDriverDisp(&m_gui);
    tftSPIInstance = display.getSPIinstance();

    // Initialize the SD card sharing the SPI instance
    pinMode(42, OUTPUT);
    digitalWrite(42, HIGH);
    if (!SD.begin(42, tftSPIInstance)) {
        Serial.println("SD card initialization failed!");
        return;
    } else {
        Serial.println("SD card initialized successfully!");
    }

    delay(250);

    // Show popup page for 1.5 seconds
    if (bootScreen) {
        bootScreenStart = millis();
        gslc_PopupShow(&m_gui, E_Popup_Boot, true);
    }

    successVibration();
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

    // ------------------------------------------------
    // Periodically call GUIslice update function
    // ------------------------------------------------
    gslc_Update(&m_gui);
}
