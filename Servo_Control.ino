#include <Servo.h>

Servo myservo;
int pos = 0; //Position of servo

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  myservo.attach(9); //Attach to a pin
}

void loop()
{
  //2 for loops that increase and decrease the angle of the servo meter
  for (pos = 0; pos <= 180; pos += 1)
  {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1)
  {
    myservo.write(pos);
    delay(15);
  }
}
