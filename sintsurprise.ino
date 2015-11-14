
//initiate the servos:
Servo lidServo;
int lidServoPin = A4;
int lidOpen = 61;
int lidClose = 0;
int lidStatus = 0;
int curLidPos = 0;

Servo lockServo;
int lockServoPin = A5;
int lockOpenPos = 0;
int lockClosePos = 90;


int ledPin = D7;
int doorKnobPin = D0;

void setup() {
    lidServo.attach(lidServoPin);
    lockServo.attach(lockServoPin);
    //lidServo.write(lidClose);
    //lockServo.write(lockClosePos);

    pinMode(ledPin,OUTPUT);
    pinMode(doorKnobPin,INPUT_PULLDOWN);
    Particle.function("testSurprise",surprise);
    Particle.function("lock",lock);
    Particle.variable("lidPos",curLidPos);

}

void loop() {
    if (Particle.connected()){
        digitalWrite(ledPin, HIGH);
    } else{
        digitalWrite(ledPin, LOW);
    }
    if (digitalRead(doorKnobPin)==HIGH){
        surprise("open");
        delay(100);
    }
    if (lidStatus == 1){
      while(1);
    }
}

int surprise(String command){
  if (command == "open"){
    lockServo.write(lockOpenPos);
    delay(250);
    for (int n = lidClose; n < lidOpen; n++){
      lidServo.write(n);
      delay(50);
    }
    curLidPos=lidServo.read();
    lidServo.detach();
    lidStatus = 1;

    //delay(1000);
  } else if (command == "close"){
    lockServo.write(lockOpenPos);
    delay(250);
    for (int n = lidOpen; n > lidClose; n=n-1){
      lidServo.write(n);
      delay(50);
    }
    lockServo.write(lockClosePos);
    delay(10);
    curLidPos=lidServo.read();
    } else {
      return -1;
    }
    return 1;
}


int lock(String command){
    if (command == "open"){
        lockServo.write(lockOpenPos);
    } else if (command == "close"){
        lockServo.write(lockClosePos);
    } else {
        return -1;
    }
    return 1;
}
