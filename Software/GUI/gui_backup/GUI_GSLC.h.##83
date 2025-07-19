//<File !Start!>
// FILE: [GUI_GSLC.h]
// Created by GUIslice Builder version: [0.17.b40]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------

#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XListbox.h"
#include "elem/XSlider.h"
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error E_PROJECT_OPTIONS tab->Graphics Library should be Adafruit_GFX
#endif
#include <TFT_eSPI.h>
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
extern "C" const unsigned short bootLogo[] PROGMEM;
extern "C" const unsigned short homeButton[] PROGMEM;
extern "C" const unsigned short settingsButton[] PROGMEM;
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_BASE,E_PG_MAIN,E_PG_Settings,E_PG_RFID,E_PG_SubGHz,E_PG_WIFI
      ,E_PG_USB,E_PG_BLE,E_PG_IR,E_Popup_Boot,E_Popup_HandshakeCapture};
enum {BLE_Button_Send,Base_Button_home,Base_Button_settings
      ,Base_Line_topBar,Base_Text_Bat,Base_Text_PageLabel
      ,Boot_Image_logo,HandshakeCapture_Box_background
      ,HandshakeCapture_Button_active,HandshakeCapture_Button_exit
      ,HandshakeCapture_Button_passive,HandshakeCapture_Text_title
      ,IR_Button_Back,IR_Button_Capture,IR_Button_Jam,IR_Button_Select
      ,IR_Listbox_stored,IR_Listscroll_stored,Main_Button_BLE
      ,Main_Button_BadUSB,Main_Button_IR,Main_Button_RFID
      ,Main_Button_SubGHz,Main_Button_WIFI
      ,Settings_Button_calibrateTouch,Settings_Button_vibrationToggle
      ,SubGHz_Button_capture,SubGHz_Button_frequency
      ,SubGHz_Button_jaming,SubGHz_Button_transmit
      ,SubGHz_Listbox_signals,SubGHz_Listscroll_signals
      ,WiFi_Button_deauth,WiFi_Button_handshake
      ,WiFi_Button_rickRollBeacon,WiFi_Button_scanNetworks
      ,WiFi_Listbox_networks,WiFi_Listscroll_networks};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN10X16,E_BUILTIN5X8,MAX_FONT};
//<Enum !End!>

typedef enum {
    mainMenu,
    settingsMenu,
    rfidMenu,
    subGHzMenu,
    wifiMenu,
    bleMenu,
    usbMenu,
    irMenu
} pageOptions;

typedef enum {
    irDeviceTypesList,
    irDeviceBrandsList,
    irDevicesList,
    irDeviceCommandsList
} irMenuLevels;

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                11

#define MAX_ELEM_PG_BASE 5 // # Elems total on page
#define MAX_ELEM_PG_BASE_RAM MAX_ELEM_PG_BASE // # Elems in RAM

#define MAX_ELEM_PG_MAIN 6 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG_Settings 2 // # Elems total on page
#define MAX_ELEM_PG_Settings_RAM MAX_ELEM_PG_Settings // # Elems in RAM

#define MAX_ELEM_PG_RFID 0 // # Elems total on page
#define MAX_ELEM_PG_RFID_RAM MAX_ELEM_PG_RFID // # Elems in RAM

#define MAX_ELEM_PG_SubGHz 7 // # Elems total on page
#define MAX_ELEM_PG_SubGHz_RAM MAX_ELEM_PG_SubGHz // # Elems in RAM

#define MAX_ELEM_PG_WIFI 7 // # Elems total on page
#define MAX_ELEM_PG_WIFI_RAM MAX_ELEM_PG_WIFI // # Elems in RAM

#define MAX_ELEM_PG_USB 0 // # Elems total on page
#define MAX_ELEM_PG_USB_RAM MAX_ELEM_PG_USB // # Elems in RAM

#define MAX_ELEM_PG_BLE 1 // # Elems total on page
#define MAX_ELEM_PG_BLE_RAM MAX_ELEM_PG_BLE // # Elems in RAM

#define MAX_ELEM_PG_IR 7 // # Elems total on page
#define MAX_ELEM_PG_IR_RAM MAX_ELEM_PG_IR // # Elems in RAM

#define MAX_ELEM_Popup_Boot 1 // # Elems total on page
#define MAX_ELEM_Popup_Boot_RAM MAX_ELEM_Popup_Boot // # Elems in RAM

#define MAX_ELEM_Popup_HandshakeCapture 5 // # Elems total on page
#define MAX_ELEM_Popup_HandshakeCapture_RAM MAX_ELEM_Popup_HandshakeCapture // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui m_gui;
gslc_tsDriver m_drv;
gslc_tsFont m_asFont[MAX_FONT];
gslc_tsPage m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asBasePage1Elem[MAX_ELEM_PG_BASE_RAM];
gslc_tsElemRef                  m_asBasePage1ElemRef[MAX_ELEM_PG_BASE];
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage3Elem[MAX_ELEM_PG_Settings_RAM];
gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_PG_Settings];
gslc_tsElem                     m_asPage4Elem[MAX_ELEM_PG_RFID_RAM];
gslc_tsElemRef                  m_asPage4ElemRef[MAX_ELEM_PG_RFID];
gslc_tsElem                     m_asPage5Elem[MAX_ELEM_PG_SubGHz_RAM];
gslc_tsElemRef                  m_asPage5ElemRef[MAX_ELEM_PG_SubGHz];
gslc_tsElem                     m_asPage6Elem[MAX_ELEM_PG_WIFI_RAM];
gslc_tsElemRef                  m_asPage6ElemRef[MAX_ELEM_PG_WIFI];
gslc_tsElem                     m_asPage7Elem[MAX_ELEM_PG_USB_RAM];
gslc_tsElemRef                  m_asPage7ElemRef[MAX_ELEM_PG_USB];
gslc_tsElem                     m_asPage8Elem[MAX_ELEM_PG_BLE_RAM];
gslc_tsElemRef                  m_asPage8ElemRef[MAX_ELEM_PG_BLE];
gslc_tsElem                     m_asPage9Elem[MAX_ELEM_PG_IR_RAM];
gslc_tsElemRef                  m_asPage9ElemRef[MAX_ELEM_PG_IR];
gslc_tsElem                     m_asPopup1Elem[MAX_ELEM_Popup_Boot_RAM];
gslc_tsElemRef                  m_asPopup1ElemRef[MAX_ELEM_Popup_Boot];
gslc_tsElem                     m_asPopup2Elem[MAX_ELEM_Popup_HandshakeCapture_RAM];
gslc_tsElemRef                  m_asPopup2ElemRef[MAX_ELEM_Popup_HandshakeCapture];
gslc_tsXListbox                 m_sListbox2;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
char                            m_acListboxBuf2[50 + XLISTBOX_BUF_OH_R];
gslc_tsXSlider                  m_sListScroll2;
gslc_tsXListbox                 m_sListbox1;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
char                            m_acListboxBuf1[50 + XLISTBOX_BUF_OH_R];
gslc_tsXSlider                  m_sListScroll1;
gslc_tsXListbox                 m_sListbox3;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
char                            m_acListboxBuf3[500 + XLISTBOX_BUF_OH_R];
gslc_tsXSlider                  m_sListScroll3;

#define MAX_STR                 200

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* batteryChrgTxt;
extern gslc_tsElemRef* m_pBLEselectButtonTxt;
extern gslc_tsElemRef* m_pElemBtn10;
extern gslc_tsElemRef* m_pElemListbox_IR;
extern gslc_tsElemRef* m_pElemListbox_SubGHz;
extern gslc_tsElemRef* m_pElemListbox_WiFi;
extern gslc_tsElemRef* m_pElemOutTxt1;
extern gslc_tsElemRef* m_pIRselectButtonTxt;
extern gslc_tsElemRef* m_pListSlider_IR;
extern gslc_tsElemRef* m_pListSlider_SubGHz;
extern gslc_tsElemRef* m_pListSlider_WiFi;
extern gslc_tsElemRef* m_pSettingsVibroButtonTxt;
extern gslc_tsElemRef* m_pSubGHzJammingButton;
extern gslc_tsElemRef* m_pWiFiDeauthButtonTxt;
extern gslc_tsElemRef* m_pWiFiDeauthButtonTxt16_18;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// Create SPI object to be retrieved by the driver
// SPIClass tftSPI;

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui, void* pvElemRef, gslc_teTouch eTouch, int16_t nX, int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui, void* pvElemRef, gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void* pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui, void* pvElemRef, int16_t nPos);
bool CbSpinner(void* pvGui, void* pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui, void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen() {
    gslc_tsElemRef* pElemRef = NULL;

    if (!gslc_Init(&m_gui, &m_drv, m_asPage, MAX_PAGE, m_asFont, MAX_FONT)) {
        return;
    }

    // ------------------------------------------------
    // Load Fonts
    // ------------------------------------------------
    //<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN10X16,GSLC_FONTREF_PTR,NULL,2)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
    //<Load_Fonts !End!>

    //<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_BASE,m_asBasePage1Elem,MAX_ELEM_PG_BASE_RAM,m_asBasePage1ElemRef,MAX_ELEM_PG_BASE);
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG_Settings,m_asPage3Elem,MAX_ELEM_PG_Settings_RAM,m_asPage3ElemRef,MAX_ELEM_PG_Settings);
  gslc_PageAdd(&m_gui,E_PG_RFID,m_asPage4Elem,MAX_ELEM_PG_RFID_RAM,m_asPage4ElemRef,MAX_ELEM_PG_RFID);
  gslc_PageAdd(&m_gui,E_PG_SubGHz,m_asPage5Elem,MAX_ELEM_PG_SubGHz_RAM,m_asPage5ElemRef,MAX_ELEM_PG_SubGHz);
  gslc_PageAdd(&m_gui,E_PG_WIFI,m_asPage6Elem,MAX_ELEM_PG_WIFI_RAM,m_asPage6ElemRef,MAX_ELEM_PG_WIFI);
  gslc_PageAdd(&m_gui,E_PG_USB,m_asPage7Elem,MAX_ELEM_PG_USB_RAM,m_asPage7ElemRef,MAX_ELEM_PG_USB);
  gslc_PageAdd(&m_gui,E_PG_BLE,m_asPage8Elem,MAX_ELEM_PG_BLE_RAM,m_asPage8ElemRef,MAX_ELEM_PG_BLE);
  gslc_PageAdd(&m_gui,E_PG_IR,m_asPage9Elem,MAX_ELEM_PG_IR_RAM,m_asPage9ElemRef,MAX_ELEM_PG_IR);
  gslc_PageAdd(&m_gui,E_Popup_Boot,m_asPopup1Elem,MAX_ELEM_Popup_Boot_RAM,m_asPopup1ElemRef,MAX_ELEM_Popup_Boot);
  gslc_PageAdd(&m_gui,E_Popup_HandshakeCapture,m_asPopup2Elem,MAX_ELEM_Popup_HandshakeCapture_RAM,m_asPopup2ElemRef,MAX_ELEM_Popup_HandshakeCapture);

  // Now mark E_PG_BASE as a "base" page which means that it's elements
  // are always visible. This is useful for common page elements.
  gslc_SetPageBase(&m_gui, E_PG_BASE);


  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_BASE
  
  
  // Create Base_Text_PageLabel runtime modifiable text
  static char m_sDisplayText1[16] = "Main Menu";
  pElemRef = gslc_ElemCreateTxt(&m_gui,Base_Text_PageLabel,E_PG_BASE,(gslc_tsRect){70,18,180,16},
    (char*)m_sDisplayText1,16,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemOutTxt1 = pElemRef;
  
  // Create Base_Text_Bat runtime modifiable text
  static char m_sDisplayText2[7] = "100%";
  pElemRef = gslc_ElemCreateTxt(&m_gui,Base_Text_Bat,E_PG_BASE,(gslc_tsRect){243,19,72,16},
    (char*)m_sDisplayText2,7,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  batteryChrgTxt = pElemRef;

  // Create Base_Line_topBar line 
  pElemRef = gslc_ElemCreateLine(&m_gui,Base_Line_topBar,E_PG_BASE,0,49,320,49);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT3,GSLC_COL_GRAY_LT3);
  
  // Create Base_Button_home button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,Base_Button_home,E_PG_BASE,(gslc_tsRect){8,8,32,32},
          gslc_GetImageFromProg((const unsigned char*)homeButton,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromProg((const unsigned char*)homeButton,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create Base_Button_settings button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,Base_Button_settings,E_PG_BASE,(gslc_tsRect){48,8,32,32},
          gslc_GetImageFromProg((const unsigned char*)settingsButton,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromProg((const unsigned char*)settingsButton,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // create Main_Button_RFID button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,Main_Button_RFID,E_PG_MAIN,
    (gslc_tsRect){40,80,96,96},(char*)"RFID",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create Main_Button_SubGHz button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,Main_Button_SubGHz,E_PG_MAIN,
    (gslc_tsRect){184,80,96,96},(char*)"Sub-GHz",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create Main_Button_WIFI button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,Main_Button_WIFI,E_PG_MAIN,
    (gslc_tsRect){40,208,96,96},(char*)"WiFi",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create Main_Button_BadUSB button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,Main_Button_BadUSB,E_PG_MAIN,
    (gslc_tsRect){40,336,96,96},(char*)"Bad USB",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create Main_Button_BLE button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,Main_Button_BLE,E_PG_MAIN,
    (gslc_tsRect){184,208,96,96},(char*)"BLE",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create Main_Button_IR button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,Main_Button_IR,E_PG_MAIN,
    (gslc_tsRect){184,336,96,96},(char*)"IR",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // -----------------------------------
  // PAGE: E_PG_Settings
  
  
  // create Settings_Button_calibrateTouch button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,Settings_Button_calibrateTouch,E_PG_Settings,
    (gslc_tsRect){40,64,240,32},(char*)"Touch Calibration",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create Settings_Button_vibrationToggle button with modifiable text label
  static char m_strbtn12[21] = "Vibration Disabled";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,Settings_Button_vibrationToggle,E_PG_Settings,
    (gslc_tsRect){40,112,240,32},
    (char*)m_strbtn12,21,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED_DK2,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  m_pSettingsVibroButtonTxt = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_RFID
  

  // -----------------------------------
  // PAGE: E_PG_SubGHz
  
  
  // Create SubGHz_Button_jaming button with modifiable text label
  static char m_strbtn16[27] = "Jamming Dissabled";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,SubGHz_Button_jaming,E_PG_SubGHz,
    (gslc_tsRect){40,104,240,32},
    (char*)m_strbtn16,27,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED_DK2,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  m_pSubGHzJammingButton = pElemRef;
  
  // create SubGHz_Button_capture button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,SubGHz_Button_capture,E_PG_SubGHz,
    (gslc_tsRect){40,144,240,32},(char*)"Capture Signals",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create SubGHz_Button_frequency button with modifiable text label
  static char m_strbtn18[27] = "Change Frequency";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,SubGHz_Button_frequency,E_PG_SubGHz,
    (gslc_tsRect){40,64,240,32},
    (char*)m_strbtn18,27,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pWiFiDeauthButtonTxt16_18 = pElemRef;
   
  // Create wrapping box for listbox SubGHz_Listbox_signals and scrollbar
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_SubGHz,(gslc_tsRect){40,224,240,247});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2);
  
  // Create listbox
  pElemRef = gslc_ElemXListboxCreate(&m_gui,SubGHz_Listbox_signals,E_PG_SubGHz,&m_sListbox2,
    (gslc_tsRect){40+2,224+4,240-4-15,247-7},E_BUILTIN5X8,
    (uint8_t*)&m_acListboxBuf2,sizeof(m_acListboxBuf2),0);
  gslc_ElemXListboxSetSize(&m_gui, pElemRef, 10, 1); // 10 rows, 1 columns
  gslc_ElemXListboxItemsSetSize(&m_gui, pElemRef, -1, -1);
  gslc_ElemSetTxtMarginXY(&m_gui, pElemRef, 5, 5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2);
  gslc_ElemXListboxSetSelFunc(&m_gui, pElemRef, &CbListbox);
  gslc_ElemXListboxItemsSetGap(&m_gui, pElemRef, 5,GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElemListbox_SubGHz = pElemRef;

  // Create vertical scrollbar for listbox
  pElemRef = gslc_ElemXSliderCreate(&m_gui,SubGHz_Listscroll_signals,E_PG_SubGHz,&m_sListScroll2,
          (gslc_tsRect){40+240-2-15,224+4,15,247-8},0,100,0,5,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pListSlider_SubGHz = pElemRef;
  
  // create SubGHz_Button_transmit button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,SubGHz_Button_transmit,E_PG_SubGHz,
    (gslc_tsRect){40,184,240,32},(char*)"Transmit Captured Signal",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // -----------------------------------
  // PAGE: E_PG_WIFI
  
  
  // create WiFi_Button_rickRollBeacon button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,WiFi_Button_rickRollBeacon,E_PG_WIFI,
    (gslc_tsRect){40,64,240,32},(char*)"Rick Roll Beacon Spam",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED_DK2,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  
  // create WiFi_Button_scanNetworks button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,WiFi_Button_scanNetworks,E_PG_WIFI,
    (gslc_tsRect){40,104,240,32},(char*)"Scan WiFi Networks",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create WiFi_Button_deauth button with modifiable text label
  static char m_strbtn9[27] = "Deauthentication Dissabled";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,WiFi_Button_deauth,E_PG_WIFI,
    (gslc_tsRect){40,184,240,32},
    (char*)m_strbtn9,27,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED_DK2,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  m_pWiFiDeauthButtonTxt = pElemRef;
  
  // Create WiFi_Button_handshake button with modifiable text label
  static char m_strbtn10[31] = "Handshake Capture";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,WiFi_Button_handshake,E_PG_WIFI,
    (gslc_tsRect){40,144,240,32},
    (char*)m_strbtn10,31,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtn10 = pElemRef;
   
  // Create wrapping box for listbox WiFi_Listbox_networks and scrollbar
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_WIFI,(gslc_tsRect){40,224,240,247});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2);
  
  // Create listbox
  pElemRef = gslc_ElemXListboxCreate(&m_gui,WiFi_Listbox_networks,E_PG_WIFI,&m_sListbox1,
    (gslc_tsRect){40+2,224+4,240-4-15,247-7},E_BUILTIN5X8,
    (uint8_t*)&m_acListboxBuf1,sizeof(m_acListboxBuf1),0);
  gslc_ElemXListboxSetSize(&m_gui, pElemRef, 10, 1); // 10 rows, 1 columns
  gslc_ElemXListboxItemsSetSize(&m_gui, pElemRef, -1, -1);
  gslc_ElemSetTxtMarginXY(&m_gui, pElemRef, 5, 5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2);
  gslc_ElemXListboxSetSelFunc(&m_gui, pElemRef, &CbListbox);
  gslc_ElemXListboxItemsSetGap(&m_gui, pElemRef, 5,GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElemListbox_WiFi = pElemRef;

  // Create vertical scrollbar for listbox
  pElemRef = gslc_ElemXSliderCreate(&m_gui,WiFi_Listscroll_networks,E_PG_WIFI,&m_sListScroll1,
          (gslc_tsRect){40+240-2-15,224+4,15,247-8},0,100,0,5,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pListSlider_WiFi = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_USB
  

  // -----------------------------------
  // PAGE: E_PG_BLE
  
  
  // create BLE_Button_Send button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,BLE_Button_Send,E_PG_BLE,
    (gslc_tsRect){40,64,240,32},(char*)"Never gonna what?",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  m_pBLEselectButtonTxt = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_IR
  
   
  // Create wrapping box for listbox IR_Listbox_stored and scrollbar
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_IR,(gslc_tsRect){40,104,240,247});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2);
  
  // Create listbox
  pElemRef = gslc_ElemXListboxCreate(&m_gui,IR_Listbox_stored,E_PG_IR,&m_sListbox3,
    (gslc_tsRect){40+2,104+4,240-4-15,247-7},E_BUILTIN5X8,
    (uint8_t*)&m_acListboxBuf3,sizeof(m_acListboxBuf3),0);
  gslc_ElemXListboxSetSize(&m_gui, pElemRef, 10, 1); // 10 rows, 1 columns
  gslc_ElemXListboxItemsSetSize(&m_gui, pElemRef, -1, -1);
  gslc_ElemSetTxtMarginXY(&m_gui, pElemRef, 5, 5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2);
  gslc_ElemXListboxSetSelFunc(&m_gui, pElemRef, &CbListbox);
  gslc_ElemXListboxItemsSetGap(&m_gui, pElemRef, 5,GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElemListbox_IR = pElemRef;

  // Create vertical scrollbar for listbox
  pElemRef = gslc_ElemXSliderCreate(&m_gui,IR_Listscroll_stored,E_PG_IR,&m_sListScroll3,
          (gslc_tsRect){40+240-2-15,104+4,15,247-8},0,100,0,5,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pListSlider_IR = pElemRef;
  
  // create IR_Button_Select button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,IR_Button_Select,E_PG_IR,
    (gslc_tsRect){40,64,240,32},(char*)"Select",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pIRselectButtonTxt = pElemRef;
  
  // create IR_Button_Back button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,IR_Button_Back,E_PG_IR,
    (gslc_tsRect){40,360,240,32},(char*)"Back",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create IR_Button_Capture button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,IR_Button_Capture,E_PG_IR,
    (gslc_tsRect){40,400,240,32},(char*)"Capture IR",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create IR_Button_Jam button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,IR_Button_Jam,E_PG_IR,
    (gslc_tsRect){40,440,240,32},(char*)"Jamming Disabled",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // -----------------------------------
  // PAGE: E_Popup_Boot
  
 
  // Create Boot_Image_logo using Image 
  pElemRef = gslc_ElemCreateImg(&m_gui,Boot_Image_logo,E_Popup_Boot,(gslc_tsRect){0,0,320,480},
    gslc_GetImageFromProg((const unsigned char*)bootLogo,GSLC_IMGREF_FMT_BMP24));

  // -----------------------------------
  // PAGE: E_Popup_HandshakeCapture
  
   
  // Create HandshakeCapture_Box_background box
  pElemRef = gslc_ElemCreateBox(&m_gui,HandshakeCapture_Box_background,E_Popup_HandshakeCapture,(gslc_tsRect){32,136,256,264});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create HandshakeCapture_Button_passive button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,HandshakeCapture_Button_passive,E_Popup_HandshakeCapture,
    (gslc_tsRect){40,208,240,32},(char*)"Passive",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create HandshakeCapture_Button_active button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,HandshakeCapture_Button_active,E_Popup_HandshakeCapture,
    (gslc_tsRect){40,248,240,32},(char*)"Active",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create HandshakeCapture_Button_exit button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,HandshakeCapture_Button_exit,E_Popup_HandshakeCapture,
    (gslc_tsRect){40,352,240,32},(char*)"Exit",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_RED_DK2,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  
  // Create HandshakeCapture_Text_title text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,HandshakeCapture_Text_title,E_Popup_HandshakeCapture,(gslc_tsRect){72,152,180,8},
    (char*)"Select Deauthentication Method",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
    //<InitGUI !End!>

    //<Startup !Start!>
  gslc_GuiRotate(&m_gui, 0);
    //<Startup !End!>
}

#endif  // end _GUISLICE_GEN_H
