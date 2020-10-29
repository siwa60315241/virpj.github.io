#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <time.h>

// Config Firebase
#define FIREBASE_HOST "virpj-5c808.firebaseio.com"
#define FIREBASE_AUTH "rNtv49Y7HgtJOrXB58V0C2uYY9MMEN0EPsRJjV7s"

// Config connect WiFi
// Config connect WiFi
//#define WIFI_SSID "WiFi-NU"
//#define WIFI_PASSWORD ""
#define WIFI_SSID "Lee"
#define WIFI_PASSWORD "60315241"


#define buttonPin D1
int buttonPushCounter = 0;   // counter for the number of button presses

int buttonState = 0;         // current state of the button

int lastButtonState = 0;     // previous state of the button

#define DEBUG_WIFICONNECT 14
#define DEBUG_PUTHDATA 5
// Config time
int timezone = 7;


char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";

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

  configTime(timezone * 3600, dst, ntp_server1, ntp_server2, ntp_server3);
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Now: " + NowString());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

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
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  
  root["buttonState"] = buttonState;
  root["buttonPushCounter"] = buttonPushCounter;
  
  root["time"] = NowString();
   root["date"] = NowStringdate();

  digitalWrite(DEBUG_PUTHDATA, HIGH);
  // append a new value to /LM1
  String name = Firebase.push("LM1", root);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /LM1 failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /LM1/");
  Serial.println(name);
  delay(2000);
  digitalWrite(DEBUG_PUTHDATA, LOW);
  delay(3000);
}

String NowString() {
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);

  String tmpNow = "";
  tmpNow += String(newtime->tm_hour);
  tmpNow += ":";
  tmpNow += String(newtime->tm_min);
  tmpNow += ":";
  tmpNow += String(newtime->tm_sec);

  return tmpNow;
}
String NowStringdate() {
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);

  String tmpNow = "";
  tmpNow += String(newtime->tm_mday);
  tmpNow += "/";
  tmpNow += String(newtime->tm_mon + 1);
  tmpNow += "/";
  tmpNow += String(newtime->tm_year + 1900);
  return tmpNow;
}
