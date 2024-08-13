
#include <Arduino.h>

#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Waveshare4InchTftShield.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; 

unsigned long delayTime;

int PinDeLecturaIntensidad1 = A8, PinDeLecturaIntensidad2 = A9, PinDeLecturaIntensidad3 = A10, PinDeLecturaIntensidad4 = A11, IniciarToma; 

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GOLD    0xFFD7
#define DGREEN  0x0683
#define ORANGE  0xFC40
#define LBLUE   0x06BF

long TextoEnPantalla();

Waveshare4InchTftShield Waveshield;
Adafruit_GFX &tft = Waveshield;

void setup() 
{
	pinMode(13, OUTPUT);   //Pin de prueba que tiene asociado un LED
  pinMode(PinDeLecturaIntensidad1, INPUT);
  Serial.begin(9600);
  while(!Serial);    
    unsigned status;
    status = bme.begin(0x77);  
  int delayTime = 100000;
	SPI.begin();
	Waveshield.begin();
  tft.setRotation(45);
  tft.fillScreen(BLACK);
  tft.drawLine(0, 62, 479, 62, RED);
}

unsigned long start = micros();

void loop() 
{
  
    TextoEnPantalla();
    delay(1000);
}


long TextoEnPantalla()
{

		tft.setCursor(40, 10);
		tft.setTextColor(RED);    tft.setTextSize(3);
		tft.println("CAMARA DE INTEMPERISMO");
		tft.println();

    tft.setCursor(200, 40);
    tft.setTextColor(CYAN);  tft.setTextSize(2);
    tft.println("GIMM");
    tft.println();

		tft.setTextColor(WHITE);
    tft.setTextSize(2); tft.println("  Sensores de");
    tft.setTextSize(0); tft.println();
    tft.setTextSize(2); tft.println(" intensidad UVA");
    tft.setTextSize(0); tft.println();
    tft.setTextSize(2); tft.println("    [mm/mw]:");
    tft.println();
		tft.setTextColor(BLUE, BLACK); tft.print(" Sensor 1: "); tft.println(printValuesUV1() );
    tft.println();
    tft.setTextColor(MAGENTA, BLACK); tft.print(" Sensor 2: "); tft.println(printValuesUV2());
    tft.println();
    tft.setTextColor(GOLD, BLACK); tft.print(" Sensor 3: "); tft.println(printValuesUV3());
    tft.println();
    tft.setTextColor(DGREEN, BLACK); tft.print(" Sensor 4: "); tft.println(printValuesUV4());


    tft.setCursor(240, 70);
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(2); tft.println("   Sensores ");
    tft.setCursor(240, 70); tft.setTextSize(0); tft.println();
    tft.setCursor(240, 95); tft.setTextSize(2); tft.println(" Ambientales: ");
    tft.setTextColor(ORANGE, BLACK); tft.setCursor(240, 130); tft.print(" T [C]: "); tft.println(printValuesTem());
    tft.setTextColor(LBLUE, BLACK); tft.setCursor(240, 155); tft.print(" HR. [%]: "); tft.println(printValuesHum());

    tft.setTextColor(GREEN);
    tft.setCursor(270, 230); tft.print(" Exportar "); tft.println();
}


float printValuesUV1() 
{
  float uvLevel = averageAnalogRead(PinDeLecturaIntensidad1);
  float uvIntensidad=0;
  float outputTension = 5.0 * uvLevel/1024;
  uvIntensidad = mapfloat(outputTension, 0.99, 2.9, 0.0, 15.0);
  
  return uvIntensidad*1.0;
}

float printValuesUV2() 
{
  float uvLevel = averageAnalogRead(PinDeLecturaIntensidad2);
  float uvIntensidad=0;
  float outputTension = 5.0 * uvLevel/1024;
  uvIntensidad = mapfloat(outputTension, 0.99, 2.9, 0.0, 15.0);
  
  return uvIntensidad*1.0;
}

float printValuesUV3() 
{
  float uvLevel = averageAnalogRead(PinDeLecturaIntensidad3);
  float uvIntensidad=0;
  float outputTension = 5.0 * uvLevel/1024;
  uvIntensidad = mapfloat(outputTension, 0.99, 2.9, 0.0, 15.0);
  
  return uvIntensidad*1.0;
}

float printValuesUV4() 
{
  float uvLevel = averageAnalogRead(PinDeLecturaIntensidad4);
  float uvIntensidad=0;
  float outputTension = 5.0 * uvLevel/1024;
  uvIntensidad = mapfloat(outputTension, 0.99, 2.9, 0.0, 15.0);
  
  return uvIntensidad*1.0;
}

float printValuesTem()
{
  float Temp = 0;
  Temp = bme.readTemperature()*1.0;

  return Temp*1.0;
 
}
float printValuesHum()
{
  float HumR=0;
  HumR = bme.readHumidity()*1.0;
  
  return HumR*1.0;
}

int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0;

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);
}
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

