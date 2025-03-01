

const int ledBlue = PB3; // Pin D11 in port B
const int ledGreen = PB4; // Pin D12 in port B
const int ledRed = PB5; // Pin D13 in port B

const int trig_pin = 2;
const int echo_pin = 3;
const int pir_pin = 4;
const int temp_pin = A5;

bool motionDetected = false;

bool objectDetected = false;

uint16_t timer = 0;
uint16_t compare_time = 62500; // Time threshold for 1 sec on 256 prescaler


void setup() {
  Serial.begin(9600);

  PCICR |= B00000111;   // Enable interrupt for all ports B, C and D.
  PCMSK2 |= B00010000;   // Enable inturrept for PIR
  DDRB |= B00111000; // Set All the LED on pin 11, 12 and 13 to output

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(pir_pin, INPUT);

  TCCR1A = 0; //Default settings to TCCR1A to 0.
  TCCR1B = 0;
  TCCR1B |= B00000100;  //Set CS12 to so prescaler is set to 256.
  TCNT1 = timer;    //Reset timer 
  OCR1A = compare_time; // 1Seconds
  
  TIMSK1 |= B00000010;  // Enable compare match and set OCIR1A  

  sei();

}

ISR(PCINT2_vect) {
  if (PIND & (1 << pir_pin)) {
    motionDetected = true;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(motionDetected){
    Serial.println("PIR Motion Detected");
    PORTB |= B00100000; //Set the pin D13 to high
    delay(1000);
    PORTB &= !(B00100000);  //Pin 13 to low.
    motionDetected = false;
  }
}

ISR(TIMER1_COMPA_vect){
  TCNT1 = timer;
  PORTB ^= (1 << ledGreen);   // Used bitwise or to flip the bit.

  int tempRaw = analogRead(temp_pin);
  float voltage = tempRaw * 5.0 / 1023.0;
  float temp = (voltage - 0.5) * 100;

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" *C");

}
