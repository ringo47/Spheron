#include <VirtualWire.h>
#include <math.h>


//Ranging sensor pins
#define trigpin1 5
#define echopin1 6
#define trigpin2 7
#define echopin2 8
#define ledpin 13


//accelerometer pins
const int ap1 = A5; 
const int ap2 = A4;
const int ap3 = A3;


//accelerometer variables 
/*int x,y,z;    
double roll = 0.00, pitch = 0.00;	
double x_Buff = 0.0;
double y_Buff = 0.0;
double z_Buff = 0.0;*/
double x_Buff = 0.0;
double y_Buff = 0.0;
double z_Buff = 0.0;    
double pitch = 0.00;

//ranging sensor variables
float time1,dist1,range1,time2, dist2, range2;

//radio variables
char *controller;

void setup(){
  Serial.begin(9600);
  
  //ranging sensor
  pinMode(trigpin1, OUTPUT);
  pinMode(echopin1, INPUT);  
  pinMode(trigpin2, OUTPUT);
  pinMode(echopin2, INPUT); 
  pinMode(ledpin, OUTPUT);
  pinMode(2, OUTPUT); 
  digitalWrite(2, HIGH);
  pinMode(3, OUTPUT); 
  digitalWrite(3, HIGH);

  //accelerometer
  analogReference(EXTERNAL);
  
  //radio
  vw_set_tx_pin(12);
  vw_setup(2000);// speed of data transfer Kbps
}

void loop(){
  
  range1=range_1();
  range2=range_2();
  
  Serial.print("Sensor-1:\t");Serial.print(range1); Serial.print("\tSensor-2:\t"); Serial.println(range2);
  
 
 

  if(range1<5.0 || range2<5.0) {
    digitalWrite(ledpin, HIGH);
    controller="1"  ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
  }
  else{
    digitalWrite(ledpin, LOW);
    controller="0"  ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
  }
  delayMicroseconds(20);
  
  

  x_Buff = float(analogRead(ap1)-512);
  delay(2); 
  y_Buff = float(analogRead(ap2)-512);
  delay(2);
  z_Buff = float(analogRead(ap3)-512);
  
  pitch = atan2((- x_Buff) , sqrt(y_Buff * y_Buff + z_Buff * z_Buff)) * 57.3;
  Serial.print("ANGLE: \t");Serial.println(pitch);
  delay(1000);   
 
 
  //loop END
  
}


float range_1(){
  
  digitalWrite(trigpin1 ,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin1, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigpin1, LOW);
  
  time1=pulseIn(echopin1, HIGH);
  dist1=(time1/2)*0.0330;
  return dist1;
}

float range_2(){
  
  digitalWrite(trigpin2 ,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin2, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigpin2, LOW);
  
  time2=pulseIn(echopin2, HIGH);
  dist2=(time2/2)*0.0330;
  return dist2;
}
