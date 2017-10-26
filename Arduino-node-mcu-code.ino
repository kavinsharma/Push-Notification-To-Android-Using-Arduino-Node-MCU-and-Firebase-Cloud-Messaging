// ___________________________Libraries Included Here ___________________________________
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// _________________________defining constant
#define FIREBASE_HOST "esri-eea51.firebaseio.com"
#define FIREBASE_AUTH "qULRQbnuzJ3qkAdYunMasgcLlKtpXic1UQ1FxHvM"
#define WIFI_SSID "kavin"
#define WIFI_PASSWORD "12345612"
#define Lat_Long "30.332628 77.998622"
// __________________________variable definied
float fire_sensor=A0;
float fire_value;


void setup()
{  
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  pinMode(fire_sensor,INPUT);
// connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("fire_sensor", 0);
  Firebase.setString("lat_long", "0");
  
}

void loop()
{
fire_value=analogRead(fire_sensor);
Serial.println("fire sensor value");
Serial.println(fire_value);
delay(1);
//delay in between reads for stability 
if(fire_value<350){

  // initialize digital pin LED_BUILTIN as an output.
  Firebase.setInt("fire_sensor_status", 1);
  Firebase.setString("lat_long", Lat_Long);
  
  digitalWrite(D1, HIGH);
  delay(500);
  digitalWrite(D1, LOW);
  delay(500);
}
else{
  Firebase.setInt("fire_sensor_status", 0);
   Firebase.setString("lat_long", "0");
  digitalWrite(D1, LOW);
  delay(10);
}
}

