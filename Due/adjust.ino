#define D_LIMIT 6//8//12
#define D_LIMIT_T 16

#define TIMER_MAX 680//2000
byte vAP = 70;//90; //100;
const uint8_t vAP_simples = 60;

int contador_ajuste = 10;//12;//20; //18;//25;//100;
const int d_wall_adjust = 280;

int esq = 0;
int dir = 0;
int tras = 0;
int fwd = 0;

void analisar_ajuste ()
{
  read_distance_wall();
  esq =  map_readWall('E');//distance_wall('E');
  dir = map_readWall('D');//distance_wall('D');
  //read_ultra_individual('T');
  tras = distance_wall('T') < dist_parede; //map_readWall('T');//distance_wall('T');
  fwd = map_readWall('F');//distance_wall('F');
  
  if((fwd || tras) && esq &&
     maze[pZ][pY[pZ]][pX[pZ]] != 'D' &&
     maze[pZ][pY[pZ]][pX[pZ]] != 'd' &&
     maze[pZ][pY[pZ]][pX[pZ]] != 'U' &&
     maze[pZ][pY[pZ]][pX[pZ]] != 'u') ajustar_parede_ESQUERDA();

  //if((!fwd && !tras) && esq) ajustar_parede_ESQ_simples();
     
  if((fwd || tras) && dir &&
     maze[pZ][pY[pZ]][pX[pZ]] != 'D' &&
     maze[pZ][pY[pZ]][pX[pZ]] != 'd' &&
     maze[pZ][pY[pZ]][pX[pZ]] != 'U' &&
     maze[pZ][pY[pZ]][pX[pZ]] != 'u') ajustar_parede_DIREITA();

  //if((!fwd && !tras) && dir) ajustar_parede_DIR_simples();
  
  if(tras) ajustar_parede_TRAS();
  if(fwd) ajustar_parede_FRENTE();
}

void ajustar_parede_FRENTE ()
{
  int contador = 0;
  int timer = millis();
  //setMotor(-100, -100, -100, -100);
  //delay(120); parar(25);

  do{
    read_distance_wall();
   //read_ultra_individual('F');

    if (distance_wall('F') > 12) //APROXIMAR C/ ULTRA
      setMotor(vAP, vAP, vAP, vAP);
    else if (distance_wall('F') < 5) //AFASTAR C/ ULTRA
      setMotor(-vAP, -vAP, -vAP, -vAP);
    else
    {
      if(read_Infra('F', 1) < 100) { // S/ PAREDE
        mecanum(vAP);
        delay(100);
      }
      else if(read_Infra('F', 2) < 100) { // S/ PAREDE
        mecanum(-vAP);
       delay(100);
      }
      
      else if(read_Infra('F', 1) > offsetWall.frente1+D_LIMIT && read_Infra('F', 2) > offsetWall.frente2+D_LIMIT)
        setMotor(-vAP, -vAP, -vAP, -vAP);
      else if(read_Infra('F', 1) > offsetWall.frente1+D_LIMIT) //AFASTAR
        setMotor(-vAP, vAP, -vAP, vAP);
      else if(read_Infra('F', 2) > offsetWall.frente2+D_LIMIT) //AFASTAR
        setMotor(vAP, -vAP, vAP, -vAP);

      if(read_Infra('F', 1) < offsetWall.frente1-D_LIMIT && read_Infra('F', 2) < offsetWall.frente2-D_LIMIT)
        setMotor(vAP, vAP, vAP, vAP);
      else if(read_Infra('F', 1) < offsetWall.frente1-D_LIMIT) //APROXIMAR
        setMotor(vAP, -vAP, vAP, -vAP);
      else if(read_Infra('F', 2) < offsetWall.frente2-D_LIMIT) //APROXIMAR
        setMotor(-vAP, vAP, -vAP, vAP);

      else{ // AJUSTADO
        setMotor(20, 20, 20, 20); delay(5);
        setMotor(-20,-20,-20,-20); delay(5);
        setMotor(0, 0, 0, 0);
        contador++;
      }
    }
    if(search_victim_adjust) procurar_vitima();
  } while (contador < contador_ajuste && (millis() - timer) < TIMER_MAX);
  setMotor(20, 20, 20, 20); delay(5);
  setMotor(-20,-20,-20,-20); delay(5);
  setMotor(0, 0, 0, 0);
}

void ajustar_parede_TRAS ()
{
  int contador = 0;
  int timer = millis();
  //setMotor(100, 100, 100, 100);
  //delay(120); parar(25);

  do {
     read_distance_wall();
   //read_ultra_individual('T');

    if (distance_wall('T') > 12) //APROXIMAR C/ ULTRA
      setMotor(-vAP, -vAP, -vAP, -vAP);
    else if (distance_wall('T') < 5) //AFASTAR C/ ULTRA
      setMotor(vAP, vAP, vAP, vAP);
    else
    {
      if(read_Infra('T', 1) < 100) { // S/ PAREDE
        mecanum(vAP);
        delay(100);
      }
      else if(read_Infra('T', 2) < 100) { // S/ PAREDE
        mecanum(-vAP);
       delay(100);
      }
      
      else if(read_Infra('T', 1) > offsetWall.tras1+D_LIMIT+15 && read_Infra('T', 2) > offsetWall.tras2+D_LIMIT+15)
        setMotor(vAP, vAP, vAP, vAP);
      else if(read_Infra('T', 1) > offsetWall.tras1+D_LIMIT+15) //AFASTAR
        setMotor(vAP, -vAP, vAP, -vAP);
      else if(read_Infra('T', 2) > offsetWall.tras2+D_LIMIT+15) //AFASTAR
        setMotor(-vAP, vAP, -vAP, vAP);

      if(read_Infra('T', 1) < offsetWall.tras1-D_LIMIT+15 && read_Infra('T', 2) < offsetWall.tras2-D_LIMIT+15)
        setMotor(-vAP, -vAP, -vAP, -vAP);
      else if(read_Infra('T', 1) < offsetWall.tras1-D_LIMIT+15) //APROXIMAR
        setMotor(-vAP, vAP, -vAP, vAP);
      else if(read_Infra('T', 2) < offsetWall.tras2-D_LIMIT+15) //APROXIMAR
        setMotor(vAP, -vAP, vAP, -vAP);

      else{ // AJUSTADO
        setMotor(20, 20, 20, 20); delay(5);
        setMotor(-20,-20,-20,-20); delay(5);
        setMotor(0, 0, 0, 0);
        contador++;
      }
    }
    //if(search_victim_adjust) procurar_vitima();
  } while (contador < contador_ajuste && (millis() - timer) < TIMER_MAX);
  setMotor(20, 20, 20, 20); delay(5);
  setMotor(-20,-20,-20,-20); delay(5);
  setMotor(0, 0, 0, 0);

  if(maze[pZ][pY[pZ]][pX[pZ]] == 'd' || maze[pZ][pY[pZ]][pX[pZ]] == 'D'){
    setMotor_encoder(TP, 2);//1.5);
   parar(1000);}
  if(maze[pZ][pY[pZ]][pX[pZ]] == 'u' || maze[pZ][pY[pZ]][pX[pZ]] == 'U'){
    setMotor_encoder(TP, 2);//1.5);
    parar(1000);}
}

void ajustar_parede_DIREITA ()
{
  int contador = 0;
  int timer = millis();

  do {
     read_distance_wall();
   //read_ultra_individual('D');

    if (distance_wall('D') > 12) //APROXIMAR C/ ULTRA
      mecanum(vAP);
    else if (distance_wall('D') < 5) //AFASTAR C/ ULTRA
      mecanum(-vAP);
    else
    {
      if(read_Infra('D', 1) < 100) { // S/ PAREDE
        setMotor(-vAP, -vAP, -vAP, -vAP);
        delay(100);
      }
      else if(read_Infra('D', 2) < 100) { // S/ PAREDE
        setMotor(vAP, vAP, vAP, vAP);
        delay(100);
      }
      
      else if(read_Infra('D', 1) > offsetWall.dir1+D_LIMIT_T && read_Infra('D', 2) > offsetWall.dir2+D_LIMIT_T)
        mecanum(-vAP);
      else if(read_Infra('D', 1) > offsetWall.dir1+D_LIMIT_T) //AFASTAR
        setMotor(-vAP, vAP, -vAP, vAP);
      else if(read_Infra('D', 2) > offsetWall.dir2+D_LIMIT_T) //AFASTAR
        setMotor(vAP, -vAP, vAP, -vAP);

      if(read_Infra('D', 1) < offsetWall.dir1-D_LIMIT_T && read_Infra('D', 2) < offsetWall.dir2-D_LIMIT_T)
        mecanum(vAP);
      else if(read_Infra('D', 1) < offsetWall.dir1-D_LIMIT_T) //APROXIMAR
        setMotor(vAP, -vAP, vAP, -vAP);
      else if(read_Infra('D', 2) < offsetWall.dir2-D_LIMIT_T) //APROXIMAR
        setMotor(-vAP, vAP, -vAP, vAP);

      else{ // AJUSTADO
        setMotor(20, 20, 20, 20); delay(5);
        setMotor(-20,-20,-20,-20); delay(5);
        setMotor(0, 0, 0, 0);
        contador++;
      }
    }
    //if(search_victim_adjust) procurar_vitima();
  } while (contador < contador_ajuste && (millis() - timer) < TIMER_MAX);
  setMotor(20, 20, 20, 20); delay(5);
  setMotor(-20,-20,-20,-20); delay(5);
  setMotor(0, 0, 0, 0);
}

void ajustar_parede_ESQUERDA ()
{
  int contador = 0;
  int timer = millis();

  do {
     read_distance_wall();
   //read_ultra_individual('E');

    if (distance_wall('E') > 12) //APROXIMAR C/ ULTRA
      mecanum(-vAP);
    else if (distance_wall('E') < 5) //AFASTAR C/ ULTRA
      mecanum(vAP);
    else
    {
      if(read_Infra('E', 1) < 100) { // S/ PAREDE
        setMotor(-vAP, -vAP, -vAP, -vAP);
        delay(100);
      }
      else if(read_Infra('E', 2) < 100) { // S/ PAREDE
        setMotor(vAP, vAP, vAP, vAP);
        delay(100);
      }
      
      else if(read_Infra('E', 1) > offsetWall.esq1+D_LIMIT_T && read_Infra('E', 2) > offsetWall.esq2+D_LIMIT_T)
        mecanum(vAP);
      else if(read_Infra('E', 1) > offsetWall.esq1+D_LIMIT_T) //AFASTAR
        setMotor(vAP, -vAP, vAP, -vAP);
      else if(read_Infra('E', 2) > offsetWall.esq2+D_LIMIT_T) //AFASTAR
        setMotor(-vAP, vAP, -vAP, vAP);

      if(read_Infra('E', 1) < offsetWall.esq1-D_LIMIT_T && read_Infra('E', 2) < offsetWall.esq2-D_LIMIT_T)
        mecanum(-vAP);
      else if(read_Infra('E', 1) < offsetWall.esq1-D_LIMIT_T) //APROXIMAR
        setMotor(-vAP, vAP, -vAP, vAP);
      else if(read_Infra('E', 2) < offsetWall.esq2-D_LIMIT_T) //APROXIMAR
        setMotor(vAP, -vAP, vAP, -vAP);

      else{ // AJUSTADO
        setMotor(20, 20, 20, 20); delay(5);
        setMotor(-20,-20,-20,-20); delay(5);
        setMotor(0, 0, 0, 0);
        contador++;
      }
    }
    //if(search_victim_adjust) procurar_vitima();
  } while (contador < contador_ajuste && (millis() - timer) < TIMER_MAX);
  setMotor(20, 20, 20, 20); delay(5);
  setMotor(-20,-20,-20,-20); delay(5);
  setMotor(0, 0, 0, 0);
}

//AJUSTE SIMPLES//

void ajustar_parede_DIR_simples ()
{
  int contador = 0;
  int timer = millis()+1000;
  int _erro[2];

  do {
    _erro[0] = read_Infra('D', 1)-offsetWall.dir1; _erro[1] = read_Infra('D', 2)-offsetWall.dir2;
    
    if(read_Infra('D', 1) < 100) { // S/ PAREDE
      setMotor(-vAP_simples, -vAP_simples, -vAP_simples, -vAP_simples);
      delay(100);
    }
    else if(read_Infra('D', 2) < 100) { // S/ PAREDE
      setMotor(vAP_simples, vAP_simples, vAP_simples, vAP_simples);
      delay(100);
    }
    
    else if( _erro[0] > (_erro[1]-(D_LIMIT_T*2)) )
      setMotor(-vAP_simples, vAP_simples, -vAP_simples, vAP_simples);

    else if( (_erro[0]-(D_LIMIT_T*2)) < _erro[1] )
      setMotor(vAP_simples, -vAP_simples, vAP_simples, -vAP_simples);

    else{ // AJUSTADO
      setMotor(20, 20, 20, 20); delay(5);
      setMotor(-20,-20,-20,-20); delay(5);
      setMotor(0, 0, 0, 0);
      contador++;
    }
    //if(search_victim_adjust) procurar_vitima();
  } while (contador < contador_ajuste && (millis() - timer) < TIMER_MAX);
  setMotor(20, 20, 20, 20); delay(5);
  setMotor(-20,-20,-20,-20); delay(5);
  setMotor(0, 0, 0, 0);
}

void ajustar_parede_ESQ_simples ()
{
  int contador = 0;
  int timer = millis()+1000;
  int _erro[2];

  do {
    _erro[0] = read_Infra('E', 1)-offsetWall.esq1; _erro[1] = read_Infra('E', 2)-offsetWall.esq2;
    
//    if(read_Infra('E', 1) < 100) { // S/ PAREDE
//      setMotor(-vAP_simples, -vAP_simples, -vAP_simples, -vAP_simples);
//      delay(100);
//    }
//    else if(read_Infra('E', 2) < 100) { // S/ PAREDE
//      setMotor(vAP_simples, vAP_simples, vAP_simples, vAP_simples);
//      delay(100);
//    }
    
    if( _erro[0] > (_erro[1]-(D_LIMIT_T*2)) )
      setMotor(vAP_simples, -vAP_simples, vAP_simples, -vAP_simples);

    else if( (_erro[0]-(D_LIMIT_T*2)) < _erro[1] )
      setMotor(-vAP_simples, vAP_simples, -vAP_simples, vAP_simples);

    else{ // AJUSTADO
      setMotor(20, 20, 20, 20); delay(5);
      setMotor(-20,-20,-20,-20); delay(5);
      setMotor(0, 0, 0, 0);
      contador++;
    }
    //if(search_victim_adjust) procurar_vitima();
  } while (contador < contador_ajuste && (millis() - timer) < TIMER_MAX);
  setMotor(20, 20, 20, 20); delay(5);
  setMotor(-20,-20,-20,-20); delay(5);
  setMotor(0, 0, 0, 0);
}
