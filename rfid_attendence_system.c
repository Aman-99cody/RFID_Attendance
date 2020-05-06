// Program to get the 12 byte string and display it on LCD by Polling method:
/*
The RFID unique code is been displayed on LCE
LCD DATA port----PORT B
ctrl port------PORT D
	rs-------PD0
	rw-------PD1
	en-------PD2
*/

#define F_CPU 11059200UL 

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "lcdlib3.h"
#include "uart_rec_lib.h"

// void LCD_cmd(unsigned char cmd);
// void init_LCD(void);
// void LCD_write(unsigned char data);

// void usart_init();
// unsigned int usart_getch();

unsigned char i, card[12];
unsigned char db1[12]={"18008909BD25"},db2[12]={"1800892219AA"},db3[12]={"1800892D9F23"};
void getcard_id(void);
void LCD_display(int);

int main(void)
{
	unsigned int t1=0,t2=0,t3=0,p=0,m=0,q=0;
	DDRA=0xff;		//LCD_DATA port as output port
	//DDRB=0x07;	//ctrl as out put		
	lcd_init();		//initialization of LCD
	_delay_ms(50);		// delay of 50 milliseconds
	usart_init();		// initiailztion of USART
		
		//Function to display string on LCD
	while(1)
	{
		lcd_print("Swipe your card:");
		t1=0,t2=0,t3=0;
		getcard_id();
// 		n=strcmp(card,db1);
// 		k=strcmp(card,db2);
// 		c=strcmp(card,db3);
		for(i=0;i<12;i++)
		{
		if(card[i]==db1[i])
		{		
			t1++;
		}	
		}		
		for(i=0;i<12;i++)
		{
		if(card[i]==db2[i])
		{		
			t2++;
		}	
		}	
		for(i=0;i<12;i++)
		{
		if(card[i]==db3[i])
		{		
			t3++;
		}	
		}			
		if(t1==12)
		{	
		lcd_clear();
		lcd_gotoxy(1,1);
		lcd_print("person 1");							//Function to get RFID card no. from serial port
		lcd_gotoxy(1,2);
		p++;	// to go in second line and zeroth position on LCD
		LCD_display(p);	
			// a function to write RFID card no. on LCD
		}
		else if(t2==12)
		{			
			//p=0;
		lcd_clear();
		lcd_gotoxy(1,1);
		lcd_print("person 2");			//Function to get RFID card no. from serial port
		lcd_gotoxy(1,2);	// to go in second line and zeroth position on LCD
		m++;
		LCD_display(m);	
		
			// a function to write RFID card no. on LCD
		}
		else if(t3==12)
		{		
		lcd_clear();
		lcd_gotoxy(1,1);
		lcd_print("person 3");				//Function to get RFID card no. from serial port
		lcd_gotoxy(1,2);	// to go in second line and zeroth position on LCD
		q++;
		LCD_display(q);	
			// a function to write RFID card no. on LCD
		}
		else
		{
			lcd_gotoxy(1,2);
			lcd_print("no access");
		}
		_delay_ms(1000);
		lcd_clear();
	}	
	
	return 0;
}

void getcard_id(void)	//Function to get 12 byte ID no. from rfid card
{	
	for(i=0;i<12;i++) 
	{
		card[i]= read_uart();	// receive card value byte by byte
	}
	return;
}

void LCD_display(int f)	//Function for displaying ID no. on LCD
{
	//int c=0;
	/*for(i=0;i<12;i++)
	{
		lcddata(card[i]);	// display card value byte by byte
	}*/
	lcd_print("attendence");
	//c++;
	lcd_gotoxy(11,2);
	lcd_display_int(f);
	return;
}

