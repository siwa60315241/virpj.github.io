#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <WiFiClientSecureAxTLS.h>

// Config Firebase
#define FIREBASE_HOST "virpj-5c808.firebaseio.com"
#define FIREBASE_AUTH "rNtv49Y7HgtJOrXB58V0C2uYY9MMEN0EPsRJjV7s"

// Config connect WiFi
#define WIFI_SSID "WiFi-NU"
#define WIFI_PASSWORD ""
//#define WIFI_SSID "Lee"
//#define WIFI_PASSWORD "60315241"

#define buttonPin D1
int buttonPushCounter = 0;   // counter for the number of button presses

int buttonState = 0;         // current state of the button

int lastButtonState = 0;     // previous state of the button


#define DEBUG_WIFICONNECT 14
#define DEBUG_PUTHDATA 5
// Config time


int dst = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  
  pinMode(DEBUG_WIFICONNECT, OUTPUT);
  pinMode(DEBUG_PUTHDATA, OUTPUT);



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
 delay(2000);
}
  void GG_ScriptSheet(){
//   YOUR SCRIPT = https://script.google.com/macros/s/AKfycbwP_dt64wXHOObKaZfVZLkRz4O4oEe0mcdyQm8tmq0e1Vv4e2I/exec
  // U can test script by fill:   /?&FIELD1=16&FIELD2=18  
  axTLS::WiFiClientSecure client;
  const char* HOST = "script.google.com";
  const char* GScriptId = "AKfycbwP_dt64wXHOObKaZfVZLkRz4O4oEe0mcdyQm8tmq0e1Vv4e2I";  
  
  buttonState = digitalRead(buttonPin);
    // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
      // if the state has changed, increment the counter
      if (buttonState == HIGH) {
        // if the current state is HIGH then the button went from off to on:
        buttonPushCounter++;
        
      } else {
      }
    }
    lastButtonState = buttonState;
   
//   String data1 = ""+ String(buttonState)+ ", "+  String(buttonPushCounter) + "";
//   Serial.println(data1);


  Serial.println(buttonState);

 Serial.println(buttonPushCounter);  
  
  
  Firebase.set("LM1/buttonState",buttonState);
  Firebase.set("LM1/buttonPushCounter",buttonPushCounter);
  String url32 = String("/macros/s/") + GScriptId + "/exec?&FIELD1="+(String) buttonState + "&FIELD2="+(String) buttonPushCounter;;
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
 
