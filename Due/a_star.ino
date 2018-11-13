/////////ROSADA///////////

byte piso_inicial = 0;



boolean empty = false, start_delete = false;

char directionv = '#'; int way_dist = 2 * TAM_MAZE;

void asterix_virtual() {
  way_traveled[pY[pZ]][pX[pZ]]++;

  //u8g.setPrintPos(1, 8);
  //u8g.print(1);

  if (way_place('U') != -1) way_value = way_place('U');
  else if (way_place('D') != -1) way_value = way_place('D');
  else if (way_place('L') != -1) way_value = way_place('L');
  else if (way_place('R') != -1) way_value = way_place('R');
  else way_value = 1000;

  //u8g.setPrintPos(1, 8);
  //u8g.print(2);

  if (way_value > way_place('U') && way_place('U') != -1) way_value = way_place('U');
  if (way_value > way_place('D') && way_place('D') != -1) way_value = way_place('D');
  if (way_value > way_place('L') && way_place('L') != -1) way_value = way_place('L');
  if (way_value > way_place('R') && way_place('R') != -1) way_value = way_place('R');

  //u8g.setPrintPos(1, 8);
  //u8g.print(3);

  if (way_place('D') != -1 && available_place('D') < way_dist && way_place('D') == way_value) {
    directionv = 'D';
    way_dist = available_place('D');
  }
  if (way_place('U') != -1 && available_place('U') < way_dist && way_place('U') == way_value) {
    directionv = 'U';
    way_dist = available_place('U');
  }
  if (way_place('L') != -1 && available_place('L') < way_dist && way_place('L') == way_value) {
    directionv = 'L';
    way_dist = available_place('L');
  }
  if (way_place('R') != -1 && available_place('R') < way_dist && way_place('R') == way_value) {
    directionv = 'R';
    way_dist = available_place('R');
  }

  //u8g.setPrintPos(1, 8);
  //u8g.print(4);

  //if(start_delete) delete_path(pX, pY); //Delete the square in case it's an endless route
  //This function isn't executed on the first loop

  //SWITCH DIRECTION TO GO// (based on the compared directions)
  switch (directionv)
  {
    case 'U':
      save_last_dir('U', pX[pZ], pY[pZ]);
      pY[pZ]++;
      break;

    case 'D':
      save_last_dir('D', pX[pZ], pY[pZ]);
      pY[pZ]--;
      break;

    case 'L':
      save_last_dir('L', pX[pZ], pY[pZ]);
      pX[pZ]--;
      break;

    case 'R':
      save_last_dir('R', pX[pZ], pY[pZ]);
      pX[pZ]++;
      break;

    default:
      // print("\n It's a trap, Mario! \n\tGAME OVER");
      // exit();
      break;
  }

  //u8g.setPrintPos(1, 8);
  //u8g.print(5);
  //start_delete = true; //Execute "delete_path()" on next loop
}

void a_star_data(){
  verificar_pos_final();
  calculate_return_end(); //Calculate distance to the end
  calculate_return_start(); //Calculate distance to the start 
}

int verificar_pos_final() {
  int let=65;
  while (1){///////
  for (int i = 0; i < TAM_MAZE; i++) {
    for (int j = 0; j < TAM_MAZE; j++) {

      if (pZ == 0){//false) {
        if (maze[pZ][i][j] == 'S')
        {
          startX = j;
          startY = i;
          return 1;
        }
      }

//      if (pZ == true) {
//        if (maze[pZ][i][j] == 'U' || maze[pZ][i][j] == 'D')
//        {
//          startX = j;
//          startY = i;
//        }
//      }
      else if(maze[pZ][i][j] == ((char)(let)) || maze[pZ][i][j] == ((char)(let+32)))
      {
         startX = j;
         startY = i;
         return 1;
      }
      
      //if(find_path(i,j) == 0){
      //  dist_to_end[i][j] ++;
      //}
    }
  }
  let++;
  }
//  calculate_return_end(); //Calculate distance to the end
//  calculate_return_start(); //Calculate distance to the start

}

void calculate_return_end () //Calculate distances (X+Y) to the end
{
  for (int i = 0; i < TAM_MAZE; i++) {
    for (int j = 0; j < TAM_MAZE; j++) {
      dist_to_end[i][j] = abs(i - startY) + abs(j - startX);

      //if(find_path(i,j) == 0){
      //  dist_to_end[i][j] ++;
      //}
    }
  }
}

void calculate_return_start () //Calculate distances (X+Y) to the start
{
  for (int i = 0; i < TAM_MAZE; i++) {
    for (int j = 0; j < TAM_MAZE; j++) {
      dist_to_start[i][j] = abs(i - pY[pZ]) + abs(j - pX[pZ]);

      //if(find_path(i,j) == 0){
      //  dist_to_end[i][j] ++;
      //}
    }
  }
}


int way_place (char letter)
{
  switch (letter)
  {
    case 'U':
      if (maze_wall[pZ][pY[pZ]][pX[pZ]][0] == true) return -1;
      else
      {
        if (maze[pZ][pY[pZ] + 1][pX[pZ]] == '#' || maze[pZ][pY[pZ] + 1][pX[pZ]] == 'X' || maze[pZ][pY[pZ] + 1][pX[pZ]] == ' ') return -1;
        else return way_traveled[pY[pZ] + 1][pX[pZ]]; ///
      }

    case 'D':
      if (maze_wall[pZ][pY[pZ]][pX[pZ]][3] == true) return -1;
      else
      {
        if (maze[pZ][pY[pZ] - 1][pX[pZ]] == '#' || maze[pZ][pY[pZ] - 1][pX[pZ]] == 'X' || maze[pZ][pY[pZ] - 1][pX[pZ]] == ' ') return -1;
        else return way_traveled[pY[pZ] - 1][pX[pZ]]; ///
      }

    case 'L':
      if (maze_wall[pZ][pY[pZ]][pX[pZ]][1] == true) return -1;
      else
      {
        if (maze[pZ][pY[pZ]][pX[pZ] - 1] == '#' || maze[pZ][pY[pZ]][pX[pZ] - 1] == 'X' || maze[pZ][pY[pZ]][pX[pZ] - 1] == ' ') return -1;
        else return way_traveled[pY[pZ]][pX[pZ] - 1]; ///
      }

    case 'R':
      if (maze_wall[pZ][pY[pZ]][pX[pZ]][2] == true) return -1;
      else
      {
        if (maze[pZ][pY[pZ]][pX[pZ] + 1] == '#' || maze[pZ][pY[pZ]][pX[pZ] + 1] == 'X' || maze[pZ][pY[pZ]][pX[pZ] + 1] == ' ') return -1;
        else return way_traveled[pY[pZ]][pX[pZ] + 1]; ///
      }

    default:
      return -1;
  }
}



//int find_path (int px, int py)//(int x, int y)
//{
//  if(x<0 || y<0 || x>=TAM_MAZE || y>=TAM_MAZE) return -1; //Outside the Maze //////////////////BARREIRA DO LABIRINTO OU DA MATRIX (ESCOLHER)////////////////////
//
//
//
//
//
//  switch(maze[pZ][y][x])
//  {
//    case '#': //Wall
//      return 0;
//
//    case '.': //Open
//    case 'S': //Start
//    case 'E': //Goal
//    case 'R': //Robot
//      return 1;
//
//    default:
//      return 0;
//  }
//}



//Returns the distance to the end from UP, DOWN,//
//LEFT and RIGHT points of a given position     //
int available_place (char letter)
{
  switch (letter)
  {
    case 'U':
      //    if(maze_wall[pZ][pY[pZ]][pX[pZ]][0] == 0)
      //    {
      //       if(maze[pZ][pY[pZ]+1][pX[pZ]] == '#' || maze[pZ][pY[pZ]=!][pX[pZ]] == 'X') return -1;
      //    }
      return dist_to_end[pY[pZ] + 1][pX[pZ]];

    case 'D':
      //    if(maze_wall[pZ][pY[pZ]][pX[pZ]][3] == 0)
      //    {
      //       if(maze[pZ][pY[pZ]-1][pX[pZ]] == '#' || maze[pZ][pY[pZ]-1][pX[pZ]] == 'X') return -1;
      //    }
      return dist_to_end[pY[pZ] - 1][pX[pZ]];

    case 'L':
      //    if(maze_wall[pZ][pY[pZ]][pX[pZ]][1] == 0)
      //    {
      //       if(maze[pZ][pY[pZ]][pX[pZ]-1] == '#' || maze[pZ][pY[pZ]][pX[pZ]-1] == 'X') return -1;
      //    }
      return dist_to_end[pY[pZ]][pX[pZ] - 1];

    case 'R':
      //    if(maze_wall[pZ][pY[pZ]][pX[pZ]][2] == 0)
      //    {
      //       if(maze[pZ][pY[pZ]][pX[pZ]+1] == '#' || maze[pZ][pY[pZ]][pX[pZ]+1] == 'X') return -1;
      //    }
      return dist_to_end[pY[pZ]][pX[pZ] + 1];

    default:
      return -1;
  }
}

//=================
//  SPECIAL CASES
//=================

//DELETE ENDLESS ROUTES//
//Delete the square in case it's an endless route


//SAVE LAST DIRECTION//
//Save the last direction gone by the robot on a square
void save_last_dir (char dir, int sx, int sy)
{
  switch (dir)
  {
    case 'U':
      last_dir[sy][sx] = 'U';
      break;

    case 'D':
      last_dir[sy][sx] = 'D';
      break;

    case 'L':
      last_dir[sy][sx] = 'L';
      break;

    case 'R':
      last_dir[sy][sx] = 'R';
      break;
  }
}

void draw_array (int _x, int _y)
{
  //  u8g.setPrintPos(1,5);
  //  u8g.setFont(u8g_font_u8glib_4);
  //  u8g.firstPage();// do{
  //
  //    LOG(" ");
  //
  //    for(int j = 0; j<_y;j++) LOG(j);
  //    LOGLN("");
  //
  //  for(int i=0; i<_y; i++)
  //  {LOG(i);
  //    //u8g.setPrintPos(1, 5*(i+1));
  //    for(int j=0; j<_x; j++)
  //    {
  //      //if(j == pX[pZ] && i == pY[pZ]) LOG('R');
  //
  //      LOG(maze[pZ][i][j]);//last_dir[i][j]);
  //      //u8g.print("");
  //    } LOG("\n");
  //  }
  //  //} while( u8g.nextPage() ); delay(300);
}

void asterix ()
{
  //  draw_array(TAM_MAZE,TAM_MAZE);
  //  while(1);

  int contador_timer = millis(); bool contador = false;
  ativar_vitima = false;

  //=======================
  //If in the initial floor
  //=======================
  if (pZ == false)
  {
    //Virtually analizes the way to come back
    //=======================================
    int _save_pX = pX[pZ], _save_pY = pY[pZ]; //save the real pX, pY value
    a_star_data();//verificar_pos_final();

    //while(1)draw_maze();
    //draw_array(0,0);
    do {
      setMotor(0, 0, 0, 0);
      asterix_virtual();
    } while (pX[pZ] != startX || pY[pZ] != startY);

    //draw_array(TAM_MAZE, TAM_MAZE);
    pX[pZ] = _save_pX; pY[pZ] = _save_pY; //return real value to pX, pY

    //Come back to initial place
    //==========================
    do {
      come_back();
    } while (pX[pZ] != startX || pY[pZ] != startY);
    print_info("GAME OVER");
    while (1) setMotor(0, 0, 0, 0); //Stop forever
  }

  ///////////////////////////////////////////////////////////////////////////////

  //===========================
  //If not in the initial floor
  //===========================

  else if (pZ == true)
  {
    //Virtually analizes the way to go to the ramp
    //============================================
    LOG("ASTERIX::1::init\n"); LOG("ASTERIX::virtual::init\n");

    int _save_pX = pX[pZ], _save_pY = pY[pZ]; //save the real pX, pY value
    a_star_data();//verificar_pos_final();

    //while(1)draw_maze();
    do {
      setMotor(0, 0, 0, 0);
      asterix_virtual(); //draw_array(TAM_MAZE, TAM_MAZE);
    } while (pX[pZ] != startX || pY[pZ] != startY);

    //draw_array(TAM_MAZE, TAM_MAZE);
    pX[pZ] = _save_pX; pY[pZ] = _save_pY; //return real value to pX, pY
    LOG("ASTERIX::virtual::end\n");

    //Go to the ramp
    //==============
    LOG("come_back::init\n");
    do {
      come_back();
    } while (pX[pZ] != startX || pY[pZ] != startY);
    LOG("come_back::end\n");

    //Go UP or DOWN into the ramp
    //===========================
    LOG("ramp::init\n");
    //Maiuscula
    if ( ( ((int)maze[pZ][pY[pZ]][pX[pZ]]) < 97 && ((int)maze[pZ][pY[pZ]][pX[pZ]]) > 64) && maze[pZ][pY[pZ]][pX[pZ]]!= 'S' 
       && maze[pZ][pY[pZ]][pX[pZ]]!= 'V' && maze[pZ][pY[pZ]][pX[pZ]]!= 'X'){//maze[pZ][pY[pZ]][pX[pZ]] == 'U') { //readAccel('X') < rampa.goingUP){
      contador_timer = millis();
      setMotor_encoder(velocidade.rampaUP, 8);
      do {
        //setMotor(velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP,velocidade.rampaUP);
        rampa_subir_encoder();//BANGBANG();//PID();

//        if ((millis() - contador_timer) > 600) {
//          if (read_Ultra('D') > 16) contador = true;
//          contador_timer = millis();
//        }

      } while (!endof_rampUP());//!contador);
      //ajustar_parede_FRENTE(); ajustar_parede_FRENTE();
    }

    //Minuscula
    else if ( ( ((int)maze[pZ][pY[pZ]][pX[pZ]]) < 123 && ((int)maze[pZ][pY[pZ]][pX[pZ]]) > 96) && maze[pZ][pY[pZ]][pX[pZ]]!= 'S' 
            && maze[pZ][pY[pZ]][pX[pZ]]!= 'V' && maze[pZ][pY[pZ]][pX[pZ]]!= 'X'){//maze[pZ][pY[pZ]][pX[pZ]] == 'D') { //readAccel('X') > rampa.goingDOWN){
      contador_timer = millis();
      setMotor_encoder(velocidade.rampaDOWN, 8);
      do {
        //setMotor(velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN,velocidade.rampaDOWN);
        rampa_descer_encoder();//BANGBANG();//PID();

//        if ((millis() - contador_timer) > 500) {
//          if (read_Ultra('E') > 16) contador = true;
//          contador_timer = millis();
//        }
      } while (!endof_rampDOWN());//!contador);
      //ajustar_parede_FRENTE(); ajustar_parede_FRENTE();
    }
    LOG("ramp::end\n");

    pZ = false; //change floor to initial
    //while(1) draw();
    //Virtually analizes the way to come back
    //=======================================
    LOG("ASTERIX::virtual::init\n");
    // pX[pZ]--;
    _save_pX = pX[pZ], _save_pY = pY[pZ]; //save the real pX, pY value
    a_star_data();//verificar_pos_final();
    //while(1)draw_maze();

    do {
      setMotor(0, 0, 0, 0);
      asterix_virtual();
    } while (pX[pZ] != startX || pY[pZ] != startY);

    //draw_array(TAM_MAZE, TAM_MAZE);
    pX[pZ] = _save_pX; pY[pZ] = _save_pY; //return real value to pX, pY
    LOG("ASTERIX::virtual::end\n");

    //Come back to initial place
    //==========================
    LOG("come_back::init\n");
    do {
      come_back();
    } while (pX[pZ] != startX || pY[pZ] != startY);

    //    read_distance_wall();
    //    if (distance_wall('D') > dist_parede) {
    //      analisar_ajuste();
    //      quadrante_direita();
    //      analisar_ajuste();
    //      setMotor_encoder(TP, 30.7);
    //
    //    }
    //    else if (distance_wall('E') > dist_parede) {
    //      analisar_ajuste();
    //      quadrante_esquerda();
    //      analisar_ajuste();
    //      setMotor_encoder(TP, 30.7);
    //
    //    }
    print_info("GAME OVER"); LOG("come_back::end\n");
    while (1) setMotor(0, 0, 0, 0); //Stop forever
  }
}

////////////////////////////////////////////////////////////////////////

//==================================================
//  ANALIZE IF ALL POSSIBLE SQUARES WERE TRAVELLED
//==================================================

bool maze_finished ()
{
  for(bool fa=0; fa<=1; fa++)
  {
    for(int fb[2]; fb[fa]<TAM_MAZE; fb[fa]++)
    {
      for(int fc[2]; fc[fa]<TAM_MAZE; fc[fa]++)
      {

        
        if(maze[pZ][pY[pZ]][pX[pZ]] == 'S' && maze[pZ][pY[pZ]][pX[pZ]] == 'V' && maze[pZ][pY[pZ]][pX[pZ]] == 'X'
        && maze[pZ][pY[pZ]][pX[pZ]] == '.' && maze[pZ][pY[pZ]][pX[pZ]] == '#')//maze[fa][fb[fa]][fc[fa]] != 'D' && maze[fa][fb[fa]][fc[fa]] != 'U' && maze[fa][fb[fa]][fc[fa]] != ' ')
        {
          if(!maze_wall[fa][fb[fa]][fc[fa]][0]){ //FRENTE
            if(maze[fa][fb[fa]+1][fc[fa]] == ' ') return 0;
          }

          if(!maze_wall[fa][fb[fa]][fc[fa]][1]){ //ESQUERDA
            if(maze[fa][fb[fa]][fc[fa]-1] == ' ') return 0;
          }

          if(!maze_wall[fa][fb[fa]][fc[fa]][2]){ //DIREITA
            if(maze[fa][fb[fa]][fc[fa]+1] == ' ') return 0;
          }

          if(!maze_wall[fa][fb[fa]][fc[fa]][3]){ //TRAS
            if(maze[fa][fb[fa]-1][fc[fa]] == ' ') return 0;
          }
        }

        
      }
    }
  }
  
  return true;
}

