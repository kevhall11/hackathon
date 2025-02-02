#include <SoftwareSerial.h>
#include <NewPing.h>

// Bluetooth Module
SoftwareSerial BT(2, 3); // RX | TX

// Motor Driver Pins
#define ENA 6
#define ENB 5
#define IN1 13
#define IN2 12
#define IN3 11
#define IN4 10

// Ultrasonic Sensor Pins
#define TRIG1 7
#define ECHO1 8
#define TRIG2 9
#define ECHO2 A0
#define MAX_DISTANCE 200
NewPing sonar1(TRIG1, ECHO1, MAX_DISTANCE);
NewPing sonar2(TRIG2, ECHO2, MAX_DISTANCE);

// Soil & Temperature Sensors
#define SOIL_SENSOR A1
#define TEMP_SENSOR A2

int motorSpeed = 150; // Default speed (0-255)

void setup() {
    Serial.begin(9600);
    BT.begin(9600);
    
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(SOIL_SENSOR, INPUT);
    pinMode(TEMP_SENSOR, INPUT);
}

void loop() {
    if (BT.available()) {
        char command = BT.read();
        processCommand(command);
    }
    
    // Check Ultrasonic Sensors
    if (sonar1.ping_cm() < 5 || sonar2.ping_cm() < 5) {
        stopMotors();
    }
    
    // Read and store sensor data
    int soilData = analogRead(SOIL_SENSOR);
    int tempData = analogRead(TEMP_SENSOR);
    Serial.print("Sensor1 "); Serial.println(soilData);
    Serial.print("Sensor2 "); Serial.println(tempData);
    processCommand(readJSON());
    delay(500);
}

void processCommand(char cmd) {
    switch(cmd) {
        case 'F': moveForward(); break;
        case 'B': moveBackward(); break;
        case 'L': turnLeft(); break;
        case 'R': turnRight(); break;
        case 'S': stopMotors(); break;
        case '+': adjustSpeed(10); break;
        case '-': adjustSpeed(-10); break;
    }
}

void moveForward() {
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void moveBackward() {
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void turnLeft() {
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnRight() {
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void stopMotors() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void adjustSpeed(int change) {
    motorSpeed = constrain(motorSpeed + change, 0, 255);
}
def readJSON(){
      if (Serial.available()) {
    // Create a buffer for incoming data
    StaticJsonDocument<capacity> doc;
    
    // Read the JSON string from Serial
    String jsonString = Serial.readStringUntil('\n');
    
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, jsonString);

    // Test if parsing succeeds
    if (error) {
      Serial.print("{\"error\":\"deserialize failed: ");
      Serial.print(error.c_str());
      Serial.println("\"}");
      return;
    }

    
  }
}
