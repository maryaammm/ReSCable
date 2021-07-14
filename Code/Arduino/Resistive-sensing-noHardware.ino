/*
 * simple resistive sensing
 * by analog pin reconfiguration
 * no hardware setup
 */

int avg = 0;
int resValue = 0;
int samplesize = 4;
float rFix = 10000.0;
float vin = 5.0;

void setup()
{
    // No pins to setup, pins can still be used regularly, although it will affect readings
    Serial.begin(9600);
 }

void loop()
{
    resValue = dualAnalogRead(A0, A1, 3); //sample resistance

    // filter   
    avg = (avg*(samplesize-1) + resValue)/samplesize;
    resValue = avg;
    
    //print to serial port
    printTo();

    // send to serial port
    //sendTo();
     
    delay(100);
}

int dualAnalogRead(int pin0, int pin1, int number) 
{
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

void sendTo() {
    Serial.write(resValue);
  }

void printTo() {
    Serial.print(5); 
    Serial.print("    ");
    Serial.print(0); 
    //Serial.print("    ");
    //Serial.print(resValue);
    Serial.print("    ");
    Serial.print(voutCal(resValue));
    Serial.print("    ");
    //Serial.print(resCalculator(resValue));
    Serial.println();
  }

// Vout calculator
float voutCal(float sensorVal)
{
  return sensorVal * (vin/1023.0);
}

// resistor calculator
float resCalculator(float sensorVal)
{
  float vout = voutCal(sensorVal);
  return rFix * (1/( vin/vout - 1));
}
