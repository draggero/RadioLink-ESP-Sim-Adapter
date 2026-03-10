#include "USB.h"
#include "USBHIDGamepad.h"
#include <BleGamepad.h>
#include "sbus.h"

USBHIDGamepad UsbGamepad;
BleGamepad bleGamepad("RadioLink S3 BLE", "DIY", 100);
bfs::SbusRx sbus_rx(&Serial1, 4, 5, true); 

void setup() {
  sbus_rx.Begin();
  
  // --- KONFIGURACJA NAZWY USB ---
  USB.productName("RadioLink S3 USB"); // To zobaczysz w joy.cpl po kablu
  USB.manufacturerName("DIY-RC");
  USB.begin();
  
  // Inicjalizacja kontrolerów
  UsbGamepad.begin();
  bleGamepad.begin();
}

void loop() {
  if (sbus_rx.Read()) {
    bfs::SbusData data = sbus_rx.data();

    // --- 1. LOGIKA USB (KABEL - 8 BITÓW) ---
    int8_t u_steer    = map(constrain(data.ch[0], 170, 1876), 170, 1876, -127, 127);
    int8_t u_throttle = map(constrain(data.ch[1], 170, 1876), 170, 1876, -127, 127);
    int8_t u_pot      = map(constrain(data.ch[2], 170, 1876), 170, 1876, -127, 127);

    UsbGamepad.leftStick(u_steer, u_throttle);
    UsbGamepad.rightStick(u_pot, 0); 

    // Przyciski USB 1-7 (zgodnie z Twoimi switchami)
    if(data.ch[3] > 1000) UsbGamepad.pressButton(1); else UsbGamepad.releaseButton(1);
    if(data.ch[4] < 600)  UsbGamepad.pressButton(2); else UsbGamepad.releaseButton(2);
    if(data.ch[4] > 1500) UsbGamepad.pressButton(3); else UsbGamepad.releaseButton(3);
    if(data.ch[5] < 600)  UsbGamepad.pressButton(4); else UsbGamepad.releaseButton(4);
    if(data.ch[5] > 1500) UsbGamepad.pressButton(5); else UsbGamepad.releaseButton(5);
    if(data.ch[6] > 1000) UsbGamepad.pressButton(6); else UsbGamepad.releaseButton(6);
    if(data.ch[7] > 1000) UsbGamepad.pressButton(7); else UsbGamepad.releaseButton(7);


    // --- 2. LOGIKA BLUETOOTH (BLE - 15 BITÓW) ---
    if (bleGamepad.isConnected()) {
      int32_t b_steer    = map(constrain(data.ch[0], 170, 1876), 170, 1876, 0, 32767);
      int32_t b_throttle = map(constrain(data.ch[1], 170, 1876), 170, 1876, 0, 32767);
      int32_t b_pot      = map(constrain(data.ch[2], 170, 1876), 170, 1876, 0, 32767);

      bleGamepad.setLeftThumb(b_steer, b_throttle);
      bleGamepad.setRightThumb(b_pot, 16384);

      if(data.ch[3] > 1000) bleGamepad.press(BUTTON_1); else bleGamepad.release(BUTTON_1);
      if(data.ch[4] < 600)  bleGamepad.press(BUTTON_2); else bleGamepad.release(BUTTON_2);
      if(data.ch[4] > 1500) bleGamepad.press(BUTTON_3); else bleGamepad.release(BUTTON_3);
      if(data.ch[5] < 600)  bleGamepad.press(BUTTON_4); else bleGamepad.release(BUTTON_4);
      if(data.ch[5] > 1500) bleGamepad.press(BUTTON_5); else bleGamepad.release(BUTTON_5);
      if(data.ch[6] > 1000) bleGamepad.press(BUTTON_6); else bleGamepad.release(BUTTON_6);
      if(data.ch[7] > 1000) bleGamepad.press(BUTTON_7); else bleGamepad.release(BUTTON_7);

      bleGamepad.sendReport();
    }
  }
  delay(2);
}