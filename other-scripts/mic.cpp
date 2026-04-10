#include <Arduino.h>

/*
    basic mic example
*/

const int micPin = GPIO_NUM_39;
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
const int resolution = 12;

void setup() {
    pinMode(micPin, INPUT); 
    Serial.begin(115200);
    analogReadResolution(resolution);
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
}