# Buddy
A small pocket friend with animated eyes. Buddy runs on a XIAO ESP32-S3 with a 2" LCD and, through a imu (LIS2DH12), reacts to how you handle it.

## Features
- Animated eyes drawn off-screen and pushed in a single transfer to the screen so ther is no flicker.
- Eyes follow the edge of the board.
- Shake / Upside down detection and reaction.
- Side button to cycle thrugh three moods (normal / happy / sleepy)
- Customized PCB with multicolor silkscreen and a hole for a carabiner to attach it as a keychain.

## Firmware

The code is in `code/code.ino`.
 
1. Install the ESP32 board package and select XIAO_ESP32S3
2. Install Adafruit GFX Library and Adafruit ST7789 Library.
3. Upload the sketch.

## BOM
| Designator | Footprint | Qty | Value | LCSC Part # | Total (USD) |
|---|---|---|---|---|---|---|
| C3, C4 | 0402 | 2 | 100nF | C1525 | 0.002 |
| CN1 | CONN-SMD_P2.00_S2B-PH-SM4-TB-LF-SN | 1 | S2B-PH-SM4-TB | C295747 | 0.22 |
| R1, R2 | 0402 | 2 | 4.7k | C25900 | 0.001 | 0.002 |
| SW1 | KEY-SMD_1TS003B | 1 | 1TS003B-1400-3500A | C319392 | 0.04 |
| U2 | LGA-12_L2.0-W2.0-P0.50-BL | 1 | LIS2DH12TR | C110926 | 0.61 |
| U3 | XIAO-ESP32-S3-SMD | 1 | XIAO ESP32-S3 | n/a (Seeed Studio) | 7.49 |
| WAVESHARE_SCREEN | PinHeader_1x08_P2.54mm_Vertical | 1 | Waveshare 2inch LCD Module | n/a (Waveshare) |  14.28 |
**Total**  **≈ 22.65** 

## Screenshots

## LICENSE

This project is under the MIT License. Read `LICENSE.md` for more information.
