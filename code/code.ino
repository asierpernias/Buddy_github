
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>


// PIN definition
#define LCD_MOSI D10
#define LCD_SCLK D8
#define LCD_CS D1
#define LCD_DC D2
#define LCD_RST D3
#define LCD_BL D4

Adafruit_ST7789 tft(LCD_CS, LCD_DC, LCD_RST);

// EYES

const int W = 320;
const int H = 240;

const int EYE_Y =70;
const int EYE_X =90;
const int EYE_RADIUS =15;
const int EYE_GAP =50;
const int 
const int CENTER_Y = H/2;
// Colors RGB
#define BG_COLOR 0x0000 // black
#define EYE_COLOR 0x25FF // cyan

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);

  // TFT screen initializing
  tft.init(240, 320);
  tft.setRotation(1);
  tft.invertDisplay(false);
  tft.setSPISpeed(20000000);

  tft.fillScreen(EYE_COLOR);
  delay(1000);
  tft.fillScreen(BG_COLOR);

  Serial.println("Pantalla LIsta")
}

void loop() {

}
