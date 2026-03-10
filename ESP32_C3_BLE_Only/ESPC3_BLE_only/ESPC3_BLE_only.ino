/*
 * RadioLink SBUS Adapter for ESP32-C3
 * Features: Bluetooth BLE Only (Optimized for Super Mini)
 */

#include <BleGamepad.h>
#include "sbus.h"

BleGamepad bleGamepad("RadioLink C3 BLE", "DIY", 100);
bfs::SbusRx sbus_rx(&Serial1, 4, 5, true); 

void setup() {
  sbus_rx.Begin();
  bleGamepad.begin();
}

void loop() {
  if (sbus_rx.Read()) {
    bfs::SbusData data = sbus_rx.data();

    if (bleGamepad.isConnected()) {
      int32_t b_steer    = map(constrain(data.ch[0], 170, 1876), 170, 1876, 0, 32767);
      int32_t b_throttle = map(constrain(data.ch[1], 170, 1876), 170, 1876, 0, 32767);
      int32_t b_pot      = map(constrain(data.ch[2], 170, 1876), 170, 1876, 0, 32767);

      bleGamepad.setLeftThumb(b_steer, b_throttle);
      bleGamepad.setRightThumb(b_pot, 16384);

      // Map buttons 1-7
      if(data.ch[3] > 1000) bleGamepad.press(BUTTON_1); else bleGamepad.release(BUTTON_1);
      if(data.ch[4] < 600)  bleGamepad.press(BUTTON_2); else bleGamepad.release(BUTTON_2);
      if(data.ch[4] > 1500) bleGamepad.press(BUTTON_3); else bleGamepad.release(BUTTON_3);
      if(data.ch[6] > 1000) bleGamepad.press(BUTTON_6); else bleGamepad.release(BUTTON_6);

      bleGamepad.sendReport();
    }
  }
  delay(10);
}