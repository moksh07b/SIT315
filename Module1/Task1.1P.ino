#define TRIG_PIN 5
#define ECHO_PIN 6
#define LED_BUILTIN 13

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    
    Serial.begin(9600);
}

void loop() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(20);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    int distance = duration * 0.034 / 2; 

    Serial.print("Dist: " + distance);
    Serial.println(" cm");

    digitalWrite(LED_BUILTIN, HIGH);
    delay(100); 
    digitalWrite(LED_BUILTIN, LOW);

    delay(500); 
}
