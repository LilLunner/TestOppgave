int LED=5;
int cell=A5;


void setup() {
    pinMode(LED, OUTPUT);
    pinMode(A5, INPUT);
    Serial.begin(9600);
}

float averageRead() {
    int sum=0;
    for (int i=0; i<5; i++) {
        sum=sum+analogRead(cell); //legger sammen lesningen av fotocellen 5 ganger
    }
    float average = sum/5; //finner gjennomsnittet med å dele på antall lesninger
    return average;
}

void blink() { //En funksjon for å styre blinkingen på en LED basert på sensoravlesningen
    int del=0;
    float x = averageRead();
    if (x>=100) {
        del=1000; //Lavere blinkehastighet om sensoravlesningen ses på som "Høy"
    }
    else {
        del=167; //Høyere blinkehastighet om sensoravlesningen ses på som "Lav"
    }
    digitalWrite(LED, HIGH);
    delay(del);
    digitalWrite(LED, LOW);
    delay(del);
}

void loop() {
    blink();
}