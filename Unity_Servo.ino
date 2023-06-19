#include <Servo.h>

int data;
int temp;

Servo myservo;
int pos = 0; //Position of servo

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(A0,INPUT);
  myservo.attach(9);
}

void WriteServo()
{
  myservo.write(pos);
  delay(15);
}

void loop() 
{
  if (Serial.available())
  {
    //============================
    //       TEMP AND LED
    //============================
    //=====================
    //TURN ON TEMP AND LED
    //=====================

    data = Serial.read();
    if (data == 'T') //T for Temp
    {
      //Turn on light
      digitalWrite(2,HIGH);
      //Turn on temp
      digitalWrite(12,HIGH);
      digitalWrite(LED_BUILTIN, HIGH);
    }
    //=====================
    //TURN OFF TEMP AND LED
    //=====================

    else if (data == 't')
    {
      //Turn off light
      digitalWrite(2,LOW);
      //turn off temp
      digitalWrite(12,LOW);
      digitalWrite(LED_BUILTIN, LOW);
    }
    //============================
    //       SERVO CONTROL
    //============================
    //=====================
    //CONTROL SERVO TO 180
    //=====================

    if (data == "S") //S for servo //"S" == RIGHT
    {
      for (pos = 0; pos <= 180; pos += 1)
      {
        WriteServo();
      }
    }
    //=====================
    //CONTROL SERVO TO 0
    //=====================

    else if (data == "s") // "s" == LEFT
    {
      for (pos = 180; pos >= 0; pos -= 1)
      {
        WriteServo();
      }
    }
  }
  //==========================
  // UPDATE TEMP FOR UNITY
  //==========================

  if (digitalRead(12) == HIGH)
  {
    int reading = analogRead(A0);
    // Convert that reading into voltage
    // Replace 5.0 with 3.3, if you are using a 3.3V Arduino
    float voltage = reading * (5.0 / 1024.0);
    // Convert the voltage into the temperature in Celsius
    float temperatureC = (voltage - 0.5) * 100;
    Serial.println("Temp,", temperatureC);
  }
  else if (digitalRead(12) == LOW)
  {
    Serial.println("Temp,Off");
  }
  //==========================
  // UPDATE SERVO FOR UNITY
  //==========================
  if (myservo.attached() == true)
  {
    if (pos == 0)
    {
      Serial.println("Servo,0");
    }
    else if (pos == 180)
    {
      Serial.println("Servo,180");
    }
    else if (pos != 180 && pos != 0)
    {
      Serial.println("Servo,Changing");
    }
  }
  else
  {
    Serial.println("Servo,Off");
  }
  delay(250);
}
