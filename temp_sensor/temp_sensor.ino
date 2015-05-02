//temp sensor code
//Rotem Avisar
//2/5/2015
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int temperaturePin = 0;

void setup(){
  //initializes the port and sets communications speed in 9600 bsp
  Serial.begin(9600);
  //initializes the port and sets lcd display to 16X2
  lcd.begin(16, 2);
  //Prints a message to the LCD
  lcd.print("Data Collection");
}


void loop(){
  float voltage;
  float degreesC;
  float degreesF;

  voltage = getVoltage(temperaturePin);
  
  // Converts voltage to degrees C
  degreesC = (voltage - 0.5) * 100.0;
  
  // Concerts degrees C to degrees F
  degreesF = degreesC * (9.0/5.0) + 32.0;
  
  //Uses serial port to print values
  Serial.print("  C: ");
  Serial.print(degreesC);
  Serial.print("  F: ");
  Serial.println(degreesF);
  
  //set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  //prints degrees C
  lcd.print("C: ");
  lcd.print(degreesC);
  //set the cursor to column 0, line 2
  lcd.setCursor(0, 2);
  //prints degrees F
  lcd.print("F: ");
  lcd.print(degreesF);
  
  // Collects data every second
  delay(1000); 
}


float getVoltage(int pin){
  return (analogRead(pin) * 0.004882814);
}

