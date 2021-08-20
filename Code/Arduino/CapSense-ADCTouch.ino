 /*
 * sense capacitance with 2 analog pin connection 
 * cap sensing source: https://playground.arduino.cc/Code/ADCTouch/
  */

#include <ADCTouch.h>

typedef struct
{
  int cap0;
  int cap1;  
} capSensing_type;

int ref0, ref1;       //reference values to remove offset
int avg = 0;
int samplesize = 4;
float cap;
 
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
    filter(cap.cap1, cap.cap0);

    //print to serial port
    printSerial(cap.cap1, cap.cap0);

    // send over serial
    //sendSerial(cap.cap1, cap.cap0);
    
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


void printSerial(int cap1, int cap0)
{
    Serial.print(500); 
    Serial.print("    ");
    Serial.print(0);
    Serial.print("    ");
    Serial.print(cap);
    Serial.print("    ");
    //Serial.print(cap0);
    //Serial.print("    ");
    //Serial.print(cap1); 
    Serial.println();
}

void sendSerial(int cap1, int cap0)
{
    Serial.write(cap1);
}

void filter(int cap1, int cap0)
{
  cap = cap1 + cap0;
  // filter   
  avg = (avg*(samplesize-1) + cap)/samplesize;
  cap = avg;
}
