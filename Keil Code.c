#include<reg51.h>
#define lcdport P1

sbit door1p = P2^0;						//door motor which rotates clockwise or anti-clockwise to open or close
sbit door1n = P2^1;
sbit door2p = P2^2;						//door motor which rotates clockwise or anti-clockwise to open or close
sbit door2n = P2^3;
sbit rs = P2^5;								//lcd control line connections: Resistor select control line
sbit rw = P2^6;								//read write connection
sbit en = P2^7;								//enable pin  all declared with Sbit
void lcddat(unsigned char);		//function to pass character by character to lcd display
void lcdcmd(unsigned char);			//function to pass command to lcd
void lcddis(unsigned char *); //function to display on lcd screen
void lcd_init();							//to send all the commands required for initialization
unsigned char rfid[12],v1;		//declaration of 12 digit RFID tag and a temperory variable
unsigned char ent_exit[50];		//for keeping track that whether car has entered or exited
unsigned int slotCount = 50; 	// Count of empty slots


unsigned int digit[5];
int k,p;
void convert(unsigned int value);
void delay2(unsigned int x);
void lcdstring(char *p);
void ldelay(unsigned int x);
void lcddata(char value);
void serial_init();						//function to write serial communication steps to initiate serial communication between RFID and Micro-controller
void check();									//to check whether the person is existing person
void delay();									//for lcd and operation
void mdelay();								//for motor operation


void main()
{
unsigned int i;
for(i=0;i<50;i++){
	ent_exit[i] = 'X'; // Initially all cars are outside - X means exited and E means entered
}

door1p = door1n = 0;					//initialize with 0 for 2 motor controls, which gives no response
door2p = door2n = 0;	
serial_init();							//Described below in the function definition
lcd_init();									//Described below in the function definition 
lcddis("RFID BASED CAR");
lcdcmd(0xc0);								//Sending cursor to second line
lcddis("PARKING SYSTEM");
mdelay();
lcdcmd(0x01);								//Clear the text
while(1)
{
lcdcmd(0x01);             //Next repetition
lcddis("SWIPE YOUR CARD");
for(v1=0;v1<12;v1++)			//Read 12 digits
{
while(RI == 0);					//RI=1 means Data is received from RFID to micro controller
rfid[v1] = SBUF;				//transfer SBUF Data to rfid variable
RI = 0;
SBUF = rfid[v1];				//re-transmission (optional)
while(TI == 0);
TI = 0;
}
check();
}
}

void check()
{ //VI123456789S - VISWAJEET SLOT
if(rfid[0]=='V'&&rfid[1]=='I'&&rfid[2]=='1'&&rfid[3]=='2'&&rfid[4]=='3'
&&rfid[5]=='4'&&rfid[6]=='5'&&rfid[7]=='6'&&rfid[8]=='7'&&rfid[9]=='8'&&rfid[10]=='9'&&rfid[11]=='S')
{
lcdcmd(0x01);
lcddis("SOCIETY MEMBER");
lcdcmd(0xc0);
lcddis("SLOT NO: 101");
delay();
mdelay();

if(ent_exit[0] == 'X'){
	slotCount--;
	door1p = 1; door1n = 0;				//clockwise direction to open entry door
	door2p = 0; door2n = 0;	
	ent_exit[0] = 'E';            //Car has enetered
	lcdcmd(0x01);
	lcddis("DOOR OPENING");
	lcdcmd(0xc0);
	lcddis("WELCOME VISWAJEET!");
	mdelay();
	door1p = 0; door1n = 0;
	mdelay();
	lcdcmd(0x01);
	door1p = 0; door1n = 1;
	lcddis("DOOR CLOSING");
	mdelay();
	door1p = 0; door1n = 0;
	lcdcmd(0x01);
	lcddis("Empty Slots:");  // Display a label
	lcdcmd(0xc0);
  convert(slotCount);
	mdelay();
	mdelay();
		
} else if(ent_exit[0] == 'E'){
	slotCount++;
	door2p = 1; door2n = 0;				//clockwise direction to open entry door
	door1p = 0; door1n = 0;
	ent_exit[0] = 'X';            //Car has exited
	lcdcmd(0x01);
	lcddis("DOOR OPENING");
	lcdcmd(0xc0);
	lcddis("Bye VISWAJEET!");
	mdelay();
	door2p = 0; door2n = 0;
	mdelay();
	lcdcmd(0x01);
	door2p = 0; door2n = 1;
	lcddis("DOOR CLOSING");
	mdelay();
	door2p = 0; door2n = 0;
	lcdcmd(0x01);
	lcddis("Empty Slots:");  // Display a label
	lcdcmd(0xc0);
  convert(slotCount);
	mdelay();
	mdelay();
}


} else if(rfid[0]=='R'&&rfid[1]=='U'&&rfid[2]=='1'&&rfid[3]=='2'&&rfid[4]=='3'
&&rfid[5]=='4'&&rfid[6]=='5'&&rfid[7]=='6'&&rfid[8]=='7'&&rfid[9]=='8'&&rfid[10]=='9'&&rfid[11]=='S')
{
lcdcmd(0x01);
lcddis("SOCIETY MEMBER");
lcdcmd(0xc0);
lcddis("SLOT NO: 102");
delay();
delay(); 

if(ent_exit[0] == 'X'){
	slotCount--;
	door1p = 1; door1n = 0;				//clockwise direction to open entry door
	door2p = 0; door2n = 0;	
	ent_exit[0] = 'E';            //Car has enetered
	lcdcmd(0x01);
	lcddis("DOOR OPENING");
	lcdcmd(0xc0);
	lcddis("WELCOME RUTIKA!");
	mdelay();
	door1p = 0; door1n = 0;
	mdelay();
	lcdcmd(0x01);
	door1p = 0; door1n = 1;
	lcddis("DOOR CLOSING");
	mdelay();
	door1p = 0; door1n = 0;
	lcdcmd(0x01);
	lcddis("Empty Slots:");  // Display a label
	lcdcmd(0xc0);
  convert(slotCount);
	mdelay();
	mdelay();
		
} else if(ent_exit[0] == 'E'){
	slotCount++;
	door2p = 1; door2n = 0;				//clockwise direction to open entry door
	door1p = 0; door1n = 0;
	ent_exit[0] = 'X';            //Car has exited
	lcdcmd(0x01);
	lcddis("DOOR OPENING");
	lcdcmd(0xc0);
	lcddis("Bye RUTIKA!");
	mdelay();
	door2p = 0; door2n = 0;
	mdelay();
	lcdcmd(0x01);
	door2p = 0; door2n = 1;
	lcddis("DOOR CLOSING");
	mdelay();
	door2p = 0; door2n = 0;
	lcdcmd(0x01);
	lcddis("Empty Slots:");  // Display a label
	lcdcmd(0xc0);
  convert(slotCount);
	mdelay();
	mdelay();
}
}

else if(rfid[0]=='R'&&rfid[1]=='U'&&rfid[2]=='1'&&rfid[3]=='2'&&rfid[4]=='3'
&&rfid[5]=='4'&&rfid[6]=='5'&&rfid[7]=='6'&&rfid[8]=='7'&&rfid[9]=='8'&&rfid[10]=='9'&&rfid[11]=='J')
{
lcdcmd(0x01);
lcddis("SOCIETY MEMBER");
lcdcmd(0xc0);
lcddis("SLOT NO: 103");
delay();
delay(); 

if(ent_exit[0] == 'X'){
	slotCount--;
	door1p = 1; door1n = 0;				//clockwise direction to open entry door
	door2p = 0; door2n = 0;	
	ent_exit[0] = 'E';            //Car has enetered
	lcdcmd(0x01);
	lcddis("DOOR OPENING");
	lcdcmd(0xc0);
	lcddis("WELCOME RUTUJA!");
	mdelay();
	door1p = 0; door1n = 0;
	mdelay();
	lcdcmd(0x01);
	door1p = 0; door1n = 1;
	lcddis("DOOR CLOSING");
	mdelay();
	door1p = 0; door1n = 0;
	lcdcmd(0x01);
	lcddis("Empty Slots:");  // Display a label
	lcdcmd(0xc0);
  convert(slotCount);
	mdelay();
	mdelay();
		
} else if(ent_exit[0] == 'E'){
	slotCount++;
	door2p = 1; door2n = 0;				//clockwise direction to open entry door
	door1p = 0; door1n = 0;
	ent_exit[0] = 'X';            //Car has exited
	lcdcmd(0x01);
	lcddis("DOOR OPENING");
	lcdcmd(0xc0);
	lcddis("Bye RUTUJA!");
	mdelay();
	door2p = 0; door2n = 0;
	mdelay();
	lcdcmd(0x01);
	door2p = 0; door2n = 1;
	lcddis("DOOR CLOSING");
	mdelay();
	door2p = 0; door2n = 0;
	lcdcmd(0x01);
	lcddis("Empty Slots:");  // Display a label
	lcdcmd(0xc0);
  convert(slotCount);
	mdelay();
	mdelay();
}
}

else
{
lcdcmd(0x01);
lcddis("OUTSIDE PERSON");
lcdcmd(0xc0);
lcddis("NO SLOT FOR YOU!");
mdelay();
mdelay();

}		
}	

void lcd_init()
{
lcdcmd(0x38);	//initialises crystal 5x7 matrix
lcdcmd(0x01); //clear screen
lcdcmd(0x10); //shift cursor position to right
lcdcmd(0x0c); //display on cursor off
lcdcmd(0x80);	//start display from 1st line 
}

void lcdcmd(unsigned char val)
{ 
P1 = val;	//P1 is connected to all Data lines from D0 to D7
rs = 0;		
rw = 0;
en = 1;		//Enable pin high to low to allow next command
delay();
en = 0;
}

void lcddat(unsigned char val)
{
P1 = val;
rs = 1;
rw = 0;
en = 1;
delay();
en = 0;
}

void delay()
{
unsigned int v5;
for(v5=0;v5<10000;v5++);
}

void lcddis(unsigned char *s)
{
unsigned char w;
for(w=0;s[w]!='\0';w++)
{
lcddat(s[w]);
}
}


void serial_init()
{
SCON = 0X50;	//Initiates serial communication
TMOD = 0X20;	//Select Timer 1 in Mode 2 by use of TMOD Register
TH1 = -3;			//baud rate = 9600
TR1 = 1;      //Start Timer
}



	
void mdelay()
{
unsigned int v6,v7;
for(v6 = 0;v6<2;v6++)
{
for(v7 = 0;v7<40000;v7++);
}
}

void convert(unsigned int value)
{
     
  for(k=0;k<2;k++)
  {
        digit[k]=value%10;
        value=value/10;
        }  
        for(p=1;p>=0;p--)
        {
       lcddata(digit[p]+48);
        ldelay(1);
        }
        if (slotCount==0)
        {
        lcdcmd(0x8d);
        lcdstring("NIL");
        }
      
        ldelay(10);
        }

			 void lcddata(char value)
{
         lcdport=value;
         rs=1;
         rw=0;
         en=1; 
         delay2(500);
         en=0;
}
			void ldelay(unsigned int x)
          {
           unsigned int i,j;
           for (i=0;i<=x;i++)
           for (j=0;j<=1275;j++);
       }

			 void lcdstring(char *p)
      {
         while(*p!='\0')
          {
            lcddata(*p);
            delay2(2000);
            p++;
          }
      }


 void delay2(unsigned int x)
 {
        unsigned int i;
        for(i=0;i<x;i++);
} 
