#include <Arduino.h>

// pins & leds
const int ledPins[] = {GPIO_NUM_16, GPIO_NUM_17, GPIO_NUM_18};
const int numLeds = 3;
int currentLed = 0;
const int micPin = GPIO_NUM_39;
// const int buzzerPin = 19;

// frequency & resolution
const int freq = 20000;
const int resolution = 12;

// microphone
const int sampleWindow = 50; // sample window in ms
unsigned int sample;
const int threshold = 3000; // placeholder value

// timer variables
const int interval = 1000; // interval 4 how long u need to scream
unsigned long previousMillis = 0;


void lightLED() {
    // Get the current time
    unsigned long currentMillis = millis();

    if (currentLed >= numLeds) {
        currentLed = 0;
    }
  
    if (currentMillis - previousMillis >= interval) {
        digitalWrite(ledPins[currentLed], HIGH); // Turn on the current LED
        currentLed++; // Move to the next LED for the next interval
        previousMillis = currentMillis;
    }
}

void setup() {
    Serial.begin(115200);
    analogReadResolution(resolution);
    pinMode(micPin, INPUT); 
    for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
}

void loop() {
    unsigned long startMillis = millis();  // Start of sample window
    unsigned int peakToPeak = 0;   // peak-to-peak level

    unsigned int signalMax = 0;
    unsigned int signalMin = 4095;
    //  collect data for 50 mS
    while (millis() - startMillis < sampleWindow) {
        sample = analogRead(micPin);
        if (sample < 4095) {
            if (sample > signalMax) {
                signalMax = sample;  // save just the max levels
            } else if (sample < signalMin) {
                signalMin = sample;  // save just the min levels
            }
        }
    }
    peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
    Serial.println(peakToPeak);

    if (peakToPeak > threshold) {
        lightLED();
    }

}