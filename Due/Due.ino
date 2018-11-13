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

#include <Servo.h>
//#include <ADXL345.h>
#include "U8glib.h"
//#include <Wire.h>
//#include <DueFlashStorage.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <ITG3205.h>
#define TAM_MAZE 23

//If this is set as TRUE, Arduino will ignore the main code and will execute the test function.
#define EXECUTAR_TESTE false  //false
#define LOG_ON false  //true
#define PRINT_MAZE true  //true

#define LOG(x) if(LOG_ON) Serial.print(x)
#define LOGLN(x) if(LOG_ON) Serial.println(x)

#define TEMP_VITIMA 30//32//26
#define MAX_VICTIMS 4//6//4

//#define PAREDE_FRENTE read_Ultra('F') < dist_parede_Ajuste
//#define PAREDE_ESQUERDA read_Ultra('E') < dist_parede_Ajuste
//#define PAREDE_DIREITA read_Ultra('D') < dist_parede_Ajuste
//#define PAREDE_TRAS read_Ultra('T') < dist_parede_Ajuste

#define KIT_OPEN 160
#define KIT_CLOSE 65
#define PRETO 100

#define LIGAR_LED digitalWrite(pin_LED, HIGH);
#define DESLIGAR_LED digitalWrite(pin_LED, LOW);
#define LIGAR_BUZZER analogWrite(pin_BUZZER, 125);//digitalWrite(pin_BUZZER, HIGH);
#define DESLIGAR_BUZZER digitalWrite(pin_BUZZER, LOW);

int tempVitima=TEMP_VITIMA;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
ITG3205 itg3205;
U8GLIB_ST7920_128X64 u8g(13, 11, 10, U8G_PIN_NONE);
//DueFlashStorage flash;
Servo kit;
//ADXL345 accel;

const int tempo=2;//20;//80;//180;//400;//180;
int mapSide[2]={0,0};

const int motor1a=30, motor1b=32, motor1_pwm=2;//8;     //TD       34/36 7 1-3
const int motor2a=26, motor2b=28, motor2_pwm=3;//9;     //FD       38/40 6 2-4
const int motor3a=38, motor3b=40, motor3_pwm=4;//10;    //TE       26/28 5 3-1
const int motor4a=34, motor4b=36, motor4_pwm=5;//11;    //FE       30/32 4 4-2
const byte TP = 142;//135;  //125;//120;

//////////MAZE//////////

char maze[3][TAM_MAZE][TAM_MAZE];
int maze_traveled[3][TAM_MAZE][TAM_MAZE];

bool maze_wall[3][TAM_MAZE][TAM_MAZE][4];
 int startX=11, startY=11;
int virtual_x[3],virtual_y[3];
int pX[3]={startX,startX,startX}; int pY[3]={startY,startY,startY};
int pZ=0;

int way_value;
uint8_t victims_found = 0;

const struct {
  const float goingUP = -1.5;//2.5;//-3.2;//3.8;//4.6;
  const float goingDOWN =2.5;//3.3;//4.6;
  //const float finishUP = -2.2;
  //const float finishDOWN = 2.2;
} rampa;
//const int rampa_UP = -22;
//const int rampa_DOWN = 70;

struct {
  uint16_t frente1=287;//308; 
  uint16_t frente2=291;//308;
  uint16_t esq1=275;//310;
  uint16_t esq2=274;//320;
  uint16_t dir1=280;//320; 
  uint16_t dir2=291;//346;
  uint16_t tras1=254;//319;//329;//279;//289; 
  uint16_t tras2=275;//317;//327;//300;//310;
} offsetWall;

uint8_t visited_places = 1;
const uint8_t min_visited = 50;//30;//36;//38;//((7*4)+(4*3)+2) * 0.9;

//[0]Frente [1]Esq [2]Dir [3]Tras
//==//

//Àsterix//
int dist_to_end[TAM_MAZE][TAM_MAZE];
int dist_to_start[TAM_MAZE][TAM_MAZE];
int way_traveled[TAM_MAZE][TAM_MAZE];
char last_dir[TAM_MAZE][TAM_MAZE];

bool ativar_vitima = true;
//==//

//TREMAUX//
const int dist_parede = 12+4;//12+4;
const int dist_parede_Ajuste = 15;

bool executar_frente = true;
bool stop_fwd = false;
bool search_victim_adjust = true;
//==//

//////////LCD//////////
char lcd_function_name[12];
  //lcd_function_name = "";
//==//

//////////DIGITAL//////////
const byte pin_ultraTras = 43;
const byte pin_ultraFrente = 47;
const byte pin_ultraEsq = 49;
const byte pin_ultraDir = 45;

const byte pin_LED = 53;
const byte pin_kit = 8;//12;
const byte pin_BUZZER = 23;
const byte pin_button_MENU = 11;
const byte pin_pushButton1 = 12;
const byte pin_pushButton2 = 9;
//==//

///////////ANALOG/////////
const byte pin_infraBaixo = 1; //ANALOG

const byte pin_infraFrente1 = 6; //ANALOG
const byte pin_infraFrente2 = 7; //ANALOG
const byte pin_infraEsq1 = 5; //ANALOG
const byte pin_infraEsq2 = 4; //ANALOG
const byte pin_infraDir1 = 8; //ANALOG
const byte pin_infraDir2 = 9; //ANALOG
const byte pin_infraTras1 = 3; //ANALOG
const byte pin_infraTras2 = 10; //ANALOG

byte pin_battery = 0;

//ENCODERS//
const int Encoder_m1_PinA = 27;
const int Encoder_m1_PinB = 29;

const int Encoder_m2_PinA = 31;
const int Encoder_m2_PinB = 33;

const int Encoder_m3_PinA = 35;
const int Encoder_m3_PinB = 37;

const int Encoder_m4_PinA = 39;
const int Encoder_m4_PinB = 41;

volatile int enc_read[] = {0,0,0,0};
volatile int enc_read_SAVED[] = {0,0,0,0};
//==//

//VITIMA//
bool vitima_na_rampa = false;
bool vitima_quadrante = false;  
bool vitima_ja_encontrada = false;
//==//

struct {
  const uint8_t rampaUP = 140;//120;//140;//180;//190;
  const uint8_t rampaDOWN = 80;//70;//90;
} velocidade;

int button_MENU=0;
int old_button_MENU = 0;
int MENU_timer = millis();
int read_button_MENU ()
{
  short int button_MENU_pulse = analogRead(pin_button_MENU);
  
  int M_time_pressed = millis() - MENU_timer;
  if(button_MENU_pulse > 700 && button_MENU_pulse < 800 && M_time_pressed >= 1000)
    {button_MENU = 4; old_button_MENU = 4;} //Back
  else if(button_MENU_pulse > 700 && button_MENU_pulse < 800)
    button_MENU = 1; //Left //176
  else if(button_MENU_pulse > 600 && button_MENU_pulse < 700)
    button_MENU = 2; //Select //270
  else if(button_MENU_pulse > 500 && button_MENU_pulse < 600)
    button_MENU = 3; //Right //321
  else{
    button_MENU = 0; MENU_timer = millis();
  }
  
  if(old_button_MENU != button_MENU)
    MENU_timer = millis();

  old_button_MENU = button_MENU;
  
  return button_MENU;
}
int contB=0;
void setup() {
  int timer_setup = millis();
  u8g.setRot180();
  draw_setup();

  if(LOG_ON)
  Serial.begin(115200);//9600);
  
  Serial1.begin(115200);
  
  LOGLN("Wire.begin");
  Wire.begin();
  
  accel.begin();
  accel.setRange(ADXL345_RANGE_16_G);
  
  LOGLN("Gyro.Init");
  itg3205.itg3205initGyro();
 // delay(100);
  //LOGLN("Gyro.Calibrate");
  //itg3205.itg3205CalGyro();
  //delay(100);
//  gyro.zeroCalibrate(500, 2); //(time?,?)
  
  
  pinMode(pin_LED, OUTPUT); DESLIGAR_LED
  pinMode(pin_BUZZER, OUTPUT);
  pinMode(pin_button_MENU, OUTPUT);
  kit.attach(pin_kit);
  kit.write(KIT_CLOSE);
  //kit.detach();
  //accel.begin();
  if(battery_level() <= 7 && battery_level() > 5.8) LIGAR_BUZZER
  else if(battery_level() <= 5.8) analogWrite(pin_BUZZER, 160);
  else DESLIGAR_BUZZER
  
  //MOTORS//
  pinMode(13, OUTPUT);
  pinMode(motor1a, OUTPUT); pinMode(motor1b, OUTPUT);
  pinMode(motor2a, OUTPUT); pinMode(motor2b, OUTPUT);
  pinMode(motor3a, OUTPUT); pinMode(motor3b, OUTPUT);
  pinMode(motor4a, OUTPUT); pinMode(motor4b, OUTPUT);
  pinMode(motor1_pwm, OUTPUT); pinMode(motor2_pwm, OUTPUT);
  pinMode(motor3_pwm, OUTPUT); pinMode(motor4_pwm, OUTPUT);
  
  digitalWrite(motor1a, LOW); digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, LOW); digitalWrite(motor2b, LOW);
  digitalWrite(motor3a, LOW); digitalWrite(motor3b, LOW);
  digitalWrite(motor4a, LOW); digitalWrite(motor4b, LOW);
  digitalWrite(motor1_pwm, LOW); digitalWrite(motor2_pwm, LOW);
  digitalWrite(motor3_pwm, LOW); digitalWrite(motor4_pwm, LOW);
  //==//
  
  digitalWrite(pin_LED, LOW);
  digitalWrite(13, LOW);
  
  //Encoder Setup
  pinMode(Encoder_m1_PinA, INPUT);
  pinMode(Encoder_m1_PinB, INPUT);
  pinMode(Encoder_m2_PinA, INPUT);
  pinMode(Encoder_m2_PinB, INPUT);
  pinMode(Encoder_m3_PinA, INPUT);
  pinMode(Encoder_m3_PinB, INPUT);
  pinMode(Encoder_m4_PinA, INPUT);
  pinMode(Encoder_m4_PinB, INPUT);

  attachInterrupt(Encoder_m1_PinA, doEncoder_m1_0A, CHANGE); //3
  attachInterrupt(Encoder_m1_PinB, doEncoder_m1_0B, CHANGE); //2
  
  attachInterrupt(Encoder_m2_PinA, doEncoder_m2_0A, CHANGE); //3
  attachInterrupt(Encoder_m2_PinB, doEncoder_m2_0B, CHANGE); //2
  
  attachInterrupt(Encoder_m3_PinA, doEncoder_m3_0A, CHANGE); //3
  attachInterrupt(Encoder_m3_PinB, doEncoder_m3_0B, CHANGE); //2
  
  attachInterrupt(Encoder_m4_PinA, doEncoder_m4_0A, CHANGE); //3
  attachInterrupt(Encoder_m4_PinB, doEncoder_m4_0B, CHANGE); //2
  //==//
  
  for(int i=TAM_MAZE-1; i>=0; i--)
  {
    for(int j=0; j<TAM_MAZE; j++)
    {
      maze[0][i][j]=' ';
      maze[1][i][j]=' ';
      maze_traveled[0][i][j]=0;
      maze_traveled[1][i][j]=0;
      
      for(int k=0; k<4; k++){
        maze_wall[0][i][j][k]=false;
        maze_wall[1][i][j][k]=false;
      }
    }
  }

  for(int i=0; i<TAM_MAZE; i++){
    for(int j=0; j<TAM_MAZE; j++){
      dist_to_start[i][j]=0;
      dist_to_end[i][j]=0;
      way_traveled[i][j]=0;
      last_dir[i][j]='X';
    }
  }
  
  maze[0][startY][startX] = 'S';
  
  //flash__read_vitima_temp();
  //flash__read_maze();
  
  while((millis() - timer_setup) <= 1200);
  DESLIGAR_BUZZER
  //kit.detach();
  
  do{
    //analogWrite(13, 180);
    draw_welcome();
  }while(read_button_MENU() == 0);
  //delay(2000);//800);
  
  while(read_button_MENU() != 0);
  
  if(read_button_MENU() == 3)
  {
    while(read_button_MENU() == 3){}
    while(1)
    {
      menu_loop();
    }
  }
  tempVitima = max(ler_temp_NANO(102),ler_temp_NANO(103));
  tempVitima = max(tempVitima,ler_temp_NANO(104));
  tempVitima = max(tempVitima,ler_temp_NANO(105));
  tempVitima += 2;//3;//2;//3;
  //tempVitima = TEMP_VITIMA;//((ler_temp_NANO(102)+ler_temp_NANO(103)+
               // ler_temp_NANO(104)+ler_temp_NANO(105))/4)+3;
  
  while(EXECUTAR_TESTE)
  {
    loop_teste();
  }
  
  u8g.setFont(u8g_font_p01type);
}

void loop_teste()
{
//  setMotor_encoder(100, 30);
//
//  setMotor(0,0,0,0); delay(800);
  
if (read_button_MENU()==3){
  while(1){
  u8g.firstPage();
  do{
  M_infra();
  
  }while(u8g.nextPage());
  }
}
if (read_button_MENU()==1){
  while(1){
  u8g.firstPage();
  do{
  M_ultra();
 
  }while(u8g.nextPage());
  }
}

//  u8g.firstPage();
//  do{
//  u8g.setFont(u8g_font_helvR08);//unifont); -8px
//  
//  u8g.setPrintPos(10, 8); u8g.print(read_corQuad());
// 
//  }while(u8g.nextPage());
//
//  setMotor(TP,TP,TP,TP);
//  LOG(read_Infra('E',1));
//  LOG(" ");
//  LOGLN(read_Infra('E',2));



//if(read_button_MENU() != 0){ LOG(++contB); LOGLN("==========================");}
//  LOGLN(readGyroscope('Y'));
//  LOG(" ");
//  LOGLN(readGyroscope('Z'));
  

//  u8g.firstPage();
//  do{
//  M_accel();
//  M_gyro();
//  }while(u8g.nextPage());

//teste_90();
  //teste_temp();
  //teste();
}

void loop()
{
  if(PRINT_MAZE) draw();
  tremaux();

  //if( read_button_MENU() != 0)//maze_finished() ) //read_button_MENU() != 0){
//  {
    while(visited_places >= min_visited && victims_found >= MAX_VICTIMS && pZ==false)
    {
      //while(1){
      LIGAR_LED;
      asterix();}
    //}
//  }

  //==TRASH CODE==//
  
 //LIGAR_LED
  //teste();
  
}

//Sometimes I believe compiler ignores all my comments
