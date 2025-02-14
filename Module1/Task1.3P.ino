#define SIGNAL_PIN 3
#define BUILTIN_LED 13
#define OTHER_LED 11
#define ledPin 10
#define sensorPin 5

bool motionDetected = false;

void motionISR() {
  motionDetected = true;
}

void setup() {
  
  pinMode (ledPin, OUTPUT);
  pinMode(SIGNAL_PIN, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(OTHER_LED, OUTPUT);
  pinMode(sensorPin, OUTPUT);
  
  
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(SIGNAL_PIN), motionISR, RISING);
  }


void loop() {
  
  float dist = getDistance();
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println("cm");
  
  if(dist < 10){
  	digitalWrite(ledPin, HIGH);
    Serial.println("Object Detected. LED ON");
  }
  else{
  	digitalWrite(ledPin, LOW);
    Serial.println("Object Not detected. LED OFF");
  }
  
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
  
  delay(1000);
}

float getDistance() {
  pinMode(sensorPin, OUTPUT);
  digitalWrite(sensorPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorPin, LOW);
  
  pinMode(sensorPin, INPUT);
  long duration = pulseIn(sensorPin, HIGH);
  float distance = duration * 0.034 / 2; 
  return distance;
}
