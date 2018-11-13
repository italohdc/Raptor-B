const uint8_t welcome_bitmap[] U8G_PROGMEM = {
  0x18,0x18,         // 00000000 
  0x66,0x66,         // 01010101
  0x81,0x99,          // 01111111
  0xbc,0x3d,         // 00111110
  0x81,0x99,         // 00111110 
  0x66,0x66,         // 00111110
  0x18,0x18,         // 00111110 
  0x0,  0x0           // 01111111
};

void draw_welcome() {
 u8g.firstPage();  
  do {
    //u8g.drawBitmapP( 1, 1, 2, 8, welcome_bitmap);
    
    u8g.setFont(u8g_font_helvB18);
    u8g.drawStr( 8, 28, "Raptor B");
    u8g.setFont(u8g_font_helvB08);
    u8g.drawStr( 12, 40, "Rescue Maze");
    
    u8g.setFont(u8g_font_p01type);
    u8g.setPrintPos(108, 6); u8g.print(battery_level()); u8g.print("V");
    u8g.setFont(u8g_font_u8glib_4);
    //u8g.setFont(u8g_font_osb21);
    if (!EXECUTAR_TESTE) u8g.drawStr( 52, 61, "START");
    if (EXECUTAR_TESTE) u8g.drawStr( 53, 61, "TESTE");
    //u8g.drawStr( 104, 61, "menu >");
  } while( u8g.nextPage() );
  //delay(5);
  //delay(10);
}

void draw_setup() {
 u8g.firstPage();  
  do {
    //u8g.drawBitmapP( 1, 1, 2, 8, welcome_bitmap);
    
    u8g.setFont(u8g_font_helvB18);
    u8g.drawStr( 8, 28, "Raptor B");
    u8g.setFont(u8g_font_helvB08);
    u8g.drawStr( 12, 40, "Rescue Maze");
    
    u8g.setFont(u8g_font_p01type);
    u8g.setPrintPos(108, 6); u8g.print(battery_level()); u8g.print("V");
    u8g.setFont(u8g_font_u8glib_4);
    //u8g.setFont(u8g_font_osb21);
    u8g.drawStr( 48, 61, "loading...");
    //u8g.drawStr( 104, 61, "menu >");
  } while( u8g.nextPage() );
  //delay(5);
  //delay(10);
}

//  ...---...
void draw() {
 u8g.firstPage();  
  do {
    //u8g.setFont(u8g_font_u8glib_4);
    //u8g.setFont(u8g_font_osb21);
    //if(lcd_function_name == ""){
      //u8g.drawStr( 1, 6, "Raptor B");
      //u8g.drawStr( 1, 16,lcd_function_name);
    //}
    //else
    //  u8g.drawStr( 1, 6, "Raptor B,");
    //--//
    
    //u8g.setFont(u8g_font_unifont);
    //u8g.setPrintPos(21, 21); //u8g.print(ler_temp_NANO(103));
    //u8g.print(read_button_MENU()); u8g.print("  ");//map_readTravel('F'));
    //u8g.print(analogRead(pin_button_MENU));//map_readTravel('E'));
    //u8g.print(map_readTravel('D'));
    //u8g.print(map_readTravel('T'));
    
    //u8g.setFont(u8g_font_osb21);
    //u8g.drawStr( 0, 22, "Hello World!");
    
    if(PRINT_MAZE) draw_maze();
    
    //M_ultra();
  } while( u8g.nextPage() );
  
  //delay(50);
}

void print_info (char info[16]) {
 u8g.firstPage();  
  do {
    u8g.setPrintPos(2, 21); u8g.print(info);
    if(PRINT_MAZE) draw_maze();
  } while( u8g.nextPage() );
  //delay(50);
}

void print_int (char info[16], int d1) {
 u8g.firstPage();  
  do {
    u8g.setPrintPos(2, 21); u8g.print(info);
    u8g.setPrintPos(2, 35); u8g.print(d1);
    if(PRINT_MAZE) draw_maze();
  } while( u8g.nextPage() );
  //delay(50);
}

void print_data (int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8) {
 u8g.firstPage();  
  do {
    u8g.setPrintPos(2, 10); u8g.print(d1); u8g.print(" "); u8g.print(d2);
    u8g.setPrintPos(2, 20); u8g.print(d3); u8g.print(" "); u8g.print(d4);
    u8g.setPrintPos(2, 30); u8g.print(d5); u8g.print(" "); u8g.print(d6);
    u8g.setPrintPos(2, 40); u8g.print(d7); u8g.print(" "); u8g.print(d8);
    if(PRINT_MAZE) draw_maze();
  } while( u8g.nextPage() );
  //delay(50);
}

void print_info_data (char d1[16], int d2, char d3[16], int d4, char d5[16], int d6,
                      char d7[16], int d8, char d9[16], int d10, char d11[16], int d12) {
 u8g.firstPage();  
  do {
    u8g.setPrintPos(2, 10); u8g.print(d1); u8g.print(" "); u8g.print(d2);
    u8g.setPrintPos(2, 20); u8g.print(d3); u8g.print(" "); u8g.print(d4);
    u8g.setPrintPos(2, 30); u8g.print(d5); u8g.print(" "); u8g.print(d6);
    u8g.setPrintPos(2, 40); u8g.print(d7); u8g.print(" "); u8g.print(d8);
    u8g.setPrintPos(2, 50); u8g.print(d9); u8g.print(" "); u8g.print(d10);
    u8g.setPrintPos(2, 60); u8g.print(d11); u8g.print(" "); u8g.print(d12);
    if(PRINT_MAZE) draw_maze();
  } while( u8g.nextPage() );
  //delay(50);
}

void print_info_char (char d1[16], char d2, char d3[16], char d4, char d5[16], char d6,
                      char d7[16], char d8, char d9[16], char d10, char d11[16], char d12) {
 u8g.firstPage();  
  do {
    u8g.setPrintPos(2, 10); u8g.print(d1); u8g.print(" "); u8g.print(d2);
    u8g.setPrintPos(2, 20); u8g.print(d3); u8g.print(" "); u8g.print(d4);
    u8g.setPrintPos(2, 30); u8g.print(d5); u8g.print(" "); u8g.print(d6);
    u8g.setPrintPos(2, 40); u8g.print(d7); u8g.print(" "); u8g.print(d8);
    u8g.setPrintPos(2, 50); u8g.print(d9); u8g.print(" "); u8g.print(d10);
    u8g.setPrintPos(2, 60); u8g.print(d11); u8g.print(" "); u8g.print(d12);
    if(PRINT_MAZE) draw_maze();
  } while( u8g.nextPage() );
  //delay(50);
}
