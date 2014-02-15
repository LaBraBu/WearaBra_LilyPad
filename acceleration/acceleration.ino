float VD=3.256;
void setup(){
  Serial.begin(9600);
}
void loop(){
  float x=analogRead(2)*VD/1024;
  float y=analogRead(3)*VD/1024;
  float z=analogRead(4)*VD/1024;
  Serial.print("X=");
  Serial.print(x);
  Serial.print("\tY=");
  Serial.print(y);
  Serial.print(" Z=");
  Serial.print(z);
  float xv=x-VD/2.0;
  float yv=y-VD/2.0;
  float zv=z-VD/2.0;
  Serial.print(" Xv=");
  Serial.print(xv);
  Serial.print(" Yv=");
  Serial.print(yv);
  Serial.print(" Zv=");
  Serial.print(z);
  float xg=xv/(0.3*VD/3.0);
  float yg=yv/(0.3*VD/3.0);
  float zg=zv/(0.3*VD/3.0);
  Serial.print(" Xg=");
  Serial.print(xg);
  Serial.print(" Yg=");
  Serial.print(yg);
  Serial.print(" Zg=");
  Serial.println(zg);

  if(zg>0){
    digitalWrite(13,LOW);
  }
  else{
    digitalWrite(13,HIGH);
  }

  delay(300);
}



