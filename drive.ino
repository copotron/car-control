/*******************************************************************************
*  MCP4922.cpp - Library for driving MCP4922 2 channel DAC using hardware SPI. *
* Created by Helge Nodland, January 1, 2015.                   *
* Released into the public domain.                                             *
*******************************************************************************/

#include <SPI.h>


class MCP4922
{
  public:
    MCP4922(int SDI, int SCK,int CS, int LDAC);
    void Set(int A, int B);

  private:
    int _SDI;
    int _SCK;
    int _CS;
    int _LDAC;


    //void sendSPIHeader();
    void sendIntValueSPI(int A, int B);
    //void sendSPIClock();
};

MCP4922::MCP4922(int SDI, int SCK, int CS, int LDAC)
{
 _SDI = SDI;
 _SCK = SCK;
 _CS = CS;
 _LDAC = LDAC;


 pinMode(_SDI,OUTPUT);
 pinMode(_SCK,OUTPUT);
 pinMode(_CS,OUTPUT);
 pinMode(_LDAC,OUTPUT);

}

//************************************************************************
void MCP4922::Set(int A, int B) {
  sendIntValueSPI(A,B);
}


//************************************************************************ 
/*
Bitmasking for setting options in dac:

The four MSB in the Mask 0b0111000000000000 and 0b1111000000000000 is for
setting different options of the DAC setup.

0bX111000000000000 where X is What DAC channel the SPI is writing to.
bit15        X=0 is writing to channel A.
           X=1 is writing to channel B.

0b0X11000000000000 where X is Buffered or UnBuffered mode. Buffered uses LDAC 
bit14        pin to simuttaneous update both channels.
           UnBuffered I guess is writing outputs directly to DAC 
           outputs and ignoring LDAC pin.
           X=0 is UnBuffered.
           X=1 is Buffered.
           
0b01x1000000000000 where X is GAIN selector.  
bit13        X=0 is 2X GAIN.
           X=1 is 1X GAIN.
           
0b011X000000000000 where X SHUTDOWN.
bit12        X=0 OUTPUT is DISABLED on selected channel.
           X=1 OUTPUT is ENABLED on selected channel.
      
0b0111XXXXXXXXXXXX where X is the 12 bits to be written to the active channel.
bit 11 down to bit 0      

 */
//************************************************************************

void MCP4922::sendIntValueSPI(int A ,int B) {
int channelA = A | 0b0111000000000000;
int channelB = B | 0b1111000000000000;
       
digitalWrite(_CS, LOW);
SPI.transfer(highByte(channelA));
SPI.transfer(lowByte(channelA));
digitalWrite(_CS, HIGH);

__asm__("nop\n\t");
//delay(1);

digitalWrite(_CS, LOW);
SPI.transfer(highByte(channelB));
SPI.transfer(lowByte(channelB));
digitalWrite(_CS, HIGH); 
digitalWrite(_LDAC,LOW);

__asm__("nop\n\t");
//delay(1);

digitalWrite(_LDAC,HIGH);
} 

//MCP4922 DAC(51,52,53,5);
MCP4922 DAC(11,13,10,7);    // (MOSI,SCK,CS,LDAC) define Connections for UNO_board, 

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(10)
  SPI.begin();
}
/*
void loop()
{
  for(int i = 0 ; i < 4096 ; i+=1)
  {
   DAC.Set(4095-i,i); delay(1000);
   //Serial.print (analogRead(A2)); 
   //Serial.print("  "); 
   //Serial.print (analogRead(A3));
   //Serial.print("  "); 
   Serial.print (analogRead(A4));
   Serial.print("  "); 
   Serial.println (analogRead(A5));
  }
}
*/


void loop()
{
   int sp = analogRead(A0);
   sp = min(750, sp);
   sp = max(250, sp);
   //int vp = analogRead(A1);
   //Serial.print(sp); Serial.print("  ");
   //int sp = 4096/2;

    char buffer[2];
   if(Serial.readBytes(buffer, 1) == 1)
   {
    sp = buffer[0];
   }
                                                                                                                                            
   DAC.Set(sp*4, 4096-(sp*4)); delay(100);
   //Serial.print (analogRead(A2)); Serial.print("  "); Serial.println (analogRead(A3));
}
 
