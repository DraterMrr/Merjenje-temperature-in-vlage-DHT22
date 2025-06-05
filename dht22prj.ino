#include <LiquidCrystal.h>
#include <DHT.h>

// LCD pinout: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// DHT senzor
#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Stikalo
#define SWITCH_PIN 13

// LED pin (modra)
#define LED_PIN 12

// rdeča LED
#define LED_RDECA_PIN 11

bool napravaVklopljena = false;
bool prikazON = false;
unsigned long casVklopa = 0;
const unsigned long prikazONcas = 1000; // 1 s prikaz "Naprava ON"

float temp = NAN;
float hum = NAN;

unsigned long prejsnjiCasDHT = 0;
unsigned long prejsnjiCasLCD = 0;
const unsigned long intervalDHT = 2000;
const unsigned long intervalLCD = 250;

unsigned long casUtripanja = 0;
bool utripPrikaz = true;
const unsigned long intervalUtripanja = 500; // 500 ms

void setup() {
  lcd.begin(16, 2);
  dht.begin();

  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_RDECA_PIN, OUTPUT); // nova rdeča LED

  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_RDECA_PIN, HIGH); // rdeča LED sveti, ker je naprava izklopljena

  lcd.setCursor(0, 0);
  lcd.print("Naprava OFF");
}

void loop() {
  unsigned long trenutniCas = millis();
  int stanjeStikala = digitalRead(SWITCH_PIN);
  bool trenutnoStanje = (stanjeStikala == LOW);

  // Sprememba stanja stikala
  if (trenutnoStanje != napravaVklopljena) {
    napravaVklopljena = trenutnoStanje;

    digitalWrite(LED_PIN, napravaVklopljena ? HIGH : LOW);
    digitalWrite(LED_RDECA_PIN, napravaVklopljena ? LOW : HIGH); // upravljanje z rdečo LED

    if (napravaVklopljena) {
      prikazON = true;
      casVklopa = trenutniCas;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Naprava ON");
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Naprava OFF");
      casUtripanja = trenutniCas;
      utripPrikaz = true;
    }
  }

  // Če naprava ni vklopljena, utripaj besedilo v 2. vrstici
  if (!napravaVklopljena) {
    if (trenutniCas - casUtripanja >= intervalUtripanja) {
      casUtripanja = trenutniCas;
      lcd.setCursor(0, 1);
      if (utripPrikaz) {
        lcd.print("Preklopi stikalo");
      } else {
        lcd.print("                ");
      }
      utripPrikaz = !utripPrikaz;
    }
    return;
  }

  // Po 1 sekundi po vklopu naprave, prikazuj podatke
  if (prikazON && (trenutniCas - casVklopa >= prikazONcas)) {
    prikazON = false;
    lcd.clear();
    prejsnjiCasDHT = 0;
    prejsnjiCasLCD = 0;
  }

  if (prikazON) {
    return; // še vedno prikazuje "Naprava ON"
  }

  // Branje senzorja
  if (trenutniCas - prejsnjiCasDHT >= intervalDHT) {
    prejsnjiCasDHT = trenutniCas;
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t) && !isnan(h)) {
      temp = t;
      hum = h;
    }
  }

  // Osveži LCD
  if (trenutniCas - prejsnjiCasLCD >= intervalLCD) {
    prejsnjiCasLCD = trenutniCas;
    lcd.setCursor(0, 0);
    if (isnan(temp)) {
      lcd.print("Napaka DHT22     ");
    } else {
      lcd.print("Temp: ");
      lcd.print(temp, 1);
      lcd.print((char)223);
      lcd.print("C    ");
    }

    lcd.setCursor(0, 1);
    if (isnan(hum)) {
      lcd.print("Napaka DHT22     ");
    } else {
      lcd.print("Vlaga: ");
      lcd.print(hum, 1);
      lcd.print("%    ");
    }
  }
}
