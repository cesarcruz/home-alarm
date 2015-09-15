/*
  Home Alarm
  Model: 01
  
  Simple alarm using magnetic contactors for doors and windows
*/

const int REED_SWITCH_1 = 7;      // Magnetic contact
const int LED_OPEN_DOOR_1 = 8;    // LED to show door opened/closed
const int LED_ACTIVE = 13;        // LED to show when alarm is active
const int BUTTON_ACTIVATION = 2;  // Button to show when alarm is active
const int SOUND_SIGNAL = 9;       // Buzzer

int door_sensor = 0;              // will be used to store the state of the door (REED_SWITCH_1 input pin)
int old_door_sensor = 0;          // this variable stores the previous value of door_sensor

int activate = 0;                 // will be used to store the state activation (BUTTON_ACTIVATION input pin)
int old_activate = 0;             // this variable stores the previous value of "activate"
int active_state = 0;             // 0 = LED off while 1 = LED on

void setup() {
  pinMode(REED_SWITCH_1, INPUT);     // Set digital pin as input
  pinMode(LED_OPEN_DOOR_1, OUTPUT);  // Set digital pin as output
  
  pinMode(BUTTON_ACTIVATION, INPUT); // Set digital pin as input
  pinMode(LED_ACTIVE, OUTPUT);       // Set digital pin as output
  
  pinMode(SOUND_SIGNAL, OUTPUT);     // Set digital pin as output
  
  // PC output
  Serial.begin(9600);                // initialize serial communication at 9600 bits per second
}

void loop() {
  int door_sensor = digitalRead(REED_SWITCH_1);  // read the input pin

  if (door_sensor != old_door_sensor) {  // If door change it status, change LED
    // Since Magnetic Contact is inverse led should be high when it is low
    // door_sensor -> HIGH: Opened
    // door_sensor -> LOW: Closed
    if (door_sensor == 1) {
      digitalWrite(LED_OPEN_DOOR_1, HIGH);  // Turn LED ON
      if (active_state == 1) { // Since alarm is active turn on sound signal
        digitalWrite(SOUND_SIGNAL, HIGH);
      }
    } else {  // If door is closed turn off led
      digitalWrite(LED_OPEN_DOOR_1, LOW);  // Turn LED OFF
    }
  }
  
  old_door_sensor = door_sensor; // Save new door status
  
  int activate = digitalRead(BUTTON_ACTIVATION);  // read the input pin
  
  // Alarm Activation
  // check if the input is HIGH (button pressed) and change the state
  if ((activate == HIGH) && (activate != old_activate)) {
    active_state = 1 - active_state;
  }

  old_activate = activate;  // activate is now old, let's store it

  if (active_state == 1) {
    digitalWrite(LED_ACTIVE, HIGH); // turn LED ON
  } else {
    digitalWrite(LED_ACTIVE, LOW);
    digitalWrite(SOUND_SIGNAL, LOW); // Stop sound
  }
}
