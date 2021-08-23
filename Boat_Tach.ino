#include <TimerOne.h>

#include <ArduinoSort.h>

#define pwmPin 5

double average = 0;
unsigned long sum = 0;
const int arrayLength = 20;
int PWM = 0;
float vout = 0;
int count = 0;
double count1 = 0;
int count2 = 0;
double RPM = 0;
int timePassed = 0;
int prevMillis = 0;
int loopTime = 500;
int timePassedDisp = 0;
int loopTimeDisp = 5;
int prevMillisDisp = 0;
unsigned long times[arrayLength];
unsigned long previousTime = 0;
int index = 0;
boolean save = true;
boolean wait = false;
int waitTime = 500;
int pulsedCounter = 0;
boolean first = true;

class LEDDISP
{
  int num;
  int pin;

  public:
    void setNum(int n) //Use to set number to be displayed on the digit
    {
      num = n;
    }
    void setPin(int p) //use to set anode pin for the display
    {
      pin = p;
    }

    void updateDisp() //will command the digit to display the current number in setNum immediately 
    {
      digitalWrite(pin, HIGH);
      switch (num)
      {
        case 0:
        digitalWrite(A5, LOW);
        digitalWrite(A2, LOW);
        digitalWrite(A4, LOW);
        digitalWrite(A1, HIGH);
        digitalWrite(A0, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(10, LOW);
        break;
        
        case 1:
        digitalWrite(A5, HIGH);
        digitalWrite(A2, HIGH);
        digitalWrite(A4, LOW);
        digitalWrite(A1, HIGH);
        digitalWrite(A0, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);
        digitalWrite(10, HIGH);
        break;
        
        case 2:
        digitalWrite(A5, LOW);
        digitalWrite(A2, LOW);
        digitalWrite(A4, HIGH);
        digitalWrite(A1, LOW);
        digitalWrite(A0, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(10, HIGH);
        break;

        case 3:
        digitalWrite(A5, HIGH);
        digitalWrite(A2, LOW);
        digitalWrite(A4, LOW);
        digitalWrite(A1, LOW);
        digitalWrite(A0, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(10, HIGH);
        break;

        case 4:
        digitalWrite(A5, HIGH);
        digitalWrite(A2, HIGH);
        digitalWrite(A4, LOW);
        digitalWrite(A1, LOW);
        digitalWrite(A0, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);
        digitalWrite(10, LOW);
        break;

        case 5:
        digitalWrite(A5, HIGH);
        digitalWrite(A2, LOW);
        digitalWrite(A4, LOW);
        digitalWrite(A1, LOW);
        digitalWrite(A0, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(10, LOW);
        break;

        case 6:
        digitalWrite(A5, LOW);
        digitalWrite(A2, LOW);
        digitalWrite(A4, LOW);
        digitalWrite(A1, LOW);
        digitalWrite(A0, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(10, LOW);
        break;

        case 7:
        digitalWrite(A5, HIGH);
        digitalWrite(A2, HIGH);
        digitalWrite(A4, LOW);
        digitalWrite(A1, HIGH);
        digitalWrite(A0, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(10, HIGH);
        break;

        case 8:
        digitalWrite(A5, LOW);
        digitalWrite(A2, LOW);
        digitalWrite(A4, LOW);
        digitalWrite(A1, LOW);
        digitalWrite(A0, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(10, LOW);
        break;

        case 9:
        digitalWrite(A5, HIGH);
        digitalWrite(A2, LOW);
        digitalWrite(A4, LOW);
        digitalWrite(A1, LOW);
        digitalWrite(A0, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(10, LOW);
        break;
        
      }
    }

    void dispOff()
    {
        digitalWrite(A5, LOW);
        digitalWrite(A2, LOW);
        digitalWrite(A4, LOW);
        digitalWrite(A1, LOW);
        digitalWrite(A0, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(10, LOW);
        digitalWrite(pin, LOW);
    }
    
};

LEDDISP LED1; //oject declaration for two digits of display
LEDDISP LED2;
LEDDISP LED3;
LEDDISP LED4;

class LEDDISPLAY
{
  int digits;
  int num;
  int num1;
  int num2;
  int num3;
  int num4;
  int displaying = 1;
  LEDDISP *Digit1;
  LEDDISP *Digit2;
  LEDDISP *Digit3;
  LEDDISP *Digit4;
  public:
    LEDDISPLAY()
    {
      
    }
    
    void setDigits(LEDDISP *D1, LEDDISP *D2, LEDDISP *D3, LEDDISP *D4)
    {
      Digit1 = D1;
      Digit2 = D2;
      Digit3 = D3;
      Digit4 = D4;
    }

    void DisplayNum(int n)
    {
      num = n;
      num1 = (n / 1U) % 10;
      num2 = (n / 10U) % 10;
      num3 = (n / 100U) % 10;
      num4 = (n / 1000U) % 10;
      Digit1->setNum(num1);
      Digit2->setNum(num2);   
      Digit3->setNum(num3);
      Digit4->setNum(num4);
    }

    void updateDisplay()
    {
      if (displaying == 1)
      {
        Digit1->dispOff();
        Digit3->dispOff();
        Digit4->dispOff();
        Digit2->updateDisp();
        displaying = 2;
      }
      else if (displaying == 2)
      {
        Digit2->dispOff();
        Digit3->dispOff();
        Digit4->dispOff();
        Digit1->updateDisp();
        displaying = 3;
      }
      else if (displaying == 3)
      {
        Digit2->dispOff();
        Digit1->dispOff();
        Digit4->dispOff();
        Digit3->updateDisp();
        displaying = 4;
      }
      else if (displaying == 4)
      {
        Digit2->dispOff();
        Digit3->dispOff();
        Digit1->dispOff();
        Digit4->updateDisp();
        displaying = 1;
      }
      
    }

    void displayOff()
    {
      Digit1->dispOff();
      Digit2->dispOff();
      Digit3->dispOff();
      Digit4->dispOff();
    }
};

LEDDISPLAY LEDDisplay1; //Object delcaration of 2 digit display

void pulseDetected()
{
  if(save)
  {
    if(!first)
    {
      times[index] = micros()-previousTime; 
      //Serial.println(String(index) + " " + String(previousTime) + " " + String(times[index]));    
      index++;
    }
    previousTime = micros();
    first = false;
  }
}

void sendPWM(float rpm)
{
  float pwmVal = 430.6258 + (0.68575 - 430.6258)/(1 + pow((rpm/4567.413), 1.206428));
  Serial.println(String(pwmVal));
  analogWrite(pwmPin, constrain(int(pwmVal), 0, 255));
}

void updateRPM()
{
  sortArray(times, arrayLength);
  for(int i = 0; i < arrayLength; i++)
  {
    Serial.print(String(times[i]) + ", " );
  }
  Serial.println("\n");
  sum = 0;
  for(int j = 0; j < arrayLength-11; j++)
  {
    sum = sum + times[j+10];
  }
  average = sum/(arrayLength-11);
  Serial.println(String(average));

  RPM = (1000000/(average*6))*60;
  Serial.println(String(RPM));
  LEDDisplay1.DisplayNum(abs(RPM));
  sendPWM(RPM);
  Serial.println("RPM " + String(RPM));
}

void timerExp()
{
  //LEDDisplay1.updateDisplay();  
  pulsedCounter++;
}


void setup() {
  // put your setup code here, to run once:
//  pinMode(13, OUTPUT);
//  pinMode(12, OUTPUT);
//  pinMode(A5, OUTPUT);
//  pinMode(A4, OUTPUT);
//  pinMode(2, OUTPUT);
//  pinMode(4, OUTPUT);
//  pinMode(5, OUTPUT);
//  pinMode(7, OUTPUT);
//  pinMode(8, OUTPUT);
//  pinMode(10, OUTPUT);
//  pinMode(A1, OUTPUT);
//  pinMode(A2, OUTPUT);
  
  pinMode(6, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(7), pulseDetected, RISING);

  Timer1.initialize(5000);
  Timer1.attachInterrupt(timerExp);

  LED1.setPin(4);
  LED2.setPin(2);
  LED3.setPin(13);
  LED4.setPin(12);

  LEDDisplay1.setDigits(&LED1, &LED2, &LED3, &LED4);
 }

void loop() {


  //timePassedDisp = millis() - prevMillisDisp;

  if(index>=arrayLength)
  {
    save = false;
    updateRPM();
    index = 0;
    wait = true;
    prevMillis = millis();
    pulsedCounter = 0;
  }

  if(wait)
  {
    timePassed = millis() - prevMillis;
    //Serial.println("waiting");
    //Serial.println(String(millis()));
    if(timePassed >= waitTime)
    {
      save = true;
      wait = false;
      first = true;
    }
  }

  if(pulsedCounter > 1000)
  {
    RPM = 0;
    LEDDisplay1.DisplayNum(RPM);
    analogWrite(pwmPin, 0);
  }

}
