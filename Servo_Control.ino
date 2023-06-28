#include <Servo.h>

int data;
int temp;

Servo myservo;

int pos; //Position of servo

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(A0,INPUT);
  myservo.attach(9);
  pos = 0;
}

void CheckServoState()
{
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
    else if (pos == 1 || pos == 179) 
    {
      Serial.println("Servo,Changing");
    }
  }
  else
  {
    Serial.println("Servo,Off");
  }
}

void CheckTempState()
{
  if (digitalRead(12) == HIGH)
  {
    int reading = analogRead(A0);
    // Convert that reading into voltage
    // Replace 5.0 with 3.3, if you are using a 3.3V Arduino
    float voltage = reading * (5.0 / 1024.0);
    // Convert the voltage into the temperature in Celsius
    float temperatureC = (voltage - 0.5) * 100;
    Serial.print("Temp,");
    Serial.println(temperatureC);
  }
  else if (digitalRead(12) == LOW)
  {
    Serial.println("Temp,Off");
  }
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

    if (data == 'S') //S for servo //"S" == RIGHT
    {
      for (int count = 0; count <= 180; count += 1)
      {
        pos = count;
        myservo.write(pos);
        delay(15);
        CheckServoState();

        //While servo is checked, the temp also needs to be checked for simultaneous updated
        if (count%20 == 0)
        {
          CheckTempState();
        }
      }
    }
    //=====================
    //CONTROL SERVO TO 0
    //=====================

    else if (data == 's') // "s" == LEFT
    {
      for (int count = 180; count >= 0; count -= 1)
      {
        pos = count;
        myservo.write(pos);
        delay(25);
        CheckServoState();

        //While servo is checked, the temp also needs to be checked for simultaneous updated
        if (count%20 == 0)
        {
          CheckTempState();
        }
        
  }
    }
  }
  //==========================
  // UPDATE TEMP FOR UNITY
  //==========================

  CheckTempState();
  
  delay(500);
}
