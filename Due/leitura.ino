//int accelX=0, accelY=0, accelZ=0;
sensors_event_t event;

float readAccel (char dim) // val_imu = readAccel('X');
{
  accel.getEvent(&event);
  //accel.read(&accelX, &accelY, &accelZ);
  
  if(dim == 'X' || dim == 'x')
    return event.acceleration.x;//accelX;
  
  if(dim == 'Y' || dim == 'y')
    return event.acceleration.y;//accelY;
  
  if(dim == 'Z' || dim == 'z')
    return event.acceleration.z;//accelZ;
}

float readGyroscope (char dim) // val_imu = readAccel('X');
{
  itg3205.itg3205ReadGyro();
  
  if(dim == 'X' || dim == 'x')
    return itg3205.itg3205GyroX();
  
  if(dim == 'Y' || dim == 'y')
    return itg3205.itg3205GyroY();
  
  if(dim == 'Z' || dim == 'z')
    return itg3205.itg3205GyroZ();
}

/////ULTRASONIC/////
int wall_Esq=0, wall_Dir=0, wall_Frente=0, wall_Tras = 0;

void read_distance_wall ()
{
  wall_Frente = read_Ultra('F');
  wall_Esq = read_Ultra('E');
  wall_Dir = read_Ultra('D');
  wall_Tras = read_Ultra('T');
}

void read_ultra_individual (char parede)
{
  if(parede == 'E' || parede == 'L'){ wall_Esq = read_Ultra('E');}
    
  
  else if(parede == 'D' || parede == 'R'){ wall_Dir = read_Ultra('D');}
    
  
  else if(parede == 'F'){
    wall_Frente = read_Ultra('F');}
    
  
  else if(parede == 'T' || parede == 'B'){
    wall_Tras = read_Ultra('T');}
    
    else{}
    
}

float distance_wall (char parede)
{
  if(parede == 'E' || parede == 'L')
    return wall_Esq;
  
  if(parede == 'D' || parede == 'R')
    return wall_Dir;
  
  if(parede == 'F')
    return wall_Frente;
  
  if(parede == 'T' || parede == 'B')
    return wall_Tras;
}

float read_Ultra (char lado)
{
  byte pingPin=0; float duration, cm;
  if(lado == 'F') pingPin=pin_ultraFrente;
  if(lado == 'E' || lado == 'L') pingPin=pin_ultraEsq;
  if(lado == 'D' || lado == 'R') pingPin=pin_ultraDir;
  if(lado == 'T' || lado == 'B') pingPin=pin_ultraTras;
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  cm = duration / 29/2;
  return cm;
  
  delayMicroseconds(2);
}

int read_Infra (char lado, char pos)
{
  if(lado == 'F' && pos==1) return analogRead(pin_infraFrente1); //FRENTE
  if(lado == 'F' && pos==2) return analogRead(pin_infraFrente2); //FRENTE
  
  if(lado == 'E' && pos==1) return analogRead(pin_infraEsq1); //ESQ
  if(lado == 'E' && pos==2) return analogRead(pin_infraEsq2); //ESQ
  
  if(lado == 'D' && pos==1) return analogRead(pin_infraDir1); //DIR
  if(lado == 'D' && pos==2) return analogRead(pin_infraDir2); //DIR
  
  if(lado == 'T' && pos==1) return analogRead(pin_infraTras1); //TRAS
  if(lado == 'T' && pos==2) return analogRead(pin_infraTras2); //TRAS
}

int read_corQuad ()
{
  return analogRead(pin_infraBaixo);
}
/////==========/////

float absolut(float a) {
  if(a >= 0) 
    return a;
  else
    return (-a); 
}
