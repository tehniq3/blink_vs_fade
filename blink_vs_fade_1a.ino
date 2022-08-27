/*
 * originsl sketch by Nicu FLORICA (niq_ro)
 * blink (flash) vs. fade leds
 * v.1 - initial, 27.08.2022. Craiova, Romania, Europe
 * v.1.a - added push button to chenge mode (blink or fade)
 */

#define LED1_PIN       10
#define LED2_PIN       11
#define LED0_PIN       9
#define PUSH_PIN       2

byte blink_enabled = 2;   // 
byte led1 = 0;            // 
byte led2 = 0;            //      

unsigned long time_to_blink;
unsigned long time_to_close_gate = millis();  //set intial millis times
unsigned long time_to_fade;  
unsigned long time_to_stop = 200;
unsigned long blink_speed = 700; // [ms] smaller number is faster blinking
unsigned long fade_delay = 2; // [ms] smaller number is faster fade

int brightness = 0;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by

void setup() {
  pinMode(LED1_PIN,   OUTPUT);
  pinMode(LED2_PIN,   OUTPUT);
  pinMode(LED0_PIN,   OUTPUT);

  pinMode(PUSH_PIN,   INPUT);
  digitalWrite(PUSH_PIN, HIGH);  // pull-up the internal resistor  

blink_speed = 2*(255/fade_delay + time_to_stop);
}

void loop() {
  // put your main code here, to run repeatedly:

if (digitalRead(PUSH_PIN) ==LOW) 
{
  blink_enabled = blink_enabled + 1;
  if (blink_enabled > 2) blink_enabled = 1;
  delay(500);
}


if(blink_enabled == 1) 
  {
  blinkLights(); 
  }
if(blink_enabled == 2) 
  { 
  fadeLights(); 
  }
if(blink_enabled == 0)
  noLights();

delay(1);  // small pause

}  // end main loop

void blinkLights() 
{
    if(millis() > time_to_blink) 
    {
      time_to_blink = millis() + blink_speed;
      led1 = !led1;
      led2 = !led1;
    
      digitalWrite(LED1_PIN, led1);
      digitalWrite(LED2_PIN, led2);
    //  digitalWrite(LED0_PIN, (led1+led2)%2); 
      }
}

void noLights() 
{
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      digitalWrite(LED0_PIN, LOW); 
}

void fadeLights() 
{
  analogWrite(LED1_PIN, brightness);
  analogWrite(LED2_PIN, 255-brightness);
  
if(millis() > time_to_fade) 
  {
  time_to_fade = millis() + fade_delay;
  brightness = brightness + fadeAmount; // change the brightness for next time through the loop:

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0) 
  {
    brightness = 0;
    fadeAmount = -fadeAmount;
    time_to_fade = time_to_fade + time_to_stop;
  }
  if (brightness >= 255) 
  {
    brightness = 255;
    fadeAmount = -fadeAmount;
    time_to_fade = time_to_fade + time_to_stop;
  }
  }
}
