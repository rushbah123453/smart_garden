//A0,A1,A2,A3 are pin number of soil humidity sensor to arduino
//it senses the moisture level of soil and sends msg accordingly


const int trigPin = 2;
const int echoPin = 4;
const int motorPin = 7;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  long duration, cm;
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);  

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
   
  if(cm<100)
  {
    digitalWrite(motorPin, HIGH);
//    Serial.println(cm);
//    Serial.println("Water level is low!!!MOTOR IS TURNED ON");
    delay(5000);
  }
  if(cm>100)
  {
    digitalWrite(motorPin, LOW);
//    Serial.println(cm);
//    Serial.println("Water level is high!!!MOTOR IS TURNED OFF");
    delay(5000);
  }

  int sensorValue1 = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  int sensorValue4 = analogRead(A3);
  int sensorValue3 = analogRead(A2);

  sms(sensorValue1 ,sensorValue2 ,sensorValue3 ,sensorValue4 );
  while(1);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / (29* 2);
} 
void sms(int sensor1,int sensor2,int sensor3,int sensor4)
{
  float percentage1, percentage2, percentage3, percentage4;
  int ans1, ans2, ans3, ans4;
  ans1 = 1023 - sensor1;
  percentage1 = ans1 * 0.09765625;
  ans2 = 1023 - sensor2;
  percentage2 = ans2 * 0.09765625;
  ans3 = 1023 - sensor3;
  percentage3 = ans3 * 0.09765625;
  ans4 = 1023 - sensor4;
  percentage4 = ans4 * 0.09765625;

  Serial.print("AT+CMGF=1\r\n");
  delay(5000);
  Serial.print("AT+CMGS=\"");
  Serial.print("9552388824");
  Serial.println("\"\r\n");
  delay(2000);
    
  //  if(ans1<120)
    {
  Serial.print("SENSOR 1:");
  Serial.print( ans1);
  Serial.print(" moisture");
  Serial.println(percentage1);  
    }
  //  if(ans2<120)
    {
  Serial.print("SENSOR 2:");
  Serial.print( ans2);
  Serial.print(" moisture");
  Serial.println(percentage2);  
    }

  //  if(ans3<120)
    {
  Serial.print("SENSOR 3:");
  Serial.print( ans3);
  Serial.print(" moisture");
  Serial.println(percentage3);  
    }
  //  if(ans4<120)
    {
  Serial.print("SENSOR 4:");
  Serial.print( ans4);
  Serial.print(" moisture");
  Serial.println(percentage4);  
    }
  Serial.write(0x1A);
}
