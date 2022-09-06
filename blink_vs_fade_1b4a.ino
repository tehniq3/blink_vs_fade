/*
 * original sketch by Nicu FLORICA (niq_ro)
 * blink (flash) vs. fade leds
 * v.1 - initial, 27.08.2022. Craiova, Romania, Europe
 * v.1.a - added push button to chenge mode (blink or fade)
 * v.1.a.1 -changed for ATtiny88 boards
 * v.1.a.2 - same time for fade and flash (corrected formula)
 * v.1.a.2.a1 - check the flash/blink as number
 * v.1.b.4 - clean the sketch
 */

#define LED1_PIN    9  // fade led 1
#define LED2_PIN   10  // fade led 2
#define LED3_PIN   11  // flash led 1
#define LED4_PIN   12  // flash led 2

byte led1 = 0;    // state for flas led

unsigned long time_to_fade;  
unsigned long time_to_stop = 100;
unsigned long fade_delay = 20; // [ms] smaller number is faster fade

int brightness = 0;    // how bright the LED is
int fade_step = 5;    // how many points to fade the LED by

int lent = 0;
int clipire = 0;
int lent0 = -1;
int clipire0 = -1;


void setup() {
  pinMode(LED1_PIN,   OUTPUT);
  pinMode(LED2_PIN,   OUTPUT);
  pinMode(LED3_PIN,   OUTPUT);
  pinMode(LED4_PIN,   OUTPUT);

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW); 
  digitalWrite(LED4_PIN, LOW); 
}

void loop() {

  analogWrite(LED1_PIN, brightness);
  analogWrite(LED2_PIN, 255-brightness);
  
if(millis() > time_to_fade) 
  {
  time_to_fade = millis() + fade_delay;
  brightness = brightness + fade_step; // change the brightness for next time through the loop:

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0) 
  {
    brightness = 0;
    fade_step = -fade_step;
    time_to_fade = time_to_fade + time_to_stop;
    lent++; 
      led1 = !led1;
      digitalWrite(LED3_PIN, led1);
      digitalWrite(LED4_PIN, !led1);
      clipire++;
  }
  if (brightness >= 255) 
  {
    brightness = 255;
    fade_step = -fade_step;
    time_to_fade = time_to_fade + time_to_stop;
  lent++; 
    led1 = !led1;
      digitalWrite(LED3_PIN, led1);
      digitalWrite(LED4_PIN, !led1);
      clipire++;
  }
  }  
  
}  // end main loop
