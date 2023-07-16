#include <Servo.h>
int t = 1000; //Delay
const int savePb1 = 18, savePb2 = 21, playPb = 22; //Save and Play buttons
int save1, save2; //Save variable
bool playPast = false,playPres = false; //Play variables for toggle button
bool saveMode1 = false, saveMode2 = false, playMode = false; //Mode for saving and playing
int Aspeed = 20, Bspeed = 20;
//A
int Apos1, Apos2, Apos3;
int AstartPos1, AstartPos2, AstartPos3;
//B
int Bpos1, Bpos2, Bpos3;
int BstartPos1, BstartPos2, BstartPos3;

int pos4, pos5, pos6;

//Servo 1
const int Pot1 = 26, sPin1 = 4;
float serPos1 = 0, AsavePos1 = 0, BsavePos1 = 0;
float Val1;
Servo sv1;

//Servo 2
const int Pot2 = 25, sPin2 = 17;
float serPos2 = 0, AsavePos2 = 0, BsavePos2 = 0;
float Val2;
Servo sv2;

//Servo 3
const int Pot3 = 32, sPin3 = 19;
float serPos3 = 0, AsavePos3 = 0, BsavePos3 = 0;
float Val3;
Servo sv3;

// //Servo 4
// const int Pot4 = 35, sPin4 = 23;
// float serPos4 = 0, savePos4 = 0;
// float Val4;
// Servo sv4;

void setup() {
  // put your setup code here, to run once:
  pinMode(savePb1, INPUT_PULLUP);
  pinMode(savePb2, INPUT_PULLUP);
  pinMode(playPb, INPUT_PULLUP);
  Serial.begin(9600);

  //Servo1
  pinMode(Pot1,INPUT);
  pinMode(sPin1,OUTPUT);
  sv1.attach(sPin1);
  sv1.write(serPos1);
  delay(t);

  //Servo2
  pinMode(Pot2,INPUT);
  pinMode(sPin2,OUTPUT);
  sv2.attach(sPin2);
  sv2.write(serPos2);
  delay(t);

  //Servo3
  pinMode(Pot3,INPUT);
  pinMode(sPin3,OUTPUT);
  sv3.attach(sPin3);
  sv3.write(serPos3);
  delay(t);

  // //Servo4
  // pinMode(Pot4,INPUT);
  // pinMode(sPin4,OUTPUT);
  // sv4.attach(sPin4);
  // sv4.write(serPos4);
  // delay(t);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Servo1
  Val1 = analogRead(Pot1);
  serPos1 = (180./4095.)*Val1;
  sv1.write(serPos1);

  //Servo2
  Val2 = analogRead(Pot2);
  serPos2 = (90./4095.)*Val2;
  sv2.write(serPos2);
  
  //Servo3
  Val3 = analogRead(Pot3);
  serPos3 = (90./4095.)*Val3;
  sv3.write(serPos3);

  // //Servo4
  // Val4 = analogRead(Pot4);
  // serPos4 = (90./4095.)*Val4;
  // sv4.write(serPos4);

  saved_1();
  saved_2();
  played();
  
}

void saved_1()
{
  //Save position
  save1 = digitalRead(savePb1);
  if(save1 == LOW)
  {
    saveMode1 = true;
    AsavePos1 = serPos1;
    AsavePos2 = serPos2;
    AsavePos3 = serPos3;
    // savePos4 = serPos4;

    delay(t);
    Serial.print("AsavePos1 = ");
    Serial.println(AsavePos1);
    Serial.println();
    Serial.print("AsavePos2 = ");
    Serial.println(AsavePos2);
    Serial.println();
    Serial.print("AsavePos3 = ");
    Serial.println(AsavePos3);

    // Serial.println();
    // Serial.print("savePos4 = ");
    // Serial.println(savePos4);
  }

}

void saved_2()
{
  //Save position
  save2 = digitalRead(savePb2);
  if(save2 == LOW)
  {
    saveMode2 = true;
    BsavePos1 = serPos1;
    BsavePos2 = serPos2;
    BsavePos3 = serPos3;

    delay(t);
    Serial.print("BsavePos1 = ");
    Serial.println(BsavePos1);
    Serial.println();
    Serial.print("BsavePos2 = ");
    Serial.println(BsavePos2);
    Serial.println();
    Serial.print("BsavePos3 = ");
    Serial.println(BsavePos3);
    // Serial.println();
    // Serial.print("savePos4 = ");
    // Serial.println(savePos4);
  }

}

void played()
{
  //Continuous Play saved position
  playPres = digitalRead(playPb);

  if(playPres != playPast)
  {
    if(playPres == 0)
    {
      playMode = !playMode;
      Serial.println(playPres);
    }
    delay(t);
  }
  playPast = playPres;

  if(playMode)
  {
    saveMode1 = false;
    saveMode2 = false;

    //A
    //Servo1
    AstartPos1 = sv1.read();
    for(Apos1 = AstartPos1; Apos1 <= AsavePos1; Apos1 += Aspeed)
    {
      sv1.write(Apos1);
       delay(500);
    }
    //Servo2
    AstartPos2 = sv2.read();
    for(Apos2 = AstartPos2; Apos2 <= AsavePos2; Apos2 += Aspeed)
    {
      sv2.write(Apos2);
       delay(500);
    }
    AstartPos3 = sv3.read();
    for(Apos3 = AstartPos3; Apos3 <= AsavePos3; Apos3 += Aspeed)
    {
      sv3.write(Apos3);
       delay(500);
    }
    // sv4.write(savePos4);

    //B
    //Servo1
    BstartPos1 = sv1.read();
    for(Bpos1 = BstartPos1; Bpos1 <= BsavePos1; Bpos1 += Bspeed)
    {
      sv1.write(Bpos1);
       delay(500);
    }
    //Servo2
    BstartPos2 = sv2.read();
    for(Bpos2 = BstartPos2; Bpos2 <= BsavePos2; Bpos2 += Bspeed)
    {
      sv2.write(Bpos2);
       delay(500);
    }
    BstartPos3 = sv3.read();
    for(Bpos3 = BstartPos3; Bpos3 <= BsavePos3; Bpos3 += Bspeed)
    {
      sv3.write(Bpos3);
       delay(500);
    }
    // sv4.write(0);
    
    //pos4, pos5, pos6
    //Servo1
    for(pos4 = Bpos1; pos4 >= AstartPos1; pos4 -= Aspeed)
    {
      sv1.write(pos4);
       delay(200);
    }
    //Servo2
    for(pos5 = Bpos2; pos5 >= AstartPos2; pos5-= Aspeed)
    {
      sv2.write(pos5);
       delay(200);
    }
    
    for(pos6 = Bpos3; pos6 >= AstartPos3; pos6 -= Aspeed)
    {
      sv3.write(pos6);
       delay(200);
    }
  }
}
