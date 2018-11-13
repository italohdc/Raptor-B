

float battery_level ()
{
  return analogRead(pin_battery) * 0.0128;//0.0123035714;
}

void teste_encoder ()
{
  do{
    setMotor(-100,-100,-100,-100);
  }while(read_button_MENU() == 0);
  
  setMotor(-20,-20,-20,-20); delay(5);
  setMotor(0,0,0,0);
  
  print_info_data("encoders", 0,
                  "m1", enc_read[0],
                  "m2", enc_read[1],
                  "m3", enc_read[2],
                  "m4", enc_read[3],
                  " ", 0);
  while(1);
}

void teste_temp ()
{
//  u8g.firstPage();  
//  do {
//    u8g.setPrintPos(2, 21); u8g.print(tempVitima);
//    draw_maze();
//  } while( u8g.nextPage() );
  
//  while(1){
    u8g.firstPage();  
    do {
      u8g.setFont(u8g_font_helvR08);//9x18);//unifont); -8px //-10px
      
      u8g.setPrintPos(12, 12); u8g.print(ler_temp_NANO(102)); u8g.print("*C"); //F1
      u8g.setPrintPos(12, 50); u8g.print(ler_temp_NANO(103)); u8g.print("*C"); //E
      u8g.setPrintPos(50, 12); u8g.print(ler_temp_NANO(104)); u8g.print("*C"); //F2
      u8g.setPrintPos(50, 50); u8g.print(ler_temp_NANO(105)); u8g.print("*C"); //D
    } while( u8g.nextPage() );
//  }
}

void teste_90(){
if (read_button_MENU()==3){
  quadrante_direita();
}
if (read_button_MENU()==1){
  quadrante_esquerda();
}
}




void teste_motor ()
{
  setMotor(100,100,100,100); delay(1000);
  setMotor(-100,100,-100,100); delay(1000);
  setMotor(-100,-100,-100,-100); delay(1000);
  setMotor(100,-100,100,-100); delay(1000);
}

void draw_teste ()
{
  u8g.firstPage();  
  do {
    //M_ultra();
    //M_infra();
  } while( u8g.nextPage() );
}

void teste ()
{
  //quadrante_frente();
  //quadrante_esquerda();
  //setMotor(TP,TP+7,TP,TP+7);
  //delay_encoder('S', 30);
  //while(true) parar(100);
  
  //setMotor(0,TP,0,0);
//  delay(500);
//  setMotor(0,TP,0,0);
//  delay(500);
//  setMotor(0,0,TP,0);
//  delay(500);
//  setMotor(0,0,0,TP);
//  delay(500);
  //delay_encoder('S', 30);
  //parar(100);

//  LOG(enc_read[0]); LOG("\t");
//  LOG(enc_read[1]); LOG("\t");
//  LOG(enc_read[2]); LOG("\t");
//  LOG(enc_read[3]); LOGLN("\t");
  
  //setMotor(-TP,TP,-TP,TP);
  //delay_encoder('A', 90);
  //while(true) parar(100);
  
  //setMotor(0,0,TP,0);
  //delay_encoder('A', 90);
  //parar(100);*/
  
  //ajustar_parede_ESQUERDA();
 // delay(400);
  
  //LOGLN(read_Infra('F',2)); //LOG("\t");
  //LOG(read_Infra('F',1)); LOG("\t");
  //LOGLN(read_Infra('F',2));
  
//  read_distance_wall();
//  LOG(distance_wall('F')); LOG("\t");
//  LOG(distance_wall('T')); LOG("\t");
//  LOG(distance_wall('E')); LOG("\t");
//  LOGLN(distance_wall('D'));
//  
  LOG(read_Infra('F',1)); LOG("\t");
  LOG(read_Infra('F',2)); LOG("\t");
  LOG(read_Infra('E',1)); LOG("\t");
  LOG(read_Infra('E',2)); LOG("\t");
  LOG(read_Infra('D',1)); LOG("\t");
  LOG(read_Infra('D',2)); LOG("\t");
  LOG(read_Infra('T',1)); LOG("\t");
  LOG(read_Infra('T',2)); LOGLN("\t");
  //LOGLN(read_corQuad());
// LOG("TEMP E: "); 
//  LOG(ler_temp_NANO(103)); LOG("\t");
//  LOG("TEMP FE: "); 
//  LOG(ler_temp_NANO(102)); LOG("\t");
//  LOG("TEMP FD: "); 
//  LOG(ler_temp_NANO(104)); LOG("\t");
//  LOG("TEMP D: "); 
//  LOGLN(ler_temp_NANO(105)); 
//LOGLN("//////////////////////////////");
//LOG(ler_temp_NANO(103)); LOG('\t'); LOG(ler_temp_NANO(102));LOG('\t'); LOG(ler_temp_NANO(104));LOG('\t'); LOGLN(ler_temp_NANO(105));
//int leitura=max(ler_temp_NANO(102),ler_temp_NANO(103));
//leitura = max(leitura,ler_temp_NANO(104));
//leitura = max(leitura,ler_temp_NANO(105));
//LOGLN(leitura);
//  LOGLN(readAccel('X'));
  //teste_temp();//encoder();
  //teste_encoder();//motor();
//  if (distance_wall('T') > 5) //APROXIMAR C/ ULTRA
//      setMotor(-90, -90, -90, -90);
//    else if (distance_wall('T') < 5) //AFASTAR C/ ULTRA
//      setMotor(90, 90, 90, 90);
//
//  LOG(read_Infra('T',1)); LOG("\t");
//  LOG(read_Infra('T',2)); LOGLN("\t");
//ajustar_parede_ESQUERDA();
//mecanum(-120);
//setMotor_encoderBACK(100,10);
  //quadrante_tras(); parar(500);
  //quadrante_direita(); quadrante_direita(); parar(500);
  
  //13 102 104 105
  //rampa_subir_PID();
  //lcd_function_name = "Tremaux";
  //flash__save_maze();
}
