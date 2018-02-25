#include <AFMotor.h>                                                            //includes AFmotor Library
#include <NewPing.h>                                                            //includes NewPing Library
#include <Servo.h>                                                                  //includes Servo Library
#define TRIGPIN A4 
#define ECHOPIN A5 
#define MAXDISTANCE 350 
#define MAX_PEED 180                                                           // sets speed of DC Motors
#define MAXSPEEDOFFSET 20
NewPing sonar(TRIGPIN, ECHOPIN, MAXDISTANCE); 
AF_DCMotor motor1(1, MOTOR12_64KHZ); 
AF_DCMotor motor3(3, MOTOR12_64KHZ);
Servo myservo; 
int pos = 0;   
int it = 10;  
boolean goesForward=false;
int distance = 100;
int speedSet = 0;
void setup()
 {
  Serial.begin(9600);
 myservo.attach(9);  
  myservo.write(90); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() 
{  
int distanceR = 0;
int distanceL =  0;
delay(40);
if(distance<=15)
 	{
  	moveStop();
  	delay(100);
 moveBackward();
  	delay(300);
  	moveStop();
  	delay(200);
  	plotpath();
  	delay(200);
  	distanceR = lookRight();
  	delay(200);
  	distanceL = lookLeft();
  	delay(200);
  if(distanceR>=distanceL)
  	{
    	turnRight();
    	moveStop();
  	}
else
 	 {
    	turnLeft();
   	moveStop();
  	}
}
else
{
  	moveForward();
 	}
 distance = readPing();
}

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;
    delay(100);
}

int readPing() 
{ 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
 	 {
    	cm = 250;
  	}
  return cm;
}

void moveStop()
 {
  motor1.run(RELEASE); 
  motor3.run(RELEASE);
  }
   void moveForward()
 {
 if(!goesForward)
 	{
    	goesForward=true;
    	motor1.run(FORWARD);      
    	motor3.run(FORWARD);      
   	for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
   		{
    		motor1.setSpeed(speedSet);
    		motor3.setSpeed(speedSet+MAX_SPEED_OFFSET);
    		delay(5);
   		}
  	}
}
void moveBackward() 
{
  goesForward=false;
  motor1.run(BACKWARD);      
  motor3.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2)  
 	{
    	motor1.setSpeed(speedSet);
    	motor3.setSpeed(speedSet+MAX_SPEED_OFFSET);
    	delay(5);
  	}
} 

void turnRight()
 {
  motor1.run(FORWARD);
  motor3.run(BACKWARD);     
  delay(300);
  motor1.run(FORWARD);      
  motor3.run(FORWARD);      
} 
 
void turnLeft()
 {
  motor1.run(BACKWARD);     
  motor3.run(FORWARD);     
  delay(300);
  motor1.run(FORWARD);     
  motor3 .run(FORWARD);
}
void plotpath()
{
  int i=0;
  int t=0;
  int a=0;
  for (i = 0; i < 180; i ++)
  	{
    	unsigned int uS = sonar.ping();
    	myservo.write(i);
    	delay(1);
    	for (t = 0; t < it; t++)
    		{
      		uS = sonar.ping();
      		a = uS/US_ROUNDTRIP_CM + a;
      		delay(2);
    		}
    	a = a / (it-1);
    	t = 0;
    	Serial.println(a); 
    	a = 0;
  	}
}
