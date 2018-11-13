#define RAMPA_UP__VEL_MIN 110 //160 //165//180
#define RAMPA_UP__VEL_MAX 170 //195 //200

#define RAMPA_DOWN__VEL_MIN 80
#define RAMPA_DOWN__VEL_MAX 100

//const int rampa_TP = 170;
const short int rampa_offset[2] = {480, 480};//295,335}; //4~5cm
const float rampa_KP = 0.5;//0.8; //0.045;//2;//0.0625;
const float rampa_KD = 0;//0.008;//0.015625;
float rampa_erro = 0;
float rampa_erroAnt[2] = {0,0};
float rampa_derivada = 0;
float turn[3] = {0,0,0};
float g,g_Ant=0,t=millis();

int contador_letra=0,letra,pZ_Ant;//1
bool add_pZ;

void analisar_rampa ()
{
  analisar_rampa_subir();
  analisar_rampa_descer();
}

void analisar_rampa_subir ()
{
  if(startof_rampUP()){ //readAccel('X') < rampa.goingUP){ //SUBIR
    executar_frente = false;
    LOG("\nramp::UP::init\n");
    print_info("going UP");

    add_pZ=false;
    
//    while(!map_readWall('T')){
//      maze[pZ][pY[pZ]][pX[pZ]] = ' ';
//      visited_places--;
//      mapear(0,-1);
//    }
//    mapear(0,1);

    //letra = 65+contador_letra;
    //while( ((char)letra) == 'S' ||((char)letra) == 'X'||((char)letra) == 'V'){contador++;letra= 65+contador_letra;}
    
    if(maze[pZ][pY[pZ]][pX[pZ]] == '.'){
    maze[pZ][pY[pZ]][pX[pZ]] = (char)(49+contador_letra);//'1'//65+contador_letra);//'U'; //visited_places++;
    //mapear(0,-1);
    //contador_letra++;
    add_pZ = true;
    pZ_Ant = pZ;
//    maze[pZ][pY[pZ]][pX[pZ]] = 'u';
    }

    setMotor(velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP); delay(400);

    //int contador_timer = millis();
    //unsigned int contRamp = 0;
    //bool contador = false;
    do{
      //setMotor(velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP);
      rampa_subir_BANGBANG();//PID();//encoder();
      procurar_vitima();

//      if(digitalRead(pin_pushButton1)  || digitalRead(pin_pushButton2))
//      {
//        if(digitalRead(pin_pushButton1)){
//          //mecanum(TP); delay(100);
//          parar(100);
//          setMotor(-velocidade.rampaUP,-velocidade.rampaUP,-velocidade.rampaUP,-velocidade.rampaUP);
//          delay(200);
//          parar(100);
//          setMotor(velocidade.rampaUP+30,0,velocidade.rampaUP+30,0);
//          delay(200);
//          //setMotor(TP,-TP,TP,-TP); delay_encoder('A', 15);
//          //setMotor(-TP,-TP,-TP,-TP); delay_encoder('T', 1.5);
//          //setMotor(TP,-TP,TP,-TP); delay_encoder('A', 30);
//          //setMotor(TP,TP,TP,TP); delay_encoder('F', 1.4);
//        }
//        else if(digitalRead(pin_pushButton2)){
//          //mecanum(-TP); delay(100);
//          parar(100);
//          setMotor(-velocidade.rampaUP,-velocidade.rampaUP,-velocidade.rampaUP,-velocidade.rampaUP);
//          delay(200);
//          parar(100);
//          setMotor(0,velocidade.rampaUP+30,0,velocidade.rampaUP+30);
//          delay(200);
//          //setMotor(-TP,TP,-TP,TP); delay_encoder('A', 15);
//          //setMotor(-TP,-TP,-TP,-TP); delay_encoder('T', 1.5);
//          //setMotor(-TP,TP,-TP,TP); delay_encoder('A', 30);
//          //setMotor(TP,TP,TP,TP); delay_encoder('F', 1.4);
//        }
//      }

      //if((millis() - contador_timer) > 600){
        //if(read_Ultra('D') > 16) contador = true;
        //contador_timer = millis();
      //}
      //endof_rampUP() ? contRamp++ : contRamp=0;
      LOG(endof_rampUP() ? " TRUE": " FALSE"); LOGLN();
    }while(!endof_rampUP()); //contRamp < 3); //!contador);// && readAccel('X') < rampa.finishUP);
    setMotor_encoder(velocidade.rampaUP, 5);
    //setMotor(velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP);
    
    mapear(2, 0); /////////////////////////
    if(add_pZ)
      pZ=49+contador_letra++; //pZ = !pZ;
    else pZ = ((int)maze[pZ][pY[pZ]][pX[pZ]])-48;
//    parar(1);
//    while(1)draw();
//    
    //if(!pZ)
    
    if(maze[pZ][pY[pZ]][pX[pZ]] == ' '){
    mapear(0,-1);
    maze[pZ][pY[pZ]][pX[pZ]] = (char)(48+pZ_Ant);//97+contador_letra);//'D'; 
    maze_traveled[pZ][pY[pZ]][pX[pZ]]++;
    
    mapear(0,1);
    }

    
//    maze[pZ][pY[pZ]][pX[pZ]] = 'd';

    //setMotor(velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP); delay(650);
    //ajustar_parede_ESQUERDA();
    //ajustar_parede_FRENTE(); ajustar_parede_FRENTE();
    LOG("ramp::UP::end\n");
  }
}

bool analisar_rampa_descer ()
{
  if(startof_rampDOWN()){ //readAccel('X') > rampa.goingDOWN){ //DESCER
    setMotor(velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN);
    executar_frente = false;
    LOG("\nramp::DOWN::init\n");
    print_info("going DOWN");

    add_pZ = false;
//    while(!map_readWall('T')){
//      maze[pZ][pY[pZ]][pX[pZ]] = ' ';
//      visited_places--;
//      mapear(0,-1);
//    }
    if(maze[pZ][pY[pZ]][pX[pZ]] == '.'){
////    mapear(0,1);
//    maze[pZ][pY[pZ]][pX[pZ]] = (char)(97+contador_letra);//'D'; //visited_places--;
//    mapear(0,-1);
//    //maze[pZ][pY[pZ]][pX[pZ]] = 'd';
maze[pZ][pY[pZ]][pX[pZ]] = (char)(49+contador_letra);//'1'//65+contador_letra);//'U'; //visited_places++;
    //mapear(0,-1);
    //contador_letra++;
    add_pZ = true;
    pZ_Ant = pZ;
    }

    //setMotor(velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN); delay(400);

    //int contador_timer = millis();
    unsigned int contRamp = 0;
    //bool contador = false;
    do{
      //setMotor(velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN);
      //parar(1000); setMotor(100,100,100,100);
      //rampa_descer_BANGBANG();//PID();
      rampa_descer_BANGBANG();//PID();
      procurar_vitima();

//      if(digitalRead(pin_pushButton1)  || digitalRead(pin_pushButton2))
//      {
//        if(digitalRead(pin_pushButton1)){
//          //mecanum(TP); delay(100);
//          parar(100);
//          setMotor(-velocidade.rampaUP,-velocidade.rampaUP,-velocidade.rampaUP,-velocidade.rampaUP);
//          delay(200);
//          parar(100);
//          setMotor(velocidade.rampaUP+30,0,velocidade.rampaUP+30,0);
//          delay(200);
//          //delay_encoder('F', 5);
//          //setMotor(-TP,-TP,-TP,-TP); delay_encoder('T', 1.5);
//          //setMotor(TP,-TP,TP,-TP); delay_encoder('A', 30);
//          //setMotor(TP,TP,TP,TP); delay_encoder('F', 1.4);
//        }
//        else if(digitalRead(pin_pushButton2)){
//          //mecanum(-TP); delay(100);
//          parar(100);
//          setMotor(-velocidade.rampaUP,-velocidade.rampaUP,-velocidade.rampaUP,-velocidade.rampaUP);
//          delay(200);
//          parar(100);
//          setMotor(0,velocidade.rampaUP+30,0,velocidade.rampaUP+30);
//          delay(200); 
//          //setMotor(-TP,TP,-TP,TP); delay_encoder('A', 5);
//          //setMotor(-TP,-TP,-TP,-TP); delay_encoder('T', 1.5);
//          //setMotor(-TP,TP,-TP,TP); delay_encoder('A', 30);
//          //setMotor(TP,TP,TP,TP); delay_encoder('F', 1.4);
//        }
//      }

//      if((millis() - contador_timer) > 500){
//        if(read_Ultra('E') > 16) contador = true;
//        contador_timer = millis();
//      }

      //endof_rampDOWN() ? contRamp++ : contRamp=0;
      
     LOG(endof_rampDOWN() ? " TRUE": " FALSE"); LOGLN();
    }while(!endof_rampDOWN()); //read_Ultra('E') < 16);// && readAccel('X') < rampa.finishUP);
    setMotor_encoder(velocidade.rampaUP, 5);
    //setMotor(velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN);
    
    mapear(2, 0);
    if(add_pZ)pZ=49+contador_letra++; //pZ = !pZ;
    else pZ = ((int)maze[pZ][pY[pZ]][pX[pZ]])-48;
    //pZ--;//pZ = !pZ;
    
    //if(!pZ)
    
    if(maze[pZ][pY[pZ]][pX[pZ]] == ' '){
//    mapear(0,-1);
//    maze[pZ][pY[pZ]][pX[pZ]] = (char)(65+contador_letra);//'U';
//    maze_traveled[pZ][pY[pZ]][pX[pZ]]++;
//    mapear(0,1);
    mapear(0,-1);
    maze[pZ][pY[pZ]][pX[pZ]] = (char)(48+pZ_Ant);//97+contador_letra);//'D'; 
    maze_traveled[pZ][pY[pZ]][pX[pZ]]++;
    
    mapear(0,1);

   // maze[pZ][pY[pZ]][pX[pZ]] = 'u';
   //contador_letra++;
    }
    
    //setMotor(velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN); delay(800);
//    ajustar_parede_DIREITA();
//    ajustar_parede_FRENTE(); ajustar_parede_FRENTE();
    LOG("ramp::DOWN::endt\n");
    return 1;
  }
  return 0;
}

void rampa_subir_PID ()
{
  //LOGLN("Hello");
  int rampa_motor[4] = {0,0,0,0};
  
  for(int ri=0; ri<2; ri++)
  {
    rampa_erro = read_Infra('E',ri+1) - rampa_offset[ri];
    //if(rampa_erro < 0) rampa_erro *= 3.5;
    rampa_derivada = rampa_erroAnt[ri] - rampa_erro;
    turn[ri] = rampa_erro*rampa_KP + rampa_derivada*rampa_KD;
    //if(turn[ri] < 0) turn[ri] *= ;
    rampa_erroAnt[ri] = rampa_erro;
  }
  
  turn[2] = (turn[0] + turn[1]); /// 2;

  rampa_motor[0] = velocidade.rampaUP+turn[2]; rampa_motor[1] = velocidade.rampaUP-turn[2];
  rampa_motor[2] = velocidade.rampaUP+turn[2]; rampa_motor[3] = velocidade.rampaUP-turn[2];

  for(int ri=0; ri<4; ri++)
  {
    //if(rampa_motor[ri] < velocidade.rampaUP) rampa_motor[ri] *= 0.95;
    
    if(rampa_motor[ri] < RAMPA_UP__VEL_MIN) rampa_motor[ri] = RAMPA_UP__VEL_MIN;//140;
    if(rampa_motor[ri] > RAMPA_UP__VEL_MAX) rampa_motor[ri] = RAMPA_UP__VEL_MAX;//200;
  }

  //LOG(rampa_motor[0]); LOG("\t");
  //LOG(rampa_motor[1]); LOG("\t");
  //LOG(rampa_motor[2]); LOG("\t");
  //LOGLN(turn[2]);//rampa_motor[3]);
  setMotor(rampa_motor[0], rampa_motor[1], rampa_motor[2], rampa_motor[3]);
  
//  print_info_data("going UP", 0,
//                  " ", turn[2],
//                  "INFRA1", rampa_motor[0],
//                  "INFRA2", rampa_motor[1],
//                  "motor1", rampa_motor[2],
//                  "motor2", rampa_motor[3]);
}

void rampa_descer_PID ()
{
  //LOGLN("Hello");
  int rampa_motor[4] = {0,0,0,0};
  
  for(int ri=0; ri<2; ri++)
  {
    rampa_erro = read_Infra('D',ri+1) - rampa_offset[ri];
    //if(rampa_erro < 0) rampa_erro *= 3.5;
    rampa_derivada = rampa_erroAnt[ri] - rampa_erro;
    turn[ri] = rampa_erro*rampa_KP + rampa_derivada*rampa_KD;
    //if(turn[ri] < 0) turn[ri] *= ;
    rampa_erroAnt[ri] = rampa_erro;
  }
  
  turn[2] = (turn[0] + turn[1]) / 2;

  rampa_motor[0] = velocidade.rampaUP-turn[2]; rampa_motor[1] = velocidade.rampaUP+turn[2];
  rampa_motor[2] = velocidade.rampaUP-turn[2]; rampa_motor[3] = velocidade.rampaUP+turn[2];

  for(int ri=0; ri<4; ri++)
  {
    //if(rampa_motor[ri] < velocidade.rampaUP) rampa_motor[ri] *= 0.8;
    
    if(rampa_motor[ri] < RAMPA_DOWN__VEL_MIN) rampa_motor[ri] = RAMPA_DOWN__VEL_MIN;//140;
    if(rampa_motor[ri] > RAMPA_DOWN__VEL_MAX) rampa_motor[ri] = RAMPA_DOWN__VEL_MAX;//200;
  }

  //LOG(rampa_motor[0]); LOG("\t");
  //LOG(rampa_motor[1]); LOG("\t");
  //LOG(rampa_motor[2]); LOG("\t");
  //LOGLN(turn[2]);//rampa_motor[3]);
  setMotor(rampa_motor[0], rampa_motor[1], rampa_motor[2], rampa_motor[3]);
  
//  print_info_data("going UP", 0,
//                  " ", turn[2],
//                  "INFRA1", rampa_motor[0],
//                  "INFRA2", rampa_motor[1],
//                  "motor1", rampa_motor[2],
//                  "motor2", rampa_motor[3]);
}

void rampa_subir_BANGBANG ()
{
  bool aa = ((read_Infra('E',1)-offsetWall.esq1) > (read_Infra('E',2) - offsetWall.esq2)) && (distance_wall('E')<dist_parede) && ((read_Infra('E',1)) > 100);//((read_Infra('E', 1)-offsetWall.esq1) > (read_Infra('E', 2)-offsetWall.esq2)) && read_Ultra('E')<5;
  bool ab = ((read_Infra('E',1)-offsetWall.esq1) < (read_Infra('E',2) - offsetWall.esq2)) && (distance_wall('E')<dist_parede) && ((read_Infra('E',1)) > 100);//((read_Infra('E', 1)-offsetWall.esq1) < (read_Infra('E', 2)-offsetWall.esq2))&& read_Ultra('E')>6;
  if(aa) {// ROBO\
    setMotor(0,0,0,0);
    setMotor(velocidade.rampaUP+30,velocidade.rampaUP,velocidade.rampaUP+30,velocidade.rampaUP);
}
 
  else if(ab){ // ROBO/
    setMotor(0,0,0,0);
    setMotor(velocidade.rampaUP,velocidade.rampaUP+30,velocidade.rampaUP,velocidade.rampaUP+30);
  }
  else {
    setMotor(0,0,0,0);
    setMotor(velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP);
  }
}
// YOU SHOT ME DOWN, BANG-BANG
// I HIT THE GROUND, BANG-BANG
// THAT AWFUL SOUND, BANG-BANG
// MY BABY SHOT ME DOWN...
//  |   |   |   |   |   |
//  V   V   V   V   V   V
void rampa_descer_BANGBANG ()
{
  bool aa = ((read_Infra('E',1)-offsetWall.esq1) > (read_Infra('E',2) - offsetWall.esq2)) && (distance_wall('E')<dist_parede) && ((read_Infra('E',1)) > 100);//((read_Infra('E', 1)-offsetWall.esq1) > (read_Infra('E', 2)-offsetWall.esq2)) && read_Ultra('E')<5;
  bool ab = ((read_Infra('E',1)-offsetWall.esq1) < (read_Infra('E',2) - offsetWall.esq2)) && (distance_wall('E')<dist_parede) && ((read_Infra('E',1)) > 100);//((read_Infra('E', 1)-offsetWall.esq1) < (read_Infra('E', 2)-offsetWall.esq2))&& read_Ultra('E')>6;
  if(aa) {// ROBO\
    setMotor(0,0,0,0);
    setMotor(velocidade.rampaDOWN+30,velocidade.rampaDOWN,velocidade.rampaDOWN+30,velocidade.rampaDOWN);
}
 
  else if(ab){ // ROBO/
    setMotor(0,0,0,0);
    setMotor(velocidade.rampaDOWN,velocidade.rampaDOWN+30,velocidade.rampaDOWN,velocidade.rampaDOWN+30);
  }
  else {
    setMotor(0,0,0,0);
    setMotor(velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN);
  }
}

void rampa_subir_ajuste ()
{
//  int contador = 0;
//  int timer = millis();
//
//  do {
//    if(read_Infra('E', 1) > offsetWall.esq1+D_LIMIT_T && read_Infra('E', 2) > offsetWall.esq2+D_LIMIT_T)
//      setMotor(velocidade.rampaDOWN+30,velocidade.rampaDOWN,velocidade.rampaDOWN+30,velocidade.rampaDOWN);
//    else if(read_Infra('E', 1) > offsetWall.esq1+D_LIMIT_T) //AFASTAR
//      setMotor(vAP, -vAP, vAP, -vAP);
//    else if(read_Infra('E', 2) > offsetWall.esq2+D_LIMIT_T) //AFASTAR
//      setMotor(-vAP, vAP, -vAP, vAP);
//
//    if(read_Infra('E', 1) < offsetWall.esq1-D_LIMIT_T && read_Infra('E', 2) < offsetWall.esq2-D_LIMIT_T)
//      mecanum(-vAP);
//    else if(read_Infra('E', 1) < offsetWall.esq1-D_LIMIT_T) //APROXIMAR
//      setMotor(-vAP, vAP, -vAP, vAP);
//    else if(read_Infra('E', 2) < offsetWall.esq2-D_LIMIT_T) //APROXIMAR
//      setMotor(vAP, -vAP, vAP, -vAP);
//
//    else{ // AJUSTADO
//      setMotor(20, 20, 20, 20); delay(5);
//      setMotor(-20,-20,-20,-20); delay(5);
//      setMotor(0, 0, 0, 0);
//      contador++;
//    }
//  } while (contador < contador_ajuste && (millis() - timer) < TIMER_MAX);
//  setMotor(20, 20, 20, 20); delay(5);
//  setMotor(-20,-20,-20,-20); delay(5);
//  setMotor(0, 0, 0, 0);
}





//====== new scope ======//

bool startof_rampUP () //einfahrt_rampUP ()
{
  if(readAccel('X') < rampa.goingUP){
    parar(180);
    if(readAccel('X') < rampa.goingUP)
      return true;
  }

  return false;
}

bool startof_rampDOWN () //einfahrt_rampUP ()
{
  if(readAccel('X') > rampa.goingDOWN){
    parar(180);
    if(readAccel('X') > rampa.goingDOWN)
      return true;
  }

  return false;
}

////====////

bool endof_rampUP ()
{
  //LOG("|readAccel('x')| = "); LOG(absolut(readAccel('x')));
  
  //return ( absolut(rampa.goingUP) <= (absolut(readAccel('x')) + absolut(readAccel('y'))) );

//  if(( absolut(readAccel('x') ) ) < 0.6){
//    parar(100);
//    if(( absolut(readAccel('x') ) ) < 0.6)
//      return true;//+ absolut(readAccel('y')
//  }

//   g = readGyroscope('X');
//   
//   g_Ant = g;
//
//   if(millis()-t >100){
//    t=millis();
//    if(absolut(g-g_Ant)>25) return true;
//   }

  read_distance_wall();
  if(distance_wall('E') > 16 || distance_wall('E') > 16){
    parar(180); read_distance_wall();
    if(distance_wall('E') > 16 || distance_wall('E') > 16)
      return true;
  }
   
   return false;
}

bool endof_rampDOWN ()
{
  //return ( absolut(rampa.goingDOWN) <= (absolut(readAccel('x')) + absolut(readAccel('y'))) );

//  if(( absolut(readAccel('x') ) ) < 0.6){
//    parar(100);
//    if(( absolut(readAccel('x') ) ) < 0.6)
//      return true;//+ absolut(readAccel('y')
//  }
//  return false;

  read_distance_wall();
  if(distance_wall('E') > 16 || distance_wall('E') > 16){
    parar(180); read_distance_wall();
    if(distance_wall('E') > 16 || distance_wall('E') > 16)
      return true;
  }
   
   return false;
}

//====//

void rampa_subir_encoder ()
{
  setMotor_encoder(velocidade.rampaUP, 1);
}

void rampa_descer_encoder ()
{
  setMotor_encoder(velocidade.rampaDOWN, 1);
}

