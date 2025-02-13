#define SIGNAL_PIN 3
#define BUILTIN_LED 13
#define OTHER_LED 11

bool motionDetected = false;

void motionISR() {
  motionDetected = true;
}

void setup() {
  
  pinMode(SIGNAL_PIN, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(OTHER_LED, OUTPUT);
  
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(SIGNAL_PIN), motionISR, RISING);
}


void loop() {
  if (motionDetected) {
    
    digitalWrite(OTHER_LED, HIGH);
    digitalWrite(BUILTIN_LED, HIGH);
    
    Serial.println("Motion detected! LED turned ON");
    
    delay(500);
    
    digitalWrite(OTHER_LED, LOW);
    digitalWrite(BUILTIN_LED, LOW);
    
    Serial.println("No motion detected. LED turned OFF");
    
    motionDetected = false;
  }
}
