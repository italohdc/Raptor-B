void setMotor (int amm, int bmm, int cmm, int dmm)
{
  ////////////////////F/E////////////////////
  if(amm>0){  // + FRENTE
    digitalWrite(motor1b, LOW);
    digitalWrite(motor1a, HIGH);
    analogWrite(motor1_pwm, amm);
  }
  if(amm<0){  // - TRAS
    amm*=-1;
    digitalWrite(motor1a, LOW);
    digitalWrite(motor1b, HIGH);
    analogWrite(motor1_pwm, amm);
  }
  if(amm==0){  // 0 PARAR
    digitalWrite(motor1a, LOW);
    digitalWrite(motor1b, LOW);
    analogWrite(motor1_pwm, 0);
  }
  
  ////////////////////F/D////////////////////
  if(bmm>0){  // + FRENTE
    digitalWrite(motor2b, LOW);
    digitalWrite(motor2a, HIGH);
    analogWrite(motor2_pwm, bmm);
  }
  if(bmm<0){  // - TRAS
    bmm*=-1;
    digitalWrite(motor2a, LOW);
    digitalWrite(motor2b, HIGH);
    analogWrite(motor2_pwm, bmm);
  }
  if(bmm==0){  // 0 PARAR
    digitalWrite(motor2a, LOW);
    digitalWrite(motor2b, LOW);
    analogWrite(motor2_pwm, 0);
  }
  
  ////////////////////T/E////////////////////
  if(cmm>0){  // + FRENTE
    digitalWrite(motor3b, LOW);
    digitalWrite(motor3a, HIGH);
    analogWrite(motor3_pwm, cmm);
  }
  if(cmm<0){  // - TRAS
    cmm*=-1;
    digitalWrite(motor3a, LOW);
    digitalWrite(motor3b, HIGH);
    analogWrite(motor3_pwm, cmm);
  }
  if(cmm==0){  // 0 PARAR
    digitalWrite(motor3a, LOW);
    digitalWrite(motor3b, LOW);
    analogWrite(motor3_pwm, 0);
  }
  
  ////////////////////T/D////////////////////
  if(dmm>0){  // + FRENTE
    digitalWrite(motor4b, LOW);
    digitalWrite(motor4a, HIGH);
    analogWrite(motor4_pwm, dmm);
  }
  if(dmm<0){  // - TRAS
    dmm*=-1;
    digitalWrite(motor4a, LOW);
    digitalWrite(motor4b, HIGH);
    analogWrite(motor4_pwm, dmm);
  }
  if(dmm==0){  // 0 PARAR
    digitalWrite(motor4a, LOW);
    digitalWrite(motor4b, LOW);
    analogWrite(motor4_pwm, 0);
  }
}

void parar(int t)
{
  setMotor(0,0,0,0);
  delay(t);
}

void mecanum (int mma)
{
  int mmb;
  if(mma > 0){
    mmb = mma+80;
    setMotor(mmb,-mma,-mma,mmb);
  }
  if(mma < 0){
    mmb = mma-80;
    setMotor(mmb,-mma,-mma,mmb);
  }
}
