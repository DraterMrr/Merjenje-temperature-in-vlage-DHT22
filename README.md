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

"C:\Users\U207.05\Documents\Arduino\dht22prj\dht22prj.ino"

