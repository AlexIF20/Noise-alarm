// C++ code
//
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include <TM1637Display.h>

#define DISPLAY_CLK 13
#define DISPLAY_DIO 12
#define RED_LED 11
#define YELLOW_LED 10
#define GREEN_LED 9
#define BUZZER_PIN 6
#define VARIABLE_INPUT_SOURCE A2

TM1637Display display(DISPLAY_CLK, DISPLAY_DIO);
const uint8_t decibelNotation[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,  //d
  SEG_F | SEG_C | SEG_D | SEG_E | SEG_G   //b
};

// Modul sunet / microfon
const int sampleWindow = 50;
unsigned int sample;

long sum = 0 ;
long Sound_signal;
int num_Measure = 128 ;
long level = 0 ; 

void setup()
{
  pinMode(VARIABLE_INPUT_SOURCE, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH);
  
  //display.begin(0x70);

  display.setBrightness(5);
  display.clear();
  display.setSegments(decibelNotation, 2, 2);
  
  Serial.begin(9600);
}

void loop()
{ 
  // Modul sunet / microfon
  for ( int i = 0 ; i <num_Measure; i ++)  
  {
    Sound_signal = analogRead (VARIABLE_INPUT_SOURCE); 
    Serial.println(Sound_signal); 
    sum =sum + Sound_signal;  
  }  
 
  level = sum / num_Measure; // Calculate the average value
  int input = level/5;  
///////////////////////////////////
  
  //input = random(40, 80);
  Serial.println(input);
  // Output buzzer si leduri

  if(input>99)
  {
    display.showNumberDec(99, false, 2, 0);
  }
  else if(input<10)
  {
    display.showNumberDec(input, false, 1, 0);
  }
  else
  {
    display.showNumberDec(input, false, 2, 0);
  }

  if(input >= 75)
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    tone(BUZZER_PIN, 1000, 100);
    delay(300);
    
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    delay(300);

    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    tone(BUZZER_PIN, 1000, 100);
    delay(300);
    
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    //noTone(BUZZER_PIN);
    //delay(500);
  }
  else if(input >= 70 && input < 75)
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    tone(BUZZER_PIN, 1000, 100);
    //delay(300);
  }
  else if (input >= 60 && input < 70)
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    //delay(300);
  }
  else if (input >= 50 && input < 60)
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    //delay(300);
  }
  else if (input < 50)
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    //delay(300);
  }
  delay(100);
  digitalWrite(BUZZER_PIN, HIGH);
  //delay(3000);
  sum = 0;
}
