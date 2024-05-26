#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 4;

HX711 scale;

void setup() {
  Serial.begin(57600);
  Serial.println("Load Cell Interfacing with ESP32 - DIY CHEAP PERFECT");
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(-357.28);    // this value is obtained by calibrating the scale with known weights as in previous step
  scale.tare();
  Wire.begin(21, 22);          // Inisialisasi I2C dengan pin SDA di GPIO 21 dan pin SCL di GPIO 22
  lcd.init();                  // Inisialisasi layar LCD
  lcd.backlight();             // Aktifkan pencahayaan belakang LCD
  lcd.setCursor(0, 0);         // Posisikan kursor di kolom 0, baris 0
  lcd.print("Starting....");				         // reset the scale to 0
}

//DIY_CHEAP_PERFECT

void loop() {
  Serial.print("Weight: ");
  lcd.setCursor(0, 1);         // Posisikan kursor di kolom 0, baris 0
  lcd.print("Weight: ");
  Serial.println(scale.get_units(10), 1);
  lcd.setCursor(0, 2);         // Posisikan kursor di kolom 0, baris 1
  lcd.print(scale.get_units(10), 1);
  scale.power_down();			        // put the ADC in sleep mode
  delay(1000);
  scale.power_up();  
}

//DIY_CHEAP_PERFECT
