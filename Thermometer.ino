// Global Variables
const int sensorPin = A0;
const float baselineTemp = 20;    // [degrees C]

const int red = 6;                //     red LED on pin 6
const int yellow = 5;             //  yellow LED on pin 5
const int green = 4;              //   green LED on pin 4
const int blueTop = 3;            // blueTop LED on pin 3
const int blueBtm = 2;            // blueBtm LED on pin 2

void setup() {
  // Open Serial port
  Serial.begin(9600);
  
  // Initialize all pins to off
  for (int pinNumber = 2; pinNumber < 7; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
  blinkLED(red);
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

  UpdateLEDs(temperature);
  delay(10000); 
}

void UpdateLEDs(float temperature){
  if(temperature < baselineTemp-6){ 
    // freezing tits off
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blueTop, HIGH);
    digitalWrite(blueBtm, HIGH);
  } else if (temperature >= baselineTemp-6 && temperature < baselineTemp-2){
    // cool
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blueTop, HIGH);
    digitalWrite(blueBtm, LOW);
  } else if (temperature >= baselineTemp-2 && temperature < baselineTemp+2){
    // comfy
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blueTop, LOW);
    digitalWrite(blueBtm, LOW);
  } else if (temperature >= baselineTemp+2 && temperature < baselineTemp+6){
    // on the warm side
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blueTop, LOW);
    digitalWrite(blueBtm, LOW);
  } else if (temperature >= baselineTemp+6 ){
    // sweating balls off
    digitalWrite(red, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blueTop, LOW);
    digitalWrite(blueBtm, LOW);
  }
}
void blinkLED(int pinNum){
  digitalWrite(pinNum, HIGH);
  delay(500);
  digitalWrite(pinNum, LOW);
  delay(500);
}
