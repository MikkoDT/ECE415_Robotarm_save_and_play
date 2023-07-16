#include <Servo.h>
int t = 1000;
const int savePb = 18, playPb = 21;
int save;
bool saveMode = false, playMode = false;
bool playPast = false,playPres = false;

//Servo 1
const int Pot1 = 26, sPin1 = 4;
float serPos1 = 0, savePos1 = 0;
float Val1;
Servo sv1;

//Servo 2
const int Pot2 = 25, sPin2 = 17;
float serPos2 = 0, savePos2 = 0;
float Val2;
Servo sv2;

//Servo 3
const int Pot3 = 32, sPin3 = 19;
float serPos3 = 0, savePos3 = 0;
float Val3;
Servo sv3;

void setup() {
  // put your setup code here, to run once:
  pinMode(savePb, INPUT_PULLUP);
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

  save_play();
  
}

void save_play()
{
  //Save position
  save = digitalRead(savePb);
  if(save == 0)
  {
    saveMode = true;
    savePos1 = serPos1;
    savePos2 = serPos2;
    savePos3 = serPos3;
    delay(t);
    Serial.print("savePos1 = ");
    Serial.println(savePos1);
    Serial.println();
    Serial.print("savePos2 = ");
    Serial.println(savePos2);
    Serial.println();
    Serial.print("savePos3 = ");
    Serial.println(savePos3);
  }

  //Continuous Play saved position
  playPres = digitalRead(playPb);

  if(playPres != playPast)
  {
    if(playPres == 0)
    {
      playMode = !playMode;
      Serial.println(playPres);
    }
    delay(250);
  }
  playPast = playPres;

  if(playMode)
  {
    saveMode = false;
    sv1.write(savePos1);
    sv2.write(savePos2);
    sv3.write(savePos3);
    delay(t);

    sv1.write(0);
    sv2.write(0);
    sv3.write(0);
    delay(t);
  }

}
