// reading multiple analog sensor value

const int sensorPin0 = A0;    // input pin for the sensor
const int sensorPin1 = A1;
const int sensorPin2 = A2;
const int sensorPin3 = A3;
int sensorValue0 = 0;  // variable to store the value coming from the sensor
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;

float threshold = 4.6;
int areaFlag = 0;

float rFix = 68000.0;
float vin = 5.0;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin0, INPUT);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
}

void loop() {
  // read the value from the sensor
  sensorValue0 = analogRead(sensorPin0);
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);

  // check and send out active signal
  areaCheck();
  //areaFlag = 0;
  
  // print the reading value with max and min for better visualization
  /*
  Serial.print(0);
  Serial.print("    ");
  Serial.print(5);
  Serial.print("    ");
  Serial.print(voutCal(sensorValue0));
  Serial.print("    ");
  Serial.print(voutCal(sensorValue1));
  Serial.print("    ");
  Serial.print(voutCal(sensorValue2));
  Serial.print("    ");
  Serial.print(voutCal(sensorValue3));
  Serial.println("    ");
  */
  delay(100);
}

void areaCheck()
{
  // area 4
  if (voutCal(sensorValue0)<threshold && voutCal(sensorValue1)<threshold && voutCal(sensorValue2)<threshold && voutCal(sensorValue3)<threshold)
    areaFlag = 4;
  // area 3
  else if (voutCal(sensorValue0)<threshold && voutCal(sensorValue1)<threshold && voutCal(sensorValue2)<threshold)
    areaFlag = 3;
  // area 2
  else if (voutCal(sensorValue0)<threshold && voutCal(sensorValue1)<threshold)
    areaFlag = 2;
  // area 1
  else if (voutCal(sensorValue0)<threshold)
    areaFlag = 1;
  else
    areaFlag = 0;

  Serial.write(areaFlag);
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
