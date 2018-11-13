//enc1 3212 | 3167 | 3177 |  2980 > 99,34
//enc2 3370 | 3367 | 3299 |  3088,5 > 102,95
//enc3 3210 | 3199 | 3155 |  3136,5 > 104,55
//enc4 3174 | 3161 | 3142 |  3178,5 > 105,95



byte eTP = TP; const float eKP = 5.2;
const float enc_const_fwd [4] ={99.34, 102.95, 104.55, 105.95};

const float enc_const [4] ={106.1777*(30/32.6)*(30/30.5),111.511*(30/32.6)*(30/30.5),106.27*(30/32.6)*(30/30.5),105.3*(30/32.6)*(30/30.5)};
//{((110.23*27.7)/30),(((106.53*27.7)/30)*(eTP+7))/eTP,((104.63*27.7)/30),(((103.13*27.7)/30)*(eTP+7))/eTP}; //Value returned by the encoder in 1cm

float tempo_enc = 0;

float aux;//temporario(Rosada)
void teste_dist(){
  while(read_button_MENU()!=0){
    setMotor(TP,TP,TP,TP);
    delay(10);
    setMotor(0,0,0,0);
    delay(10);
    
  }
  u8g.setFont(u8g_font_helvR08);
  aux=(float)((((enc_read[0])/enc_const[0])+((enc_read[1])/enc_const[1])+((enc_read[2])/enc_const[2])+((enc_read[3])/enc_const[3]))/4);
   u8g.setPrintPos(30, 8); u8g.print(aux);
}

//[P]ID ENCODER//
void delay_encoder (char dir, float dist) //Function to travel the robot using [P]ID on encoders
{
  //float enc_setPoint;
  
  if(dir == 'L' || dir == 'E' || dir == 'R' || dir == 'D' || dir == 'A')
  {
    dist *= PI *(1800/135)*(92/90)/ 180; // ANGULO * 2 * RAIO * pi / 360  ////14
  }
  
  int enc_motor[4]; //setPoint of the PID
  float enc_dist[4] = {0,0,0,0}; //Will measure distance traveled in cm
  enc_read [0] = 0;  enc_read [1] = 0;
  enc_read [2] = 0;  enc_read [3] = 0; //reset values
  //setMotor(eTP,eTP,eTP,eTP); delay(200);
  
  do{
    for(int e=0; e<4; e++){
      enc_dist[e] =  (enc_read[e])/enc_const[e] ; //Measure distance in cm traveled by each encoder
      enc_dist[e]=abs(enc_dist[e]);
      //LOG(enc_dist[e]);LOG("\t");
      if(enc_dist[e] < dist) enc_motor[e]=eTP; 
      else enc_motor[e]=0; //LOG(enc_dist[e]); LOG("\t");
    }
    //LOGLN(" ");
    //LOGLN();
    
    /*enc_setPoint = (enc_dist[0]+enc_dist[1]+enc_dist[2]+enc_dist[3])/4; //Measure setPoint by setting the average value of the encoders
    
    for(int e=0; e<4; e++){
      enc_motor[e] = eTP - ((enc_dist[e] - enc_setPoint)*eKP);
    }*/
    
    /*enc_motor[0] = eTP - (((enc_dist[0]+enc_dist[2])/2 - enc_setPoint)*eKP);
    enc_motor[2] = enc_motor[0];
    enc_motor[1] = eTP - (((enc_dist[1]+enc_dist[3])/2 - enc_setPoint)*eKP);
    enc_motor[3] = enc_motor[1];*/
    
    /*for(int e=0; e<4; e++){
      if(enc_dist[e] < dist)
        enc_motor[e] = eTP - ((enc_dist[e] - enc_setPoint)*eKP); //Increase error on motor speed
      else
        enc_motor[e] = 0;//enc_motor[e] = ((dist - enc_dist[e])*eKP);
    }*/

    //if(vitima_quadrante && search_victim_adjust && !vitima_ja_encontrada){
    //  procurar_vitima();
    //  setMotor(TP,TP,TP,TP);
    //}
    //setMotor(enc_motor[0],enc_motor[1]+7,enc_motor[2],enc_motor[3]+7); //Inject speed
  }while(enc_dist[0]<dist || enc_dist[1]<dist || enc_dist[2]<dist || enc_dist[3]<dist);
}
//==//

//FORWARD W/ ENCODER//
void setMotor_encoder (uint8_t vel,  float dist) //Function to travel the robot using [P]ID on encoders
{
  float enc_setPoint; uint8_t contador_rampa=0;
  
  uint8_t enc_motor[4]; //setPoint of the PID
  float enc_dist[4] = {0,0,0,0}; //Will measure distance traveled in cm
  enc_read [0] = 0;  enc_read [1] = 0;
  enc_read [2] = 0;  enc_read [3] = 0; 
  enc_dist[0] = 0; enc_dist[1] = 0;
  enc_dist[2] = 0; enc_dist[3] = 0;//reset values
  //setMotor(eTP,eTP,eTP,eTP); delay(200);
  
  do{
    enc_read_SAVED[0] = enc_read[0]; enc_read_SAVED[1] = enc_read[1];
    enc_read_SAVED[2] = enc_read[2]; enc_read_SAVED[3] = enc_read[3];
    if(vitima_quadrante && search_victim_adjust && enc_dist[0] > 7){//5){// && !vitima_ja_encontrada){
      if(procurar_vitima()){
        enc_read[0] = enc_read_SAVED[0]; enc_read[1] = enc_read_SAVED[1];
        enc_read[2] = enc_read_SAVED[2]; enc_read[3] = enc_read_SAVED[3];
      }
      //setMotor(TP,TP,TP,TP);
    }

    if(digitalRead(pin_pushButton1)  || digitalRead(pin_pushButton2))
    {
      if(!(read_corQuad() < PRETO))
      {
        enc_read_SAVED[0] = enc_read[0]; enc_read_SAVED[1] = enc_read[1];
        enc_read_SAVED[2] = enc_read[2]; enc_read_SAVED[3] = enc_read[3];
        if(digitalRead(pin_pushButton1)){
          //mecanum(TP); delay(100);
          setMotor(-TP,TP,-TP,TP); delay_encoder('A', 40);//30);
          setMotor(-TP,-TP,-TP,-TP); delay_encoder('T', 1.5);
          setMotor(TP,-TP,TP,-TP); delay_encoder('A', 42);//30);
          setMotor(TP,TP,TP,TP); delay_encoder('F', 1.4);
        }
        else if(digitalRead(pin_pushButton2)){
          //mecanum(-TP); delay(100);
          setMotor(TP,-TP,TP,-TP); delay_encoder('A', 40);//30);
          setMotor(-TP,-TP,-TP,-TP); delay_encoder('T', 1.5);
          setMotor(-TP,TP,-TP,TP); delay_encoder('A', 42);//30);
          setMotor(TP,TP,TP,TP); delay_encoder('F', 1.4);
        }
        enc_read[0] = enc_read_SAVED[0]; enc_read[1] = enc_read_SAVED[1];
        enc_read[2] = enc_read_SAVED[2]; enc_read[3] = enc_read_SAVED[3];
      }
    }
    
    enc_setPoint=0;
    for(int e=0; e<4; e++){
      enc_dist[e] = (enc_read[e])/enc_const_fwd[e]; //Measure distance in cm traveled by each encoder
      enc_dist[e] = enc_dist[e];
      
      enc_setPoint += enc_dist[e];
      
      //if(enc_dist[e] < dist) enc_motor[e]=eTP; 
      //else enc_motor[e]=0; //LOG(enc_dist[e]); LOG("\t");
    }
    
    enc_setPoint /= 4;
    //LOGLN(" ");
    //LOGLN();
//    
//    enc_setPoint = (enc_dist[0]+enc_dist[1]+enc_dist[2]+enc_dist[3])/4; //Measure setPoint by setting the average value of the encoders
//    
//    for(int e=0; e<4; e++){
//      enc_motor[e] = eTP - ((enc_dist[e] - enc_setPoint)*eKP);
//    }
//    
    enc_motor[0] = vel - (((enc_dist[0]+enc_dist[2])/2 - enc_setPoint)*eKP);
    enc_motor[2] = enc_motor[0];
    enc_motor[1] = vel - (((enc_dist[1]+enc_dist[3])/2 - enc_setPoint)*eKP);
    enc_motor[3] = enc_motor[1];
    
    for(int e=0; e<4; e++){
      if(enc_dist[e] >= dist)
        enc_motor[e] = 0; //Increase error on motor speed
    }
   
//    for(int e=0; e<4; e++){
//      if(enc_dist[e] < dist)
//        enc_motor[e] = vel - ((enc_dist[e] - enc_setPoint)*eKP); //Increase error on motor speed
//      else
//        enc_motor[e] = 0;//enc_motor[e] = ((dist - enc_dist[e])*eKP);
//    }

    
//    print_info_data("encoders", 0,
//                  "m1", enc_read[0],
//                  "m2", enc_read[1],
//                  "m3", enc_read[2],
//                  "m4", enc_read[3],
//                  " ", 0);
    setMotor(enc_motor[0],enc_motor[1],enc_motor[2],enc_motor[3]); //Inject speed
    
//    if(readAccel('X') > rampa.goingDOWN && readAccel('X') < 5) contador_rampa++;
//    if(contador_rampa >= 20){//12){
//      if(analisar_rampa_descer()) return;
//    }
    
  }while((enc_dist[0]<dist || enc_dist[1]<dist || enc_dist[2]<dist || enc_dist[3]<dist) && !stop_fwd);
}
//==//

//BACK W/ ENCODER//
void setMotor_encoderBACK (int vel,  float dist) //Function to travel the robot using [P]ID on encoders
{
;
  if(vel > 0) vel *= -1;
  if(dist > 0) dist *= -1;
  float enc_setPoint;
  
  uint8_t enc_motor[4]; //setPoint of the PID
  float enc_dist[4] = {0,0,0,0}; //Will measure distance traveled in cm
  enc_read [0] = 0;  enc_read [1] = 0;
  enc_read [2] = 0;  enc_read [3] = 0; 
  enc_dist[0] = 0; enc_dist[1] = 0;
  enc_dist[2] = 0; enc_dist[3] = 0;//reset values
  //setMotor(eTP,eTP,eTP,eTP); delay(200);
  
  do{
    enc_setPoint=0;
    for(int e=0; e<4; e++){
      enc_dist[e] = (enc_read[e])/enc_const_fwd[e]; //Measure distance in cm traveled by each encoder
      enc_dist[e] = enc_dist[e];
      
      enc_setPoint += enc_dist[e];
    }
    
    enc_setPoint /= 4;
//    
    enc_motor[0] = vel - (((enc_dist[0]+enc_dist[2])/2 - enc_setPoint)*eKP);
    enc_motor[2] = enc_motor[0];
    enc_motor[1] = vel - (((enc_dist[1]+enc_dist[3])/2 - enc_setPoint)*eKP);
    enc_motor[3] = enc_motor[1];
    
    for(int e=0; e<4; e++){
      if(enc_dist[e] <= dist)
        enc_motor[e] = 0; //Increase error on motor speed
    }
    setMotor(enc_motor[0],enc_motor[1],enc_motor[2],enc_motor[3]); //Inject speed
  }while((enc_dist[0]>dist || enc_dist[1]>dist || enc_dist[2]>dist || enc_dist[3]>dist));
}
//==//

//////////ENCODER 1//////////
void delay_encoder1 (float dist_enc) //Inserir distancia em CM
{ //MOTOR EsqTras
  if(dist_enc > 0)
  {
    enc_read[0] = 100;
    tempo_enc = dist_enc * enc_const[0];
    while(enc_read[0] < tempo_enc+100){}
    enc_read[0] = 100;
  }
  else if(dist_enc < 0)
  {
    enc_read[0] = 30000;//100;
    tempo_enc = dist_enc * enc_const[0];
    while(enc_read[0] > tempo_enc+30000){}
    enc_read[0] = 100;
  }
}

float return_delay_encoder1 (float dist_enc) //Inserir distancia em CM
{ //MOTOR EsqTras
  if(dist_enc > 0)
  {
    enc_read[0] = 100;
    tempo_enc = dist_enc * enc_const[0];
    return tempo_enc+100;
  }
  else if(dist_enc < 0)
  {
    enc_read[0] = 30000;//100;
    tempo_enc = dist_enc * enc_const[0];
    return tempo_enc+30000;
  }
}

//ENCODER'1//
void doEncoder_m1_0A ()
{
  if(digitalRead(Encoder_m1_PinA) == HIGH)
  {
    if(digitalRead(Encoder_m1_PinB) == LOW)
      enc_read[0] = enc_read[0] + 1;	//CW

    else
      enc_read[0] = enc_read[0] - 1;	//CCW
  }

  else
  {
    if(digitalRead(Encoder_m1_PinB) == HIGH)
      enc_read[0] = enc_read[0] + 1;	//CW

    else
      enc_read[0] = enc_read[0] - 1;	//CCW
  }

 // LOG("I: "); LOG(enc_read[0]); LOG("  ");
}

void doEncoder_m1_0B ()
{
  if(digitalRead(Encoder_m1_PinB) == HIGH)
  {
    if(digitalRead(Encoder_m1_PinA) == HIGH)
      enc_read[0] = enc_read[0] + 1;	//CW

    else
      enc_read[0] = enc_read[0] - 1;	//CCW
  }

  else
  {
    if(digitalRead(Encoder_m1_PinA) == HIGH)
      enc_read[0] = enc_read[0] + 1;	//CW

    else
      enc_read[0] = enc_read[0] - 1;	//CCW
  }
  //LOG("I: "); LOG(enc_read[0]);
}
//==//

//ENCODER'2//
void doEncoder_m2_0A ()
{
  if(digitalRead(Encoder_m2_PinA) == HIGH)
  {
    if(digitalRead(Encoder_m2_PinB) == LOW)
      enc_read[1] = enc_read[1] + 1;	//CW

    else
      enc_read[1] = enc_read[1] - 1;	//CCW
  }

  else
  {
    if(digitalRead(Encoder_m2_PinB) == HIGH)
      enc_read[1] = enc_read[1] + 1;	//CW

    else
      enc_read[1] = enc_read[1] - 1;	//CCW
  }

//  LOG("II: "); LOG(enc_read[1]); LOG("  ");
}

void doEncoder_m2_0B ()
{
  if(digitalRead(Encoder_m2_PinB) == HIGH)
  {
    if(digitalRead(Encoder_m2_PinA) == HIGH)
      enc_read[1] = enc_read[1] + 1;	//CW

    else
      enc_read[1] = enc_read[1] - 1;	//CCW
  }

  else
  {
    if(digitalRead(Encoder_m2_PinA) == HIGH)
      enc_read[1] = enc_read[1] + 1;	//CW

    else
      enc_read[1] = enc_read[1] - 1;	//CCW
  }
  //LOG("II: "); LOGLN(enc_read[1]);
}
//==//

//ENCODER'3//
void doEncoder_m3_0A ()
{
  if(digitalRead(Encoder_m3_PinA) == HIGH)
  {
    if(digitalRead(Encoder_m3_PinB) == LOW)
      enc_read[2] = enc_read[2] + 1;	//CW

    else
      enc_read[2] = enc_read[2] - 1;	//CCW
  }

  else
  {
    if(digitalRead(Encoder_m3_PinB) == HIGH)
      enc_read[2] = enc_read[2] + 1;	//CW

    else
      enc_read[2] = enc_read[2] - 1;	//CCW
  }

  //LOG("III: "); LOG(enc_read[2]); LOG("  ");
}

void doEncoder_m3_0B ()
{
  if(digitalRead(Encoder_m3_PinB) == HIGH)
  {
    if(digitalRead(Encoder_m3_PinA) == HIGH)
      enc_read[2] = enc_read[2] + 1;	//CW

    else
      enc_read[2] = enc_read[2] - 1;	//CCW
  }

  else
  {
    if(digitalRead(Encoder_m3_PinA) == HIGH)
      enc_read[2] = enc_read[2] + 1;	//CW

    else
      enc_read[2] = enc_read[2] - 1;	//CCW
  }
  //LOG("III: "); LOGLN(enc_read[2]);
}
//==//

//ENCODER'4//
void doEncoder_m4_0A ()
{
  if(digitalRead(Encoder_m4_PinA) == HIGH)
  {
    if(digitalRead(Encoder_m4_PinB) == LOW)
      enc_read[3] = enc_read[3] + 1;	//CW

    else
      enc_read[3] = enc_read[3] - 1;	//CCW
  }

  else
  {
    if(digitalRead(Encoder_m4_PinB) == HIGH)
      enc_read[3] = enc_read[3] + 1;	//CW

    else
      enc_read[3] = enc_read[3] - 1;	//CCW
  }

 // LOG("IV: "); LOG(enc_read[3]); LOGLN("  ");
}

void doEncoder_m4_0B ()
{
  if(digitalRead(Encoder_m4_PinB) == HIGH)
  {
    if(digitalRead(Encoder_m4_PinA) == HIGH)
      enc_read[3] = enc_read[3] + 1;	//CW

    else
      enc_read[3] = enc_read[3] - 1;	//CCW
  }

  else
  {
    if(digitalRead(Encoder_m4_PinA) == HIGH)
      enc_read[3] = enc_read[3] + 1;	//CW

    else
      enc_read[3] = enc_read[3] - 1;	//CCW
  }
  //LOG("IV: "); LOGLN(enc_read[3]);
}
//==//
