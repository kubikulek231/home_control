#include <Arduino.h>
#include "LightSource.h"
void setup()
{
  //test git 2
  // put your setup code here, to run once:
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
  digitalWrite(8, LOW);
  pinMode(9, OUTPUT);
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

// array of arrays of bytes with led states
// (pin_number, state, brightness, duration)
// state: 0 - static, 1 - rising, 2 - falling
int light_state_list[8][5] = {{4, 0, 0, 0, 0}, {5, 0, 0, 0, 0}, {6, 0, 0, 0, 0}, {7, 0, 0, 0, 0}, {8, 0, 0, 0, 0}, {9, 0, 0, 0, 0}, {10, 0, 0, 0, 0}, {11, 0, 0, 0, 0}};

// attach light to a given pir sensor
void attach_pir(int pir_pin, int array_element)
{
  if (digitalRead(pir_pin) == 1)
  {
    light_state_list[array_element][1] = 1;
    light_state_list[array_element][3] = 0;
    if (light_state_list[array_element][4] < 40)
    {
      light_state_list[array_element][4]++;
    }
  }
}

// print the array (in case of debugging)
void print_array()
{
  for (int i = 0; i <= sizeof(light_state_list) / sizeof(light_state_list[0]) - 1; i++)
  {
    for (int k = 0; k <= 4; k++)
    {
      Serial.print(light_state_list[i][k]);
      Serial.print(",");
      if (k == 4)
      {
        Serial.println(" ");
      }
    }
  }
}

// main interrupt code
ISR(TIMER4_COMPA_vect) // timer compare interrupt service routine
{
  // cycles through all the items in the light_state_list

  for (int i = 0; i <= sizeof(light_state_list) / sizeof(light_state_list[0]) - 1; i++)
  {

    // if rising add +1 brightness
    if (light_state_list[i][1] == 1)
    {
      // if at full brightness change from rising to static
      if (light_state_list[i][2] == 255)
      {
        light_state_list[i][1] = 0;
      }
      else
      {
        light_state_list[i][2]++;
      }
      analogWrite(light_state_list[i][0], light_state_list[i][2]);
    }

    // if falling add -1 brightness
    if (light_state_list[i][1] == 2)
    {
      // if at lowest brightness change from falling to static
      if (light_state_list[i][2] == 0)
      {
        light_state_list[i][1] = 0;
        light_state_list[i][4] = 0;
      }
      else
      {
        light_state_list[i][2]--;
      }
      analogWrite(light_state_list[i][0], light_state_list[i][2]);
    }

    // if at full brightness and static
    if (light_state_list[i][2] == 255 and light_state_list[i][1] == 0)
    {
      if (light_state_list[i][3] == 1500 + light_state_list[i][4] * 20)
      {
        light_state_list[i][3] = 0;
        light_state_list[i][1] = 2;
      }
      else
      {
        light_state_list[i][3]++;
      }
    }
  }
}

void loop()
{
  LightSource led1;
  unsigned char test[] = {1, 5};
  unsigned char test2[] = {9};
  led1.setPinTrig(1);
  Serial.println(led1.getPinTrig()[1]);
  Serial.println(led1.getPinTrig()[0]);
  led1.setPinTrig(test2);
  Serial.println(led1.getPinTrig()[0]);
  delay(10000);
}