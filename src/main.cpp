
#include <Arduino.h>
#include "Adafruit_VL53L0X.h"
#include "LightSource.h"
#include "func.h"
#include "TaskScheduler.h"
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

  pinMode(FOT_CHODBA, INPUT);

  pinMode(LED_CHODBA_ORI_WC, OUTPUT);
  digitalWrite(LED_CHODBA_ORI_WC, LOW);
}


void loop()
{
  LightSource chodba_wc;
  LightSource chodba_str_mat;
  LightSource koupelka;
  LightSource koupelka_police_bila;
  
  // deklarace promenych
  chodba_wc.setPinTrig(PIR_CHODBA_WC);
  
  // hlavni smycka
  while (true)
  {
    delay(10);
    chodba_str_mat.update();
    chodba_wc.update();

    //  nacti data z pir senzorů
    chodba_wc.sense();

    /*koupelka.enable(je_tma_koupelka);
    koupelka_police_bila.enable(je_tma_koupelka);
    chodba_str_mat.enable(je_tma_chodba);
    chodba_wc.enable(je_tma_chodba);*/
  }
}
