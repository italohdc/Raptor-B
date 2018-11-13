char mF, mT, mE, mD; int mFv, mTv, mEv, mDv;
int mFx, mTx, mEx, mDx; int mFy, mTy, mEy, mDy;

const uint8_t BIT_up_arrow[] U8G_PROGMEM = {
  0x40, 0xE0, 0x0}; //01000000, 11100000, 00000000 };
  
const uint8_t BIT_down_arrow[] U8G_PROGMEM = {
  0x0, 0xE0, 0x40}; //00000000, 11100000, 01000000 };

const uint8_t BIT_left_arrow[] U8G_PROGMEM = {
  0x40, 0xC0, 0x40}; //01000000, 11000000, 01000000 };

const uint8_t BIT_right_arrow[] U8G_PROGMEM = {
  0x40, 0x60, 0x40}; //01000000, 01100000, 01000000 };

const uint8_t BIT_deleted[] U8G_PROGMEM = {
  0xA0, 0x40, 0xA0}; //10100000, 01000000, 10100000 };

const uint8_t BIT_black[] U8G_PROGMEM = {
  0xE0, 0xE0, 0xE0}; //11100000, 11100000, 11100000 };

const uint8_t BIT_rampaD[] U8G_PROGMEM = {
  0x40, 0xA0, 0xA0}; //01000000, 10100000, 10100000 };

const uint8_t BIT_rampaU[] U8G_PROGMEM = {
  0xA0, 0xA0, 0x40}; //10100000, 10100000, 01000000 };

const uint8_t BIT_victim[] U8G_PROGMEM = {
  0x40, 0xE0, 0x40}; //01000000, 11100000, 01000000 };

void mapear(int ma, int mb)
{
  mapPosition(ma);
  mapCalculate(mb);
}

void mapPosition(int mz)
{
  mapSide[pZ]=mapSide[pZ]+mz;

  while(mapSide[pZ]>3)
    mapSide[pZ]=mapSide[pZ]-4;

  while(mapSide[pZ]<0)
    mapSide[pZ]=mapSide[pZ]+4;
}

void mapCalculate(int nQuad)
{
  if(mapSide[pZ]==0){ //>
    pX[pZ] += nQuad;
    if(PRINT_MAZE) u8g.setRot90();
  }
  
  if(mapSide[pZ]==1){ //v
    pY[pZ] -= nQuad;
    if(PRINT_MAZE) u8g.undoRotation();
  }
  
  if(mapSide[pZ]==2){ //<
    pX[pZ] -= nQuad;
    if(PRINT_MAZE) u8g.setRot270();
  }
  
  if(mapSide[pZ]==3){ //^
    pY[pZ] += nQuad;
    if(PRINT_MAZE) u8g.setRot180();
  }
  
  //draw();
}

void mapSetDirec ()
{
  //[0]Frente [1]Esq [2]Dir [3]Tras
  //mX  => MapSide = RealSide; => return real side
  //mXv => RealSide = MapSide[Position]; => return virtual side in array pos
  //mXx, mXy => coordinates to add to array pos to achieve next square
  
  if(mapSide[pZ]==0){mF='E'; mE='T'; mD='F'; mT='D';
                 mFx=1;  mEx=0;  mDx=0;  mTx=-1;
                 mFy=0;  mEy=1;  mDy=-1;  mTy=0;
                 mFv=2;  mEv=0;  mDv=3;  mTv=1;} //>
                 
  if(mapSide[pZ]==1){mF='T'; mE='D'; mD='E'; mT='F';
                 mFx=0;  mEx=1;  mDx=-1;  mTx=0;
                 mFy=-1;  mEy=0;  mDy=0;  mTy=1;
                 mFv=3;  mEv=2;  mDv=1;  mTv=0;} //v
                 
  if(mapSide[pZ]==2){mF='D'; mE='F'; mD='T'; mT='E';
                 mFx=-1;  mEx=0;  mDx=0;  mTx=1;
                 mFy=0;  mEy=-1;  mDy=1;  mTy=0;
                 mFv=1;  mEv=3;  mDv=0;  mTv=2;} //<
                 
  if(mapSide[pZ]==3){mF='F'; mE='E'; mD='D'; mT='T';
                 mFx=0;  mEx=-1;  mDx=1;  mTx=0;
                 mFy=1;  mEy=0;  mDy=0;  mTy=-1;
                 mFv=0;  mEv=1;  mDv=2;  mTv=3;} //^
}

bool map_readWall (char parede)
{
  mapSetDirec();
  
  if(parede == 'E' || parede == 'L')
    return maze_wall[pZ][pY[pZ]][pX[pZ]][mEv];
  
  if(parede == 'D' || parede == 'R')
    return maze_wall[pZ][pY[pZ]][pX[pZ]][mDv];
  
  if(parede == 'F')
    return maze_wall[pZ][pY[pZ]][pX[pZ]][mFv];
  
  if(parede == 'T' || parede == 'B')
    return maze_wall[pZ][pY[pZ]][pX[pZ]][mTv];
}

char map_readQuad (char lado)
{
  mapSetDirec();
  
  if(lado == 'E' || lado == 'L')
    return maze[pZ][pY[pZ]+mEy][pX[pZ]+mEx];
  
  if(lado == 'D' || lado == 'R')
    return maze[pZ][pY[pZ]+mDy][pX[pZ]+mDx];
  
  if(lado == 'F')
    return maze[pZ][pY[pZ]+mFy][pX[pZ]+mFx];
  
  if(lado == 'T' || lado == 'B')
    return maze[pZ][pY[pZ]+mTy][pX[pZ]+mTx];
}

int map_readTravel (char lado)
{
  mapSetDirec();
  
  if(lado == 'E' || lado == 'L')
    return maze_traveled[pZ][pY[pZ]+mEy][pX[pZ]+mEx];
  
  if(lado == 'D' || lado == 'R')
    return maze_traveled[pZ][pY[pZ]+mDy][pX[pZ]+mDx];
  
  if(lado == 'F')
    return maze_traveled[pZ][pY[pZ]+mFy][pX[pZ]+mFx];
  
  if(lado == 'T' || lado == 'B')
    return maze_traveled[pZ][pY[pZ]+mTy][pX[pZ]+mTx];
}

void mapearQuad ()
{
  //read_distance_wall_check();
  maze_traveled[pZ][pY[pZ]][pX[pZ]]++;
  
  mapSetDirec();
  
  if(dist_parede > distance_wall(mF)){// < 200){
    maze_wall[pZ][pY[pZ]][pX[pZ]][0]=true;
    maze_wall[pZ][pY[pZ]+1][pX[pZ]][3]=true;
  }
  else{
    maze_wall[pZ][pY[pZ]][pX[pZ]][0]=false;
    maze_wall[pZ][pY[pZ]+1][pX[pZ]][3]=false;
  }
  
  if(dist_parede > distance_wall(mE)){// < 200){
    maze_wall[pZ][pY[pZ]][pX[pZ]][1]=true;
    maze_wall[pZ][pY[pZ]][pX[pZ]-1][2]=true;
  }
  else{
    maze_wall[pZ][pY[pZ]][pX[pZ]][1]=false;
    maze_wall[pZ][pY[pZ]][pX[pZ]-1][2]=false;
  }
  
  if(dist_parede > distance_wall(mD)){// < 200){
    maze_wall[pZ][pY[pZ]][pX[pZ]][2]=true;
    maze_wall[pZ][pY[pZ]][pX[pZ]+1][1]=true;
  }
  else{
    maze_wall[pZ][pY[pZ]][pX[pZ]][2]=false;
    maze_wall[pZ][pY[pZ]][pX[pZ]+1][1]=false;
  }
  
  if(dist_parede > distance_wall(mT)){// < 200){
    maze_wall[pZ][pY[pZ]][pX[pZ]][3]=true;
    maze_wall[pZ][pY[pZ]-1][pX[pZ]][0]=true;
  }
  else{
    maze_wall[pZ][pY[pZ]][pX[pZ]][3]=false;
    maze_wall[pZ][pY[pZ]-1][pX[pZ]][0]=false;
  }
  
//  for(int i=TAM_MAZE-1; i>=0; i--)
//  {
//    for(int j=0; j<TAM_MAZE; j++)
//    {
//      //LOG(maze_wall[0][i][j][0]);
//      //LOG(maze_wall[0][i][j][1]);
//      //LOG(maze_wall[0][i][j][2]);
//      //LOG(maze_wall[0][i][j][3]);
//      //if(maze_wall[0][i][j][0]==true) LOG("[");
//      if(maze_wall[0][i][j][1]==true) LOG("|");
//      //if(maze_wall[0][i][j][2]==true) LOG("_");
//      if(maze_wall[0][i][j][3]==true) LOG("_");
//      //LOG(maze_traveled[0][i][j]);
//      //LOG("\t");
//    }
//    LOGLN();
//  }
//  LOGLN();
}

void mapearQuad2 ()
{
  //read_distance_wall();
  //REAR//
  if(distance_wall('T') < dist_parede){
    maze_wall[pZ][pY[pZ]][pX[pZ]][mTv] = true;
    maze_wall[pZ][pY[pZ]+mTy][pX[pZ]+mTx][mFv] = true;
  }
  else{
    maze_wall[pZ][pY[pZ]][pX[pZ]][mTv] = false;
    maze_wall[pZ][pY[pZ]+mTy][pX[pZ]+mTx][mFv] = false;
  }

  //FWD//
  if(distance_wall('F') < dist_parede){
    maze_wall[pZ][pY[pZ]][pX[pZ]][mFv] = true;
    maze_wall[pZ][pY[pZ]+mFy][pX[pZ]+mFx][mTv] = true;
  }
  else{
    maze_wall[pZ][pY[pZ]][pX[pZ]][mFv] = false;
    maze_wall[pZ][pY[pZ]+mFy][pX[pZ]+mFx][mTv] = false;
  }

  //LEFT//
  if(distance_wall('E') < dist_parede){
    maze_wall[pZ][pY[pZ]][pX[pZ]][mEv] = true;
    maze_wall[pZ][pY[pZ]+mEy][pX[pZ]+mEx][mDv] = true;
  }
  else{
    maze_wall[pZ][pY[pZ]][pX[pZ]][mEv] = false;
    maze_wall[pZ][pY[pZ]+mEy][pX[pZ]+mEx][mDv] = false;
  }

  //RIGHT//
  if(distance_wall('D') < dist_parede){
    maze_wall[pZ][pY[pZ]][pX[pZ]][mDv] = true;
    maze_wall[pZ][pY[pZ]+mDy][pX[pZ]+mDx][mEv] = true;
  }
  else{
    maze_wall[pZ][pY[pZ]][pX[pZ]][mDv] = false;
    maze_wall[pZ][pY[pZ]+mDy][pX[pZ]+mDx][mEv] = false;
  }
}

void draw_maze ()
{
  for(int mi=0; mi<TAM_MAZE; mi++)//(int mi=TAM_MAZE-1; mi>=0; mi--)
  {
    for(int mj=0; mj<TAM_MAZE; mj++)
    {
      int m_sum1, m_sum2, m_tam1, m_tam2;
      //if(mapSide[pZ]==1)
      //{
        //m_sum1 = mj*4 + 63;
        //m_sum2 = ((TAM_MAZE-1)-mi)*4;
        
  if(mapSide[pZ]==0 || mapSide[pZ]==2) //PORTRAIT
	{
  	  m_sum1 = mj*4;
	  m_sum2 = (((TAM_MAZE-1)-mi)*4) + 63;
	}
	if(mapSide[pZ]==1 || mapSide[pZ]==3) //LANDSCAPE
	{
	  m_sum1 = mj*4 + 63;
	  m_sum2 = ((TAM_MAZE-1)-mi)*4;
	}

//m_sum1 = mj*4;
//m_sum2 = ((TAM_MAZE-1)-mi)*4;
        
        m_tam1 = 5;
        m_tam2 = 1;
      //}
      /*if(mapSide[pZ]==3)
      {
        m_sum1 = ((TAM_MAZE-1)-mj)*4 + 63;
        m_sum2 = mi*4;
        m_tam1 = 5;
        m_tam2 = 1;
      }*/
      /*if(mapSide[pZ]==2)
      {
        m_sum1 = ((TAM_MAZE-1)-mj)*4 + 63;
        m_sum2 = ((TAM_MAZE-1)-mi)*4;
        m_tam1 = 1;
        m_tam2 = 5;
      }*/
      /*if(mapSide[pZ]==0)
      {
        m_sum1 = mj*4 + 63;
        m_sum2 = mi*4 - 4;
        m_tam1 = 5;
        m_tam2 = 1;
      }*/
      
      if(maze_wall[pZ][mi][mj][0])
      {
        //if(mapSide[pZ]==1) 
        u8g.drawBox(m_sum1,m_sum2,m_tam1,m_tam2);
        //if(mapSide[pZ]==2) u8g.drawBox(m_sum1,m_sum2,m_tam1,m_tam2); //SWAP
        //if(mapSide[pZ]==3) u8g.drawBox(m_sum1,m_sum2,m_tam1,m_tam2);
        //if(mapSide[pZ]==0) u8g.drawBox(m_sum1,m_sum2,m_tam1,m_tam2); //SWAP
      }
        
      if(maze_wall[pZ][mi][mj][1])
      {
        //if(mapSide[pZ]==1) 
        u8g.drawBox(m_sum1,m_sum2,m_tam2,m_tam1);
        //if(mapSide[pZ]==2) u8g.drawBox(m_sum1,m_sum2,m_tam2,m_tam1); //SWAP
        //if(mapSide[pZ]==3) u8g.drawBox(m_sum1,m_sum2,m_tam2,m_tam1);
        //if(mapSide[pZ]==0) u8g.drawBox(m_sum1,m_sum2,m_tam2,m_tam1); //SWAP
      }
      
      if(mj == pX[pZ] && mi == pY[pZ])
      {
        if(mapSide[pZ]==1) u8g.drawBitmapP(m_sum1+1, m_sum2+1, 1, 3, BIT_down_arrow);
        if(mapSide[pZ]==2) u8g.drawBitmapP(m_sum1+1, m_sum2+1, 1, 3, BIT_left_arrow);
        if(mapSide[pZ]==3) u8g.drawBitmapP(m_sum1+1, m_sum2+1, 1, 3, BIT_up_arrow);
        if(mapSide[pZ]==0) u8g.drawBitmapP(m_sum1+1, m_sum2+1, 1, 3, BIT_right_arrow);
        
        //if(mapSide[pZ]==1) 
        //u8g.drawBox(m_sum1+2,m_sum2+2,1,1);
        //if(mapSide[pZ]==2) u8g.drawBox(m_sum1-2,m_sum2+2,1,1);
        //if(mapSide[pZ]==3) u8g.drawBox(m_sum1-2,m_sum2-2,1,1);
        //if(mapSide[pZ]==0) u8g.drawBox(m_sum1+2,m_sum2-2,1,1);
      }
      
      else
      {
        if(maze[pZ][mi][mj] == 'X')
        {
          u8g.drawBitmapP(m_sum1+1, m_sum2+1, 1, 3, BIT_deleted);
        }

//        if(mi==startY && mj ==startX )
//        {
//          u8g.drawBitmapP(m_sum1+1, m_sum2+1, 1, 3, BIT_black);
//        }
        if(maze[pZ][mi][mj] == '#')
        {
          u8g.drawBitmapP(m_sum1+1, m_sum2+1, 1, 3, BIT_black);
          //u8g.drawBox(m_sum1+1, m_sum2+1, 3, 3);//, BIT_black);
        }
        if(maze[pZ][mi][mj] == 'S')
        {
          u8g.drawBox(m_sum1+2, m_sum2+2, 1, 1);
        }
        if(maze[pZ][mi][mj] == 'u' || maze[pZ][mi][mj] == 'U')
        {
          u8g.drawBitmapP(m_sum1+1, m_sum2+1, 1, 3, BIT_rampaU);
        }
        if(maze[pZ][mi][mj] == 'd' || maze[pZ][mi][mj] == 'D')
        {
          u8g.drawBitmapP(m_sum1+1, m_sum2+1, 1, 3, BIT_rampaD);
        }
        if(maze[pZ][mi][mj] == 'V')
        {
          u8g.drawBitmapP(m_sum1+1, m_sum2+1, 1, 3, BIT_victim);
        }
      }
    }
  }
}

void come_back ()
{
  search_victim_adjust = false;
  mapSetDirec();

  if(last_dir[pY[pZ]][pX[pZ]] == 'U') go_to_pos(mF);
  if(last_dir[pY[pZ]][pX[pZ]] == 'D') go_to_pos(mT);
  if(last_dir[pY[pZ]][pX[pZ]] == 'L') go_to_pos(mE);
  if(last_dir[pY[pZ]][pX[pZ]] == 'R') go_to_pos(mD);
}

void go_to_pos (char side)
{
  if(side == 'F'){
    analisar_ajuste();
    quadrante_frente(); mapear(0,1);
    analisar_ajuste();
  }
  if(side == 'E'){
    analisar_ajuste();
    quadrante_esquerda(); mapear(-1,0);
    analisar_ajuste();
    quadrante_frente(); mapear(0,1);
  }
  if(side == 'D'){
    analisar_ajuste();
    quadrante_direita(); mapear(1,0);
    analisar_ajuste();
    quadrante_frente(); mapear(0,1);
  }
  if(side == 'T'){
    analisar_ajuste();
    quadrante_tras(); mapear(2,0);
    analisar_ajuste();
    quadrante_frente(); mapear(0,1);
  }
}
