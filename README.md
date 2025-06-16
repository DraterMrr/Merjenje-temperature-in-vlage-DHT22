# Merjenje-temperature-in-vlage-DHT22


Namen tega projekta je razvoj preprostega in učinkovitega sistema za merjenje temperature in vlažnosti zraka z uporabo senzorja DHT22, priklopljenega na Arduino mikrokontroler. Merjeni podatki se v realnem času prikazujejo na LCD zaslonu z I2C komunikacijo. Sistem omogoča osnovno spremljanje okoljskih pogojev v prostoru ali okolici, zato je primeren za hobi uporabo, osnovno avtomatizacijo prostora, merjenje klime v rastlinjakih ali kot uvod v IoT (Internet stvari).


Projekt omogoča uporabnikom, da se naučijo delati s senzorji, digitalnim branjem podatkov, LCD zasloni in programiranjem z uporabo Arduino platforme. Poleg tega je projekt mogoče razširiti v bolj kompleksne sisteme z dodatnimi funkcionalnostmi, kot so beleženje podatkov, alarmi in daljinsko spremljanje.
Za izdelavo tega projekta potrebujemo naslednje elektronske komponente:


1.	Arduino Uno – Osrednji krmilnik projekta.

2.	DHT22 (AM2302) – Digitalni senzor za merjenje temperature in relativne vlažnosti. Ima višjo natančnost kot DHT11.

3.	LCD 16x2 z I2C vmesnikom – Zaslon za prikaz rezultatov. I2C modul omogoča enostavnejše povezovanje z Arduinom.

4. Perf Board za povezovanje komponent

5.	LED ena modra,

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

![Screenshot 2025-06-17 001430](https://github.com/user-attachments/assets/6c1ac08f-4ea6-417e-8081-bb856de0323b)


4. Uporabljene knjižnice 

 

Za pravilno delovanje kode je treba v Arduino IDE vključiti naslednje knjižnice: 

DHT sensor library – Omogoča komunikacijo z DHT senzorjem. Avtor: Adafruit. 

Adafruit Unified Sensor – Niz knjižnic, ki podpirajo različne senzorje in poenoteno komunikacijo. 

LiquidCrystal_I2C – Omogoča komunikacijo z LCD zaslonom preko I2C vodila. 

Brez teh knjižnic koda ne bo delovala, saj Arduino ne bo prepoznal ukazov za senzor in zaslon.


5.Opis delovanja sistema


Ko je sistem napajan, se na LCD zaslonu prikaže začetno sporočilo "Naprava OFF", ki uporabniku jasno pove, da merilni sistem še ni aktiven. V tem stanju sveti rdeča LED, kar vizualno potrdi, da je naprava izklopljena. Na drugi vrstici LCD-ja utripajoče besedilo "Preklopi stikalo" opozarja uporabnika, da lahko s pritiskom na stikalo napravo aktivira.


Ko uporabnik pritisne stikalo (na digitalnem pinu 13), sistem zazna preklop in preide v aktivno stanje. V tem trenutku:

Modra LED se prižge, kar pomeni, da je sistem aktiven.

Na LCD zaslonu se za 1 sekundo izpiše "Naprava ON".

Nato sistem samodejno začne prikazovati merjene vrednosti temperature in vlage, ki jih zazna senzor DHT22.

Vrednosti se prikazujejo v realnem času, LCD pa se osvežuje vsakih 250 milisekund, medtem ko se meritve s senzorja osvežijo vsakih 2 sekundi, da se prepreči prekomerna obremenitev senzorja.

Če senzor DHT22 ne poda veljavnih vrednosti (zaradi napake, nepravilne povezave ali motenj), sistem na LCD-ju izpiše "Napaka DHT22".

Ob ponovnem pritisku na stikalo se naprava izklopi, vrednosti prenehajo s prikazovanjem in sistem se vrne v začetno stanje.

KALIBRACIJA:

DHT-22 ima že tovarniško narejeno kalibracijo in vlago samostojno preko programa zapiše v odstotkih (%). Temperaturo pa sva nastavila na stopinje celzija (°C)

DHT-22 ima mejo napake +/- 2% RH in +/- 0,5 °C

Temperatura je že določena, in natančnost merjenja najnega izdelka sva testirala z napravo, ki jo ima doma eden od naju. Ta naprava je TFA DUSTMANN.

![image](https://github.com/user-attachments/assets/49e4fa58-6fa5-49ad-afc8-de957803c528)


Zgoraj so vse meritve določene po prostorih, kjer so vgrajeni sistemi merilca vlage TFA DUSTMANN, vidimo, da so vse razlike v tolerancah mejah napake senzorja DHT-22. Da sva izmerila sva v vsak prostor položila najno napravo in počakala, da se umeri in sva zapisala končne rezultate.








