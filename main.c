#include<reg52.h>
#include<stdio.h>


sbit LCDrs=P0^0;  //The Register select Pin
sbit LCDrw=P0^1;  //The Read/Write Pin
sbit LCDen=P0^2;  //The Enable Pin

sbit Sensor=P2^1;  


char sbuf[16],c,store; 
char buf[16]; 
void transmit(unsigned char );
void phoneCall();
void sendMessage();
void delay(unsigned int rtime)
	{
	unsigned int r,s;
	for(r=0;r<rtime;r++)
	for(s=0;s<1275;s++);
	}
void lcdcmd (unsigned char DATA)
	{

				LCDrs=0;
				LCDrw=0;
				LCDen=1;
				P1=DATA;
				LCDrs=0;
				LCDen=0;
	}
void initialize (void) 
	{
				lcdcmd (0x30);	 //1 line and 5x7 matrix 
				delay(1);
				lcdcmd (0x38);	 //2 line and 5x7 matrix
				delay(1);
				lcdcmd (0x0C);	 //Display on, cursor off
				delay(1);
				lcdcmd (0x01);	 //Clear display Screen
				delay(1);
				lcdcmd (0x06);	 //shift cursor to right
				delay(1);
	}
void lcddat (unsigned int DATA)
	{	   

				LCDrs=1;
				LCDrw=0;
				LCDen=1;
				P1=DATA;
				LCDrs=1;
				LCDen=0;
	}
void display_lcd (unsigned char location, unsigned char *d)
	{  
					lcdcmd(0x80 | location); 
					delay(1);
					while(*d)
					 	{
					 	  lcddat(*d++);  
					 	  
					 	}	 
	}

char mygetchar(void) 
{ 
char c; 
while(!RI); 
RI =0; 
c = SBUF; 
return SBUF; 
} 
void init()
{
TMOD=0x20;
TH1=0xFD;
TL1=0xFD;
SCON=0x50;
TR1=1;
TI=1;
}
void main()
{

	init();
	ES=1;
	EA=1;
	P0=0xFF;
	initialize();
	Sensor=1;  
	
	display_lcd(0x80, "   reset  ");
	delay(1000);
	
	while(1) 
	{
		display_lcd(0x80, "  In while loop  ");	
		if(Sensor==0)
		{
			/*sendMessage();	
			display_lcd(0x80, "   Message  ");	
			display_lcd(0xC0, "    Sent   ");
			
			delay(1000);  */
		  
			phoneCall();
			
			display_lcd(0x80, "phone call");
			display_lcd(0xC0, "           ");	
			delay(5000);
			continue;
		}
	}
	display_lcd(0x80, "   breaked ");

	delay(1000);
	
}					 

void phoneCall()	  
{
	transmit('A');
	transmit('T');
	transmit('+');
	transmit('Q');
	transmit('A');
	transmit('U');
	transmit('D');
	transmit('C');
	transmit('H');
	transmit('=');
	transmit('1');
	transmit('\r');
	
	transmit('A');
	transmit('T');
	transmit('D');
	transmit('9');
	transmit('4');
	transmit('0');
	transmit('5');
	transmit('9');
	transmit('1');
	transmit('1');
	transmit('3');
	transmit('5');
	transmit('8');
	transmit(';');
	transmit('\r');
}
void sendMessage()
{
	transmit('A');
	transmit('T');
	transmit('+');
	transmit('C');
	transmit('M');
	transmit('G');
	transmit('F');
	transmit('=');
	transmit('1');
	transmit('\r');
	transmit('A');
	transmit('T');
	transmit('+');
	transmit('C');
	transmit('M');
	transmit('G');
	transmit('S');
	transmit('=');
	transmit('"');
	transmit('9');
	transmit('9');
	transmit('7');
	transmit('5');
	transmit('6');
	transmit('3');
	transmit('4');
	transmit('7');
	transmit('9');
	transmit('0');
	transmit('"');
	transmit('\r');
	transmit('K');
	transmit('A');
	transmit('P');
	transmit('I');
	transmit('L');
	transmit('H');
	transmit('E');
	transmit('R');
	transmit('E');
	transmit('\x1A');
	transmit('\r');
	transmit('\n');
} 
void transmit(unsigned char c)
{
while(!TI);
TI=0;
SBUF=c;
}
