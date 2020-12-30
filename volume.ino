const int LEN = 1;
int count = 0;

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
}

bool on = false;

void loop() {
  // put your main code here, to run repeatedly:
  Serial.read();
  for(int i=0;i<LEN;i++){
    Control* c = &controls[i];
    c->val = analogRead(c->pinout)/4;
    if(c->val < c->oldVal-1 || c->val > c->oldVal+1){
      Serial.write(i);
      Serial.write(c->val);
      c->oldVal = c->val;
    }
  }
  count++;
  delay(100);
}
