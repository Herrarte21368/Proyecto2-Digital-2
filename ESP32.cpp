//*****************************************************************************
// Universidad del Valle de Guatemala
// BE3015 - Electrónica Digital 2
// Andrée Herrarte 
// Proyecto 2
//*****************************************************************************

//*****************************************************************************
// Librerías
//*****************************************************************************
#include <Arduino.h>

//*****************************************************************************
// Definición de pines
//*****************************************************************************

#define pinADC 35 //Pin de lectura del ADC 

//configuración del ADC para el sensor de temperatura

float adcRaw = 0.0;
float promedioLecturas = 0;     // Almacena el valor promedio de las lecturas
int numLecturas = 10;           // Número de muestras para el promedio
float temp = 0.0;
int digito;
int decenas = 0;
int unidades = 0;
int decimal = 0;
bool punto = 0;

int temp1;
//*****************************************************************************
// Variables Globales
//*****************************************************************************


//*****************************************************************************
// Prototipos de función
//*****************************************************************************

void promedio(void);
void mediaMovil(void);
float convertToTemperature(float adcValue);
//*****************************************************************************
// Configuración
//*****************************************************************************

void setup()
{
  Serial.begin(115200);
  //Serial.println("conexion con computadora");
  Serial2.begin(115200);
  //Serial2.println("conexion con TIVA");
  
  pinMode(pinADC, INPUT);
  //while (!Serial);
}
//*****************************************************************************
// Loop Principal
//*****************************************************************************

void loop()
{
  adcRaw = analogRead(pinADC); // Leer el valor crudo del ADC
  promedio();                  // Realizar el cálculo del promedio
  mediaMovil();                // Realizar el cálculo del promedio móvil

//Funcion del boton si se apacha el boton 
  if (Serial2.available() > 0 ){
    temp1 = Serial2.read();
    if (temp1 == '1'){
      float voltage = convertToTemperature(adcRaw); // Convertir ADC a Celsius
      Serial2.print(voltage);
      temp1 = 0;
    }   
  }
}

// Funcion de ADC
void promedio(void)
{
  int sumaLecturas = 0;
  for (int k = 0; k < numLecturas; k++)
  {
    sumaLecturas += analogRead(pinADC);
    delay(1);
  }
  promedioLecturas = sumaLecturas / numLecturas;
}

// Funcion de ADC
void mediaMovil(void)
{
  adcRaw = analogReadMilliVolts(pinADC);
}

// convertir voltage a Celius
float convertToTemperature(float adcValue)
{

  float voltage = adcValue / 10;
  return voltage;
}
