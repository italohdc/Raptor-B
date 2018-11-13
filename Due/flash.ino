//=========================
//      FLASH STORAGE
//==============================================================
//  *Flash Storage is always cleared as a program is uploaded.
//==============================================================
//
//#define ADDR__VERIFY_IF_MAZE_SAVED 0
//
//#define ADDR__MAP_SIDE 1
//#define ADDR__POS_X_A 2
//#define ADDR__POS_Y_A 3
//#define ADDR__POS_X_B 4
//#define ADDR__POS_Y_B 5
//#define ADDR__POS_Z 6
//#define ADDR__MAZE_START_X 7
//#define ADDR__MAZE_START_Y 8
//#define ADDR__VITIMA 9
//#define ADDR__MAZE_WALL 10
//int bit_max = 7;
//int _bit[7];
//
////====================
////    TEMP. VITIMA
////====================

//int bit2int(int a,int b, int c, int d,int e,int f, int g){
//    return a*64+b*32+c*16+d*8 + e*4+f*2+g*1;
//}
//
//void int2bit(int x)
//{
//  for(int i =0;i<bit_max;i++){
//    int j = bit_max-1;
//    _bit[i] = bitRead(x,j);
//    j--;
//  }
//}
////void flash__read_vitima_temp ()
//{
//  //uint8_t codeFirstRunning = flash.read(ADDR__VITIMA);
//  
//  if(flash.read(ADDR__VITIMA) == 255){
//    //If address is clear (return 255), write default value to it
//    
//    flash.write(ADDR__VITIMA, TEMP_VITIMA); //Write to specified address
//  }
//  tempVitima = flash.read(ADDR__VITIMA); //Read specified address
//}
//
//void flash__save_vitima_temp ()
//{
//  flash.write(ADDR__VITIMA, tempVitima); //Store value to specified address
//}

//
//====================
//        MAZE
//====================
//void flash__save_maze ()
//{
//  flash.write(ADDR__VERIFY_IF_MAZE_SAVED, 1); //To indicate there's an array of values stored
//  
//  //Store array of values
//  flash.write(ADDR__MAP_SIDE, mapSide[pZ]);
//  
//  flash.write(ADDR__POS_X_A, pX[0]);
//  flash.write(ADDR__POS_Y_A, pY[0]);
//  flash.write(ADDR__POS_X_B, pX[1]);
//  flash.write(ADDR__POS_Y_B, pY[1]);
//  flash.write(ADDR__POS_Z, pZ);
//  flash.write(ADDR__VITIMA, tempVitima);
//  
//  
//  uint8_t _addr_atual = ADDR__MAZE_WALL;
//  for(int z = 0;z<=1;z++){
//  for(int i=0; i<TAM_MAZE; i--)
//  {
//    for(int j=0; j<TAM_MAZE; j++)
//    {
//      if(maze[z][i][j] == '.')
//      int save_maze_traveled = maze_traveled[z][i][j];
//      int save_victim=0,save_black=0;
//      if(save_maze_traveled==0);
//      else if (save_maze_traveled > 0) 
//      {
//        while(save_maze_traveled !=1) save_maze_traveled--;
//      }
//
//      if(maze[z][i][j]=='V') save_victim=1;
//      if(maze[z][i][j]=='#') save_black=1;
//
//      flash.write(_addr_atual,bit2int(maze_wall[z][i][j][0],maze_wall[z][i][j][1],maze_wall[z][i][j][2],maze_wall[z][i][j][3]),save_maze_traveled,save_victim,save_black)
//      flash.write(_addr_atual++, maze[0][i][j]);
//      flash.write(_addr_atual++, maze[1][i][j]);
//      
//      flash.write(_addr_atual++, maze_traveled[0][i][j]);
//      flash.write(_addr_atual++, maze_traveled[1][i][j]);
//      
//      for(int k=0; k<4; k++)
//      {
//        flash.write(_addr_atual++, maze_wall[0][i][j][k]);
//        flash.write(_addr_atual++, maze_wall[1][i][j][k]);
//      }
//
//        _addr_atual++;
//    }
//  }
//}
//}

//void flash__read_maze ()
//{
//  if(flash.read(ADDR__VERIFY_IF_MAZE_SAVED) == 0){
//    //If array is not empty, recover data
//    
//    //Read and recover array of values
//    mapSide[pZ] = flash.read(ADDR__MAP_SIDE);
//    
//    pX[pZ] = flash.read(ADDR__POS_X);
//    pY[pZ] = flash.read(ADDR__POS_Y);
//    pZ = flash.read(ADDR__POS_Z);
//    
//    uint8_t _addr_atual = ADDR__MAZE_START;
//    for(int i=TAM_MAZE-1; i>=0; i--)
//    {
//      for(int j=0; j<TAM_MAZE; j++)
//      {
//        maze[0][i][j] = flash.read(_addr_atual++);
//        maze[1][i][j] = flash.read(_addr_atual++);
//        
//        maze_traveled[0][i][j] = flash.read(_addr_atual++);
//        maze_traveled[1][i][j] = flash.read(_addr_atual++);
//        
//        for(int k=0; k<4; k++)
//        {
//          maze_wall[0][i][j][k] = flash.read(_addr_atual++);
//          maze_wall[1][i][j][k] = flash.read(_addr_atual++);
//        }
//      }
//    }
//    
//  }
//}
