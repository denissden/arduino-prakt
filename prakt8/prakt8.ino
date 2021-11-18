int bpin = 7;
int gpin = 6;
int rpin = 5;
int potpin = A7;
int btnpin = 2;



void setup() {
  pinMode(bpin, OUTPUT);
  pinMode(gpin, OUTPUT);
  pinMode(rpin, OUTPUT);
  pinMode(potpin, INPUT);
  pinMode(btnpin, INPUT);
  Serial.begin(38400);
}

int val, r, g, b;
bool btn_last = false, btn_now;
short selected_color = 0;
void loop() {
  val = analogRead(potpin);
  btn_now = digitalRead(btnpin);
  if (btn_now && !btn_last)
    onclick();
  btn_last = btn_now;

  switch (selected_color){
    case 0:
      r = val / 4;
      break;
    case 1:
      g = val / 4;
      break;
    case 2:
      b = val / 4;
      break;
  }
  
  analogWrite(bpin, b);
  analogWrite(gpin, g);
  analogWrite(rpin, r);
}

void onclick(){
  selected_color++;
  if (selected_color > 2) selected_color = 0;
}
