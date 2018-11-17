#define CODIGO__TEMPERATURA_0 102 //0x54 //FE
#define CODIGO__TEMPERATURA_1 103 //0x24 //E1
#define CODIGO__TEMPERATURA_2 104 //0x22 //FD
#define CODIGO__TEMPERATURA_3 105 //0x5A //D1

#define FOUND__VITIMA_EF temperatura[0] >= tempVitima
#define FOUND__VITIMA_DF temperatura[2] >= tempVitima
#define FOUND__VITIMA_E1 temperatura[1] >= tempVitima
#define FOUND__VITIMA_D1 temperatura[3] >= tempVitima

#define FOUND__ULTRA_F read_Ultra('F') < 16
#define FOUND__ULTRA_E read_Ultra('E') < 16
#define FOUND__ULTRA_D read_Ultra('D') < 16

int temperatura[4];

void imprimir_temp_vit (){
 /* lcd.setCursor(10,1);
  lcd.print(tempVitima);
  lcd.print("C");*/
}

int ler_temp_NANO (int cod_temp)
{
  Serial1.write(cod_temp);
  int temp_nano = ler_Serial();
  return temp_nano;
}

int ler_Serial ()
{
  int Serial_value=0;
  boolean lido = false;
  do{
    if(Serial1.available() > 0){
      Serial_value = Serial1.read();
      lido = true;
    }
  }while(lido==false);
  
  return Serial_value;
}

void ler_temperatura ()
{
  /////VITIMA
  temperatura[0] = ler_temp_NANO(CODIGO__TEMPERATURA_0);
  temperatura[1] = ler_temp_NANO(CODIGO__TEMPERATURA_1);
  temperatura[2] = ler_temp_NANO(CODIGO__TEMPERATURA_2);
  temperatura[3] = ler_temp_NANO(CODIGO__TEMPERATURA_3);
}

bool procurar_vitima ()
{
  if(!ativar_vitima) return 0;
  if(read_corQuad() < PRETO+50) return 0;
  ler_temperatura();
  
  if((FOUND__VITIMA_EF || FOUND__VITIMA_DF) && !vitima_ja_encontrada){
    if(FOUND__ULTRA_F){// || DESATIVAR__ULTRA){
    if(maze[pZ][pY[pZ]][pX[pZ]] == 'V') return 0; ///////////////////////////////////////////////////////
    
      print_info("VITIMA F");
      search_victim_adjust = false;
      
        setMotor(-vAP,-vAP,-vAP,-vAP);
        delay_encoder('B', 2);
        
        setMotor(0,0,0,0);
      
      stop_fwd = true;
      avisar_vitima(); delay(100);
      vitima_ja_encontrada = true;
      search_victim_adjust = true; ///////////////////////////////////////////////////////
      if(maze[pZ][pY[pZ]][pX[pZ]] == ' ') visited_places++;
      maze[pZ][pY[pZ]][pX[pZ]] = 'V'; victims_found++;
      setMotor(0,0,0,0);
      return 1;
  }}
  
  else if(FOUND__VITIMA_E1 && vitima_ja_encontrada == false){
    if(FOUND__ULTRA_E){// || DESATIVAR__ULTRA){
    if(maze[pZ][pY[pZ]][pX[pZ]] == 'V') return 0;
    
      print_info("VITIMA E");
      search_victim_adjust = false;
      
      //Save last encoder value for encoder_delay//
      enc_read_SAVED[0] = enc_read[0]; enc_read_SAVED[1] = enc_read[1];
      enc_read_SAVED[2] = enc_read[2]; enc_read_SAVED[3] = enc_read[3];
      //==//
      
      quadrante_esquerda();
      setMotor(-vAP,-vAP,-vAP,-vAP);
      delay_encoder('B', 2);
      ajustar_parede_FRENTE();
      
      setMotor(0,0,0,0);
      
      avisar_vitima(); delay(100);
      vitima_ja_encontrada = true;
      quadrante_direita();
      search_victim_adjust = true;
      if(maze[pZ][pY[pZ]][pX[pZ]] == ' ') visited_places++;
      maze[pZ][pY[pZ]][pX[pZ]] = 'V'; victims_found++;
      setMotor(0,0,0,0);
      return 1;
    }
  }
  
  else if(FOUND__VITIMA_D1 && vitima_ja_encontrada == false){
    if(FOUND__ULTRA_D){// || DESATIVAR__ULTRA){
    if(maze[pZ][pY[pZ]][pX[pZ]] == 'V') return 0;
    
      print_info("VITIMA D");
      search_victim_adjust = false;
      
      //Save last encoder value for encoder_delay//
      enc_read_SAVED[0] = enc_read[0]; enc_read_SAVED[1] = enc_read[1];
      enc_read_SAVED[2] = enc_read[2]; enc_read_SAVED[3] = enc_read[3];
      //==//
      
      quadrante_direita();
      setMotor(-vAP,-vAP,-vAP,-vAP);
      delay_encoder('B', 2);
      ajustar_parede_FRENTE();
      
      setMotor(0,0,0,0);
      
      avisar_vitima(); delay(100);
      vitima_ja_encontrada = true;
      quadrante_esquerda();
      search_victim_adjust = true;
      if(maze[pZ][pY[pZ]][pX[pZ]] == ' ') visited_places++;
      maze[pZ][pY[pZ]][pX[pZ]] = 'V'; victims_found++;
      setMotor(0,0,0,0);
      return 1;
    }
  }
  
  return 0;
}

void avisar_vitima ()
{
  setMotor(0,0,0,0);
  //kit.attach(pin_kit);
  if(maze[pZ][pY[pZ]][pX[pZ]] != 'V')
    kit.write(KIT_OPEN);
  for(int l=0; l<6; l++)
  {
    digitalWrite(pin_LED, HIGH); delay(250);
    digitalWrite(pin_LED, LOW); delay(250);
  }
  kit.write(KIT_CLOSE);
  for(int l=0; l<4; l++)
  {
    digitalWrite(pin_LED, HIGH); delay(250);
    digitalWrite(pin_LED, LOW); delay(250);
  }
  //kit.detach();
}
