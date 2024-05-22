#include <ESP8266WiFi.h>
#include <Bounce2.h>

// WiFi credentials
const char* ssid = "2info4";
const char* password = "12345678";

// Define relay control pins
const int relayPins[] = {D1, D2, D3, D4};

// Define button pins
const int buttonPins[] = {D5, D6, D7, D8};

Bounce debouncer[4];

void setup() {
  Serial.begin(115200);

   //Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
   Serial.println(WiFi.localIP());

  // Initialize relays and buttons
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);

    pinMode(buttonPins[i], INPUT_PULLUP);
    debouncer[i] = Bounce();
    debouncer[i].attach(buttonPins[i]);
    debouncer[i].interval(50);
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    debouncer[i].update();

    if (debouncer[i].fell()) {
      // Button pressed, toggle the relay state
      digitalWrite(relayPins[i], !digitalRead(relayPins[i]));
    }
  }
}