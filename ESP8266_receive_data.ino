/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLhiFjOkEt"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "1dJzplaqxYw-9qFszMxDQtNRYQT2u1tw"
#define SwitchPin1 10
#define RelayPin1 5 
#define VPIN_BUTTON_1    V0
// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#define IN1 5
#define IN2 4
#define IN3 14
#define IN4 12
#define melodyPin 2

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "pitches.h"
#include <Servo.h>

Servo servo;
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "UiTiOt-Staff";
char pass[] = "UiTiOtAP";
int wifiFlag = 0;
int toggleState_1 = 1;
int check = 0;
int checkfloor1 = 0;
int checkf1 = 0;
int checkfloor2 = 0;
int checkf2 = 0;
int flag=0;
BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes


BLYNK_WRITE(V0)
{
  if (check==0)
  {
    check=1;
    servo.write(150);    
  }
  else
  {
    check=0;
    servo.write(0);
  }
}


BLYNK_WRITE(V11)
{
  if (checkfloor1 == 0)
  {
    checkfloor1 = 1;
    digitalWrite(12, HIGH);    
  }
  else
  {
    checkfloor1 = 0;
    digitalWrite(12, LOW);
  }
}

BLYNK_WRITE(V12)
{
  if (checkf1 == 0)
  {
    checkf1 = 1;
    digitalWrite(13, HIGH);    
  }
  else
  {
    checkf1 = 0;
    digitalWrite(13, LOW);
  }
}
//------------------------------
BLYNK_WRITE(V13)
{
  if (checkfloor2 == 0)
  {
    checkfloor2 = 1;
    digitalWrite(10, HIGH);    
  }
  else
  {
    checkfloor2 = 0;
    digitalWrite(10, LOW);
  }
}
BLYNK_WRITE(V14)
{
  if (checkf2 == 0)
  {
    checkf2 = 1;
    digitalWrite(14, HIGH);    
  }
  else
  {
    checkf2 = 0;;
    digitalWrite(14, LOW);
  }
}
BLYNK_WRITE(V10)
{
  servo.write(130);
}

//

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}
int wish_melody[] = {
  NOTE_B3, 
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
};

int wish_tempo[] = {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
};
// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  
  // You can send any value at any time.
  int isButtonPressed = digitalRead(5);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("Cảnh báo có cháy");
    digitalWrite(2,LOW);    
    
    flag=1;
  }
  else if (isButtonPressed==0)
  {
    digitalWrite(2,HIGH);
    flag=0;
      
  }
  // Please don't send more that 10 values per second.

}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  servo.attach(15); // NodeMCU D8 pin
  servo.write(0);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(14, OUTPUT); 
  pinMode(2, OUTPUT);     
  pinMode(5,INPUT_PULLUP); 
  // Setup a function to be called every second
  timer.setInterval(500L, myTimerEvent);
}
void relayOnOff(){

  if(toggleState_1 == 1){
      digitalWrite(RelayPin1, LOW); // turn on relay 1
      toggleState_1 = 0;
      Serial.println("Device1 ON");
    }
    else{
      digitalWrite(RelayPin1, HIGH); // turn off relay 1
      toggleState_1 = 1;
      Serial.println("Device1 OFF");
    }
    delay(100);  
}

void with_internet(){
    //Manual Switch Control
}
void without_internet(){
    //Manual Switch Control
    if (digitalRead(SwitchPin1) == LOW){
      delay(200);
      relayOnOff();      
    }
}



void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi Not Connected");
  }
  else
  {
    
    Blynk.run();
  }
  timer.run();
  if (wifiFlag == 0)
    with_internet();
  else
    without_internet();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

