const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
int x;
int y;
int d;
int buzzer = 4;
char ch;

void setup() {
  pinMode(SW_pin, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void buzz(){
   for(int i=0; i<10; i++){
    digitalWrite(buzzer, HIGH);
    delay(3);
    digitalWrite(buzzer, LOW);
    delay(3);
  }
}

void loop() {
  while(true){
    x = analogRead(X_pin);
  
    y = analogRead(Y_pin);

    if(Serial.available()){  
      ch = Serial.read();
    }
    if( ch == 'E' ){
      buzz();
      ch = 'O';
    }
    if( ch == 'R' ){
      d = 0;
      ch = 'O';
    }
  
    if( x == 1023 && y == 1023){
      continue;
    }
    if( x == 1023 && y == 0){
      continue;
    }
    if( x == 0 && y == 1023){
      continue;
    }
    if( x == 0 && y == 0){
      continue;
    }
    if(d != 1){
       if(x == 1023){
           Serial.print("right\n");
           d = 1;
       }
       if( x == 0 ){
         Serial.print("left\n");
         d = 1;
       }
    }
    if(d != 2 ){
      if( y == 1023 ){
         Serial.print("down\n");
         d = 2;
      }
      if( y == 0 ){
         Serial.print("up\n");
         d =2;
      }
    }
  }
}
