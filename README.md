Wi-Fi Controlled Mobile Car with ESP8266
This project demonstrates how to build a mobile car that can be controlled over Wi-Fi using an ESP8266 microcontroller. 
The ESP8266 hosts a web server that provides a simple control interface for moving the car forward, backward, left, right, stop, and track its location via Bluetooth.

Features:
+ Control Car Over Wi-Fi: The car can be controlled using a web interface accessible from any device connected to the same network.
+ Bluetooth Integration: Allows location tracking of the car, which is displayed on the web interface.
+ Responsive Web UI: The control interface is responsive and can be accessed from both desktop and mobile devices.

Components Used:
+ ESP8266 (NodeMCU or similar)
+ Motor Driver (H-Bridge) for controlling the motors
+ DC Motors connected to the car
+ Bluetooth module (SoftwareSerial is used for communication)
+ Web-based control panel

Pin Configuration:
ESP8266 Pin	- Function
D0	        - ENA (Motor A speed control)
D1	        - IN1 (Motor A direction 1)
D2	        - IN2 (Motor A direction 2)
D3	        - IN3 (Motor B direction 1)
D4	        - IN4 (Motor B direction 2)
D5	        - ENB (Motor B speed control)
D6	        - Bluetooth TX (ESP8266 RX)
D7	        - Bluetooth RX (ESP8266 TX)

How It Works:
+ Web Interface:
The ESP8266 runs a simple HTTP web server which serves a control panel with the following buttons
Forward (Tiến)
Backward (Lùi)
Left (Trái)
Right (Phải)
Stop (Dừng)
Track Location (Track)
Each button sends a request to a corresponding route on the ESP8266 (e.g., /tien for moving forward). The car’s movement is controlled by adjusting the GPIO pins connected to the motor driver, enabling motor control.
+ Bluetooth Location Tracking
When the Track button is clicked, the ESP8266 reads location data sent from a Bluetooth device. This data is displayed on the web interface in real-time.

Setup and Installation
1. Wiring: Connect the ESP8266 to the motor driver, DC motors, and the Bluetooth module as per the pin configuration table.
2. Code Upload: Upload the provided code to the ESP8266 using the Arduino IDE.
3. Wi-Fi Setup: Ensure your ESP8266 is connected to your local Wi-Fi network. Modify the WiFi.begin() function in the code with your network’s SSID and password.
4. Accessing the Control Panel: Once connected, open a web browser and navigate to the IP address assigned to the ESP8266. This will bring up the control panel to drive the car.

Dependencies
The code requires the following libraries:
+ ESP8266WiFi
+ ESP8266WebServer
+ ESP8266mDNS
+ SoftwareSerial
Make sure to install these libraries through the Arduino IDE Library Manager if not already installed.

How to Use
1. Power the ESP8266 and ensure it connects to the Wi-Fi network.
2. Open a web browser and navigate to the ESP8266’s IP address.
3. Use the buttons on the web interface to control the car.
4. For tracking location, click the "Track" button, and the location will be retrieved via Bluetooth and displayed on the web interface.
