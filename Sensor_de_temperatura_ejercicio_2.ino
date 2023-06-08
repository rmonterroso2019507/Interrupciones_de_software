/*
 * Fundacion Kinal
 * Centro educativo tecnico laboral Kinal
 * Perito en electonica
 * Quinto perito
 * EB5AM 
 * Taller de electronica digital y reparacion de computadoras
 * Nombre: Roberto Antonio Monterroso Aguilar
 * Carne: 2019507
*/

//librerias a utilizar
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <Ticker.h>

//directivas de preprocesador
#define push_1 3

//Variables
volatile static bool estado;
  
//Funciones a usar 
void isrTemp(void);
void isrBoton(void);

//Constructores
OneWire ourWire(2); //Se establece el pin 2 para usar la libreria onewire
DallasTemperature sensorCR7(&ourWire); //Se declara un objeto para que detecte el sensor
Ticker accionTemp(isrTemp, 3000); 
Ticker accionBoton(isrBoton, 6000);

void setup() 
{
  Serial.begin(19200);//inicia la comunicacion serial
  pinMode(push_1, INPUT);//define el pin a utilizar
  sensorCR7.begin();//se le da inicio a la comunicacion del sensor
  accionTemp.start();
  accionBoton.start();
  Serial.println("Inicia la comunicacion");
}

void loop() 
  {
   accionTemp.update();
   accionBoton.update();
  }

void isrTemp(void)
  {
  sensorCR7.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp= sensorCR7.getTempCByIndex(0); //Se obtiene la temperatura en ºC
  Serial.print("#### ");  
  Serial.print("La temperatura es: ");  
  Serial.print(temp);
  Serial.print(" C°");  
  Serial.println(" ####");
  }
  
void isrBoton(void)
  {
  estado = digitalRead(push_1);
  if(estado == HIGH){
    Serial.println("//// push_1 Activado ////");
    }
  if(estado == LOW){
    Serial.println("//// push_1 Desactivado ////");
    }
  }
