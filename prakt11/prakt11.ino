int echoPin = 2; 
int trigPin = 3; 
int soundPin = 7;

int displayRows[8] = { 52, 50, 48, 46, 44, 42, 40, 38 };
int displayCols[8] = { 36, 34, 32, 30, 28, 26, 24, 22 };

auto display = new int[8][8];

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(soundPin, OUTPUT);
  Serial.begin(9600);
  for (int i = 0; i < 8; i++){
    pinMode(displayRows[i], OUTPUT);
    pinMode(displayCols[i], OUTPUT);
    digitalWrite(displayRows[i], HIGH);
    digitalWrite(displayCols[i], LOW);
  }
}

long duration; 
int distance; 
int soundFreq;
auto graph = new int[8];

void loop() {
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 300)
  { 
    soundFreq = 10000 / distance;
    tone(soundPin, soundFreq);
    addToGraph(300 / distance);
  }
  drawGraph(1);
  drawGraph(1);
  drawGraph(1);
  drawGraphCol(0);
  //delay(100);
}

void selectRow(int r){
  for (int i = 0; i < 8; i++){
    if (i == r){
      digitalWrite(displayRows[i], LOW);
    } else {
      digitalWrite(displayRows[i], HIGH);
    }
  }
}

void drawGraphCol(int height){
  if (height > 8) height = 8;
  height = 8 - height;
  for (int i = 0; i < 8; i++){
    if (i >= height) digitalWrite(displayCols[i], HIGH);
    else digitalWrite(displayCols[i], LOW);
  }
}

void drawGraph(int d){
  for (int i = 0; i < 8; i++){
    selectRow(i);
    drawGraphCol(graph[i]);
    delay(d);
  }
}

void addToGraph(int val){
  for (int i = 0; i < 7; i++){
    graph[i] = graph[i + 1];
  }
  graph[7] = val;
}


// return distance in cm
int getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}
