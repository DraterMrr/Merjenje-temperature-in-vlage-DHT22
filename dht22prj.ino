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

// LED pin
#define BLUE_LED_PIN 12  // modra LED

bool napravaVklopljena = false;

float temp = NAN;
float hum = NAN;

unsigned long prejsnjiCasDHT = 0;
unsigned long prejsnjiCasLCD = 0;
const unsigned long intervalDHT = 2000;
const unsigned long intervalLCD = 250;

unsigned long casStanja = 0; // Čas začetka trenutnega stanja (ON ali OFF)
const unsigned long trajanjePrikaza = 1000; // 1 sekunda za prikaz "Naprava ON" ali "OFF"

unsigned long zadnjiCasUtripLED = 0;
bool modraLEDgori = false;

// Za utripanje LED ob spremembi stanja z uporabo delay (ker je samo dvakrat)
void utripniModroLED(int ponovitve, int trajanje = 150) {
  for (int i = 0; i < ponovitve; i++) {
    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(trajanje);
    digitalWrite(BLUE_LED_PIN, LOW);
    delay(trajanje);
  }
}

void setup() {
  lcd.begin(16, 2);
  dht.begin();

  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(BLUE_LED_PIN, OUTPUT);

  digitalWrite(BLUE_LED_PIN, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Naprava OFF");
}

void loop() {
  unsigned long trenutniCas = millis();
  int stanjeStikala = digitalRead(SWITCH_PIN);
  bool trenutnoStanje = (stanjeStikala == LOW);

  // Če se stanje spremeni, izvedemo akcije
  if (trenutnoStanje != napravaVklopljena) {
    napravaVklopljena = trenutnoStanje;
    casStanja = trenutniCas;

    if (napravaVklopljena) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Naprava ON");
      utripniModroLED(2);
      zadnjiCasUtripLED = trenutniCas;  // za redno utripanje LED kasneje
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Naprava OFF");
      utripniModroLED(2);
      digitalWrite(BLUE_LED_PIN, LOW);
    }
  }

  // Če je naprava OFF - utripaj napis v 2. vrstici
  if (!napravaVklopljena) {
    static bool utripPrikaz = true;
    static unsigned long casUtripanja = 0;
    if (trenutniCas - casUtripanja >= 500) {
      casUtripanja = trenutniCas;
      lcd.setCursor(0, 1);
      if (utripPrikaz) {
        lcd.print("Preklopi stikalo");
      } else {
        lcd.print("                ");
      }
      utripPrikaz = !utripPrikaz;
    }
    return; // Ne delaj več, ker je OFF
  }

  // Če je naprava ON in je od spremembe minila manj kot 1 sekunda,
  // samo prikazujemo "Naprava ON"
  if (trenutniCas - casStanja < trajanjePrikaza) {
    // Ne delaj nič drugega, samo počakaj
    return;
  }

  // Po 1s po vklopu začne prikazovati podatke z DHT22

  // Vsakih 5 sekund modra LED zasveti za 0.5 sekunde
  if (trenutniCas - zadnjiCasUtripLED >= 5000) {
    digitalWrite(BLUE_LED_PIN, HIGH);
    modraLEDgori = true;
    zadnjiCasUtripLED = trenutniCas;
  }
  if (modraLEDgori && (trenutniCas - zadnjiCasUtripLED >= 500)) {
    digitalWrite(BLUE_LED_PIN, LOW);
    modraLEDgori = false;
  }

  // Branje DHT senzorja vsake 2 sekundi
  if (trenutniCas - prejsnjiCasDHT >= intervalDHT) {
    prejsnjiCasDHT = trenutniCas;
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t) && !isnan(h)) {
      temp = t;
      hum = h;
    }
  }

  // Osvežitev LCD vsake 250 ms
  if (trenutniCas - prejsnjiCasLCD >= intervalLCD) {
    prejsnjiCasLCD = trenutniCas;

    lcd.setCursor(0, 0);
    if (isnan(temp)) {
      lcd.print("Napaka DHT22     ");
    } else {
      lcd.print("Temp: ");
      lcd.print(temp, 1);
      lcd.print((char)223); // stopinja znak
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
