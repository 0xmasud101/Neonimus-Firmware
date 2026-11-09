/*
 * Neonimus Firmware - board bring-up stub for neonimus-core
 * Modeled on upstream boards/_New-Device-Model/interface.cpp.
 * Fill in each function as Phase 1 hardware bring-up proceeds;
 * leave the ones you haven't wired yet returning their safe default.
 */
#include "core/powerSave.h"
#include <interface.h>

/***************************************************************************************
** Function name: _setup_gpio()
** Location: main.cpp
** Description:   initial setup for the device, runs once at boot
***************************************************************************************/
void _setup_gpio() {
    // TODO Phase 1: pinMode() calls for TFT_BL, power switch sense pin, etc.
}

/***************************************************************************************
** Function name: _post_setup_gpio()
** Location: main.cpp
** Description:   second stage gpio setup, after display/SD are up
***************************************************************************************/
void _post_setup_gpio() {}

/***************************************************************************************
** Function name: getBattery()
** location: display.cpp
** Description:   battery percentage 1-100, or 0 if no fuel gauge wired
***************************************************************************************/
int getBattery() { return 0; }

/*********************************************************************
** Function: isCharging()
**********************************************************************/
bool isCharging() { return false; }

/*********************************************************************
** Function: _setBrightness
** location: settings.cpp
**********************************************************************/
void _setBrightness(uint8_t brightval) {
    // TODO Phase 1: analogWrite/ledc PWM on TFT_BL
}

/*********************************************************************
** Function: InputHandler
** Handles PrevPress, NextPress, SelPress, AnyKeyPress, EscPress
** This handheld has no physical nav buttons in the BOM above -
** wire this to a touch overlay, rotary encoder, or GPIO buttons
** if you add one, otherwise leave empty (UI navigation would then
** rely on the voice command set from Phase 3, or a future USB/BLE
** keyboard fallback).
**********************************************************************/
void InputHandler(void) {
    checkPowerSaveTime();
    PrevPress   = false;
    NextPress   = false;
    SelPress    = false;
    AnyKeyPress = false;
    EscPress    = false;
}

/*********************************************************************
** Function: keyboard
** location: mykeyboard.cpp
**********************************************************************/
String keyboard(String mytext, int maxSize, String msg) { return mytext; }

/*********************************************************************
** Function: powerOff
**********************************************************************/
void powerOff() {
    // TODO Phase 1: drive power-switch/MOSFET latch pin low if present
}

/*********************************************************************
** Function: checkReboot
**********************************************************************/
void checkReboot() {}
