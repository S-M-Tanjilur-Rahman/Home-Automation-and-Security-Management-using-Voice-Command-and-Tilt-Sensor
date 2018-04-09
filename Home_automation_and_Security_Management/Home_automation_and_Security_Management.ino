int inPin = 2;   // the number of the input pin
int reading;     // the current reading from the input pin
int GreenLedPin = 13;  // the number of the Green LED output pin
int RedLedPin = 12;    // the number of the Red LED output pin
const int SpeakerPin = 11; // the number of the Speaker/Buzzer pin

int LightPin = 7; // it gives signal to control the light of the room 
int FanPin = 6;   // it gives signal to control the fan of the room

const char *ControlStrings[] = {"*light on#", "*light off#", "*fan on#", "*fan off#"};  // commands using for controlling light and fan

void setup() {
  // put your setup code here, to run once:
  pinMode (inPin, INPUT);           // taking the tilting position of the chip which is attached to the precious thing
  pinMode (GreenLedPin, OUTPUT);    // Giving voltage to green LED which indicates that product is safe
  pinMode (RedLedPin, OUTPUT);      // Giving voltage to red LED which indicates that product is in danger
  Serial.begin(9600);               // setting the baud rate of serial communication at 9600kbps
  pinMode(LightPin, OUTPUT);        
  pinMode(FanPin, OUTPUT);
  digitalWrite(LightPin, 0);      //initially the light will be off
  digitalWrite(FanPin, 0);        //initially the fan will be off
}

void loop() {
  // put your main code here, to run repeatedly:
  String SerialString; 
  int i;
  while (Serial.available() > 0) {              // available() function is presenting the number of command
    SerialString = Serial.readString();         // readString() function is converting the given command into string
    for (i = 0; i < 4; i++)
      if (SerialString == ControlStrings[i])    // checking that which command has been given?
        break;
    switch (i) {
      case 0: digitalWrite(LightPin, 1); break;   // For turn on the light
      case 1: digitalWrite(LightPin, 0); break;   // For turn off the light
      case 2: digitalWrite(FanPin, 1); break;   // For turn on the fan
      case 3: digitalWrite(FanPin, 0); break;   // For turn off the fan
      default: break;
    }
  }
  reading = digitalRead(inPin);
  if (reading == 1) {
    digitalWrite(RedLedPin, HIGH);   // if tilted, turn the red LED ON
    digitalWrite(GreenLedPin, LOW);
    tone(SpeakerPin, 494, 500);      // if tilted, turn the Speaker ON
   delay(500);
   
  } else {
    digitalWrite(RedLedPin, LOW);
    digitalWrite(GreenLedPin, HIGH);    // if not tilted, turn the green LED ON
  }
  Serial.println(reading); // not really needed

  delay(200);   // pause 200 milliseconds between readings
}
