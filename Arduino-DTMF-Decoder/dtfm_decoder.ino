#include <FlexiTimer2.h>

int STD = 3;
int Q1 = 5;
int Q2 = 6;
int Q3 = 7;
int Q4 = 8;

unsigned char QDat = 0x00;
unsigned char STDat = 0x00;
unsigned char DecodFinish = 0x00;

void dtmfDecode(void){
   int STDState = 0;
   int IOState = 0;
   
    STDState = digitalRead(STD);
    
    if(STDState) {if(STDat < 100) STDat ++;}  else STDat = 0;

    if(STDat==3){
       QDat = 0x00;
    
      IOState = digitalRead(Q1);
      if(IOState) 
         QDat = 0x01;
    
      IOState = digitalRead(Q2);
      if(IOState) 
         QDat |= 0x02;
    
      IOState = digitalRead(Q3);
      if(IOState) 
         QDat |= 0x04;
    
      IOState = digitalRead(Q4);
      if(IOState) 
         QDat |= 0x08;
    
      DecodFinish = 0xff;
    }
}

void setup()
{
   pinMode(STD, INPUT); 
   pinMode(Q1, INPUT);
   pinMode(Q2, INPUT);
   pinMode(Q3, INPUT);
   pinMode(Q4, INPUT);
    
   Serial.begin(9600);
   FlexiTimer2::set(5, 1.0/1000, dtmfDecode);
   FlexiTimer2::start();
}

void loop(){
   if(DecodFinish){
      DecodFinish = 0;
      
      Serial.print("DTMF Decoder Status Activate : " );
      
      switch(QDat){
         case 1 : Serial.print("8 \n" );  break;
         case 2 : Serial.print("4 \n" );  break;
         case 3 : Serial.print("# \n" );  break;
         case 4 : Serial.print("2 \n" );  break;
         case 5 : Serial.print("0 \n" );  break;
         case 6 : Serial.print("6 \n" );  break;
         case 7 : Serial.print("B \n" );  break;
         case 8 : Serial.print("1 \n" );  break;
         case 9 : Serial.print("9 \n" );  break;
         case 10 : Serial.print("5 \n" );  break;
         case 11 : Serial.print("A \n" );  break;
         case 12 : Serial.print("3 \n" );  break;
         case 13 : Serial.print("* \n" );  break;
         case 14 : Serial.print("7 \n" );  break;
         case 15 : Serial.print("C \n" );  break;
         default : Serial.print("D \n" );  break;
      } 
   }
}
