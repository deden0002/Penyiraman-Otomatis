#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SENSOR_PIN A0
#define RELAY_PIN 9
#define BUZZER_PIN 10

LiquidCrystal_I2C lcd(0x27, 16, 2); // Atur alamat I2C LCD dan ukuran LCD

int moistureThreshold = 60; // Ambang kelembaban tanah untuk memulai penyiraman, sesuaikan sesuai kebutuhan

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Pastikan relay mati pada awalnya
  digitalWrite(BUZZER_PIN, LOW); // Pastikan buzzer mati pada awalnya
  Serial.begin(9600);
  lcd.begin(); // Inisialisasi LCD
  lcd.backlight(); // Nyalakan backlight LCD
}

void loop() {
  int moistureLevel = map(analogRead(SENSOR_PIN), 0, 1023, 100, 0); // Inversi nilai kelembaban
  
  lcd.clear(); // Bersihkan layar LCD
  lcd.setCursor(0, 0);
  lcd.print("Kelembaban: ");
  lcd.print(moistureLevel);
  lcd.print("%");

  Serial.print("Kelembaban tanah: ");
  Serial.print(moistureLevel);
  Serial.println("%");

  if (moistureLevel < moistureThreshold) {
    // Tanah kering, hidupkan penyiraman dan aktifkan buzzer
    Serial.println("Penyiraman dinyalakan");
    digitalWrite(RELAY_PIN, HIGH); // Hidupkan relay (hidupkan pompa air)
    digitalWrite(BUZZER_PIN, HIGH); // Aktifkan buzzer
    delay(10000); // Penyiraman selama 5 detik (sukar interval penyiraman sesuai kebutuhan)
    digitalWrite(RELAY_PIN, LOW); // Matikan relay setelah penyiraman selesai
    digitalWrite(BUZZER_PIN, LOW); // Matikan buzzer setelah penyiraman selesai
  } else {
    // Tanah sudah cukup lembab, matikan penyiraman dan buzzer
    Serial.println("Penyiraman dimatikan");
    digitalWrite(RELAY_PIN, LOW); // Pastikan relay mati
    digitalWrite(BUZZER_PIN, LOW); // Pastikan buzzer mati
  }
  delay(10000); // Tunggu 10 detik sebelum melakukan pembacaan sensor selanjutnya
}
