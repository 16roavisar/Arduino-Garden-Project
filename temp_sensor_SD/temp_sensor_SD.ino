//temp sensor code
//Rotem Avisar
//2/5/2015
#include <SD.h>
#include <dht.h>
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

dht DHT;
#define DHT11_PIN 5

const int chipSelect = 8;
float degreesC;
float degreesF;
float humidity;
int soilMoisture;
int photoReceptor;

void setup(){
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  pinMode(10, OUTPUT);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  delay(3000);
}
void loop(){
  tmElements_t tm;
  
  //gets the humidity
  humidity = DHT.humidity, 1;
  
  //converts voltage to degrees C
  degreesC = DHT.temperature, 1;
  
  //concerts degrees C to degrees F
  degreesF = degreesC * (9.0/5.0) + 32.0;
  
  //gets soil moisture
  soilMoisture = analogRead(0);
  
  //gets soil moisture
  photoReceptor = analogRead(1);
  
  int chk = DHT.read11(DHT11_PIN);
  
  String dataString = "";
  String time = "";
  
  if(RTC.read(tm)){
    time += String(tm.Day);
    time += String("/");
    time += String(tm.Month);
    time += String("/");
    time += String(tmYearToCalendar(tm.Year));
    time += String(" ");
    time += String(tm.Hour);
    time += String(":");
    time += String(tm.Minute);
    time += String(":");
    time += String(tm.Second);
    Serial.println(time);
  }
  
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

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  if (dataFile) {
    dataFile.println(time);
    dataFile.println(dataString);
    dataFile.print("\n");
    dataFile.println("......................................................................");
    dataFile.print("\n");
    dataFile.close();
    // print to the serial port too:
    if(chk == DHTLIB_OK){
    Serial.println(dataString);
    Serial.print("\n");
    Serial.println("......................................................................");
    Serial.print("\n");
    }
  }
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(1000);
}
