void tremaux ()
{
  setMotor(0,0,0,0);
  LOG("tremaux::init\n"); draw();
  LOG(maze[pZ][pY[pZ]][pX[pZ]]);
  LOG("/"); LOG(maze[pZ][pY[pZ]][pX[pZ]]);
  
  if(maze[pZ][pY[pZ]][pX[pZ]] == ' '){
    visited_places++;
    maze[pZ][pY[pZ]][pX[pZ]] = '.';
  }
  
  search_victim_adjust = false;
  vitima_quadrante = false;
  vitima_ja_encontrada = false;
  stop_fwd = false;
  read_distance_wall_check();
  
  mapearQuad();

  //mapearQuad2();
  
  delete_path();
  compare_way();
  executar_frente = true;

  LOG("\n X:"); LOG(pX[pZ]);
  LOG("\t Y:"); LOG(pY[pZ]);
  LOG("\t Z:"); LOG(pZ);

  LOG("\nCorQuad: "); LOG(read_corQuad());
  
  LOG("\nUltra: F:"); LOG(distance_wall('F'));
  LOG("cm\tT:"); LOG(distance_wall('T'));
  LOG("cm\tE:"); LOG(distance_wall('E'));
  LOG("cm\tD:"); LOG(distance_wall('D'));
  LOG("cm\n:");

  LOG("\nInfra:\n");
  LOG("F1:"); LOG(read_Infra('F', 1));
  LOG("\tT1:"); LOG(read_Infra('T', 1));
  LOG("\tE1:"); LOG(read_Infra('E', 1));
  LOG("\tD1:"); LOG(read_Infra('D', 1));
  LOG("\nF2:"); LOG(read_Infra('F', 2));
  LOG("\tT2:"); LOG(read_Infra('T', 2));
  LOG("\tE2:"); LOG(read_Infra('E', 2));
  LOG("\tD2:"); LOG(read_Infra('D', 2));

  /*print_info_data("compare_way", compared_way (),
                  "WF", map_readTravel('F'),
                  "WE", map_readTravel('E'),
                  "WD", map_readTravel('D'),
                  "WT", map_readTravel('T'),
                  " ", 0); //delay(5);
  //do{}while(read_button_MENU() == 0);
  //do{}while(read_button_MENU() != 0);
  
  print_info_data("map_readWall", 0,
                  "WF", map_readWall('F'),
                  "WE", map_readWall('E'),
                  "WD", map_readWall('D'),
                  "WT", map_readWall('T'),
                  " ", 0); //delay(5);
  //do{}while(read_button_MENU() == 0);
  //do{}while(read_button_MENU() != 0);

  print_info_char("map_readQuad", 0,
                  "WF", map_readQuad('F'),
                  "WE", map_readQuad('E'),
                  "WD", map_readQuad('D'),
                  "WT", map_readQuad('T'),
                  " ", 0); //delay(5);
  //do{}while(read_button_MENU() == 0);
  //do{}while(read_button_MENU() != 0);*/
  
  if(PRINT_MAZE) draw();

//  if(victims_found >= 4 && maze[pZ][pY[pZ]][pX[pZ]] == 'S')
//  {
//    setMotor(0,0,0,0);
//    print_info("END"); int _cont_stop = millis(); 
//    do{
//      print_int("END", millis()-_cont_stop);
//    }while((millis()-_cont_stop) < 10000);//8500);
//  }
  
  //LOGLN(map_readQuad('F'));

  //ACCEL
  if(readAccel('X') < rampa.goingUP || readAccel('X') > rampa.goingDOWN)
  {
    parar(100);//165);
    if(readAccel('X') < rampa.goingUP || readAccel('X') > rampa.goingDOWN){
      parar(120);//200);
      analisar_rampa();
    }
  }

//  else if(distance_wall('D') > 200 && distance_wall('F') < 15
//    && read_Infra('D',1)<300 && read_Infra('D',2)<300)
//  {
//    parede_falsa_DIR();
//    parar(tempo);
//  }
//  else if(distance_wall('E') > 200 && distance_wall('F') < 15
//    && read_Infra('E',1)<300 && read_Infra('E',2)<300)
//  {
//    parede_falsa_ESQ();
//    parar(tempo);
//  }
  
  //QUADRADO PRETO
  else if(read_corQuad() < PRETO)//80)//150)
  {
    print_info("PRETO");
    maze[pZ][pY[pZ]][pX[pZ]] = '#';
    mapear(0,-1);
    quadrante_re();
    quadrante_tras();
    executar_frente = false;
    mapear(2, 0);
    maze_traveled[pZ][pY[pZ]][pX[pZ]]--;
  }
  
  //DIREITA//
  else if(distance_wall('D') > dist_parede &&// distance_wall('D') < 200 &&
     map_readQuad('D') != '#' && map_readQuad('D') != 'X' && map_readTravel('D') <= compared_way())
  {
    //print_info("DIREITA");
    analisar_ajuste();
    mapear(1,0);
    
    quadrante_direita();
    search_victim_adjust = true;
    analisar_ajuste();
   // mapear(0,1);
  }

  /////FRENTE/////
  else if(distance_wall('F') > dist_parede &&// distance_wall('F') < 200 &&
          map_readQuad('F') != '#' && map_readQuad('F') != 'X' && map_readTravel('F') <= compared_way())
  {
    search_victim_adjust = true;
    
    if(distance_wall('E') > dist_parede)
    if(map_readTravel('E') == 0)
    if(map_readQuad('E') == ' ')
    if(map_readQuad('E') != '#' && map_readQuad('E') != 'X')
    {
      quadrante_esquerda();
      if(read_Ultra('T') < dist_parede) ajustar_parede_TRAS();

      mapear(-1,1);
      maze[pZ][pY[pZ]][pX[pZ]] = '.';
      visited_places++;
      
      vitima_quadrante = true;
      quadrante_frente();
      parar(tempo);
      procurar_vitima();

      read_distance_wall();
      mapearQuad();
      maze_traveled[pZ][pY[pZ]][pX[pZ]]--;
      mapear(0,-1); mapear(1,0);

      stop_fwd = false;
      vitima_quadrante = false;
      vitima_ja_encontrada = false;

      quadrante_re();
      if(read_Ultra('T') < dist_parede) ajustar_parede_TRAS();
      quadrante_direita();

      read_distance_wall();
      //mapearQuad();
      maze_traveled[pZ][pY[pZ]][pX[pZ]]--;
    }
    
    //print_info("FRENTE");
   // mapear(0,1);
    //read_distance_wall();

    /*if(distance_wall('E') > dist_parede && distance_wall('E') < 200)
    {
      //ajustar_parede_DIREITA();
      quadrante_esquerda();
      //ajustar_parede_TRAS();
      quadrante_frente();
      
      quadrante_re();

      quadrante_direita();
    }*/
  }
  
  /////ESQUERDA/////
  else if(distance_wall('E') > dist_parede &&// distance_wall('E') < 200 &&
          map_readQuad('E') != '#' && map_readQuad('E') != 'X' && map_readTravel('E') <= compared_way())
  {
    //print_info("ESQUERDA");
    analisar_ajuste();
    mapear(-1,0);
    
    quadrante_esquerda();
    search_victim_adjust = true;
    analisar_ajuste();
    //mapear(0,1);
  }

  /////VOLTAR/////
  else
  {
    //print_info("VOLTAR");
    //mapear(0,-1);
    analisar_ajuste();
//    if(map_readWall('E') && map_readWall('D') && map_readWall('F'))
//    {
//      
//    }
    
    if(map_readWall('F')){
      search_victim_adjust = false;//true;
      ajustar_parede_FRENTE();  
      //procurar_vitima();//search_victim_adjust = false;
    }
    
    quadrante_tras();//re();
    mapear(2,0);
    //executar_frente = false;
    
    analisar_ajuste();
    //mapear(0,1);
   
  }
  
//  print_info_data(" ", 0,
//                  "visited_places", visited_places,
//                  "min_visited", min_visited,
//                  " ", 0,
//                  "victims_found", victims_found,
//                  "MAX", MAX_VICTIMS);
                  
  if(executar_frente)
  {
    mapear(0,1);
    //print_info("NEXT");
    vitima_quadrante = true;
    quadrante_frente();
    //parar(100);//
    vitima_quadrante = false;
  }

  procurar_vitima();
  
/*  else{
    analogWrite(pin_LED, 180);
    delay(120);
    digitalWrite(pin_LED,LOW);
    delay(120);
    analogWrite(pin_LED, 180);
    delay(120);
    digitalWrite(pin_LED,LOW);
  }*/
  LOG("\ntremaux::end\n\n");
}

void compare_way ()
{
  if(map_readWall('F') == false && map_readQuad('F') != '#' && map_readQuad('F') != 'X')
    way_value=map_readTravel('F');
  else if(map_readWall('T') == false && map_readQuad('T') != '#' && map_readQuad('T') != 'X')
    way_value=map_readTravel('T');
  else if(map_readWall('E') == false && map_readQuad('E') != '#' && map_readQuad('E') != 'X')
    way_value=map_readTravel('E');
  else if(map_readWall('D') == false && map_readQuad('D') != '#' && map_readQuad('D') != 'X')
    way_value=map_readTravel('D');
  else
    way_value=0;
 
  if(way_value > map_readTravel('F') && !map_readWall('F') && map_readQuad('F') != '#' && map_readQuad('F') != 'X')
    way_value=map_readTravel('F');
  if(way_value > map_readTravel('T') && !map_readWall('T') && map_readQuad('T') != '#' && map_readQuad('T') != 'X')
    way_value=map_readTravel('T');
  if(way_value > map_readTravel('E') && !map_readWall('E') && map_readQuad('E') != '#' && map_readQuad('E') != 'X')
    way_value=map_readTravel('E');
  if(way_value > map_readTravel('D') && !map_readWall('D') && map_readQuad('D') != '#' && map_readQuad('D') != 'X')
    way_value=map_readTravel('D');
}

int compared_way ()
{
  return way_value;
}

void read_distance_wall_check()
{
  int e1=0, d1=0, t1=0, f1=0;
  int e2=0, d2=0, t2=0, f2=0;
  unsigned int contU = 0;

  do{
    read_distance_wall();
    e1 = distance_wall('E');
    d1 = distance_wall('D');
    f1 = distance_wall('F');
    t1 = distance_wall('T');

    read_distance_wall();
    e2 = distance_wall('E');
    d2 = distance_wall('D');
    f2 = distance_wall('F');
    t2 = distance_wall('T');
  }while((e1!=e2 || d1!=d2 || f1!=f2 || t1!=t2) && contU++<4);
}
