int stan = 1;

// Piny do sterownika

int enA = 9;   // Enable pin Motor A prawy silnik
int in1 = 8;   // Control pin 1 Motor A
int in2 = 13;   // Control pin 2 Motor A
int enB = 10;  // Enable pin Motor B lewy silnik
int in3 = 12;  // Control pin 1 Motor B
int in4 = 11;  // Control pin 2 Motor B
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
// Piny do czujników wroga
int obstacle1 = 2;
int obstacle2 = 3; 

// Piny do czujników linii
int LeftSensor = 4;
int RightSensor = 5;
int FrontSensor = 6;     

bool robotOn = false;

// funkcja dla Motora A
void motorA(int speed, bool forward) {
  if (forward) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else { // do tyłu
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  analogWrite(enA, speed);
}

// funkcja dla Motora B
void motorB(int speed, bool forward) {
  if (forward) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else { // do tyłu
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  analogWrite(enB, speed);
}

void setup() {
  stan = 1;
  // Set pin - sterownik
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Set pin - czujniki wroga
  pinMode(obstacle1, INPUT);
  pinMode(obstacle2, INPUT);

  // Set pin - czujniki linii
  pinMode(LeftSensor, INPUT);
  pinMode(RightSensor, INPUT);
  pinMode(FrontSensor, INPUT);

  // Bluetooth
  Serial.begin(9600);

  // Wyłączanie robota
  robotOn = false;
  motorA(0, false);
  motorB(0, false);
}

void loop() {

// Sprawdzanie Bluetooth
  if (Serial.available() > 0){
    stan = Serial.read(); 
  }
    if (stan == '1') {
      // Włączanie robota
      robotOn = true;
      delay(5000);  // 5 s opóźnienia
    } else if (stan == '0') {
      // Wyłączanie robota
      robotOn = false;
      motorA(0, false);
      motorB(0, false);
      delay(1);  // 1 ms 
    }
  
  // jeśli robot jest włączony to następuje czytanie czujników
  if (robotOn) {
    int LeftValue = digitalRead(LeftSensor);
    int RightValue = digitalRead(RightSensor); 
    int FrontValue = digitalRead(FrontSensor); 
    bool obstacleDetected = digitalRead(obstacle1) || digitalRead(obstacle2);

    if (LeftValue == HIGH) {
    // Skręt w prawo
    motorA(0, false);
    motorB(0, false);
    delay(10);
    motorA(50, false);
    motorB(50, false);
    delay(500);
    }
    if (RightValue == HIGH) {
    // skręt w lewo
      motorA(0, false);
      motorB(0, false);
      delay(10);
      motorA(50, true);
      motorB(50, true);
      delay(500);
    } 
    if(FrontValue == HIGH){
      // do tyłu
      motorA(0, false);
      motorB(0, false);
      delay(10);
      motorA(50, true);
      motorB(50, false);
      delay(500);
    }
    if(obstacleDetected){
      motorA(200, false);
      motorB(200, true);
      delay(40);
      // motorA(0, false);
      // motorB(0, true);
      // delay(100);
      
    
    } else {
      // Jeździ w kółko i szuka przeszkód
      motorA(200, false);
      motorB(200, true);
      delay(40);
    }
  }
}

