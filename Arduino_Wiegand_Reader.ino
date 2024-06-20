#include <Arduino.h>

#define DEBUG 1

#include "src\Wiegand.h"

#define PIN_D0 2
#define PIN_D1 3

Wiegand wiegand(PIN_D0, PIN_D1);
unsigned long lastHeartbeat = 0;

void setup() {

    Serial.begin(9600);

    while (!Serial);

    Serial.println();
    Serial.println("Starting Wiegand...");
    wiegand.begin();
}

void loop() {
    wiegand.update();
}
