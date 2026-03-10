# RadioLink-ESP-Sim-Adapter (Dual-Mode)

A high-performance SBUS to USB HID/Bluetooth adapter for RadioLink transmitters (RC6GS, RC4GS, etc.). This project allows you to use your real RC radio as a controller for simulators like **VRC Pro, BeamNG.drive, Assetto Corsa, and Liftoff**.

## 🚀 Features
- **Dual Mode (S3):** Operates as a wired USB Gamepad and a wireless Bluetooth controller simultaneously.
- **Native USB HID:** Plug-and-play on Windows/Linux/Mac. No special drivers required.
- **Low Latency:** Optimized SBUS parsing (~100Hz) with minimal processing overhead.
- **Full Channel Support:** Maps 8 channels including steering, throttle, dials, and up to 7 logical buttons for switches.
- **Custom Branding:** Displays as "RadioLink S3 USB" in Windows game controller settings.

## 🛠️ Hardware Requirements
- **Microcontroller:** ESP32-S3 (Recommended for USB+BLE) or ESP32-C3 (BLE only).
- **Receiver:** Any SBUS-capable receiver (e.g., RadioLink R7GS).
- **Cabling:** Micro-USB/USB-C for power and data.

### Wiring Diagram
| Receiver Pin | ESP32 Pin | Description |
| :--- | :--- | :--- |
| **GND** | **GND** | Ground |
| **VCC** | **5V / VCC** | Power (use 3.3V for more accurate telemetry) |
| **Signal (SBUS)**| **GPIO 4 (RX1)** | SBUS Data Line |



## 💻 Software Setup
1. Install **Arduino IDE**.
2. Install **ESP32 Arduino Core (v3.0.0 or newer)** via Boards Manager.
3. Install the following libraries:
   - [ESP32-BLE-Gamepad](https://github.com/lemmingDev/ESP32-BLE-Gamepad)
   - [Bolder Flight Systems SBUS](https://github.com/bolderflight/sbus)

### Critical Board Settings (For S3)
- **Board:** `ESP32S3 Dev Module`
- **USB Mode:** `USB-OTG (TinyUSB)`
- **USB CDC On Boot:** `Enabled`



## 🎮 Calibration
1. Connect via USB (Native Port) or Bluetooth.
2. Press `Win + R` and type `joy.cpl`.
3. Select the device and go to **Properties -> Settings -> Calibrate**.
4. Move all sticks and flick all switches to their limits.

## ⚖️ License
MIT License. Feel free to modify and share!
