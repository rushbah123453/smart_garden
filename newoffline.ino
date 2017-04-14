int readf=0,readf2=0,readf3=0;
int  static flag=0,flag2=0,flag3=0;
 int static sensorValue1,sensorValue2;
#include <SoftwareSerial.h>
SoftwareSerial GPRS(7, 8); // RX, TX

enum _parseState {
  PS_DETECT_MSG_TYPE,

  PS_IGNORING_COMMAND_ECHO,

  PS_READ_CMTI_STORAGE_TYPE,
  PS_READ_CMTI_ID,

  PS_READ_CMGR_STATUS,
  PS_READ_CMGR_NUMBER,
  PS_READ_CMGR_SOMETHING,
  PS_READ_CMGR_DATE,
  PS_READ_CMGR_CONTENT
};

byte state = PS_DETECT_MSG_TYPE;

char buffer[80];
byte pos = 0;

int lastReceivedSMSId = 0;
boolean validSender = false;

void resetBuffer() {
  memset(buffer, 0, sizeof(buffer));
  pos = 0;
}

void setup()
{
  GPRS.begin(9600);
  Serial.begin(9600);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
  // Set as appropriate for your case
  pinMode(3, INPUT);
  pinMode(5, INPUT);
    pinMode(4, INPUT);
    pinMode(A1,INPUT);
       pinMode(A0,INPUT);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
digitalWrite(10, HIGH);
digitalWrite(11, HIGH);  
digitalWrite(12, HIGH); 
   //readf=0;
   //readf2=0;
  int sensorValue2 = analogRead(A1);
  int sensorValue4 = analogRead(A3);
  int sensorValue3 = analogRead(A2);
digitalWrite(10, HIGH);
  for (int i = 1; i <= 15; i++) {
    GPRS.print("AT+CMGD=");
    GPRS.println(i);
    delay(200);

    // Not really necessary but prevents the serial monitor from dropping any input
    while(GPRS.available()) 
      Serial.write(GPRS.read());
  }
}

void loop()
{
  readf=0;
  readf2=0;
  readf3=0;
  flag=0,flag2=0,flag3=0;
   sensorValue1 = analogRead(A1);
   sensorValue2 = analogRead(A0);
     Serial.print("value of s1:- ");
  Serial.print(sensorValue1);
  Serial.print("value of s2:- ");
   Serial.print(sensorValue1);

  
  while(GPRS.available()) {
    parseATText(GPRS.read());
  /*  delay(20);
     digitalWrite(10, HIGH);
  delay(15);
readf=digitalRead(4);
Serial.print(readf);
if(readf==1)
{
  digitalWrite(10, LOW);
  delay(10);
  Serial.print("relay on");
}*/
  }
      // digitalWrite(10, HIGH);
  
     // digitalWrite(10, HIGH);
  delay(15);
readf=digitalRead(5);
readf2=digitalRead(3);
readf3=digitalRead(2);
Serial.print(readf);
if(flag==0)
{
if(readf==1)
{
  readf=0;
  //if(sensorValue1>600){
 // if( sensorValue1 >360){
  digitalWrite(10, LOW);
  delay(6000);
  flag=1;
   digitalWrite(10, HIGH);
  //}

}
 if(readf==0)
{
  digitalWrite(10, HIGH);
}
}



//}







if(flag2==0)
{
if(readf2==1)
{

  Serial.print("in flag2");
  Serial.print(readf2);
  readf2=0;
  //if(sensorValue1>600){
  digitalWrite(11, LOW);
  delay(6000);
  flag2=1;
   digitalWrite(11, HIGH);
  
 /* if(readf==0 || readf2==0){
     digitalWrite(10, HIGH);
     digitalWrite(11, HIGH);}
     delay(20);
  Serial.print("relay on");
  //}*/
}
 if(readf==0)
{
  digitalWrite(11, HIGH);
}







}



if(flag3==0)
{
if(readf3==1)
{

  Serial.print("in flag3");
  Serial.print(readf3);
  readf3=0;
  //if(sensorValue1>600){
  digitalWrite(12, LOW);
  delay(6000);
  flag3=1;
   digitalWrite(12, HIGH);
  
 /* if(readf==0 || readf2==0){
     digitalWrite(10, HIGH);
     digitalWrite(11, HIGH);}
     delay(20);
  Serial.print("relay on");
  //}*/
}
 if(readf3==0)
{
  digitalWrite(12, HIGH);
}







}









}

void parseATText(byte b) {

  buffer[pos++] = b;

  if ( pos >= sizeof(buffer) )
    resetBuffer(); // just to be safe

  /*
   // Detailed debugging
   Serial.println();
   Serial.print("state = ");
   Serial.println(state);
   Serial.print("b = ");
   Serial.println(b);
   Serial.print("pos = ");
   Serial.println(pos);
   Serial.print("buffer = ");
   Serial.println(buffer);*/

  switch (state) {
  case PS_DETECT_MSG_TYPE: 
    {
      if ( b == '\n' )
        resetBuffer();
      else {        
        if ( pos == 3 && strcmp(buffer, "AT+") == 0 ) {
          state = PS_IGNORING_COMMAND_ECHO;
        }
        else if ( pos == 6 ) {
          //Serial.print("Checking message type: ");
          //Serial.println(buffer);

          if ( strcmp(buffer, "+CMTI:") == 0 ) {
            Serial.println("Received CMTI");
            state = PS_READ_CMTI_STORAGE_TYPE;
          }
          else if ( strcmp(buffer, "+CMGR:") == 0 ) {
            Serial.println("Received CMGR");            
            state = PS_READ_CMGR_STATUS;
          }
          resetBuffer();
        }
      }
    }
    break;

  case PS_IGNORING_COMMAND_ECHO:
    {
      if ( b == '\n' ) {
        //Serial.print("Ignoring echo: ");
        //Serial.println(buffer);
        state = PS_DETECT_MSG_TYPE;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMTI_STORAGE_TYPE:
    {
      if ( b == ',' ) {
        Serial.print("SMS storage is ");
        Serial.println(buffer);
        state = PS_READ_CMTI_ID;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMTI_ID:
    {
      if ( b == '\n' ) {
        lastReceivedSMSId = atoi(buffer);
        Serial.print("SMS id is ");
        Serial.println(lastReceivedSMSId);

        GPRS.print("AT+CMGR=");
        GPRS.println(lastReceivedSMSId);
        //delay(500); don't do this!

        state = PS_DETECT_MSG_TYPE;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_STATUS:
    {
      Serial.print("b =");
      Serial.print(b);
      if ( b == ',' ) {
        Serial.print("CMGR status: ");
        Serial.println(buffer);
        state = PS_READ_CMGR_NUMBER;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_NUMBER:
    {
      if ( b == ',' ) {
        Serial.print("CMGR number: ");
        Serial.println(buffer);

        // Uncomment these two lines to check the sender's cell number
        //validSender = false;
        //if ( strcmp(buffer, "\"+0123456789\",") == 0 )
        validSender = true;

        state = PS_READ_CMGR_SOMETHING;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_SOMETHING:
    {
      if ( b == ',' ) {
        Serial.print("CMGR something: ");
        Serial.println(buffer);
        state = PS_READ_CMGR_DATE;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_DATE:
    {
      if ( b == '\n' ) {
        Serial.print("CMGR date: ");
        Serial.println(buffer);
        state = PS_READ_CMGR_CONTENT;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_CONTENT:
    {
      if ( b == '\n' ) {
        Serial.print("CMGR content: ");
        Serial.print(buffer);

        parseSMSContent();

        GPRS.print("AT+CMGD=");
        GPRS.println(lastReceivedSMSId);
        //delay(500); don't do this!

        state = PS_DETECT_MSG_TYPE;
        resetBuffer();
      }
    }
    break;
  }
}

void parseSMSContent() {

  char* ptr = buffer;

  while ( strlen(ptr) >= 2 ) {

    if ( ptr[0] == 'm' ) {
      if ( ptr[1] == '1' )
       { digitalWrite(10, LOW);
       Serial.print("in on");
        delay(5000);
              digitalWrite(10, HIGH);
        }
      else
        digitalWrite(10, HIGH);
    }

    if ( ptr[0] == 'n' ) {
      if ( ptr[1] == '1' ){
        digitalWrite(11, LOW);
        delay(5000);
              digitalWrite(11, HIGH);}
      else
      
        digitalWrite(11, HIGH);
    }
  if ( ptr[0] == 'o' ) {
      if ( ptr[1] == '1' ){
        digitalWrite(12, LOW);
        delay(5000);
              digitalWrite(12, HIGH);}
      else
        digitalWrite(12, HIGH);
    }
    ptr += 2;
  }
}



