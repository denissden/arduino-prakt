int led = 13;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(38400);
  Serial.setTimeout(100);
}

int d = 100;

void blink(){
  digitalWrite(led, HIGH);
  delay(d);
  digitalWrite(led, LOW);
  delay(d - 100);
}


bool led_on = true;
void loop() {
  String input = Serial.readString();
  input.trim();
  Serial.println(input);

  if (input == "ledon") {
    Serial.println("on");
    led_on = true;
  }
  else if (input == "ledoff") {
    led_on = false;
  }

  digitalWrite(led, led_on);
}
