
#include <Arduino.h>
#include "Adafruit_VL53L0X.h"
#include "LightSource.h"
#include "func.h"
#include "TaskScheduler.h"

const unsigned char PIR_CHODBA_WC = 32;
const unsigned char PIR_CHODBA_MATES = 33;
const unsigned char PIR_KUCHYN = 35;
const unsigned char PIR_KOUPELNA_VST = 36;
const unsigned char PIR_KOUPELNA_VAN = 31;
const unsigned char PIR_CHODBA_STR = 34;

static const uint8_t FOT_CHODBA = (uint8_t)68U;   // analog 14
static const uint8_t FOT_KOUPELNA = (uint8_t)69U; // analog 15

const unsigned char LED_CHODBA_ORI_WC = 4;
const unsigned char LED_CHODBA_ORI_MATES = 11;
const unsigned char LED_KOUPELNA_ORI_WC = 5;
const unsigned char LED_KOUPELNA_ORI_UMYVADLO = 12;
const unsigned char LED_KOUPELNA_ZRCADLO = 7;
const unsigned char LED_KOUPELNA_POLICE_ZL = 6;
const unsigned char LED_KOUPELNA_POLICE_BI = 10;
// A ok 51 50   43 41 39 36 34 38 40 44  42 46 48ok
// B 32 33 bad
// C 33 42  bad
// const unsigned char RELE_ZACHOD = 35;

// Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  // muxSwitch(4);

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
  pinMode(PIR_KOUPELNA_VST, INPUT);
  pinMode(PIR_KUCHYN, INPUT);
  pinMode(PIR_KOUPELNA_VAN, INPUT);

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

  // pinMode(RELE_ZACHOD, OUTPUT);
  // digitalWrite(RELE_ZACHOD, HIGH);
  /*
  noInterrupts(); // disable all interrupts
                  // set timer4 interrupt at 1Hz
  TCCR4A = 0;     // set entire TCCR1A register to 0
  TCCR4B = 0;     // same for TCCR1B
  TCNT4 = 0;      // initialize counter value to 0
  // set compare match register for 1hz increments
  OCR4A = 15624 / 36; // = (16*10^6) / (1*1024) - 1 (must be <65536) //72
  // turn on CTC mode
  TCCR4B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR4B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK4 |= (1 << OCIE4A);
  interrupts(); // enable all interrupts
  */
}


// main interrupt code
ISR(TIMER4_COMPA_vect) // timer compare interrupt service routine
{
  /*chodba_str_mat.update();
  chodba_wc.update();
  koupelka.update();
  koupelka_police_bila.update();*/
}

void loop()
{
  LightSource chodba_wc;
  LightSource chodba_str_mat;
  LightSource koupelka;
  LightSource koupelka_police_bila;
  // deklarace promenych
  chodba_str_mat.setPinLed(LED_CHODBA_ORI_MATES);
  chodba_str_mat.setPinTrig(PIR_CHODBA_MATES, PIR_CHODBA_STR);
  chodba_wc.setPinLed(LED_CHODBA_ORI_WC);
  chodba_wc.setPinTrig(PIR_CHODBA_WC);
  koupelka.setPinLed(LED_KOUPELNA_ORI_UMYVADLO, LED_KOUPELNA_ORI_WC, LED_KOUPELNA_POLICE_ZL); // zahrnuje i polici - zluta
  koupelka.setPinTrig(PIR_KOUPELNA_VST, PIR_KOUPELNA_VAN);
  koupelka_police_bila.setPinLed(koupelka_police_bila);
  koupelka_police_bila.setPinTrig(PIR_KOUPELNA_VAN, PIR_KOUPELNA_VST);
  koupelka_police_bila.setBrightnessMax(80);
  int c = 0;
  bool je_tma_koupelka = true;
  bool je_tma_chodba = true;
  // hlavni smycka
  while (true)
  {
    delay(10);
    chodba_str_mat.update();
    chodba_wc.update();
    koupelka.update();
    koupelka_police_bila.update();
    // chodba_str_mat.debug();
    //  nacti data z pir senzorů
    koupelka_police_bila.sense();
    chodba_wc.sense();
    chodba_str_mat.sense();
    koupelka.sense();

    // jestli je svetlo na fotosenzoru => true

    // je_tma_koupelka = analogRead(FOT_KOUPELNA) < 35;

    // je_tma_chodba = analogRead(FOT_CHODBA) < 2;

    // vypni/zapni svetlo
    /*koupelka.enable(je_tma_koupelka);
    koupelka_police_bila.enable(je_tma_koupelka);
    chodba_str_mat.enable(je_tma_chodba);
    chodba_wc.enable(je_tma_chodba);*/
  }
}