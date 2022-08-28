#include<Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1);
Servo esc;

int cnt = -1;
int Run = 0;
int Speed = 0;
int SpeedAdj = 0;
int On = 0;
int connect0 = 0;
int connect1 = 0;
int connectOn = 0;

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 3;
task tasks[tasksNum];

// Bluetooth
enum SM1_States { SM1_INIT, SM1_S0};
int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM1_INIT:
         //State Transition
            cnt = -1;
            On = 0;
            state = SM1_S0;
        break;
      case SM1_S0:
         //State Transition
        break;
    }
    switch(state){ // State Action
      case SM1_INIT:
         //State Action
        break;
      case SM1_S0:
          //State Action
          if(Serial.available() > 0){
            cnt++;
            if(cnt >= 4) cnt = 0;
            Run = mySerial.read();
            Serial.print(cnt);
            Serial.println(Serial.read());
          }
          if(Run >= 99 && cnt == 1) {
            On = 1;
            Run = 0;
          }
          else if(Run <= 49 && cnt == 1) {
            On = 0;
            Run = 0;
          }
//          Serial.print("Serial.available() = ");
//          Serial.println(Serial.available());
//          Serial.print("Run = ");
//          Serial.println(Run);
//          Serial.print("cnt = ");
//          Serial.println(cnt);
//          Serial.print("On = ");
//          Serial.println(On);
          if(connectOn == 0) state = SM1_INIT;
        break;
    }
    return state;
}

// Speed Control
enum SM2_States { SM2_INIT, SM2_S0};
int SM2_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM2_INIT:
         //State Transition
            state = SM2_S0;
        break;
      case SM2_S0:
        //State Transition
        break;
    }
    switch(state){ // State Action
      case SM2_INIT:
         //State Action
        break;
      case SM2_S0:
         //State Action
           if(On == 1 && connectOn == 1) { // fix some bugs run and see the serial monitor. if i turn off the bluetooth then it should stay zero at the end.
             Speed = Speed + 1;
             if(Speed >= 255) Speed = 255; 
           }
           else if(On == 0 || connectOn == 0) {
             Speed = Speed - 2.5;
             if (Speed <= 0) Speed = 0;
           }
           SpeedAdj = Speed;
           SpeedAdj = map(Speed, 0, 255, 0, 60);
           esc.write(SpeedAdj);
           Serial.print("SpeedAdj= ");
           Serial.println(SpeedAdj);
        break;
    }
    return state;
}

enum SM3_States { SM3_INIT, SM3_S0, SM3_S1};
int SM3_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM3_INIT:
         //State Transition
            state = SM3_S0;
        break;
      case SM3_S0:
         //State Transition
        break;
    }
    switch(state){ // State Action
      case SM3_INIT:
         //State Action
        break;
      case SM3_S0:
          //State Action
          if(digitalRead (2) == 1) connect1++;
          if(digitalRead (2) == 0) connect1 = 0;
          if(connect1 >= 21) connect1 = 21;
          if(connect1 == 21 && digitalRead (2) == 1) {
            connectOn = 1; 
          }
          if(digitalRead (2) == 0) connectOn = 0;
//          Serial.print("connectOn = ");
//          Serial.println(connectOn);
//          Serial.print("connect1 = ");
//          Serial.println(connect1);
        break;
    }
    return state;
}

void setup(){
  esc.attach(8, 1000, 2000);
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode (2, INPUT);

  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 20;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 20;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
  i++;
  tasks[i].state = SM3_INIT;
  tasks[i].period = 20;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM3_Tick;

}

void loop(){
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
     }
  }
}