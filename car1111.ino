#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>


// Ultrasonic Pins (Ultrasonic on Analog pins A0/A1 to keep 2 & 3 free for BT-5)
const int Trig = A0;
const int Echo = A1;
const int spoint = 103;

// Motor Driver Pins
const int enableRightMotor = 6;  // ENA (PWM Speed)
const int rightMotorPin1 = 7;    // IN1
const int rightMotorPin2 = 8;    // IN2

const int enableLeftMotor = 11;  // ENB (PWM Speed)
const int leftMotorPin1 = 9;     // IN3
const int leftMotorPin2 = 10;    // IN4


int distance;
int Left = 0;
int Right = 0;
int Speed = 200; // Motor speed

void setup() {
  Serial.begin(9600);
  Serial.println("Robot Booting Up...");

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
 

  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  rotateMotor(0, 0);

  // Dabble automatically uses Pins 2 (RX) and 3 (TX) on Arduino Uno/Nano for BT-5
  Dabble.begin(9600);
  Serial.println("System Ready!");
}

void loop() {
  // --- CHOOSE YOUR ACTIVE MODE ---
  
  // Mode 1: Control your robot using the Dabble GamePad app via BT-5
  DabbleControl();

  // Mode 2: Autonomous Obstacle Avoidance (Uncomment below if you want to test obstacle mode)
  Obstacle();
}

void DabbleControl() {
  Dabble.processInput(); // Reads BT-5 commands from the app

  int rightMotorSpeed = 0;
  int leftMotorSpeed = 0;

  if (GamePad.isUpPressed()) {
    rightMotorSpeed = Speed;
    leftMotorSpeed = Speed;
  }
  else if (GamePad.isDownPressed()) {
    rightMotorSpeed = -Speed;
    leftMotorSpeed = -Speed;
  }
  else if (GamePad.isLeftPressed()) {
    rightMotorSpeed = Speed;
    leftMotorSpeed = -Speed; // Turn left on the spot
  }
  else if (GamePad.isRightPressed()) {
    rightMotorSpeed = -Speed;
    leftMotorSpeed = Speed; // Turn right on the spot
  }

  rotateMotor(rightMotorSpeed, leftMotorSpeed);
}

void Obstacle() {
  distance = ultrasonic();
  
  if (distance <= 12) {
    // 1. Stop momentarily
    rotateMotor(0, 0);
    delay(100);

    // 2. FIRST: Back up for a fixed time (roughly 6 cm of movement)
    rotateMotor(-Speed, -Speed);
    delay(300);                  // Back up duration
    rotateMotor(0, 0);
    delay(150);

    // 3. THEN: Spin 90 degrees (using a balanced delay to prevent battery sag)
    rotateMotor(Speed, -Speed);  // Spin right on the spot
    delay(750);                  // Adjusted turn duration 
    rotateMotor(0, 0);
    delay(150);
  } else {
    // Path is clear, drive straight forward
    rotateMotor(Speed, Speed); 
  }
}
// Noise-filtered ultrasonic distance reading function
int ultrasonic() {
  long sum = 0;
  int successfulReads = 0;

  for (int i = 0; i < 3; i++) {
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);

    long t = pulseIn(Echo, HIGH, 30000); // 30ms timeout for open spaces
    if (t > 0) {
      sum += (t / 29 / 2);
      successfulReads++;
    }
    delay(5);
  }

  if (successfulReads == 0) {
    return 250; // Safe default for open space
  }
  return sum / successfulReads;
}

// Unified motor rotation function
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);    
  } else {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);         
  }

  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);    
  } else {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);         
  }analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));     
}

