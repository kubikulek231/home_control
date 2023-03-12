
#include <Arduino.h>
#include "Adafruit_VL53L0X.h"
#include "LightSource.h"
#include "func.h"
#include "TaskScheduler.h"


const unsigned char PIR_CHODBA_WC = 31;
const unsigned char PIR_CHODBA_MATES = 30;
const unsigned char PIR_OBYVAK = 32;
const unsigned char PIR_KUCHYN = 33;
const unsigned char PIR_KOUPELNA = 8;

const unsigned char FOT_CHODBA = 14;
const unsigned char FOT_KOUPELNA = 15;

const unsigned char LED_CHODBA_ORI_WC = 4;
const unsigned char LED_CHODBA_ORI_MATES = 11;
const unsigned char LED_KOUPELNA_ORI_WC = 5;
const unsigned char LED_KOUPELNA_ORI_UMYVADLO = 12;
const unsigned char LED_KOUPELNA_ZRCADLO = 7;
const unsigned char LED_KOUPELNA_POLICE_BI = 9;
const unsigned char LED_KOUPELNA_POLICE_ZL = 10;

const unsigned char RELE_ZACHOD = 35;

//Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  //muxSwitch(4);

  /*delay(3000);
  Serial.println("VL53L0X booting...");
  if (!lox.begin())
  {
    Serial.println(("VL53L0X FAILED"));
  }
  else
  {
    Serial.println(("VL53L0X OK"));
  }
  lox.startRangeContinuous();
  */
  pinMode(PIR_CHODBA_WC, INPUT);
  pinMode(PIR_CHODBA_MATES, INPUT);
  pinMode(PIR_OBYVAK, INPUT);
  pinMode(PIR_KUCHYN, INPUT);
  pinMode(PIR_KOUPELNA, INPUT);

  pinMode(FOT_CHODBA, INPUT);
  pinMode(FOT_KOUPELNA, INPUT);

  pinMode(LED_CHODBA_ORI_WC, OUTPUT);
  digitalWrite(LED_CHODBA_ORI_WC, LOW);
  pinMode(LED_CHODBA_ORI_MATES, OUTPUT);
  digitalWrite(LED_CHODBA_ORI_MATES, LOW);
  pinMode(LED_KOUPELNA_ORI_WC, OUTPUT);
  digitalWrite(LED_KOUPELNA_ORI_WC, LOW);
  pinMode(LED_KOUPELNA_ORI_UMYVADLO, OUTPUT);
  digitalWrite(LED_KOUPELNA_ORI_UMYVADLO, LOW);
  pinMode(LED_KOUPELNA_ZRCADLO, OUTPUT);
  digitalWrite(LED_KOUPELNA_ZRCADLO, LOW);
  pinMode(LED_KOUPELNA_POLICE_BI, OUTPUT);
  digitalWrite(LED_KOUPELNA_POLICE_BI, LOW);
  pinMode(LED_KOUPELNA_POLICE_ZL, OUTPUT);
  digitalWrite(LED_KOUPELNA_POLICE_ZL, LOW);

  pinMode(RELE_ZACHOD, OUTPUT);
  digitalWrite(RELE_ZACHOD, HIGH);

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
LightSource koupelka_police_zluta;

TaskScheduler zachod_odsavani;

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
  chodba.setPinLed(LED_CHODBA_ORI_MATES, LED_CHODBA_ORI_WC);
  chodba.setPinTrig(PIR_CHODBA_MATES, PIR_CHODBA_WC);
  koupelka.setPinLed(LED_KOUPELNA_ORI_UMYVADLO, LED_KOUPELNA_ORI_WC, LED_KOUPELNA_POLICE_BI, LED_KOUPELNA_POLICE_ZL); // zahrnuje i polici - zluta
  koupelka.setPinTrig(PIR_KOUPELNA);
  koupelka_police_bila.setPinLed(PIR_KOUPELNA);
  koupelka_police_bila.setBrightnessMax(100);
  zachod_odsavani.setTresHoldMax(100);
  int c = 0;
  // hlavni smycka
  while (true)
  {

    delay(50);
    // nacti data z pir senzorů
    chodba.sense();
    koupelka.sense();
    koupelka_police_bila.sense();

    // jestli je svetlo na fotosenzoru => true
    bool je_tma_koupelka = analogRead(FOT_KOUPELNA) < 30;
    bool je_tma_chodba = analogRead(FOT_CHODBA) < 30;
    je_tma_chodba = true;
    je_tma_koupelka = true;

    // vypni/zapni svetlo
    koupelka.enable(je_tma_koupelka);
    chodba.enable(je_tma_chodba);
    koupelka_police_bila.enable(je_tma_koupelka);

    /*if (zachod_odsavani.trigger(lox.readRange() < 600))
    {
      digitalWrite(RELE_ZACHOD, 0);
    }
    else
    {
      digitalWrite(RELE_ZACHOD, 1);
    }*/
    if (c == 10)
    {
      chodba.debug();
      Serial.println(digitalRead(PIR_CHODBA_MATES));
      Serial.println(digitalRead(PIR_CHODBA_WC)); 
      Serial.println(digitalRead(PIR_KOUPELNA));
      Serial.println(digitalRead(FOT_CHODBA));
      c = 0;
    }
    c++;
  }
}