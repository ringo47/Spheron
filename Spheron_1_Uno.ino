#include <VirtualWire.h>

#define m1a 4
#define m1b 5
#define m1s 3
#define m2a 7
#define m2b 6
#define m2s 11
#define ledpin 13


char signal;
int acc;

//edited april 5

void setup(){

  Serial.begin(9600);

  pinMode(m1a,OUTPUT);
  pinMode(m2a,OUTPUT);
  pinMode(m1b,OUTPUT);
  pinMode(m2b,OUTPUT);
  pinMode(m1s,OUTPUT);
  pinMode(m2s,OUTPUT);
  pinMode(ledpin,OUTPUT);
  
  vw_set_rx_pin(8);
  vw_setup(2000);  // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
}


void loop(){

    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    
    if(Serial.available()>0){
  
      signal = Serial.read();
      //Serial.println(signal);
      
      if(signal !='S'){
        switch(signal){
        
          case 'B':
            mgoF(255);
            break;
           
          case 'F':
            mgoB(255);
            break;
            
          case 'L':
            steerLeft();
            break;
            
          case 'R':
            steerRight();
            break;
          
          case 'X':
            mStop();
            break;
          
          case 'x':
            mStop();
            break;
            
          case 'w':
            mAcc();
            break;
            
          case 'W':
            mAcc();
            break;
            
          case 'S':
            mStop();
            break;
            
         
            
          default: break;
          

            
          }
      }
  }
      
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      if(buf[0]=='1'){
        digitalWrite(ledpin,HIGH);
        mStop();
      }  
     if(buf[0]=='0'){
        digitalWrite(ledpin,LOW);
      }
    }

}


void mgoF(int m){
  
  //if(flag=='b'){analogWrite(rmpinS, 0);}
 
  analogWrite(m1s, m);
  analogWrite(m2s, m);
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  
}

void mgoB(int m){
  
  //if(flag=='b'){analogWrite(rmpinS, 0);}
 
  analogWrite(m1s, m);
  analogWrite(m2s, m);
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);
  
}

void mStop(){
  
  analogWrite(m1s, 0);
  analogWrite(m2s, 0);
  
}


void steerLeft(){
  
  analogWrite(m1s, 180);
  analogWrite(m2s, 180);
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  delay(100);
  analogWrite(m1s, 0);
  analogWrite(m2s, 0);
  
  
}

void steerRight(){
  
  analogWrite(m1s, 180);
  analogWrite(m2s, 180);
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);
  delay(100);
  analogWrite(m1s, 0);
  analogWrite(m2s, 0);
  
  
}



void mAcc(){
 
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  
 for(acc=155;acc<256;acc+=5){
 
  analogWrite(m1s, acc);
  analogWrite(m2s, acc);
  delay(300);
   
 }
 
}



/*void test(){
  
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  
  //Serial.println("Starting\t");
  
  for(acc=155;acc<256;acc+=5){
 
  analogWrite(m1s, acc);
  analogWrite(m2s, acc);
  
  //Serial.println(acc);
  
  delay(1000);
  analogWrite(m1s, 0);
  analogWrite(m2s, 0);
  delay(1000);
   
 }

}*/

