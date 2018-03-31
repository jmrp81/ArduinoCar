#include <SoftwareSerial.h>

//Variables
const byte rxPin = 11;
const byte txPin = 10;
long bps = 9600 ;

int IN1 = 5;//motora
int IN2 = 4;//motora
int IN3 = 3;//motorb
int IN4 = 2;//motorb

int ENA = 6;//motora engine
int ENB = 9;//motorb engine

int VEL = 100;//initial speed - velocidad inicial 

SoftwareSerial myConnect(txPin, rxPin); // RX, TX recordar que se cruzan

void setup()
{
  //motor A
  pinMode (ENA, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);

  //Motor B
  pinMode (ENB, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  
  Serial.begin(bps);
  myConnect.begin(bps);
}

void loop()
{
  char data = ' ';

  if (myConnect.available()) 
  {
    data = myConnect.read();
    Serial.write(data);  
  }

  if (Serial.available()) 
  {
    data = Serial.read();
    myConnect.write(data);
  }

  switch (data)
  {
    case '0':
      stoP();
      break;
    case '1':
      straight();
      break;
    case '2':
      turn_left();
      break;
    case '3':
      turn_right();
      break;
    case '4':
      forward();
      break;
    case '5':
      speedUp();
      break;
    case '6':
      speedDown();
      break;
    default:
      break;
  }
}

void start()//arrancar
{
  Serial.println("start");
  
  analogWrite(ENA, VEL); //start motor A
  analogWrite(ENB, VEL); //start motor B
}

void stoP()//detener
{
  Serial.println("stop");
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  analogWrite(ENA, 0); //stop motor A
  analogWrite(ENB, 0); //stop motor B
}

void straight()//avanzar
{
  Serial.println("straight");
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  start();
}

void forward()//retroceder
{
  Serial.println("forward");
  
  digitalWrite(IN3, HIGH);//with vcc - tension
  digitalWrite(IN4, LOW);//without vcc - sin tension
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  start();
}

void turn_left()//girar a la izquierda
{
  Serial.println("turn_left");

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  start();
}

void turn_right()//girar a derecha
{
  Serial.println("turn_right");
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  start();
}

void speedUp()//acelerar
{
  Serial.println("speedUp");
  
  if(VEL < 255 && (VEL + 15) <= 255)
  {
    VEL += 15;
  }
}

void speedDown()//frenar
{
  Serial.println("speedDown");
  
  if(VEL > 0 && (VEL - 15) >= 0)
  {
    VEL -=  15;
  }
}
