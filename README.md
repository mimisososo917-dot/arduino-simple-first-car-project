# 🚗 Arduino Dual-Mode Smart Car Project

> This project is every student's first project in robotics. We will be making an Arduino smart car that is controlled with Bluetooth and also has obstacle detection (your choice) . 
---

## 🛠️ Components Used
* **Microcontroller:** Arduino Uno
* **Motor Driver:** L298N
* **Actuation:** 2x DC Motors with wheels, 1x SG90 Servo Motor
* **Sensors:** HC-SR04 Ultrasonic Distance Sensor
* **Communication:** Bluetooth Module (BT-5 / HM-10 running with Dabble app)
* **Power Source:**  18650 Li-ion cells
* **Power Control:** Slide Switch / Rocker Switch (for main battery power toggle)
---

## 📌 Pin Configuration
| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **Bluetooth (BT-5)** | Pins 2 & 3 | RX / TX communication | !!! A MUST ! CANNOT CHANGE !
| **Servo Motor** | Pin 4 | Ultrasonic sensor sweeping |
| **Motor Driver (ENA)** | Pin 6 | Right motor speed (PWM) |
| **Motor Driver (IN1 / IN2)** | Pins 7 & 8 | Right motor direction |
| **Motor Driver (IN3 / IN4)** | Pins 9 & 10 | Left motor direction |
| **Motor Driver (ENB)** | Pin 11 | Left motor speed (PWM) |
| **Ultrasonic (Trig)** | Pin A0 | Distance trigger |
| **Ultrasonic (Echo)** | Pin A1 | Distance echo return |

---

## ⚙️ How the Code Works

### 1. Bluetooth Control Mode
only need to uncomment it in the code sent.
Using the Dabble smartphone app GamePad module, commands are sent over serial communication to direct the car manually.

### 2. Autonomous Obstacle Avoidance
The ultrasonic sensor constantly reads distance. If an object is closer than 12cm, the robot stops, backs up, sweeps its servo left and right to compare open space, and turns toward the clearer path.

---

## 🚀 Getting Started & Installation
1. Clone or download this repository.
2. Open the `.ino` file inside the **Arduino IDE**.
3. Install the required libraries (**Dabble** and **Servo**).
4. Select your board and port, then upload the code!

---

## 📝 Personal Notes & Challenges Faced
-if robot keeps spining rather then moving forward in no obstacle mode , u need to change the wiring of the motor driver ( OUT ). 
-when u use the bluetooth module u need to have TX -> pin 2  RX -> pin 3   , U CANNOT CHANGE THEM  or else it won't work. 
-When soldering wires to the DC motors, start by soldering a red and black wire to one motor. Then, mirror the exact same wire placement on the other motor; this ensures consistent wheel rotation and prevents directional mismatches later.
