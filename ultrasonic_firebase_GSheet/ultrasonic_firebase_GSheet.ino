#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <time.h>
#include <WiFiClientSecureAxTLS.h>

// Config Firebase
#define FIREBASE_HOST "virpj-5c808.firebaseio.com"
#define FIREBASE_AUTH "rNtv49Y7HgtJOrXB58V0C2uYY9MMEN0EPsRJjV7s"

// Config connect WiFi
// Config connect WiFi
#define WIFI_SSID "WiFi-NU"
#define WIFI_PASSWORD ""
//#define WIFI_SSID "Lee"
//#define WIFI_PASSWORD "60315241"


int ECHO_PIN    = D1;
int TRIGGER_PIN = D2;

#define DEBUG_WIFICONNECT 14
#define DEBUG_PUTHDATA 5
// Config time


int dst = 0;

void setup() {
 
  pinMode(DEBUG_WIFICONNECT, OUTPUT);
  pinMode(DEBUG_PUTHDATA, OUTPUT);

  pinMode(TRIGGER_PIN, OUTPUT);
     pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(DEBUG_WIFICONNECT, !digitalRead(DEBUG_WIFICONNECT));
    delay(500);
  }
  digitalWrite(DEBUG_WIFICONNECT, HIGH);
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  GG_ScriptSheet();
 delay(5000);
}
  void GG_ScriptSheet(){
//   YOUR SCRIPT = https://script.google.com/macros/s/AKfycbweatt_gdGsU9rstnQHePO2xf_wUtX1npQFn30NRrkRbAw5LqHV/exec
  // U can test script by fill:   /?&FIELD1=16&FIELD2=18  
  axTLS::WiFiClientSecure client;
  const char* HOST = "script.google.com";
  const char* GScriptId = "AKfycbweatt_gdGsU9rstnQHePO2xf_wUtX1npQFn30NRrkRbAw5LqHV";  
  //float TEMP HUMD
//  float TEMP = (random(2,50))/3.00;
//  float HUMD = (random(20,80))/3.00;
  long duration;
  long distance;
  digitalWrite(TRIGGER_PIN, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  
  Firebase.set("Ultrasonic/distance",distance);
  String url32 = String("/macros/s/") + GScriptId + "/exec?&FIELD1="+(String) distance;
  Serial.print("Client.Connecting...");
  
  if (client.connect(HOST, 443)) {
    client.println("GET " + String(url32) + " HTTP/1.0"); //HTTP/1.0 OK sent LINEnotify and GoogleSheet
    client.println("Host: " + String(HOST));
    client.println("User-Agent: ESP8266\r\n");
    client.println("Connection: close\r\n\r\n");
    //client.println(true ? "" : "Connection: close\r\n");
    //client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Type: application/json");    
    //2client.println("Connection: close");    
    client.println("Content-Length: " + String(url32.length()));
    client.println();
    //client.println(postData);
    client.print("\r\n\r\n");
    Serial.print("Response...");  
  }
  Serial.println("OK !!!");  
}
 
