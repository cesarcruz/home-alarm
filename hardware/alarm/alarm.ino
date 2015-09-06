/*
  Home Alarm
  Model: 01
  
  Simple alarm using magnetic contactors for doors and windows
*/

const int REED_SWITCH_1 = 7;  // Magnetic contact attached to digital pin 2
const int LED_OPEN_DOOR_1 = 13;  // LED to show door opned/closed attached to digital pin 12

int door_state = 0; // will be used to store the state of the door (REED_SWITCH_1 input pin)

void setup() {
  pinMode(REED_SWITCH_1, INPUT);  // Set digital pin as input
  pinMode(LED_OPEN_DOOR_1, OUTPUT);  // Set digital pin as output
  
  // PC output
  Serial.begin(9600); // initialize serial communication at 9600 bits per second
}

void loop() {
  int door_state = digitalRead(REED_SWITCH_1);  // read the input pin
  
  // Since Magnetic Contact is inverse led should be high when it is low
  // door_state -> HIGH: Opened
  // door_state -> LOW: Closed
  if (door_state ==  LOW) {  // If door is opened turn on led
    digitalWrite(LED_OPEN_DOOR_1, HIGH);  // Turn LED ON
  } else {  // If door is closed turn off led
    digitalWrite(LED_OPEN_DOOR_1, LOW);  // Turn LED OFF
  }

  // PC output
  delay(1); // delay in between reads for stability
  Serial.println(door_state);  // print out the door state
}
