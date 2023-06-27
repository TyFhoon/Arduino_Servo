#include <Servo.h>

Servo myservo;
int pos; //Position of servo

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  myservo.attach(9); //Attach to a pin
  pos = 0;
}

void loop()
{
  //2 for loops that increase and decrease the angle of the servo meter
  for (int count = 0; count <= 180; count += 1)
  {
    pos = count;
    myservo.write(pos);
    delay(15);
    Serial.println(pos);
  }
  for (int count = 180; count >= 0; count -= 1)
  {
    pos = count;
    myservo.write(pos);
    delay(15);
    Serial.println(pos);
  }
  Serial.println(pos);
  
}
