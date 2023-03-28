#define BLYNK_TEMPLATE_ID "TMPLUWnQDgZ4"
#define BLYNK_TEMPLATE_NAME "Latihan 2"
#define BLYNK_AUTH_TOKEN "CalzrRIANdSYkBZLWCkrJmWsVXY289PR"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0X27
#define LCD_COLUMNS 20
#define LCD_LINES 4
#define LED1 13
#define LED2 12
#define LED3 14
#define LED4 27
#define BUZZ 23
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht (DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

char auth[] = "CalzrRIANdSYkBZLWCkrJmWsVXY289PR";
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Monitoring Suhu");
  Serial.println("=================================================");
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(LCD_LINES, OUTPUT);
  Wire.begin(4,5);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("I Made Dwaja Sanjaya");
  lcd.setCursor(2, 1);
  lcd.print("2015344040");
  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();
  float Lembab = dht.readHumidity();

  if(temp < 20){
    Serial.println("Status Suhu : DINGIN");
    Serial.println("Lampu Hijau Menyala");
    Serial.println("Buzzer belum menyala...");
    Serial.println("=================================================");
    digitalWrite(LED3,HIGH);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED4,LOW);
    Blynk.virtualWrite(V3, HIGH);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V2, LOW);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V5, LOW);
    tone(BUZZ,0,0);
  } else if(temp >= 20 && temp < 30 ){
    Serial.println("Status Suhu : NORMAL");
    Serial.println("Lampu Biru Menyala");
    Serial.println("Buzzer menyala dengan frekuensi 100Hz...");
    Serial.println("=================================================");
    digitalWrite(LED4, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED1, LOW);
    Blynk.virtualWrite(V4, HIGH);
    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V2, LOW);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V5, HIGH);
    tone(BUZZ,100,2000);
  } else if(temp >= 30 && temp < 40){
    Serial.println("Status Suhu : HANGAT");
    Serial.println("Lampu Kuning Menyala");
    Serial.println("Buzzer menyala dengan frekuensi 500Hz...");
    Serial.println("=================================================");
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    Blynk.virtualWrite(V2, HIGH);
    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V5, HIGH);
    tone(BUZZ,500,1000);
  } else if(temp >= 40){
    Serial.println("Status Suhu : PANAS");
    Serial.println("Lampu Merah Menyala");
    Serial.println("Buzzer menyala dengan frekuensi 1000Hz...");
    Serial.println("=================================================");
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    Blynk.virtualWrite(V1, HIGH);
    Blynk.virtualWrite(V2, LOW);

    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V5, HIGH);
    tone(BUZZ,1000,100);
  }

  Blynk.virtualWrite(V0,temp);

  Serial.print("Temperature : ");;
  Serial.print(temp);
  Serial.println(" C");
  lcd.setCursor(1, 0);
  lcd.println("Suhu :");
  lcd.println(temp);
  lcd.setCursor (2, 1);
  lcd.println("lembab:");
  lcd.println(Lembab);
  lcd.println("%");



  Blynk.run();
  timer.run();
}