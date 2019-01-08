// Global Variables
const int sensorPin = A0;         // Pin number for input from thermistor

const int leastPinNumber = 2;     // Lowest pin number used for 2^5 place value
const int greatestPinNumber = 7;  // Greatest pin number used for 2^0 place value
const int red = 9;                // Red LED on pin 9

void setup() {
  // Open Serial port. Set Baud rate to 9600
  Serial.begin(9600);

  TurnOffPins();
  
  blinkLED(red);

  // Send out startup phrase
  Serial.println("Arduino Starting Up...");
  
}
void loop() {
  
  int sensorVal = analogRead(sensorPin); // Value read from thermistor
  /*
  * convert the ADC reading to voltage
  * The sensor has a bit depth of 2^10 = 1024.
  * The max voltage from the arduino is 5 [V}.
  * This formula came from the Arduino Projects book.
  */
  float voltage = ( sensorVal / 1024.0 ) * 5.0;   // [V]
  
  /* 
   * convert the voltage to temperature in degrees. 
   * This formula came from the Arduino Projects book
   */
  float temperature = (voltage - 0.5)*100;    // [degrees C]

  // Print data to serial port
  String message = "@Sensor Value:  " + String(sensorVal) + ", Volts:  " + String(voltage) + ", degrees C: " + String(temperature);
  Serial.println(message);

  // Update LED display
  displayInBinary(temperature);

  // Wait for next reading
  delay(900000);

  // For debugging
  //countUpFromZero(64);
}

/*
 * Display a number in binary using LEDs
 *     INPUT - float inNum: number to be displayed on LEDs
 *    OUTPUT - displays number to LEDs. Does not return anything to parent function
 */
void displayInBinary(float inNum){
  int inNumRnd = round(inNum);            // Round input number. LED display not setup to handle decimals
  /* // For debugging 
  String inNumRndStr = (String)inNumRnd;  
  String binaryRep = "";
  
  Serial.println((String)temperature + " " + (String)inNumRnd);
  */

  // Find binary representation of inNum.
  for (int n = greatestPinNumber - leastPinNumber; n >=0; n--){
    int pinNumber = greatestPinNumber - n;
    /*  Proof that pinNumber = greatestPinNumber - n
     *      n = greatestPinNumber - leastPinNumber
     *   => pinNumber = greatestPinNumber - n
     *                 = greatestPinNumber - (greatestPinNumber - leastPinNumber)
     *                 = leastPinNumber
     *      n = 0
     *   => pinNumber = greatestPinNumber - n
     *                 = greatestPinNumber - 0
     *                 = greatestPinNumber
     *  For every k in  [ 1 , (greatestPinNumber - leastPinNumber) - 1 ]
     *      n = greatestPinNumber - leastPinNumber - k // The minus k comes from n--
     *   => pinNumber = greatestPinNumber - n
     *                 = greatestPinNumber - (greatestPinNumber - leastPinNumber - k)
     *                 = leastPinNumber + k
     */
    int twoToTheN = exponentiateIntegers(2, n); // 2^n
    int remainder = inNumRnd - twoToTheN;

    /* // For Debugging
    String nStr = (String)(n);
    String pinNumberStr = (String)pinNumber;
    String twoToTheNStr = (String)twoToTheN;
    String remainderStr = (String)remainder;
    */
    
    if ( remainder >= 0 ){
      inNumRnd = inNumRnd - twoToTheN;
      digitalWrite(pinNumber, HIGH);
      /* // For Debugging
      inNumRndStr = inNumRnd;
      Serial.println(inNumRndStr + " - " + twoToTheNStr + " = " + remainderStr);
      binaryRep = binaryRep + "1";
      */
    } else{
      digitalWrite(pinNumber, LOW);
      /* // For Debugging
      Serial.println(inNumRndStr + " - " + twoToTheNStr + " = " + remainderStr);
      binaryRep = binaryRep + "0";
      */
    }
    // For Debugging
    //Serial.println(nStr + " " + pinNumberStr);
  }
  // For Debugging
  //Serial.println(inNumRndStr + " " + binaryRep);
}

/*
 * This method turns on the given LED, waits for 0.5 seconds, turns off LED,
 *  then waits for another 0.5 seconds
 *  INPUT - int pinNum: pin number of LED one wishes to blink
 * OUTPUT - blink LED but does not return anything to parent function
 */
void blinkLED(int pinNum){
  digitalWrite(pinNum, HIGH);
  delay(500);
  digitalWrite(pinNum, LOW);
  delay(500);
}

/*
 * Set all pins to output and set them to low
 *  INPUT - none
 * OUTPUT - set all pinNumbers from leastPinNumber to greatestPinNumber 
 *          to output and turn them off
 */
void TurnOffPins(){
  for (int pinNumber = leastPinNumber; pinNumber <=  red; pinNumber++){
      pinMode(pinNumber, OUTPUT);
      digitalWrite(pinNumber, LOW);
    }
}

/*
 * x^y where x, y are Integers
 *  INPUT - x: base
 *           y: exponent
 * OUTPUT - result: x^y
 */
int exponentiateIntegers(int x, int y){
  int result = 1;
  for (int n = 1; n <= y; n++){
    result = result*x;
  }
  return result;
}

/*
 * Count up to a given number from 0 and display each number in binary on LEDs
 *  INPUT - int endNum: number one wishes to count to
 * OUTPUT - display number in binary on LEDs
 */
void countUpFromZero(int endNum){
  for (int n = 0; n < endNum; n++){
    displayInBinary(n);
    delay(500);
  }
}
