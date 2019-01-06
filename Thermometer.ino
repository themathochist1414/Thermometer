// Global Variables
const int sensorPin = A0;

const int red = 8;                  // red LED on pin 8
const int greatestPinNumber = 8;

void setup() {
  // Open Serial port
  Serial.begin(9600);

  TurnOffPins(greatestPinNumber);
  
  BlinkLED(red);
  Serial.println("Arduino Starting Up...");
  
}
void loop() {
  
  int sensorVal = analogRead(sensorPin);
  
  // convert the ADC reading to voltage
  float voltage = ( sensorVal / 1024.0 ) * 5.0;
  
  // convert the voltage to temperature in degrees
  float temperature = (voltage - 0.5)*100;
  //Serial.println(temperature);
  String message = "@Sensor Value:  " + String(sensorVal) + ", Volts:  " + String(voltage) + ", degrees C: " + String(temperature);
  Serial.println(message);

  DisplayTempInBinary(temperature);
  delay(500); 
}

void DisplayTempInBinary(float temperature){
  int rndTemp = round(temperature);
  String rndTempStr = (String)rndTemp;
  String binaryRep = "";
  
  // For Debugging
  //Serial.println((String)temperature + " " + (String)rndTemp);

  for (int n = greatestPinNumber - 2; n >=0; n--){
    int pinNumber = greatestPinNumber - n;
    int twoToTheN = exponentiateIntegers(2, n);
    int remainder = rndTemp - twoToTheN;

    /* // For Debugging
    String nStr = (String)(n);
    String pinNumberStr = (String)pinNumber;
    String twoToTheNStr = (String)twoToTheN;
    String remainderStr = (String)remainder;
    */
    
    if ( remainder >=0 ){
      rndTemp = rndTemp - twoToTheN;
      digitalWrite(pinNumber, HIGH);
      /* // For Debugging
      rndTempStr = rndTemp;
      Serial.println(rndTempStr + " - " + twoToTheNStr + " = " + remainderStr);
      binaryRep = binaryRep + "1";
      */
    } else{
      digitalWrite(pinNumber, LOW);
      /* // For Debugging
      Serial.println(rndTempStr + " - " + twoToTheNStr + " = " + remainderStr);
      binaryRep = binaryRep + "0";
      */
    }
    // For Debugging
    //Serial.println(nStr + " " + pinNumberStr);
  }
  // For Debugging
  //Serial.println(rndTempStr + " " + binaryRep);
}

void BlinkLED(int pinNum){
  digitalWrite(pinNum, HIGH);
  delay(500);
  digitalWrite(pinNum, LOW);
  delay(500);
}

void TurnOffPins(int greatestPinNumber){
  for (int pinNumber = 2; pinNumber < greatestPinNumber; pinNumber++){
      pinMode(pinNumber, OUTPUT);
      digitalWrite(pinNumber, LOW);
    }
}

int exponentiateIntegers(int x, int y){
  int result = 1;
  for (int n = 1; n <= y; n++){
    result = result*x;
  }
  return result;
}
