#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// pantalla
#define LCD_MOSI D10
#define LCD_SCLK D8
#define LCD_CS   D1
#define LCD_DC   D2
#define LCD_RST  D3
#define LCD_BL   D4

// IMU LIS2DH12 (I2C) y boton
#define IMU_SDA  D5
#define IMU_SCL  D6
#define BTN      D0
#define IMU_ADDR 0x18   // SA0 a GND

Adafruit_ST7789 tft(LCD_CS, LCD_DC, LCD_RST);

#define BG_COLOR  0x0000
#define EYE_COLOR 0x25FF

const int W = 320;
const int H = 240;

// el canvas solo cubre la franja de los ojos
const int CANVAS_Y = 50;
const int CANVAS_H = 140;
GFXcanvas16 *canvas;

const int EYE_W      = 70;
const int EYE_MAX_H  = 80;
const int EYE_RADIUS = 15;
const int EYE_GAP    = 50;
const int LEFT_CX    = W / 2 - EYE_GAP / 2 - EYE_W / 2;
const int RIGHT_CX   = W / 2 + EYE_GAP / 2 + EYE_W / 2;
const int CENTER_Y   = CANVAS_H / 2;

// si miran al lado contrario al inclinar, cambia el signo
const int SIGNO_X = 1;
const int SIGNO_Y = -1;

enum Animo { NORMAL, FELIZ, SUENO };
Animo animo = NORMAL;

float altoAct = EYE_MAX_H, altoObj = EYE_MAX_H;
float xAct = 0, xObj = 0;
float yAct = 0, yObj = 0;

// aceleracion en mg
float ax = 0, ay = 0, az = 1000;
bool hayIMU = false;

unsigned long proxParpadeo = 0;
unsigned long proxMirada   = 0;
unsigned long ultimoFrame  = 0;
unsigned long sustoHasta   = 0;
unsigned long ultimoMov    = 0;

int ultAlto = -1, ultX = 9999, ultY = 9999;
Animo ultAnimo = NORMAL;

bool btnPrevio = HIGH;
unsigned long btnTiempo = 0;

// IMU

void escribirReg(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(IMU_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

int16_t leer16() {
  uint8_t lo = Wire.read();
  uint8_t hi = Wire.read();
  return (int16_t)((hi << 8) | lo);
}

bool iniciarIMU() {
  Wire.begin(IMU_SDA, IMU_SCL);
  Wire.setClock(400000);

  Wire.beginTransmission(IMU_ADDR);
  Wire.write(0x0F);                     // who am i
  if (Wire.endTransmission(false) != 0) return false;
  Wire.requestFrom(IMU_ADDR, 1);
  if (!Wire.available() || Wire.read() != 0x33) return false;

  escribirReg(0x20, 0x57);              // 100 Hz, XYZ activos
  escribirReg(0x23, 0x88);              // BDU + alta resolucion, +-2g
  return true;
}

bool leerIMU() {
  Wire.beginTransmission(IMU_ADDR);
  Wire.write(0x28 | 0x80);              // lectura continua desde OUT_X_L
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom(IMU_ADDR, 6) != 6) return false;

  int16_t x = leer16();
  int16_t y = leer16();
  int16_t z = leer16();

  // 12 bits alineados a la izquierda, 1 mg por cuenta
  ax = x >> 4;
  ay = y >> 4;
  az = z >> 4;
  return true;
}

// boton

void revisarBoton() {
  bool ahora = digitalRead(BTN);
  if (ahora == LOW && btnPrevio == HIGH && millis() - btnTiempo > 60) {
    btnTiempo = millis();
    ultimoMov = millis();
    animo = (Animo)((animo + 1) % 3);
    Serial.print("animo: ");
    Serial.println(animo);
  }
  btnPrevio = ahora;
}

// draw
void dibujarOjo(int cx, int alto, int ox, int oy) {
  int x = cx - EYE_W / 2 + ox;
  int y = CENTER_Y - alto / 2 + oy;
  int r = min(EYE_RADIUS, alto / 2);

  canvas->fillRoundRect(x, y, EYE_W, alto, r, EYE_COLOR);

  if (alto < 30) return;                // casi cerrado, nada mas que tapar

  if (animo == FELIZ) {
    // circulo negro por debajo: deja el ojo en forma de ^
    canvas->fillCircle(cx + ox, y + alto + 10, EYE_W / 2 + 2, BG_COLOR);
  } else if (animo == SUENO) {
    // parpado de arriba caido
    canvas->fillRect(x - 1, y - 1, EYE_W + 2, alto * 45 / 100, BG_COLOR);
  }
}

void dibujar(int alto, int ox, int oy) {
  canvas->fillScreen(BG_COLOR);
  dibujarOjo(LEFT_CX,  alto, ox, oy);
  dibujarOjo(RIGHT_CX, alto, ox, oy);

  // un solo envio a la pantalla
  tft.startWrite();
  tft.setAddrWindow(0, CANVAS_Y, W, CANVAS_H);
  tft.writePixels(canvas->getBuffer(), W * CANVAS_H);
  tft.endWrite();
}

// setup/loop

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);
  pinMode(BTN, INPUT_PULLUP);

  SPI.begin(LCD_SCLK, -1, LCD_MOSI, LCD_CS);
  tft.init(240, 320);
  tft.setRotation(1);
  tft.invertDisplay(false);
  tft.setSPISpeed(40000000);

  tft.fillScreen(EYE_COLOR);
  delay(500);
  tft.fillScreen(BG_COLOR);

  canvas = new GFXcanvas16(W, CANVAS_H);
  if (!canvas->getBuffer()) {
    Serial.println("sin memoria para el canvas");
    while (true) delay(1000);
  }

  hayIMU = iniciarIMU();
  Serial.println(hayIMU ? "IMU ok" : "IMU no encontrado, mirada aleatoria");

  randomSeed(esp_random());
  proxParpadeo = millis() + 2000;
  proxMirada   = millis() + 1500;
  ultimoMov    = millis();

  dibujar(EYE_MAX_H, 0, 0);
  Serial.println("Pantalla lista");
}

void loop() {
  revisarBoton();

  unsigned long ahora = millis();
  if (ahora - ultimoFrame < 25) return;
  ultimoFrame = ahora;

  int altoMax = EYE_MAX_H;
  bool bocaAbajo = false;

  if (hayIMU && leerIMU()) {
    // sacudida: la aceleracion total se aleja de 1g
    float total = sqrt(ax * ax + ay * ay + az * az);
    if (fabs(total - 1000) > 700) {
      sustoHasta = ahora + 1200;
      ultimoMov = ahora;
    }

    // boca abajo = se duerme
    bocaAbajo = (az < -700);

    // inclinar = mirar hacia ese lado
    xObj = constrain(SIGNO_X * ax / 40.0f, -20, 20);
    yObj = constrain(SIGNO_Y * ay / 70.0f, -10, 10);

    if (fabs(ax) > 150 || fabs(ay) > 150) ultimoMov = ahora;
  } else if (ahora >= proxMirada) {
    xObj = random(-18, 19);
    yObj = random(-8, 9);
    proxMirada = ahora + random(1200, 3500);
  }

  // 30 s quieto y se aburre
  bool aburrido = hayIMU && (ahora - ultimoMov > 30000);

  if (ahora < sustoHasta) {
    altoMax = EYE_MAX_H + 22;           // ojos grandes por el susto
    xObj = 0;
    yObj = 0;
  }

  if (bocaAbajo || aburrido) {
    altoObj = 6;                        // cerrados
  } else {
    if (ahora >= proxParpadeo) {
      altoObj = 6;
      proxParpadeo = ahora + random(2500, 5500);
    }
    // cuando ya cerro del todo, vuelve a abrir
    if (altoObj == 6 && altoAct < 14) altoObj = altoMax;
    if (altoObj != 6) altoObj = altoMax;
  }

  float vel = (altoObj < altoAct) ? 0.55f : 0.35f;
  altoAct += (altoObj - altoAct) * vel;
  xAct += (xObj - xAct) * 0.18f;
  yAct += (yObj - yAct) * 0.18f;

  int a = round(altoAct);
  int x = round(xAct);
  int y = round(yAct);

  // solo mando datos si algo cambio
  if (a != ultAlto || x != ultX || y != ultY || animo != ultAnimo) {
    dibujar(a, x, y);
    ultAlto = a; ultX = x; ultY = y; ultAnimo = animo;
  }
}
