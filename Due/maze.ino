void delete_path ()
{
  bool _wall1=false, _wall2=false, _wall3=false, _wall4=false;
  if(map_readQuad('F')=='X' || map_readQuad('F')=='#') _wall1=true;
  if(map_readQuad('E')=='X' || map_readQuad('E')=='#') _wall2=true;
  if(map_readQuad('D')=='X' || map_readQuad('D')=='#') _wall3=true;
  if(map_readQuad('T')=='X' || map_readQuad('T')=='#') _wall4=true;
  
  int av_place = (map_readWall('F')|_wall1) + (map_readWall('T')|_wall4) +
      (map_readWall('E')|_wall2) + (map_readWall('D')|_wall3);
  
  if(av_place == 3 && maze[pZ][pY[pZ]][pX[pZ]] != 'S')
  {
    if(maze[pZ][pY[pZ]][pX[pZ]] != '#')
    {
      if(maze[pZ][pY[pZ]][pX[pZ]] != 'U')
      if(maze[pZ][pY[pZ]][pX[pZ]] != 'D')
      if(maze[pZ][pY[pZ]][pX[pZ]] != 'u')
      if(maze[pZ][pY[pZ]][pX[pZ]] != 'd')
      maze[pZ][pY[pZ]][pX[pZ]] = 'X';
    }
  }
}
