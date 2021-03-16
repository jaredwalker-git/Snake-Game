const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
int x;
int y;
double ix;
double iy;
double magx;
double magy;
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
    ix = (515 - x)/10;
    y = analogRead(Y_pin);
    iy = (500 - y)/10;
    magx = ix*ix;
    magy = iy*iy;

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
    if( magx == magy ){
      continue;
    }
    if( d != 1 ){
      if(x > 530){
        if(magx > magy){
            Serial.print("right\n");
            d = 1;
        }
      }
      if( x < 500 ){
        if(magx > magy){
          Serial.print("left\n");
          d = 1;
        }
      }
    }
    if( d != 2 ){
      if( y > 520 ){
        if(magy > magx){
          Serial.print("down\n");
          d = 2;
        }
      }
      if( y < 480 ){
        if(magy > magx){
          Serial.print("up\n");
          d = 2;
        }
      }
    }
  }
}
