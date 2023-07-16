#include <Servo.h>
int t = 1000;
const int savePb = 18, playPb = 21;
int save;
bool saveMode = false, playMode = false;

//Servo 1
const int Pot1=26, sPin1=4;
bool playPast = false,playPres = false;
float serPos1 = 0, savePos1 = 0;
float Val1;
Servo sv1;

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

}

void loop() {
  // put your main code here, to run repeatedly:
  //Servo1
  Val1 = analogRead(Pot1);
  serPos1 = (180./4095.)*Val1;
  sv1.write(serPos1);

  //Save position
  save = digitalRead(savePb);
  if(save == 0)
  {
    saveMode = true;
    savePos1 = serPos1;
    delay(t);
    Serial.print("savePos1 = ");
    Serial.println(savePos1);
  }

  //Continuous Play saved position
  playPres = digitalRead(playPb);

  if(playPres != playPast)
  {
    if(playPres == 0)
    {
      playMode = !playMode;
    }
    delay(t);
  }
  playPast = playPres;

  if(playMode)
  {
    saveMode = false;
    sv1.write(savePos1);
    delay(t);
    sv1.write(0);
    delay(t);
  }

}
