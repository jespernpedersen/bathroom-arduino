//Code for the www.MakeUseOf.com Wi-Fi connected Button tutorial by Ian Buckley
 
#include <IFTTTWebhook.h>
#include <ESP8266WiFi.h>
 
#define ledPin 5
#define wakePin 16
#define ssid "Jesper P"
#define password "metoo123"
#define IFTTT_API_KEY "bze9-KISVD6x3rlquF1VQS"
#define IFTTT_EVENT_NAME "pushbutton"
 
void setup() {
  Serial.begin(9600);
  while(!Serial) {
  }
  Serial.println(" ");// print an empty line before and after Button Press    
  Serial.println("Button Pressed");
  Serial.println(" ");  
 
  connectToWifi();
 
  IFTTTWebhook hook(IFTTT_API_KEY, IFTTT_EVENT_NAME);
  hook.trigger();
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);  
  delay(200);              
  digitalWrite(ledPin, LOW);
 
 
 
 
  ESP.deepSleep(wakePin);
}
 
 
void connectToWifi() {
  // Serial.print("Connecting to: NAME "); //uncomment next line to show SSID name
  Serial.print(ssid);
  WiFi.begin(ssid, password);  
  Serial.println(" ");
  Serial.print("Attempting to connect: ");
 
  //try to connect for 10 seconds
  int i = 10;
  while(WiFi.status() != WL_CONNECTED && i >=0) {
    delay(1000);
    Serial.print(i);
    Serial.print(", ");
    i--;
  }
  Serial.println(" ");
 
  //print connection result
  if(WiFi.status() == WL_CONNECTED){
  Serial.print("Connected.");
  Serial.println(" ");
  Serial.print("NodeMCU ip address: ");
  Serial.println(WiFi.localIP());
  }
  else{
    Serial.println("Connection failed - check your credentials or connection");
  }
}
 
 
 
void loop(){
//if deep sleep is working, this code will never run.
Serial.println("This should never get printed");
delay(1000);
}
