long sensor1 = 0;
long sensor2 = 0;
long sensor3 = 0;
long sensor4 = 0;
long sensor5 = 0;
long sensor6 = 0;
long sensor7 = 0;
long sensor8 = 0;
long hata;
float Kp = 0.20;
float Ki = 0;
float Kd = 0.30;
long toplam_hata;
long son_hata;
long pid;
//long motorR1;
//long motorR2;
//long motorRe;
//long motorL1;
//long motorL2;
//long motorLe;
long motor_guc;
long motorR = 255;
long motorL = 255;
unsigned long  pay;
unsigned long  payda;
long int ortalama;

int maxVal = 80;



void setup() {
  Serial.begin (9600);
  pinMode(3 , OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
}
void loop() {
  sensor1 = analogRead(A0);
  sensor2 = analogRead(A1);
  sensor3 = analogRead(A2);
  sensor4 = analogRead(A3);
  sensor5 = analogRead(A4);
  sensor6 = analogRead(A5);
  sensor7 = analogRead(A6);
  sensor8 = analogRead(A7);



  pay = sensor1 * (0 * 1000) + sensor2 * (1 * 1000) + sensor3 * (2 * 1000) + sensor4 * (3 * 1000) + sensor5 * (4 * 1000) + sensor6 * (5 * 1000) + sensor7 * (6 * 1000) + sensor8 * (7 * 1000);
  payda = sensor1 + sensor2 + sensor3 + sensor4 + sensor5 + sensor6 + sensor7 + sensor8;

  ortalama = pay / payda;

  hata = 3500 - ortalama;
  pid = Kp * hata + Kd * (hata - son_hata) + Ki * toplam_hata;
  son_hata = hata;
  toplam_hata += hata;


  motor_guc = map(pid, -3500, 3500, -255, 255);



  motorR = maxVal + motor_guc;

  motorL = maxVal - motor_guc;



  if (motorR > 100) motorR = 100;
  if (motorR < 0) motorR = 0;
  if (motorL > 100) motorL = 100;
  if (motorL < 0 ) motorL = 0;

  if (analogRead(A0) < 300) {
    while (analogRead(A2) > 300) {
      analogWrite(3, 80);
      digitalWrite(7, 1);
      digitalWrite(8, 0);

      analogWrite(9, 80);
      digitalWrite(11, 0);
      digitalWrite(12, 1 );
    }
  }

  if (analogRead(A7) < 300) {
    while (analogRead(A5) > 300) {
      analogWrite(3, 80);
      digitalWrite(7, 0);
      digitalWrite(8, 1);

      analogWrite(9, 80);
      digitalWrite(11, 1);
      digitalWrite(12, 0);
   } 
  }
  if (analogRead(A7) < 300 && analogRead(A6) < 300 && analogRead(A5) < 300) {
    while (analogRead(A3) > 300) {
      analogWrite(3, 70);
      digitalWrite(7, 0);
      digitalWrite(8, 1);

      analogWrite(9, 70);
      digitalWrite(11, 1); 
      digitalWrite(12, 0);
     } 
  }
   if (analogRead(A0) < 300 && analogRead(A1) < 300 && analogRead(A2) < 300) {
    while (analogRead(A5) > 300) {
      analogWrite(3, 70);
      digitalWrite(7, 1);
      digitalWrite(8, 0);

      analogWrite(9, 70);
      digitalWrite(11, 0);
      digitalWrite(12, 1);
     } 
  }


  analogWrite(3, motorR);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);

  analogWrite(9, motorL);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);



}
