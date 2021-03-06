//temp sensor code
//Rotem Avisar
//2/5/2015
#include <LiquidCrystal.h>
#include <SD.h>
#include <dht.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

dht DHT;
#define DHT11_PIN 5

const int temperaturePin = 0;
const int chipSelect = 8;
float degreesC;
float degreesF;
float humidity;
int soilMoisture;
int photoReceptor;
int chk = DHT.read11(DHT11_PIN);

void setup(){
  //initializes the port and sets communications speed in 9600 bsp
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //initializes the port and sets lcd display to 16X2
  lcd.begin(16, 2);
  //Prints a message to the LCD
  lcd.print("Data Collection");
  Serial.print("Initializing SD card...");
  pinMode(10, OUTPUT);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}


void loop(){
  float voltage;
  float degreesC;
  float degreesF;

  voltage = getVoltage(temperaturePin);
  //gets the humidity
  humidity = DHT.humidity, 1;
  
  // Converts voltage to degrees C
  degreesC = (voltage - 0.5) * 100.0;
  //converts voltage to degrees C
  degreesC = DHT.temperature, 1;
  
  // Concerts degrees C to degrees F
  //concerts degrees C to degrees F
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

  //gets soil moisture
  soilMoisture = analogRead(0);
  
  //gets soil moisture
  photoReceptor = analogRead(1);
  
  String dataString = "";
  
  dataString += String("C: ");
  dataString += String(degreesC);
  dataString += String(" F: ");
  dataString += String(degreesF);
  dataString += String(" Humidity: ");
  dataString += String(humidity);
  dataString += String(" Soil Moisture: ");
  dataString += String(soilMoisture);
  dataString += String(" Photo Receptor: ");
  dataString += String(photoReceptor);

float getVoltage(int pin){
  return (analogRead(pin) * 0.004882814);
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  else {
    Serial.println("error opening datalog.txt");
  } 
  if(chk == DHTLIB_OK){
    //uses serial port to print values
    Serial.print("  C: ");
    Serial.print(degreesC);
    Serial.print("  F: ");
    Serial.println(degreesF);
    Serial.print("  Humidity: ");
    Serial.print(humidity);
    Serial.print("  Soild Moisture: ");
    Serial.println(soilMoisture);
    Serial.print("  Photo Receptor: ");
    Serial.println(photoReceptor);
  }
  delay(1000);
}


