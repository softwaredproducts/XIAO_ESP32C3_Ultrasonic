// Simple measure distance
#define TRIG_PIN  D0
#define ECHO_PIN  D2

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);  
  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  // TRIG ON
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(100);
  digitalWrite(TRIG_PIN, LOW);

  // Measure HIGH duration by pulseIn funtion
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000); 
  float distance_cm = duration * 0.034 / 2.0;

  Serial.printf("duration=%lu us, distance=%.2f cm\n", duration, distance_cm);
  delay(1000);
}
