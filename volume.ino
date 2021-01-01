const int LEN = 2;

const int COMMAND_GET_SIZE = 'C';
const int COMMAND_GET_VALUE = 'G';

struct Control{
  int pinout;
  int oldVal;
  int val;
};

Control controls[LEN];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  controls[0].pinout = A0;
  controls[1].pinout = A1;
}

bool on = false;

void loop() {
  // put your main code here, to run repeatedly:
  int command = Serial.read();

  switch(command){
    case COMMAND_GET_SIZE:
      Serial.write(LEN);
      break;
    case COMMAND_GET_VALUE:
      int index = Serial.read();
      Serial.write(controls[index].val);
      break;
  }
  
  for(int i=0;i<LEN;i++){
    Control* c = &controls[i];
    c->val = analogRead(c->pinout)/4;
    if(c->val < c->oldVal-1 || c->val > c->oldVal+1){
      Serial.write(i);
      Serial.write(c->val);
      c->oldVal = c->val;
    }
  }
  delay(100);
}
