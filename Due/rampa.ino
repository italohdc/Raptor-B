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
    
    if(maze[pZ][pY[pZ]][pX[pZ]] == '.'){
      maze[pZ][pY[pZ]][pX[pZ]] = (char)(49+contador_letra);//'1'//65+contador_letra);//'U'; //visited_places++;
      add_pZ = true;
      pZ_Ant = pZ;
    }

    setMotor(velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP); delay(400);

    do{
      rampa_subir_BANGBANG();//PID();//encoder();
      procurar_vitima();

      LOG(endof_rampUP() ? " TRUE": " FALSE"); LOGLN();
    }while(!endof_rampUP()); //contRamp < 3); //!contador);// && readAccel('X') < rampa.finishUP);
    setMotor_encoder(velocidade.rampaUP, 5);
    
    mapear(2, 0); /////////////////////////
    if(add_pZ)
      pZ=49+contador_letra++; //pZ = !pZ;
    else pZ = ((int)maze[pZ][pY[pZ]][pX[pZ]])-48;
    
    if(maze[pZ][pY[pZ]][pX[pZ]] == ' '){
      mapear(0,-1);
      maze[pZ][pY[pZ]][pX[pZ]] = (char)(48+pZ_Ant);//97+contador_letra);//'D'; 
      maze_traveled[pZ][pY[pZ]][pX[pZ]]++;
      
      mapear(0,1);
    }

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
    if(maze[pZ][pY[pZ]][pX[pZ]] == '.'){
      maze[pZ][pY[pZ]][pX[pZ]] = (char)(49+contador_letra);//'1'//65+contador_letra);//'U'; //visited_places++;
      add_pZ = true;
      pZ_Ant = pZ;
    }

    unsigned int contRamp = 0;
    do{
      rampa_descer_BANGBANG();//PID();
      procurar_vitima();
      
      LOG(endof_rampDOWN() ? " TRUE": " FALSE"); LOGLN();
    }while(!endof_rampDOWN()); //read_Ultra('E') < 16);// && readAccel('X') < rampa.finishUP);
    setMotor_encoder(velocidade.rampaUP, 5);
    
    mapear(2, 0);
    if(add_pZ)pZ=49+contador_letra++; //pZ = !pZ;
    else pZ = ((int)maze[pZ][pY[pZ]][pX[pZ]])-48;
    
    if(maze[pZ][pY[pZ]][pX[pZ]] == ' '){
      mapear(0,-1);
      maze[pZ][pY[pZ]][pX[pZ]] = (char)(48+pZ_Ant);//97+contador_letra);//'D'; 
      maze_traveled[pZ][pY[pZ]][pX[pZ]]++;
      
      mapear(0,1);
    }
    
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
    rampa_derivada = rampa_erroAnt[ri] - rampa_erro;
    turn[ri] = rampa_erro*rampa_KP + rampa_derivada*rampa_KD;
    rampa_erroAnt[ri] = rampa_erro;
  }
  
  turn[2] = (turn[0] + turn[1]); /// 2;

  rampa_motor[0] = velocidade.rampaUP+turn[2]; rampa_motor[1] = velocidade.rampaUP-turn[2];
  rampa_motor[2] = velocidade.rampaUP+turn[2]; rampa_motor[3] = velocidade.rampaUP-turn[2];

  for(int ri=0; ri<4; ri++)
  {
    if(rampa_motor[ri] < RAMPA_UP__VEL_MIN) rampa_motor[ri] = RAMPA_UP__VEL_MIN;//140;
    if(rampa_motor[ri] > RAMPA_UP__VEL_MAX) rampa_motor[ri] = RAMPA_UP__VEL_MAX;//200;
  }

  setMotor(rampa_motor[0], rampa_motor[1], rampa_motor[2], rampa_motor[3]);
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
    if(rampa_motor[ri] < RAMPA_DOWN__VEL_MIN) rampa_motor[ri] = RAMPA_DOWN__VEL_MIN;//140;
    if(rampa_motor[ri] > RAMPA_DOWN__VEL_MAX) rampa_motor[ri] = RAMPA_DOWN__VEL_MAX;//200;
  }

  setMotor(rampa_motor[0], rampa_motor[1], rampa_motor[2], rampa_motor[3]);
  
}

void rampa_subir_BANGBANG ()
{
  bool aa = ((read_Infra('E',1)-offsetWall.esq1) > (read_Infra('E',2) - offsetWall.esq2)) && (distance_wall('E')<dist_parede) && ((read_Infra('E',1)) > 100);//((read_Infra('E', 1)-offsetWall.esq1) > (read_Infra('E', 2)-offsetWall.esq2)) && read_Ultra('E')<5;
  bool ab = ((read_Infra('E',1)-offsetWall.esq1) < (read_Infra('E',2) - offsetWall.esq2)) && (distance_wall('E')<dist_parede) && ((read_Infra('E',1)) > 100);//((read_Infra('E', 1)-offsetWall.esq1) < (read_Infra('E', 2)-offsetWall.esq2))&& read_Ultra('E')>6;
  if(aa) {// ROBO DOWN
    setMotor(0,0,0,0);
    setMotor(velocidade.rampaUP+30,velocidade.rampaUP,velocidade.rampaUP+30,velocidade.rampaUP);
}
 
  else if(ab){ // ROBO UP
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
  if(aa) {// ROBO DOWN
    setMotor(0,0,0,0);
    setMotor(velocidade.rampaDOWN+30,velocidade.rampaDOWN,velocidade.rampaDOWN+30,velocidade.rampaDOWN);
}
 
  else if(ab){ // ROBO UP
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

