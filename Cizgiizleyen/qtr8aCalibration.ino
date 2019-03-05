//For trying calibration QTR 8A

#include <QTRSensors.h>

#define NUM_SENSORS 8
#define NUM_SAMPLES_PER_SENSOR 4
#define EMITTER_PIN 2

QTRSensorsAnalog qtra((unsigned char[]) {
  0, 1, 2, 3, 4, 5, 6, 7
}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

long sensor1 = 0;
long sensor2 = 0;
long sensor3 = 0;
long sensor4 = 0;
long sensor5 = 0;
long sensor6 = 0;
long sensor7 = 0;
long sensor8 = 0;
long hata;
float Kp = 0.5;
float Ki = 0;
float Kd = 0.7;
long toplam_hata;
long son_hata;
unsigned long pid;
long motorR1;
long motorR2;
long motorRe;
long motorL1;
long motorL2;
long motorLe;
long motor_guc;
long motorR = 255;
long motorL = 255;
unsigned long  pay;
unsigned long  payda;
long int ortalama;

int maxVal = 60;




void setup()
{

  Serial.begin (9600);
  pinMode(3 , OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);

  Serial.begin(9600);
  int i;
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  for (i = 0; i < 80; i++)
  {
    qtra.calibrate();
  }
  
  digitalWrite(13, LOW);
}

void loop()
{
  unsigned int position = qtra.readLine(sensorValues);

  Serial.print(position);
  Serial.print("  ");

  hata = 3500 - position;
  pid = Kp * hata + Kd * (hata - son_hata) + Ki * toplam_hata;
  son_hata = hata;
  toplam_hata += hata;

  Serial.print(pid);
  Serial.print("  ");

//  motor_guc = map(pid, -3500, 3500, -255, 255);
//  Serial.print(motor_guc);
//  Serial.print("  ");
//
//  motorR = maxVal + motor_guc;
//  motorL = maxVal - motor_guc;
//
//  if (motorR > 100) motorR = 100;
//  if (motorR < 0) motorR = 0;
//  if (motorL > 100) motorL = 100;
//  if (motorL < 0 ) motorL = 0;


//Serial.print(analogRead(A0));
//Serial.print("|");
//Serial.print(analogRead(A1));
//Serial.print("|");
//Serial.print(analogRead(A2));
//Serial.print("|");
//Serial.print(analogRead(A3));
//Serial.print("|");
//Serial.print(analogRead(A4));
//Serial.print("|");
//Serial.print(analogRead(A5));
//Serial.print("|");
//Serial.print(analogRead(A6));
//Serial.print("|");
//Serial.println(analogRead(A7));
//
//  analogWrite(3,motorR);
// digitalWrite(7, HIGH);
// digitalWrite(8, LOW);
// 
//  analogWrite(9,motorL);
//  digitalWrite(11, HIGH);
// digitalWrite(12, LOW);

  Serial.print(motorR);
  Serial.print("  ");
  Serial.print(motorL);
 Serial.println("  ");
}
