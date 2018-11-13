#define NUM_CHECKSUM 3
bool checksum_ok [NUM_CHECKSUM];
char *checksum_strings[MENU_ITEMS] =
  {"Ultrasonic", "Infra", "Encoders"};//Temp, Quad, Accel, Gyro

void M_checksum ()
{
  u8g.setFont(u8g_font_baby);
  for(int i=0; i<NUM_CHECKSUM; i++){
    checksum_ok[i] = false;
  }
  for(int i=0; i<NUM_CHECKSUM; i++)
  {
    M_check_sensor(i);
    if(!checksum_ok[i]) M_check_sensor(i);
    u8g.firstPage();
    do{
      for(int j=0; j<=i; j++)
      {
        u8g.setPrintPos(1, 6*j); u8g.print(*checksum_strings[j]);
        checksum_ok[j] ? u8g.print(" -OK-") : u8g.print(" -xx-");
      }
    }while(u8g.nextPage());
  }
  delay(500);
  //break_task = true;
}

void M_check_sensor (char _check)
{
  switch(_check)
  {
    case 0:
      if(read_Ultra('F')!=0 && read_Ultra('F')!=0 &&
         read_Ultra('F')!=0 && read_Ultra('F')!=0)
        checksum_ok[_check] = true;
    break;
    
    case 1:
      if(read_Infra('F',1)!=0 && read_Infra('F',2)!=0 &&
         read_Infra('E',1)!=0 && read_Infra('E',2)!=0 &&
         read_Infra('D',1)!=0 && read_Infra('D',2)!=0 &&
         read_Infra('T',1)!=0 && read_Infra('T',2)!=0)
        checksum_ok[_check] = true;
    break;
    
    case 2:
      setMotor(100,100,100,100); setMotor(0,0,0,0);
      if(enc_read[0]!=0 && enc_read[1]!=0 &&
         enc_read[2]!=0 && enc_read[3]!=0)
        checksum_ok[_check] = true;
    break;
  }
}

void M_ultra ()
{
  u8g.setFont(u8g_font_helvR08);//9x18);//unifont); -8px //-10px
  
  u8g.setPrintPos(54, 10); u8g.print(read_Ultra('F')); u8g.print(" cm"); //Frente
  u8g.setPrintPos(1, 36); u8g.print(read_Ultra('E')); u8g.print(" cm"); //Esquerda
  u8g.setPrintPos(86, 36); u8g.print(read_Ultra('D')); u8g.print(" cm"); //Direita
  u8g.setPrintPos(54, 62); u8g.print(read_Ultra('T')); u8g.print(" cm"); //Tras
}

void M_infra ()
{
  u8g.setFont(u8g_font_helvR08);//unifont); -8px
  
  u8g.setPrintPos(30, 8); u8g.print(read_Infra('F',1));
  u8g.setPrintPos(72, 8); u8g.print(read_Infra('F',2));
  
  u8g.setPrintPos(1, 25); u8g.print(read_Infra('E',1));
  u8g.setPrintPos(1, 46); u8g.print(read_Infra('E',2));
  
  u8g.setPrintPos(101, 25); u8g.print(read_Infra('D',1));
  u8g.setPrintPos(101, 46); u8g.print(read_Infra('D',2));
  
  u8g.setPrintPos(30, 62); u8g.print(read_Infra('T',1));
  u8g.setPrintPos(72, 62); u8g.print(read_Infra('T',2));
}

void M_accel()
{
  u8g.setFont(u8g_font_helvR08);//unifont); -8px
  
  u8g.setPrintPos(10, 8); u8g.print(readAccel('X'));
  u8g.setPrintPos(10, 24); u8g.print(readAccel('Y'));
  u8g.setPrintPos(10, 40); u8g.print(readAccel('Z'));
  
}

void M_gyro()
{
  u8g.setFont(u8g_font_helvR08);//unifont); -8px
  
  u8g.setPrintPos(40, 8); u8g.print(readAccel('X'));
  u8g.setPrintPos(40, 24); u8g.print(readAccel('Y'));
  u8g.setPrintPos(40, 40); u8g.print(readAccel('Z'));
  
}

