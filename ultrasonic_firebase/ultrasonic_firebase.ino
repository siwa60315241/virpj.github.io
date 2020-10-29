#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <time.h>

// Config Firebase
#define FIREBASE_HOST "virpj-5c808.firebaseio.com"
#define FIREBASE_AUTH "rNtv49Y7HgtJOrXB58V0C2uYY9MMEN0EPsRJjV7s"

// Config connect WiFi
// Config connect WiFi
#define WIFI_SSID "WiFi-NU"
#define WIFI_PASSWORD ""


int ECHO_PIN    = D1;
int TRIGGER_PIN = D2;

#define DEBUG_WIFICONNECT 14
#define DEBUG_PUTHDATA 5
// Config time
int timezone = 7;


char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";

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
   long duration;
  long distance;
  String outofrange;
  
  digitalWrite(TRIGGER_PIN, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
    if (distance <= 10){
  Serial.println("Out of range");
  delay(500);
  }
  else {
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
  }
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  
  root["distance"] = distance;
  root["time_ultra"] = NowString();
  root["date_ultra"] = NowStringdate();

  digitalWrite(DEBUG_PUTHDATA, HIGH);
  // append a new value to /LM1
  String name = Firebase.push("Ultrasonic", root);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /Ultrasonic failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /Ultrasonic/");
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
