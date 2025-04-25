//<File !Start!>
// FILE: [GUI_Slice_Test_GSLC.h]
// Created by GUIslice Builder version: [0.17.b38]
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

// Ensure optional features are enabled in the configuration
#if !(GSLC_SD_EN)
  #error "Config: GSLC_SD_EN required for this program but not enabled. Please see: https://github.com/ImpulseAdventure/GUIslice/wiki/Configuring-GUIslice"
#endif
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
#define IMG_BLE                   "/BLE.bmp"
#define IMG_BLE_SEL               "/BLE.bmp"
#define IMG_HOME                  "/home.bmp"
#define IMG_HOME_SEL              "/home.bmp"
#define IMG_IR                    "/IR.bmp"
#define IMG_IR_SEL                "/IR.bmp"
#define IMG_RFID                  "/RFID.bmp"
#define IMG_RFID_SEL              "/RFID.bmp"
#define IMG_SETTINGS              "/settings.bmp"
#define IMG_SETTINGS_SEL          "/settings.bmp"
#define IMG_SUBGHZ                "/SUB-GHz.bmp"
#define IMG_SUBGHZ_SEL            "/SUB-GHz.bmp"
#define IMG_USB                   "/USB.bmp"
#define IMG_USB_SEL               "/USB.bmp"
#define IMG_WIFI                  "/WiFi.bmp"
#define IMG_WIFI_SEL              "/WiFi.bmp"
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_PG_RFID,E_PG_WIFI};
enum {E_ELEM_BTN3,E_ELEM_BTN4,E_ELEM_BTN5,E_ELEM_LISTBOX1,E_LISTSCROLL1
      ,E_Main_Button_BLE,E_Main_Button_Home,E_Main_Button_IR
      ,E_Main_Button_RFID,E_Main_Button_Settings,E_Main_Button_SubGHz
      ,E_Main_Button_USB,E_Main_Button_WiFi,E_Main_Text_Menu_Label
      ,E_RFID_Button_Home,E_RFID_Button_Settings,E_RFID_Text_Menu_Label
      ,E_WIFI_Button_Home,E_WIFI_Button_Settings,E_WIFI_Text_Menu_Label};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN10X16,E_BUILTIN5X8,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                3

#define MAX_ELEM_PG_MAIN 9 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG_RFID 3 // # Elems total on page
#define MAX_ELEM_PG_RFID_RAM MAX_ELEM_PG_RFID // # Elems in RAM

#define MAX_ELEM_PG_WIFI 9 // # Elems total on page
#define MAX_ELEM_PG_WIFI_RAM MAX_ELEM_PG_WIFI // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage8Elem[MAX_ELEM_PG_RFID_RAM];
gslc_tsElemRef                  m_asPage8ElemRef[MAX_ELEM_PG_RFID];
gslc_tsElem                     m_asPage10Elem[MAX_ELEM_PG_WIFI_RAM];
gslc_tsElemRef                  m_asPage10ElemRef[MAX_ELEM_PG_WIFI];
gslc_tsXListbox                 m_sListbox1;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
char                            m_acListboxBuf1[100 + XLISTBOX_BUF_OH_R];
gslc_tsXSlider                  m_sListScroll1;

#define MAX_STR                 200

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemListbox1;
extern gslc_tsElemRef* m_pListSlider1;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN10X16,GSLC_FONTREF_PTR,NULL,2)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG_RFID,m_asPage8Elem,MAX_ELEM_PG_RFID_RAM,m_asPage8ElemRef,MAX_ELEM_PG_RFID);
  gslc_PageAdd(&m_gui,E_PG_WIFI,m_asPage10Elem,MAX_ELEM_PG_WIFI_RAM,m_asPage10ElemRef,MAX_ELEM_PG_WIFI);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_WIFI);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // Create E_Main_Button_Home button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_Main_Button_Home,E_PG_MAIN,(gslc_tsRect){16,8,32,32},
          gslc_GetImageFromSD((const char*)IMG_HOME,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_HOME_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_Main_Button_Settings button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_Main_Button_Settings,E_PG_MAIN,(gslc_tsRect){64,8,32,32},
          gslc_GetImageFromSD((const char*)IMG_SETTINGS,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_SETTINGS_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_Main_Text_Menu_Label text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_Main_Text_Menu_Label,E_PG_MAIN,(gslc_tsRect){116,16,108,16},
    (char*)"Main Menu",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_Main_Button_RFID button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_Main_Button_RFID,E_PG_MAIN,(gslc_tsRect){32,80,96,96},
          gslc_GetImageFromSD((const char*)IMG_RFID,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_RFID_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_Main_Button_SubGHz button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_Main_Button_SubGHz,E_PG_MAIN,(gslc_tsRect){192,80,96,96},
          gslc_GetImageFromSD((const char*)IMG_SUBGHZ,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_SUBGHZ_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_Main_Button_WiFi button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_Main_Button_WiFi,E_PG_MAIN,(gslc_tsRect){32,208,96,96},
          gslc_GetImageFromSD((const char*)IMG_WIFI,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_WIFI_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_Main_Button_BLE button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_Main_Button_BLE,E_PG_MAIN,(gslc_tsRect){192,208,96,96},
          gslc_GetImageFromSD((const char*)IMG_BLE,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_BLE_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_Main_Button_USB button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_Main_Button_USB,E_PG_MAIN,(gslc_tsRect){32,336,96,96},
          gslc_GetImageFromSD((const char*)IMG_USB,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_USB_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_Main_Button_IR button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_Main_Button_IR,E_PG_MAIN,(gslc_tsRect){192,336,96,96},
          gslc_GetImageFromSD((const char*)IMG_IR,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_IR_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);

  // -----------------------------------
  // PAGE: E_PG_RFID
  
  
  // Create E_RFID_Button_Home button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_RFID_Button_Home,E_PG_RFID,(gslc_tsRect){16,8,32,32},
          gslc_GetImageFromSD((const char*)IMG_HOME,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_HOME_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_RFID_Button_Settings button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_RFID_Button_Settings,E_PG_RFID,(gslc_tsRect){64,8,32,32},
          gslc_GetImageFromSD((const char*)IMG_SETTINGS,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_SETTINGS_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_RFID_Text_Menu_Label text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_RFID_Text_Menu_Label,E_PG_RFID,(gslc_tsRect){104,8,108,16},
    (char*)"RFID Menu",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // -----------------------------------
  // PAGE: E_PG_WIFI
  
  
  // Create E_WIFI_Button_Home button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_WIFI_Button_Home,E_PG_WIFI,(gslc_tsRect){16,8,32,32},
          gslc_GetImageFromSD((const char*)IMG_HOME,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_HOME_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_WIFI_Button_Settings button with image label
  pElemRef = gslc_ElemCreateBtnImg(&m_gui,E_WIFI_Button_Settings,E_PG_WIFI,(gslc_tsRect){64,8,32,32},
          gslc_GetImageFromSD((const char*)IMG_SETTINGS,GSLC_IMGREF_FMT_BMP24),
          gslc_GetImageFromSD((const char*)IMG_SETTINGS_SEL,GSLC_IMGREF_FMT_BMP24),
          &CbBtnCommon);
  
  // Create E_WIFI_Text_Menu_Label text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_WIFI_Text_Menu_Label,E_PG_WIFI,(gslc_tsRect){104,8,108,16},
    (char*)"WIFI Menu",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
   
  // Create wrapping box for listbox E_ELEM_LISTBOX1 and scrollbar
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_WIFI,(gslc_tsRect){43,181,233,271});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  
  // Create listbox
  pElemRef = gslc_ElemXListboxCreate(&m_gui,E_ELEM_LISTBOX1,E_PG_WIFI,&m_sListbox1,
    (gslc_tsRect){43+2,181+4,233-4-25,271-7},E_BUILTIN10X16,
    (uint8_t*)&m_acListboxBuf1,sizeof(m_acListboxBuf1),0);
  gslc_ElemXListboxSetSize(&m_gui, pElemRef, 5, 1); // 5 rows, 1 columns
  gslc_ElemXListboxItemsSetSize(&m_gui, pElemRef, -1, 10);
  gslc_ElemSetTxtMarginXY(&m_gui, pElemRef, 5, 5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_GRAY);
  gslc_ElemXListboxSetSelFunc(&m_gui, pElemRef, &CbListbox);
  gslc_ElemXListboxItemsSetGap(&m_gui, pElemRef, 5,GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_pElemListbox1 = pElemRef;

  // Create vertical scrollbar for listbox
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_LISTSCROLL1,E_PG_WIFI,&m_sListScroll1,
          (gslc_tsRect){43+233-2-25,181+4,25,271-8},0,16,0,8,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_GRAY_DK2,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pListSlider1 = pElemRef;
  
  // create E_ELEM_BTN3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN3,E_PG_WIFI,
    (gslc_tsRect){52,61,80,40},(char*)"Rick Roll\x0a Beacon",0,E_BUILTIN5X8,&CbBtnCommon);
  
  // create E_ELEM_BTN4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN4,E_PG_WIFI,
    (gslc_tsRect){52,119,80,40},(char*)"Scan WiFi\x0a Networks",0,E_BUILTIN5X8,&CbBtnCommon);
  
  // create E_ELEM_BTN5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN5,E_PG_WIFI,
    (gslc_tsRect){159,117,80,40},(char*)"Deauth",0,E_BUILTIN5X8,&CbBtnCommon);
//<InitGUI !End!>

//<Startup !Start!>
  gslc_GuiRotate(&m_gui, 0);
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
