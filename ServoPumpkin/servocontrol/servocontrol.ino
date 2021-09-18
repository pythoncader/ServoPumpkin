#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, so you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;
int myrandom = 0;
int pass = 0;
int top3 = 0;
int top1 = 1;
int bottom3 = 2;
int top4 = 3;
int bottom4 = 4;
int bottom2 = 5;
int bottom1 = 6;
int top2 = 7;


//all of these minimum and maximums are defining each servo individually.
//update them to fit your needs so the servos don't over-rotat
int min0 = 30;
int max0 = 100;
int min1 = 30;
int max1 = 80;
int min2 = 85;
int max2 = 180;

int min3 = 95;
int max3 = 180;
int min4 = 40;
int max4 = 100;

int min5 = 85;
int max5 = 180;
int min6 = 25;
int max6 = 110;
int min7 = 5;
int max7 = 80;
int currentAngles[] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  //yield();
}

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   return pulse;
}
void set_angle(int channel, int myangle, float servowait=1){
  currentAngles[channel] = myangle;
  pwm.setPWM(channel, 0, angleToPulse(myangle));
  Serial.print("servowait: ");
  Serial.println(servowait*1000);
  delay(servowait*1000);
}
//pick random based on the range of each channel
int pickrandom(int channel){
  switch (channel) {
  case 0:
    myrandom = random(min0, max0);
    return myrandom;
  case 1:
    myrandom = random(min1, max1);
    return myrandom;
  case 2:
    myrandom = random(min2, max2);
    return myrandom;
  case 3:
    myrandom = random(min3, max3);
    return myrandom;
  case 4:
    myrandom = random(min4, max4);
    return myrandom;
  case 5:
    myrandom = random(min5, max5);
    return myrandom;
  case 6:
    myrandom = random(min6, max6);
    return myrandom;
  case 7:
    myrandom = random(min7, max7);
    return myrandom;
}
}
// have the other function pick a random angle based on a given channel, then tell the servo on that channel to move to that angle.
int settorandom(int channel, float servowait=0){
  set_angle(channel, pickrandom(channel), servowait);
}

//
//this runs continually:
void loop() {
  for(int i=0; i<8; i++){ //run through the eight servos on eight channels respectively
    settorandom(i); //call the other function with the looped channel
    delay(random(0, 300)); //wait a little bit before telling another servo to move.
  }
}

//Written by pythoncader
/*
Creative Commons License
*/
