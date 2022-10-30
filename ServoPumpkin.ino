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

//all of these minimum and maximums are defining each servo individually.
//update them to fit your needs so the servos don't over-rotate
int min0 = 35;
int max0 = 82;
int min1 = 137;
int max1 = 180;
int min2 = 35;
int max2 = 84;

int min3 = 80;
int max3 = 135;
int min4 = 30;
int max4 = 70;

int min5 = 90;
int max5 = 140;
int min6 = 80;
int max6 = 150;
int min7 = 38;
int max7 = 83;

int currentAngles[] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  //yield();
}

int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX); // map angle of 0 to 180 to Servo min and Servo max
  return pulse;
}
void set_angle(int channel, int myangle, float servowait = 1) {
  currentAngles[channel] = myangle;
  pwm.setPWM(channel, 0, angleToPulse(myangle));
  Serial.print("servowait: ");
  Serial.println(servowait * 1000);
  delay(servowait * 1000);
}
//pick random based on the range of each channel
int pickrandom(int channel) {
  switch (channel) {
    case 0:
      return random(min0, max0);
    case 1:
      return random(min1, max1);
    case 2:
      return random(min2, max2);
    case 3:
      return random(min3, max3);
    case 4:
      return random(min4, max4);
    case 5:
      return random(min5, max5);
    case 6:
      return random(min6, max6);
    case 7:
      return random(min7, max7);
  }
}
// have the other function pick a random angle based on a given channel, then tell the servo on that channel to move to that angle.
int settorandom(int channel, float servowait = 0) {
  set_angle(channel, pickrandom(channel), servowait);
}

//
//this runs continually:
void loop() {
  for (int i = 0; i < 8; i++) { //run through the eight servos on eight channels respectively
    settorandom(i); //call the other function with the looped channel
    delay(random(0, 300)); //wait a little bit before telling another servo to move.
  }
}

//Written by pythoncader
/*
  Creative Commons License
*/
