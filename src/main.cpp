
#include <Arduino.h>
#include "LightSource.h"
#include "func.h"
void setup()
{
  // test git 2
  //  put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(14, INPUT); // fotodioda chodba
  pinMode(31, INPUT); // chodba mates
  pinMode(30, INPUT); // chodba wc
  pinMode(22, INPUT); // kuchyn
  pinMode(32, INPUT); // obývák
  pinMode(33, INPUT); // koupelna
                      //  put your setup code here, to run once:
  pinMode(4, OUTPUT); // led světlo chodba orientační WC
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT); // led světlo kooupelna orientační vana +WC
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT); // led světlo koupelna orientační umyvadlo +koše
  digitalWrite(6, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW); // led světlo zrcadlo koupelna
  digitalWrite(8, LOW); // led svetlo police zluta
  pinMode(9, OUTPUT);   // led svetlo police bila
  digitalWrite(9, LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(11, OUTPUT); // led světlo orientační chodba Matěj
  digitalWrite(11, LOW);
  // put your setup code here, to run once:

  noInterrupts(); // disable all interrupts
                  // set timer4 interrupt at 1Hz
  TCCR4A = 0;     // set entire TCCR1A register to 0
  TCCR4B = 0;     // same for TCCR1B
  TCNT4 = 0;      // initialize counter value to 0
  // set compare match register for 1hz increments
  OCR4A = 15624 / 72; // = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR4B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR4B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK4 |= (1 << OCIE4A);
  interrupts(); // enable all interrupts
}

LightSource chodba;
LightSource koupelka;
LightSource koupelka_police_bila;

// main interrupt code
ISR(TIMER4_COMPA_vect) // timer compare interrupt service routine
{
  chodba.update();
  koupelka.update();
  koupelka_police_bila.update();
}

void loop()
{
  // deklarace promenych
  chodba.setPinLed(4, 11);
  chodba.setPinTrig(31);
  koupelka.setPinLed(5, 6, 8);
  koupelka.setPinTrig(33);
  koupelka_police_bila.setPinLed(9);
  koupelka_police_bila.setBrightnessMax(50);

  // hlavni smycka
  while (true)
  {
    delay(50);

    // nacti data z pir senzorů
    chodba.sense();
    koupelka.sense();
    koupelka_police_bila.sense();

    // jestli je svetlo na fotosenzoru => true
    bool je_svetlo_koupelka = analogRead(15) > 20;
    bool je_svetlo_chodba = analogRead(15) > 20;

    // vypni/zapni svetlo
    koupelka.enable(je_svetlo_koupelka);
    chodba.enable(je_svetlo_chodba);
    koupelka_police_bila.enable(je_svetlo_koupelka);
  }
}