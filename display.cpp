#include <Arduino.h>

/*
    This script is only used for the gif in the readme.md
*/

const int ledPins[] = {
GPIO_NUM_32, 
GPIO_NUM_33, 
GPIO_NUM_25, 
GPIO_NUM_26,
GPIO_NUM_27,
GPIO_NUM_14};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
const int motor1A = GPIO_NUM_18;
const int motor2A = GPIO_NUM_17;
const int enableA = GPIO_NUM_16;
const int buttonPin = GPIO_NUM_19;

int current = 0;
int direction = 1; // 1 = forward, -1 = backward

void setup() {
    for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
    pinMode(motor1A, OUTPUT);
    pinMode(motor2A, OUTPUT);
    pinMode(enableA, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);

    ledcAttach(enableA, 20000, 8); // 20 kHz frequency, 8-bit resolution
    ledcWrite(enableA, 0);  // Start with motor stopped
}

void loop() {
    if (digitalRead(buttonPin) == LOW) {
        digitalWrite(motor1A, HIGH);
        digitalWrite(motor2A, LOW);
        ledcWrite(enableA, 255);
        while (true) {
                // Turn all LEDs off
            for (int i = 0; i < numLeds; i++) {
                digitalWrite(ledPins[i], LOW);
            }

            // Turn current LED on
            digitalWrite(ledPins[current], HIGH);

            delay(100);

            // Move position
            current += direction;

            // Reverse direction at ends
            if (current == numLeds - 1 || current == 0) {
                direction *= -1;
            }
        }
    }
}