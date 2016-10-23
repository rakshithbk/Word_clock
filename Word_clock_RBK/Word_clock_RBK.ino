/*
 *                                                                         *
 *  W O R D C L O C K   - A clock that tells the time using words.         *
 *                                                                         *
 * Hardware:  Arduino Uno with a set of LED Strips under a word stencil.   *
 *                                                                         *
 *   Original Copyright (C) 2009  Doug Jackson (doug@doughq.com)           *
 *                                                                         *
 *                  ╦═╗╔╗ ╦╔═                                              *
 *  Modified by --  ╠╦╝╠╩╗╠╩╗   2014                                       *
 *                  ╩╚═╚═╝╩ ╩                                              *                          
 *                                                                         *
 ***************************************************************************
Detailed connection and DIY is porvied at -- 
                http://www.instructables.com/id/Simple-Word-clock-arduino/

RTClib information---
            SDA pin -----> A4 / D18
            SCL pin -----> A5 / D19
*/


#include <string.h>
#include <Wire.h>  
#include"RTClib.h"



                    // Display output pin assignments
#define MINUTES	Display1=Display1   | B00000001
#define MTEN 	Display1=Display1   | B00000010  
#define HALF	Display1=Display1   | B00000100
#define PAST	Display1=Display1   | B00001000
#define THREE	Display1=Display1   | B00010000
#define ITIS	Display1=Display1   | B00100000
#define TWENTY	Display1=Display1   | B01000000
#define TO	    Display1=Display1   | B10000000

#define TWO	    Display2=Display2   | B00000001
#define SIX	    Display2=Display2   | B00000010 
#define TWELVE	Display2=Display2   | B00000100
#define HFIVE	Display2=Display2   | B00001000
#define SEVEN	Display2=Display2   | B00010000
#define OCLOCK	Display2=Display2   | B00100000
#define ONE	    Display2=Display2   | B01000000
#define QUARTER	Display2=Display2   | B10000000


#define EIGHT	Display3=Display3   | B00000001
#define MFIVE	Display3=Display3   | B00000010 
#define ARDUINO	Display3=Display3   | B00000100
#define ELEVEN	Display3=Display3   | B00001000
#define HTEN	Display3=Display3   | B00010000
#define NINE	Display3=Display3   | B00100000
#define FOUR	Display3=Display3   | B01000000
#define RBK	    Display3=Display3   | B10000000






int hour=0, minute=0, second=0;
static unsigned long msTick =0;  // the number of Millisecond Ticks since we last 
// incremented the second counter
int  selftestmode;          // 1 = in self test - flash display
char Display1=0, Display2=0, Display3=0;
                        
// hardware constants
int LEDClockPin=8;  // Arduino Pin#8 - Shift register 74HC595 Pin 11 clock
int LEDDataPin=9;   // Arduino Pin#9  - Shift register 74HC595 pin 14 Data
int LEDLatchPin=10; // Arduino Pin#10  - Shift register 74HC595 pin 12 Latch



// RTC DEFINE-
RTC_DS1307 RTC ;





void setup()
{
  // initialise the hardware	
  // initialize the appropriate pins as outputs:
  pinMode(LEDClockPin, OUTPUT); 
  pinMode(LEDDataPin, OUTPUT); 
  pinMode(LEDLatchPin, OUTPUT); 
  
  



  
  

  Serial.begin(9600);   // setup the serial port to 9600 baud
  Wire.begin();
  RTC.begin();
  

  // test whether the DS1307 is there
  Serial.print("Verifying DS1307 ");
  
  if ( RTC.isrunning()) {
    Serial.println("RTC is running.....");
     DateTime now = RTC.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  }
      
  DateTime now = RTC.now();
  
  msTick=millis();      // Initialise the msTick counter

  selftest();  // validate the hardware for the user

  selftestmode=0;

  if ( RTC.isrunning() ) {
    // Get the current time and date from the RTC chip 
    
    second=now.second();     
    minute=now.minute();
    hour=now.hour(); 
  }

  displaytime();        // display the current time
}



  
  
  void WriteLEDs(){
    // Now we write the actual values to the hardware
    shiftOut(LEDDataPin, LEDClockPin, MSBFIRST, Display3);
    shiftOut(LEDDataPin, LEDClockPin, MSBFIRST, Display2);
    shiftOut(LEDDataPin, LEDClockPin, MSBFIRST, Display1);
    digitalWrite(LEDLatchPin,HIGH);
    //delay(2);
    digitalWrite(LEDLatchPin,LOW);    
    
  }
  



void ledsoff(void) {
  Display1=0;
  Display2=0;
  Display3=0;
 
}



void selftest(void){
  // start by clearing the display to a known state
  ledsoff(); 
  ITIS; 
  WriteLEDs();  
  delay(500); 
  ledsoff(); 
  MTEN;
  WriteLEDs();  
  delay(500); 
  ledsoff(); 
  HALF;
  WriteLEDs();  
  delay(500); 
  ledsoff(); 
  TWENTY;  
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  QUARTER; 
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  MFIVE;   
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  MINUTES; 
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  PAST;    
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  TO;      
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  ONE;     
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  TWO;     
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  THREE;   
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  FOUR;    
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  HFIVE;   
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  SIX;     
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  SEVEN;   
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  EIGHT;   
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  NINE;    
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  HTEN;    
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  ELEVEN;  
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  TWELVE;  
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  OCLOCK;  
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  RBK;    
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  ARDUINO; 
  WriteLEDs();
  delay(500); 
  ledsoff(); 
  

  for(int i=0; i<5; i++)
  {
    Display1=255; 
    Display2=255; 
    Display3=255;
    WriteLEDs();
    delay(500);
    ledsoff(); 
    WriteLEDs();
    delay(500);
  }

}


void displaytime(void){

  // start by clearing the display to a known state
  ledsoff();

  // Now, turn on the "It is" leds
  ITIS;
  Serial.print("It is ");

  // now we display the appropriate minute counter
  if ((minute>4) && (minute<10)) { 
    MFIVE; 
    MINUTES; 
    Serial.print("Five Minutes ");
  } 
  if ((minute>9) && (minute<15)) { 
    MTEN; 
    MINUTES; 
    Serial.print("Ten Minutes ");
  }
  if ((minute>14) && (minute<20)) {
    QUARTER; 
    Serial.print("Quarter ");
  }
  if ((minute>19) && (minute<25)) { 
    TWENTY; 
    MINUTES; 
    Serial.print("Twenty Minutes ");
  }
  if ((minute>24) && (minute<30)) { 
    TWENTY; 
    MFIVE; 
    MINUTES;
    Serial.print("Twenty Five Minutes ");
  }  
  if ((minute>29) && (minute<35)) {
    HALF;
    Serial.print("Half ");
  }
  if ((minute>34) && (minute<40)) { 
    TWENTY; 
    MFIVE; 
    MINUTES;
    Serial.print("Twenty Five Minutes ");
  }  
  if ((minute>39) && (minute<45)) { 
    TWENTY; 
    MINUTES; 
    Serial.print("Twenty Minutes ");
  }
  if ((minute>44) && (minute<50)) {
    QUARTER; 
    Serial.print("Quarter ");
  }
  if ((minute>49) && (minute<55)) { 
    MTEN; 
    MINUTES; 
    Serial.print("Ten Minutes ");
  } 
  if (minute>54) { 
    MFIVE; 
    MINUTES; 
    Serial.print("Five Minutes ");
  }



  if ((minute <5))
  {
    switch (hour) {
    case 1:
    case 13: 
      ONE; 
      Serial.print("One ");
      break;
    case 2:
    case 14: 
      TWO; 
      Serial.print("Two ");
      break;
    case 3: 
    case 15:
      THREE; 
      Serial.print("Three ");
      break;
    case 4: 
    case 16:
      FOUR; 
      Serial.print("Four ");
      break;
    case 5: 
    case 17:
      HFIVE; 
      Serial.print("Five ");
      break;
    case 6: 
    case 18:
      SIX; 
      Serial.print("Six ");
      break;
    case 7: 
    case 19:
      SEVEN; 
      Serial.print("Seven ");
      break;
    case 8: 
    case 20:
      EIGHT; 
      Serial.print("Eight ");
      break;
    case 9: 
    case 21:
      NINE; 
      Serial.print("Nine ");
      break;
    case 10:
    case 22: 
      HTEN; 
      Serial.print("Ten ");
      break;
    case 11:
    case 23: 
      ELEVEN; 
      Serial.print("Eleven ");
      break;
    case 0:
    case 12: 
      TWELVE; 
      Serial.print("Twelve ");
      break;
    }
    OCLOCK;
    Serial.println("O'Clock");
  }
  else
    if ((minute < 35) && (minute >4))
    {
      PAST;
      Serial.print("Past ");
      switch (hour) {
      case 1:
      case 13: 
        ONE; 
        Serial.println("One ");
        break;
      case 2: 
      case 14:
        TWO; 
        Serial.println("Two ");
        break;
      case 3: 
      case 15:
        THREE; 
        Serial.println("Three ");
        break;
      case 4: 
      case 16:
        FOUR; 
        Serial.println("Four ");
        break;
      case 5: 
      case 17:
        HFIVE; 
        Serial.println("Five ");
        break;
      case 6: 
      case 18:
        SIX; 
        Serial.println("Six ");
        break;
      case 7: 
      case 19:
        SEVEN; 
        Serial.println("Seven ");
        break;
      case 8: 
      case 20:
        EIGHT; 
        Serial.println("Eight ");
        break;
      case 9: 
      case 21:
        NINE; 
        Serial.println("Nine ");
        break;
      case 10:
      case 22: 
        HTEN; 
        Serial.println("Ten ");
        break;
      case 11:
      case 23: 
        ELEVEN; 
        Serial.println("Eleven ");
        break;
      case 0:
      case 12: 
        TWELVE; 
        Serial.println("Twelve ");
        break;
      }
    }
    else
    {
      // if we are greater than 34 minutes past the hour then display
      // the next hour, as we will be displaying a 'to' sign
      TO;
      Serial.print("To ");
      switch (hour) {
      case 1: 
      case 13:
        TWO; 
        Serial.println("Two ");
        break;
      case 14:
      case 2: 
        THREE; 
        Serial.println("Three ");
        break;
      case 15:
      case 3: 
        FOUR; 
        Serial.println("Four ");
        break;
      case 4: 
      case 16:
        HFIVE; 
        Serial.println("Five ");
        break;
      case 5: 
      case 17:
        SIX; 
        Serial.println("Six ");
        break;
      case 6: 
      case 18:
        SEVEN; 
        Serial.println("Seven ");
        break;
      case 7: 
      case 19:
        EIGHT; 
        Serial.println("Eight ");
        break;
      case 8: 
      case 20:
        NINE; 
        Serial.println("Nine ");
        break;
      case 9: 
      case 21:
        HTEN; 
        Serial.println("Ten ");
        break;
      case 10: 
      case 22:
        ELEVEN; 
        Serial.println("Eleven ");
        break;
      case 11: 
      case 23:
        TWELVE; 
        Serial.println("Twelve ");
        break;
      case 0:
      case 12: 
        ONE; 
        Serial.println("One ");
        break;
      }
    }

   
}



void loop()
{
  DateTime now = RTC.now();
  
    second=now.second();     
    minute=now.minute();
    hour=now.hour();

  //Serial.println("Loop Started");
  
  
  // Flash the onboard Pin13 Led every 5 sec so we know something is hapening!
  if ( millis() - msTick >5000) {
    msTick=millis();
    
    
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);  
    delay(50);
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);  

    Serial.print(second);
    Serial.print("..");
  }
  
  if (second==59) // Update the display every 1 minute...
  {
    displaytime();
    WriteLEDs();
  }
  
  
}		  




