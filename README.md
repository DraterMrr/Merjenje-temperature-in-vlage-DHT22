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





Opis delovanja sistema


Ko je sistem napajan, se na LCD zaslonu prikaže začetno sporočilo "Naprava OFF", ki uporabniku jasno pove, da merilni sistem še ni aktiven. V tem stanju sveti rdeča LED, kar vizualno potrdi, da je naprava izklopljena. Na drugi vrstici LCD-ja utripajoče besedilo "Preklopi stikalo" opozarja uporabnika, da lahko s pritiskom na stikalo napravo aktivira.


Ko uporabnik pritisne stikalo (na digitalnem pinu 13), sistem zazna preklop in preide v aktivno stanje. V tem trenutku:

Modra LED se prižge, kar pomeni, da je sistem aktiven.

Rdeča LED ugasne.

Na LCD zaslonu se za 1 sekundo izpiše "Naprava ON".

Nato sistem samodejno začne prikazovati merjene vrednosti temperature in vlage, ki jih zazna senzor DHT22.

Vrednosti se prikazujejo v realnem času, LCD pa se osvežuje vsakih 250 milisekund, medtem ko se meritve s senzorja osvežijo vsakih 2 sekundi, da se prepreči prekomerna obremenitev senzorja.

Če senzor DHT22 ne poda veljavnih vrednosti (zaradi napake, nepravilne povezave ali motenj), sistem na LCD-ju izpiše "Napaka DHT22".

Ob ponovnem pritisku na stikalo se naprava izklopi, vrednosti prenehajo s prikazovanjem in sistem se vrne v začetno stanje.


Možne nadgradnje in razširitve

Projekt je zasnovan modularno, kar pomeni, da ga je mogoče preprosto razširiti z dodatnimi funkcionalnostmi:

Zapisovanje podatkov (Data Logging)

Dodajanje SD kartice za shranjevanje meritev v CSV obliki.

Možnost analize podatkov naknadno na računalniku.

Daljinsko spremljanje

Vključitev WiFi modula (npr. ESP8266) za pošiljanje podatkov v oblak.

Vmesnik z mobilno aplikacijo ali spletno nadzorno ploščo.

Alarmni sistem

Dodajanje zvočnega ali vizualnega alarma, če temperatura ali vlaga presežeta določene meje.

Uporaba relejev za vklop prezračevanja ali ogrevanja.

Samodejno vklapljanje

Uporaba senzorja gibanja (PIR) za avtomatski vklop sistema, ko je oseba v prostoru.

Upravljanje z meniji

Razširitev LCD prikaza z menijskim sistemom in več informacijami (npr. maksimalna/minimalna temperatura).



