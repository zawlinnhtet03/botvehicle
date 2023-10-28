#include <IRremote.hpp>
#include <AFMotor.h>
#include <IRremote.h>
#include <NewPing.h>

//defining pins and variables
#define left A5
#define right A2
#define irPin A1
#define trig A3
#define echo A4
#define max_distance 200

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

IRrecv IR(irPin);
decode_results result;

NewPing sonar(trig, echo, max_distance);

void setup() { 
    Serial.begin(115200);

    pinMode(left, INPUT);
    pinMode(right, INPUT);
    IR.enableIRIn();
}

void loop() {
    int obstacleDistance = sonar.ping_cm(); 
    if (IR.decode(&result)) {
        Serial.println(result.value);

        if(result.value == 4294967295) {
            motor2.run(BACKWARD);
            motor1.run(BACKWARD);
            motor4.run(BACKWARD);
            motor3.run(BACKWARD);

            motor2.setSpeed(150);
            motor1.setSpeed(150);
            motor4.setSpeed(150);
            motor3.setSpeed(150);  
            
            delay(500);

            motor1.run(RELEASE);
            motor2.run(RELEASE);
            motor3.run(RELEASE);
            motor4.run(RELEASE);
        } 
        else {
            motor2.run(BACKWARD);
            motor1.run(BACKWARD);
            motor4.run(BACKWARD);
            motor3.run(BACKWARD);

            motor2.setSpeed(150);
            motor1.setSpeed(150);
            motor4.setSpeed(150);
            motor3.setSpeed(150);  
          
            delay(500);

            motor1.run(RELEASE);
            motor2.run(RELEASE);
            motor3.run(RELEASE);
            motor4.run(RELEASE);
        }

        IR.resume();
    }

   

     if (obstacleDistance > 0 && obstacleDistance <= 20) {
        // If obstacle is within 20 cm, perform obstacle avoidance

        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        motor4.run(BACKWARD);
        motor3.run(BACKWARD);

        motor1.setSpeed(150);
        motor2.setSpeed(150);
        motor4.setSpeed(150);
        motor3.setSpeed(150);

        delay(500);

        motor1.run(RELEASE);
        motor2.run(RELEASE);
        motor3.run(RELEASE);
        motor4.run(RELEASE);
    } 
    else {
        int leftValue = digitalRead(left);
        int rightValue = digitalRead(right);

        if(leftValue == LOW && rightValue == LOW) {   
            motor2.run(BACKWARD);
            motor1.run(BACKWARD);
            motor4.run(BACKWARD);
            motor3.run(BACKWARD);

            motor2.setSpeed(100);
            motor1.setSpeed(100);
            motor4.setSpeed(100);
            motor3.setSpeed(100);    
        }
        else if(leftValue == HIGH && rightValue == LOW) {
            motor2.run(BACKWARD);
            motor1.run(BACKWARD);
            motor4.run(BACKWARD);
            motor3.run(BACKWARD);

            motor2.setSpeed(220);
            motor1.setSpeed(220);
            motor4.setSpeed(220);
            motor3.setSpeed(0);
        }
        else if(leftValue == LOW && rightValue == HIGH) {  
            motor2.run(BACKWARD);
            motor1.run(BACKWARD);
            motor4.run(BACKWARD);
            motor3.run(BACKWARD);

            motor2.setSpeed(220);
            motor1.setSpeed(220);
            motor4.setSpeed(0);
            motor3.setSpeed(220);
        }
        else {    
            motor1.run(RELEASE);
            motor2.run(RELEASE);
            motor3.run(RELEASE);
            motor4.run(RELEASE);   
        }  
    }     
}

  