# Merjenje-temperature-in-vlage-DHT22


Namen tega projekta je razvoj preprostega in učinkovitega sistema za merjenje temperature in vlažnosti zraka z uporabo senzorja DHT22, priklopljenega na Arduino mikrokontroler. Merjeni podatki se v realnem času prikazujejo na LCD zaslonu z I2C komunikacijo. Sistem omogoča osnovno spremljanje okoljskih pogojev v prostoru ali okolici, zato je primeren za hobi uporabo, osnovno avtomatizacijo prostora, merjenje klime v rastlinjakih ali kot uvod v IoT (Internet stvari).


Projekt omogoča uporabnikom, da se naučijo delati s senzorji, digitalnim branjem podatkov, LCD zasloni in programiranjem z uporabo Arduino platforme. Poleg tega je projekt mogoče razširiti v bolj kompleksne sisteme z dodatnimi funkcionalnostmi, kot so beleženje podatkov, alarmi in daljinsko spremljanje.
Za izdelavo tega projekta potrebujemo naslednje elektronske komponente:


1.	Arduino Uno – Osrednji krmilnik projekta.

2.	DHT22 (AM2302) – Digitalni senzor za merjenje temperature in relativne vlažnosti. Ima višjo natančnost kot DHT11.

3.	LCD 16x2 z I2C vmesnikom – Zaslon za prikaz rezultatov. I2C modul omogoča enostavnejše povezovanje z Arduinom.

4. Perf Board za povezovanje komponent

5.	LED ena modra, ena rdeča

6.	Stikalo, za preklop in izklop naprave

7.	Povezovalne žice (jumper kabli) – Za električne povezave med komponentami.

Te komponente so dostopne v večini trgovin z elektroniko in jih pogosto najdemo tudi v Arduino kompletih za začetnike. Priporočljivo je tudi imeti računalnik z nameščenim Arduino IDE programom za pisanje in nalaganje kode.

Povezava vezja (shema priklopa)

DHT22 senzor:

•	VCC → 5V na Arduino plošči (zagotavlja napajanje)

•	GND → GND na Arduino (ozemljitev)

•	DATA → Digitalni vhod 8 (za komunikacijo z mikrokontrolerjem)
LCD 16x2 :

•	VSS → GND na Arduino 

•	VDD → 5V na Arduino 

•	VO → Srednji pin potenciometra (za nastavitev kontrasta LCD-ja)

•	RS → Digitalni pin 7 na Arduino (Register Select)

•	RW → GND na Arduino (stalno pisanje na LCD)

•	E → Digitalni pin 6 na Arduino (Enable – sprožitev prenosa)

•	D4 → Digitalni pin  5 na Arduino

•	D5 → Digitalni pin 4 na Arduino 

•	D6 → Digitalni pin 3 na Arduino 

•	D7 → Digitalni pin 2 na Arduino 

•	A (LED+) → 5V na Arduino 

•	K (LED−) → GND na Arduino


STIKALO: 

•	Srednja noga stikala → pin 13 na Arduino (podatkovna linija)

•	Prva noga stikala → GND na Arduino (ozemljivetv)


LED: 

•	Anoda → pin 12 na Arduino (podatkovna linija)

•	Katoda → GND
![dht22ee](https://github.com/user-attachments/assets/e51236a1-dfbb-4972-bbf9-433419e6d3ff)


4. Uporabljene knjižnice 

 

Za pravilno delovanje kode je treba v Arduino IDE vključiti naslednje knjižnice: 

DHT sensor library – Omogoča komunikacijo z DHT senzorjem. Avtor: Adafruit. 

Adafruit Unified Sensor – Niz knjižnic, ki podpirajo različne senzorje in poenoteno komunikacijo. 

LiquidCrystal_I2C – Omogoča komunikacijo z LCD zaslonom preko I2C vodila. 

Brez teh knjižnic koda ne bo delovala, saj Arduino ne bo prepoznal ukazov za senzor in zaslon. 

 
5. Izvorna koda 

Tu je koda za delovanje sistema: 
[Uploading d#include <LiquidCrystal.h>
#include <DHT.h>

// LCD pinout: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// DHT senzor
#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Stikalo
#define SWITCH_PIN 13

// LED pin (zelena)
#define LED_PIN 12

// Nova rdeča LED
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
ht22prj.ino…]()

