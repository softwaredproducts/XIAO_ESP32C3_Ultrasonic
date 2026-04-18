// Simple measure distance ISR ver.
#include "driver/pulse_cnt.h"
#include "driver/gpio.h"

#define TRIG_PIN D0
#define ECHO_PIN D2

volatile uint32_t echo_start_us = 0;
volatile uint32_t pulse_duration_us = 0;

// ISR
void IRAM_ATTR echo_isr() {
    uint32_t now = esp_timer_get_time(); 
    if (digitalRead(ECHO_PIN) == HIGH) {
        echo_start_us = now;
    } else {
        if (echo_start_us > 0) {
            pulse_duration_us = now - echo_start_us;
        }
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIG_PIN, LOW);
    // falling/rising edge
    attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echo_isr, CHANGE);
}

void loop() {
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    // ?data is saved
    if (pulse_duration_us > 0) {
        float distance = pulse_duration_us * 0.034 / 2.0;
        Serial.printf("Distance: %.2f cm (Pulse: %d us)\n", distance, pulse_duration_us);
    }
    delay(200);
}