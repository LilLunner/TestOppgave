#include <movingAvg.h>

int LED=5;
int cell=A5;


void setup() {
    pinMode(LED, OUTPUT);
    pinMode(A5, INPUT);
    Serial.begin(9600);

}

float averageRead() {
    movingAvg mySensor(5); //Sier at gjennomsnittet
    mySensor.begin();
    for (int i=0; i<5; i++) {
        int sensorData=analogRead(cell);
        mySensor.reading(sensorData);
    }
    int average=mySensor.getAvg();
    return average;
}

void blink() {
    int del=0;
    float x = averageRead();
    if (x>=100) {
        del=1000;
    }
    else {
        del=167;
    }
    digitalWrite(LED, HIGH);
    delay(del);
    digitalWrite(LED, LOW);
    delay(del);
}

void loop() {
    blink();
}