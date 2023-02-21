#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define D_SCLK 8 // Serial clock out (SCLK)
#define D_DIN 9 // Serial data out (DIN)
#define D_DC 10 // Data/Command select (D/C)
#define D_CS 11 // LCD chip select (CS)
#define D_RST 12 // LCD reset (RST)

#define D_CONTRAST 35

Adafruit_PCD8544 display = Adafruit_PCD8544(D_DC, D_CS, D_RST);

#define IRL_IR 33
#define IRL_D1 A15
#define IRL_D2 A14
#define IRL_D3 A13
#define IRL_D4 A13
#define IRL_D5 A12
#define IRL_D6 A11
#define IRL_D7 A10
#define IRL_D8 A9

#define IRL_MINVAL 600
#define IRL_MAXVAL 950
#define IRL_LEVEL 3

bool readIRL(float* DD) {
  int irlD[] = {IRL_D1, IRL_D2, IRL_D3, IRL_D4, IRL_D5, IRL_D6, IRL_D7, IRL_D8};
  int irlV[8];
  float D = 0;
  int nD = 0;

  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = 0; i < 8; i++) {
    irlV[i] = map(analogRead(irlD[i]), IRL_MAXVAL, IRL_MINVAL, 1, 5);
    Serial.print("D[");
    Serial.print(i);
    Serial.print("]=");
    Serial.println(irlV[i]);
    if (irlV[i] < IRL_LEVEL) {
      display.setCursor(i*7,0);
      display.print("#");
      display.setCursor(i*7,10);
      display.print(irlV[i]);
      D += i;
      nD++;
    }
    else {
      display.setCursor(i*7,0);
      display.print(" ");
      display.setCursor(i*7,10);
      display.print(irlV[i]);
    }
  }
  display.setCursor(0, 20);
  display.print("D=");
  if (nD != 0) {
    D /= nD;
    D -= 3.5;
    display.println(D, 1);
    *DD = D;
    display.display();
    return true;
  } else {
    display.println("?");
    display.display();
    return false;
  }
}

void setup() {
  pinMode(IRL_IR, OUTPUT);
  // IRL Start
  digitalWrite(IRL_IR, HIGH);
  Serial.begin(115200);
  // Initial Display status
  display.begin();
  display.setContrast(D_CONTRAST);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.setTextColor(WHITE, BLACK); // 'inverted' text
  display.println("              ");
  display.println("   IRL Test   ");
  display.println("              ");
  display.setTextColor(BLACK);
  display.println();
  display.display();
  delay(1000);
  display.setTextSize(1);
  display.setTextColor(BLACK);
}

void loop() {
  float D = 0;
  if (readIRL(&D)) {
    Serial.println(D, 1);
  } else {
    Serial.println("?");
  }
  delay(200);
}