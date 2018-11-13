/*================================================
 *                    Raptor B
 *================================================
 *
 * Este código, em conjunto com o robô "Raptor", destina-se à participação na CBR
 * (Competição Brasileira de Robótica) e na RoboCup Junior, categoria Rescue Maze.
 *
 * Equipe Raptor B (Rescue Maze): Ítalo Lélis de Carvalho, João Pedro Rosada Canesin
 * Técnico: Igor Araujo Dias Santos
 * Domingo. 6 de Setembro, 2015
 *
 *================================================
 *
 * This code, along with the robot "Raptor", aims to participate in the CBR
 * (Brazilian Robotics Competition) and in the RoboCup Junior, category Rescue Maze.
 *
 *
 * Team Raptor B (Rescue Maze): Italo Lelis de Carvalho, Joao Pedro Rosada Canesin
 * Instructor: Igor Araujo Dias Santos
 * Sunday. September 6th, 2015
 *
 *================================================
 *
 * CBR (Brazilian Robotics Competition):
 *    http://www.cbrobotica.org/
 *
 * RoboCup Junior:
 *    https://www.robocup.org/
 *
 */

//#include "Ultrasonic.h"
#include <i2cmaster.h>
//#define NUM_ULTRA 4
#define NUM_TEMP 4

#define CODIGO__TEMP_DEV_0 0x54<<1
#define CODIGO__TEMP_DEV_1 0x24<<1
#define CODIGO__TEMP_DEV_2 0x22<<1
#define CODIGO__TEMP_DEV_3 0x5A<<1

//Ultrasonic ultrasonic0(6,7);
//Ultrasonic ultrasonic1(4,5);
//Ultrasonic ultrasonic2(2,3);

int celsius[]={0,0,0,0};

int recByte=0;
//int ultra[3];

void setup ()
{
  pinMode(13,OUTPUT); digitalWrite(13,HIGH);
  Serial.begin(115200);//19200);
  i2c_init();
  PORTC = (1 << PORTC4) | (1 << PORTC5);
  digitalWrite(13,LOW);
}


void loop ()
{
  comunicar();
  //testar_sensores();
  
  //ler_temperatura(2);
  //Serial.println((celsius[2]/10)*2);
}

/*void testar_sensores () {
  Serial.print(ultrasonic0.Ranging(CM));
  Serial.print('\t');
  Serial.print(ultrasonic1.Ranging(CM));
  Serial.print('\t');
  Serial.println(ultrasonic2.Ranging(CM));
}*/

void comunicar ()
{
  digitalWrite(13,LOW);
  if(Serial.available() > 0)
  {
    recByte = Serial.read();
    
   /* if(recByte==107){
      ler_ultra(0);
      Serial.write(ultra[0]);
    }
    if(recByte==108){
      ler_ultra(1);
      Serial.write(ultra[1]);
    }
    if(recByte==109){
      ler_ultra(2);
      Serial.write(ultra[2]);
    }
    if(recByte==110){
      ler_ultra(3);
      Serial.write(ultra[3]);
    }
    */
    if(recByte==102){
      ler_temperatura(0);
      Serial.write(celsius[0]);
    }
    if(recByte==103){
      ler_temperatura(1);
      Serial.write(celsius[1]);
    }
    if(recByte==104){
      ler_temperatura(2);
      Serial.write(celsius[2]);
    }
    if(recByte==105){
      ler_temperatura(3);
      Serial.write(celsius[3]);
    }
    
    if(recByte==100){
      Serial.write(1);
    }
  }
  //digitalWrite(13,HIGH);
  //delay(100);
}

/*void ler_ultra (int u)
{
  if(u==0)
    ultra[0] = ultrasonic0.Ranging(CM);
    
  if(u==1)
    ultra[1] = ultrasonic1.Ranging(CM);
  
  if(u==2)
    ultra[2] = ultrasonic2.Ranging(CM);
  
  //delay(5);
}
*/
void ler_temperatura (int t)
{
  int dev;
  
  switch(t)
  {
    case 0:
      dev = CODIGO__TEMP_DEV_0;
    break;
    
    case 1:
      dev = CODIGO__TEMP_DEV_1;
    break;
    
    case 2:
      dev = CODIGO__TEMP_DEV_2;
    break;
    
    case 3:
      dev = CODIGO__TEMP_DEV_3;
    break;
  }
  
  int data_low = 0;
  int data_high = 0;
  int pec = 0;
  
  i2c_start_wait(dev+I2C_WRITE);
  i2c_write(0x07);
  
  // read
  i2c_rep_start(dev+I2C_READ);
  data_low = i2c_readAck(); 
  data_high = i2c_readAck(); 
  pec = i2c_readNak();
  i2c_stop();
  
  double tempFactor = 0.02; 
  double tempData = 0x0000; 
  int frac;

  tempData = (double)(((data_high & 0x007F) << 8) + data_low);
  tempData = (tempData * tempFactor)-0.01;
  celsius[t] = ((tempData - 273.15));///2)*10;
}
