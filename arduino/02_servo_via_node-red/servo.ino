#include <Servo.h>

Servo servo0;
int pos = 0;
int target = 0;

constexpr unsigned int SERVO_PIN = 3;


void setup() {
  servo0.attach(SERVO_PIN);
  Serial.begin(9600);
}

int cmd_threshold(int target, int pos) {
  if (pos > target) {
    return -1;
  }
  else if (pos < target) {
    return 1;
  }
  return 0;
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    unsigned int pos = msg.indexOf(';');
    target = atoi(msg.substring(0, pos).c_str());
    Serial.println(msg);
    Serial.println(target);
  }
  int dx = cmd_threshold(target, pos);
  if (dx != 0 && pos <= 180 && pos >= 0){
    pos += dx;    
    servo0.write(pos);
    //delay(15);
  }

}