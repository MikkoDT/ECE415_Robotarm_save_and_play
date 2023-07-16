#include <Servo.h>
int t = 1000; //Delay
const int savePb1 = 18, savePb2 = 21, playPb = 22; //Save and Play buttons
int save1, save2; //Save variable
bool playPast = false,playPres = false; //Play variables for toggle button
bool saveMode1 = false, saveMode2 = false, playMode = false; //Mode for saving and playing

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

    sv1.write(moveTo(AsavePos1));
    sv2.write(AsavePos2);
    sv3.write(AsavePos3);
    // sv4.write(savePos4);
    delay(t);

    sv1.write(BsavePos1);
    sv2.write(BsavePos2);
    sv3.write(BsavePos3);
    // sv4.write(0);
    delay(t);
  }
}
