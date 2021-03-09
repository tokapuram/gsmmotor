#include <SoftwareSerial.h>
SoftwareSerial gsm(10, 11); 
String bu;
String number;
int led=A3;
void setup()
{
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  Serial.begin(9600);
  gsm.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);
    
 while(1)
 {
   gsm.println("AT");
   delay(500);
   if(updateSerial().indexOf("OK")!=-1)
   {
    break;
   }
 }
   gsm.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  gsm.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
 

}

void loop()
{
while(gsm.available())  
{if(updateSerial().indexOf("on")!=-1)
{
  digitalWrite(led,LOW);
  Serial.println("on");
    gsm.println("AT+CMGS=\"+919704654772\"");
  updateSerial();
  gsm.print("motor on\ntokapuram.github.io/profile"); //text content
  updateSerial();
  gsm.write(26);
}
if(updateSerial().indexOf("off")!=-1)
{
  digitalWrite(led,HIGH);
  Serial.println("off");
      gsm.println("AT+CMGS=\"+919704654772\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  gsm.print("motor off\ntokapuram.github.io/profile"); //text content
  updateSerial();
  gsm.write(26);
}
 
}
}

String updateSerial()
{
  delay(500);
  while(gsm.available()) 
  {
    bu=gsm.readString();
    Serial.println(bu);//Forward what Software Serial received to Serial Port
  }
  return bu;
}
