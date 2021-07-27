/*
 * sense resistance and capacitance with 2 analog pin connection 
 * cap sensing source: https://playground.arduino.cc/Code/ADCTouch/
 * res sensing source: https://github.com/zPatch/zPatch.github.io/blob/master/ArduinoCode/fabricSensor/fabricSensor.ino
 */
 // TODO
 // filter res value
 // filter cap value -> refer to zpatch

#include <ADCTouch.h>

typedef struct
{
  int cap0;
  int cap1;  
} capSensing_type;

int ref0, ref1;       //reference values to remove offset
 
void setup()
{
    // No pins to setup, pins can still be used regularly, although it will affect readings
 
    Serial.begin(9600);
 
    ref0 = ADCTouch.read(A0, 500);    //create reference values to
    ref1 = ADCTouch.read(A1, 500);      //account for the capacitance of the pad
}

void loop()
{
    //int capValue = capSensing(A0, A1, 3);
    capSensing_type cap = capSensing(A0, A1, 3);
    int resValue = dualAnalogRead(A0, A1, 3); //sample resistance

    //print to serial port
    printSerial(resValue, cap.cap1, cap.cap0);

    // send over serial
    //sendSerial(resValue, cap.cap1, cap.cap0);
    
    delay(100);
}

capSensing_type capSensing(int pin0, int pin1, int number) 
{
  int capacitance = 0;
  capSensing_type cap;

  //for (int i = 0; i < number; i++) {

    cap.cap0 = ADCTouch.read(A0);   //no second parameter
    cap.cap1 = ADCTouch.read(A1);
    
    cap.cap0 -= ref0;       //remove offset
    cap.cap1 -= ref1;
  
    capacitance = capacitance + cap.cap0 + cap.cap1; // this result in weird values, don't know why
    //Serial.println(capacitance);
  //}

  return cap;
}

int dualAnalogRead(int pin0, int pin1, int number) {
  int res0 = 0;
  int res1 = 0;
  int resistance = 0;

  for (int i = 0; i < number; i++) {
    pinMode(pin0, OUTPUT);
    digitalWrite(pin0, LOW);
    pinMode(pin1, INPUT_PULLUP);
    res1 = analogRead(pin1);

    pinMode(pin1, OUTPUT);
    digitalWrite(pin1, LOW);
    pinMode(pin0, INPUT_PULLUP);
    res0 = analogRead(pin0);

    resistance = resistance + (res0 + res1) / 2;

  }
  return resistance / number;
}

void printSerial(int resValue, int cap1, int cap0)
{
    Serial.print(500); 
    Serial.print("    ");
    Serial.print(0);  
    Serial.print("    ");
    Serial.print(resValue);
    Serial.print("    ");
    Serial.print(cap0);
    Serial.print("    ");
    Serial.print(cap1); 
    Serial.println();
}

void sendSerial(int resValue, int cap1, int cap0)
{
    Serial.write(resValue);
}
