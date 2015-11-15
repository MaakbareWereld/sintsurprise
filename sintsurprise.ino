
//initiate the servos:
Servo lidServo;
int lidServoPin = A4;
int lidOpen = 61; // in degrees
int lidClose = 0;
int lidStatus = 0;

Servo lockServo;
int lockServoPin = A5;
int lockOpenPos = 0;
int lockClosePos = 90;

//have a manual pin to open the box
int doorKnobPin = D0;

void setup() {
  //initiate the servos
  lidServo.attach(lidServoPin);
  lockServo.attach(lockServoPin);

  //initiatie the manual pin
  pinMode(doorKnobPin,INPUT_PULLDOWN);

  //these functions can be called from the Particle Cloud.
  Particle.function("testSurprise",surprise);
  Particle.function("lock",lock);

}

void loop() {

  //test for the doorKnobPin, if connected, open the box
  if (digitalRead(doorKnobPin)==HIGH){
    surprise("open");
    delay(100);
  }

  //once the box has been opened, this hangs the code, and also freezes the
  //servo, so the lid will not close anymore.
  if (lidStatus == 1){
    while(1);
  }
}

int surprise(String command){
  //open both the lock and the lid, in succesion. The for loop for the lid is
  //needed to keep it in check: otherwise it flips open too fast.
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
