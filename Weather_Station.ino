
#include<SPI.h>
#include<SD.h>

#include<LiquidCrystal.h>

LiquidCrystal lcd(1,2,3,4,5,6);
int sensor1Pin = A2;
int sensor1Value = 0;
int sensor2Pin = A1;
int sensor2Value = 0;
int sensor3Pin = A3;
int sensor3Value = 0;
const int chipSelect = 10;
int mydata;

void setup()
{
  lcd.begin(16,2);
  lcd.print("TEMP  HUM  LDR ");
  Serial.begin(9600);
  Serial.print ("Initilizing SD card...");
  pinMode(10, OUTPUT);
  if(!SD.begin(chipSelect))
  {
    Serial.print("Card failed,or not present"); 
  }
  else 
  {
    Serial.print("Card Initialized.");
  }
}


void loop()
{
  lcd.begin(16,2);
  delay(200);
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  {
    sensor1Value=analogRead(sensor1Pin);
    delay(150);
    sensor2Value=analogRead(sensor2Pin);
    delay(150);
    sensor3Value=analogRead(sensor3Pin);
    delay(150);
    if(dataFile)
    {
      dataFile.print("Temp");
      Serial.print("Temp");
      sensor1Value=analogRead(sensor1Pin);
      dataFile.print(sensor1Value*0.48828125);
      dataFile.println("C");
      Serial.print(sensor1Value*0.48828125);
      Serial.println("C");
      lcd.setCursor(0,1);
      lcd.print(sensor1Value*0.48828125);
      
      dataFile.print("HUM");
      Serial.print("HUM");
      sensor2Value=analogRead(sensor2Pin);
      dataFile.print(sensor2Value/6.7);
      dataFile.println("%RH");
      Serial.print(sensor2Value/6.7);
      Serial.println("%RH");
      lcd.setCursor(6,1);
      lcd.print(sensor2Value/6.7);


      dataFile.print("LDR");
      Serial.print("LDR");
      sensor3Value=analogRead(sensor3Pin);
      dataFile.print(sensor3Value*0.097);
      dataFile.println("%");
      Serial.print(sensor3Value*0.097);
      Serial.println("%");
      lcd.setCursor(12,1);
      lcd.print(sensor3Value*0.097);

      dataFile.close();
      delay(3000);  
    }
    
  }
  
}



