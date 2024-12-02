# Health Monitoring System
## Description
- Two sensors will take in the heartbeat and temperature and once the data has been read, it will send out a signal that will light up either red or green based on whether the user is healthy or not. If the client has inconsistent heartbeats, the LED will blink red. If the user has abnormal temperature, then the LED will blink green. And if the user has abnormal heartbeats then it will blink red.
## Setup
- We will require a Arduino, breadboard, MAX30102 sensor, a DHT22 sensors, and jumper wires.
- Supply power to the power rails of the breadboard using the 5V and gnd ports.
- For the DHT22 sensor, connect the power and ground ports to the respective power rails. Connect the data port to pin 2 of the Arduino.
- For the MAX30102 sensor, connect the power and ground ports to the respective power rails. Connect the SCL port to the A5 pin and the SDA port to the A4 pin.
- Connect the green LED to pin 7 and the red LED to pin 8.
## How to Use
- Once setup, connect the Arduino to power and load the Arduino with the code.
- The HMS (Health Monitoring System) will keep looping back till it senses a heartbeat.
- Once the heartbeat is sensed it will read the temperature and calculate the heartbeat.
- It will return an output to the LEDs after it processes both the temperature and heartbeat.
