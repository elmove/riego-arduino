
//Pines y variables#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
#include <DHT.h>
#define DHTPIN 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
Adafruit_LiquidCrystal lcd(0);

int temp, humedad;//Configuro las variables de temperatura y humedad del DHT11
//Pines Bomba de agua
const int bomba1 = 2; 
const int bomba2 = 3;
const int bomba3 = 4;
const int bomba4 = 5;
//Pines Humedad Suelo
const int humedadsuelo1 = A0;
const int humedadsuelo2 = A1;
const int humedadsuelo3 = A2;
const int humedadsuelo4 = A3;
//Nivel agua
const int nivel = 13;


void setup()
{
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  Serial.begin(9600);//Arrancamos el puerto serie a 9600
  dht.begin();//Arranco el sensor DHT11
  //Configuramos entradas y salidas
  pinMode(humedadsuelo1, INPUT);
  //pinMode(humedadsuelo2, INPUT);
  //pinMode(humedadsuelo3, INPUT);
  //pinMode(humedadsuelo4, INPUT);//Configuro humedadsuelo como entrada
  pinMode(bomba1, OUTPUT);
  //pinMode(bomba2, OUTPUT);
  //pinMode(bomba3, OUTPUT);
  //pinMode(bomba4, OUTPUT);//Configuro bomba como salida
  //pinMode(nivel, INPUT);//Configuro en nivel de agua como entrada
  lcd.setCursor(0, 0);
  lcd.print("Cargando...");
  lcd.setCursor(0, 1);
  lcd.print("  Arduriego V1");
  delay(5000);
  lcd.clear();
 }

void loop()
{
  
  int SensorValue1 = analogRead(humedadsuelo1);
  //int SensorValue2 = analogRead(humedadsuelo2);
  //int SensorValue3 = analogRead(humedadsuelo3);
  //int SensorValue4 = analogRead(humedadsuelo4);//Leo el valor de la humedad y lo meto en SensorValue
  //int SensorNivel = digitalRead(nivel); //Leo lo que marca el nivel de agua
  
  //Leo y meto los valores de temperatura y humedad en las variables temp y humedad
  humedad = dht.readHumidity();
  temp = dht.readTemperature();

  lcd.setCursor(0, 0);
  Serial.print("Temp: "); Serial.print(temp);
  lcd.print("Temp:");lcd.print(temp);
  Serial.print("ºC Humedad: "); Serial.print(humedad); Serial.println("%");
  lcd.print(" Hum:");lcd.print(humedad);
  //Imprimo por el puerto serie el valor de la humedad del suelo
  Serial.print("Humedad del suelo: ");Serial.print(SensorValue1); Serial.println("%");
  delay(1000);
   
   if(SensorValue1 >= 700){
   // Si la tierra está seca, comenzara a regar
   // Riega durante 1 segundo y espera a comprobar la humedad otro segundo
   Serial.println("La tierra está seca, comienza el riego");
   lcd.setCursor(0, 1);
   lcd.print("Regando  ");
   digitalWrite(bomba1, HIGH);
   delay(2000);
   digitalWrite(bomba1, LOW);
   delay(1000);
   }
   else{
    lcd.setCursor(0,1);
    lcd.print("Tierra ok");
}
  delay(2000);
}
