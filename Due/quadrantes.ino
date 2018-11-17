float t90_DIR=7*PI, t90_ESQ=7*PI, t180=14.5*PI, tFrente=31;//31.3;//31.5;//28.5;
byte erro_motor = 0;//6;

void quadrante_direita ()
{
  setMotor(0,0,0,0);
  setMotor(TP,-TP,TP,-TP);
  delay_encoder('A', 90);//delay_encoder1(t90_DIR);
  setMotor(-25,25,-25,25); delay(5);
  parar(tempo);
}

void quadrante_esquerda ()
{
  setMotor(0,0,0,0);
  setMotor(-TP,TP,-TP,TP);
  delay_encoder('A', 90);//delay_encoder1(t90_DIR);
  setMotor(25,-25,25,-25); delay(5);
  parar(tempo);
}

void quadrante_frente ()
{
  setMotor(0,0,0,0);
  setMotor_encoder(TP, tFrente);//29.2);//30);
  setMotor(-25,-25,-25,-25); delay(5);
  parar(tempo);
}

void quadrante_tras ()
{
  
  setMotor(0,0,0,0);
  if(map_readWall('E') && !map_readWall('D'))
    setMotor(TP,-TP,TP,-TP);
  else if(!map_readWall('E') && map_readWall('D'))
    setMotor(-TP,TP,-TP,TP);
  else
    setMotor(TP,-TP,TP,-TP);

  delay_encoder('A', 185);//delay_encoder1(t90_DIR);
  setMotor(-25,-25,-25,-25); delay(5);
  setMotor(25,25,25,25); delay(5);
  parar(tempo);
  
}

void quadrante_re ()
{
  setMotor(0,0,0,0);
  setMotor(-TP,-TP-erro_motor,-TP,-TP-erro_motor);
  delay_encoder('F', tFrente);//30);//delay_encoder1(t90_DIR);
  setMotor(25,25,25,25); delay(5);
  parar(tempo);
}
