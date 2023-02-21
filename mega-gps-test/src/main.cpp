
#include <Arduino.h>
#include <Wire.h>
#include <TinyGPS.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define D_SCLK 8 // Serial clock out (SCLK)
#define D_DIN 9 // Serial data out (DIN)
#define D_DC 10 // Data/Command select (D/C)
#define D_CS 11 // LCD chip select (CS)
#define D_RST 12 // LCD reset (RST)

#define D_CONTRAST 45

TinyGPS gps;
float lat,lon;
Adafruit_PCD8544 display = Adafruit_PCD8544(D_DC, D_CS, D_RST);

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600);
  // Initial Display status
  display.begin();
  display.setContrast(D_CONTRAST);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.setTextColor(WHITE, BLACK); // 'inverted' text
  display.println("              ");
  display.println("   GPS Test   ");
  display.println("              ");
  display.setTextColor(BLACK);
  display.println();
  display.println("Waiting...");
  display.display();
  delay(1000);
  display.setTextSize(1);
  display.setTextColor(BLACK);
}

void loop()
{
  float flat, flon;
  unsigned long age;

  while(Serial2.available()) // check for gps data 
  {
    if(gps.encode(Serial2.read()))// encode gps data 
    {
      gps.f_get_position(&flat, &flon, &age);
    // display position 
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(0,0);
      display.print("LT:"); 
      display.println(flat, 6); 
      display.print("LN:"); 
      display.println(flon, 6);
      display.print("SAT:"); 
      display.println(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
      display.print("DIR:"); 
      display.println(gps.f_course() == TinyGPS::GPS_INVALID_F_ANGLE ? 0 : gps.f_course());
      display.display();
      Serial.print("LATTITUDE=");
      Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
      Serial.print(" LONGITUDE=");
      Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
      Serial.print(" SATS=");
      Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
      Serial.print(" PRECISION=");
      Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
      Serial.print(" ALTITUDE=");
      Serial.print(gps.f_altitude() == TinyGPS::GPS_INVALID_F_ALTITUDE ? 0 : gps.f_altitude());
      Serial.print(" COURSE=");
      Serial.print(gps.f_course() == TinyGPS::GPS_INVALID_F_ANGLE ? 0 : gps.f_course());
      Serial.print(" SPEED=");
      Serial.print(gps.f_speed_kmph() == TinyGPS::GPS_INVALID_F_SPEED ? 0 : gps.f_speed_kmph());
    } 
  } 

}
