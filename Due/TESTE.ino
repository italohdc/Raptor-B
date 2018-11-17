

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
    u8g.firstPage();  
    do {
      u8g.setFont(u8g_font_helvR08);//9x18);//unifont); -8px //-10px
      
      u8g.setPrintPos(12, 12); u8g.print(ler_temp_NANO(102)); u8g.print("*C"); //F1
      u8g.setPrintPos(12, 50); u8g.print(ler_temp_NANO(103)); u8g.print("*C"); //E
      u8g.setPrintPos(50, 12); u8g.print(ler_temp_NANO(104)); u8g.print("*C"); //F2
      u8g.setPrintPos(50, 50); u8g.print(ler_temp_NANO(105)); u8g.print("*C"); //D
    } while( u8g.nextPage() );
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

// ======= //
// SANDBOX //
// ======= //

void teste ()
{
  LOG(read_Infra('F',1)); LOG("\t");
  LOG(read_Infra('F',2)); LOG("\t");
  LOG(read_Infra('E',1)); LOG("\t");
  LOG(read_Infra('E',2)); LOG("\t");
  LOG(read_Infra('D',1)); LOG("\t");
  LOG(read_Infra('D',2)); LOG("\t");
  LOG(read_Infra('T',1)); LOG("\t");
  LOG(read_Infra('T',2)); LOGLN("\t");
}
