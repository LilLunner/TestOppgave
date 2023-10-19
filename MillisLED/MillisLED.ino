int green = 5;
int red = 7;
int blue = 6;
int button = 2;
int pastMillis, pressTime, releaseTime, duration, pressState;
bool shortButtonPressed=0;
bool longButtonPressed=0;
bool blinkState=0;
int shortPress=2000;
int blinkSpeed=850;
int lastState=LOW;


void setup() {
    pinMode(green, OUTPUT);
    pinMode(blue, OUTPUT);
    pinMode(red, OUTPUT);
    pinMode(button, INPUT);
}

void buttonPress() {
    int butState = digitalRead(button);
    if (butState == HIGH && lastState == LOW) {
        pressTime=millis();
        lastState=butState;
    }

    if (butState == LOW && lastState == HIGH) {
        releaseTime=millis();
        lastState=butState;
        pressState=1;
    }

    duration = releaseTime - pressTime;

    if (duration<shortPress && pressState == 1) { //Sjekker om knappen har et kort knappetrykk og at knappen har blitt trykket inn og sluppet
        shortButtonPressed = !shortButtonPressed; //shortButtonPressed styrer om enten blå+grønn LEDene er på eller om blå+rød LEDene er på
        pressState = 0; //Sørger for at koden kun kjører en gang per knappetrykk
    }

     if (duration>=shortPress && pressState == 1) { //Sjekker om knappen har et langt knappetrykk og at knappen har blitt trykket inn og sluppet
        longButtonPressed = !longButtonPressed; //longButtonPressed styrer om alle LEDene blinker eller om kun blå LED blinker
        pressState = 0;
     }

}

void blinkMode() {
    if ((millis()-pastMillis>=blinkSpeed) && (blinkState == 0)){ //blinkState gjør at loopen veksler mellom de to forskjellige if-setningene som skrur LEDene av og på
        digitalWrite(blue, HIGH); //Blå skal alltid blinke
        if (shortButtonPressed==1) {
            digitalWrite(green, HIGH);
        }
        else {
            digitalWrite(red, HIGH);
        }
        pastMillis=millis();
        blinkState = !blinkState;
    }
    if ((millis()-pastMillis>=blinkSpeed) && (blinkState != 0)){
        digitalWrite(blue, LOW);
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
        pastMillis=millis();
        blinkState = !blinkState;
        //Skrur av alle LEDene og endrer blinkState tilbake til 0 slik at LEDene vil skru seg på igjen etter intervallet blinkSpeed
    }
}

void ConstantMode() {
    if ((millis()-pastMillis>=blinkSpeed) && (blinkState == 0)){ 
        digitalWrite(blue, HIGH);
        if (shortButtonPressed==1) {
            digitalWrite(red, LOW); //Skrur av LEDen som skal være av om man gjør et kort knappetrykk
            digitalWrite(green, HIGH);
        }
        else {
            digitalWrite(green, LOW);
            digitalWrite(red, HIGH);
        }
        pastMillis=millis();
        blinkState = !blinkState;
    }
    if ((millis()-pastMillis>=blinkSpeed) && (blinkState != 0)){
        digitalWrite(blue, LOW); //Skrur kun blå av og på slik at den blinker
        pastMillis=millis();
        blinkState = !blinkState;
    }

}

void loop() {
    buttonPress();
    if(longButtonPressed == 0){
        blinkMode();
    }
    else {
        ConstantMode();
    }
}