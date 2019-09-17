/* Controlling LED using Firebase console by CircuitDigest(www.circuitdigest.com) */
#include <ESP8266WiFi.h>                                                // esp8266 library
#include <FirebaseArduino.h>                                             // firebase library
#include <DHT.h>                                                            // dht11 temperature and humidity sensor library

#define ledPin 5
#define wakePin 16
#define FIREBASE_HOST "bathroom-28f4f.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "m7uvInuGgG4hqqyI91vuwlQtnqYkC5zsfciGhvFF"                  // the secret key generated from firebase
#define WIFI_SSID "Jesper P"                                         // input your home or public wifi name 
#define WIFI_PASSWORD "metoo123"                                  //password of wifi ssid
#define DHTPIN D4                                                           // what digital pin we're connected to
#define DHTTYPE DHT11                                                       // select dht type as DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);                                                     


String fireStatus = "";                                                     // led status received from firebase
int led = D1;


void setup() {
  Serial.begin(9600);
  delay(1000);  
  pinMode(LED_BUILTIN, OUTPUT);      
  pinMode(led, OUTPUT);               
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
  Firebase.setString("LED_STATUS", "OFF");  
  dht.begin();                                                               //Start reading dht sensor
}

void loop() { 

  
    fireStatus = Firebase.getString("LED_STATUS");              // get ld status input from firebase
    if (fireStatus == "ON" || fireStatus == "on") {                                   // compare the input of led status received from firebase
      Serial.println("Led Turned ON");                         
      digitalWrite(LED_BUILTIN, HIGH);                             // make bultin led ON
      digitalWrite(led, HIGH);                                    // make external led ON
    } 
     else if (fireStatus == "OFF" || fireStatus == "off") {                                // compare the input of led status received from firebase
      Serial.println("Led Turned OFF");
      digitalWrite(LED_BUILTIN, LOW);                                // make bultin led OFF
      digitalWrite(led, LOW);                                         // make external led OFF
    }
      
    else {
      Serial.println("Wrong Credential! Please send ON/OFF");
    }
  
  float h = dht.readHumidity();                                              // Reading temperature or humidity takes about 250 milliseconds!
  float t = dht.readTemperature();                                           // Read temperature as Celsius (the default)
    
  if (isnan(h) || isnan(t)) {                                                // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h) + String("%");                                         //convert integer humidity to string humidity 
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("°C ");
  String fireTemp = String(t) + String("°C");                                                     //convert integer temperature to string temperature
  delay(4000);
  
  Firebase.pushString("/DHT11/Humidity", fireHumid);                                  //setup path and send readings
  Firebase.pushString("/DHT11/Temperature", fireTemp);                                //setup path and send readings
   
}
