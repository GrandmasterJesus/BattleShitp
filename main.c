/*
 * BattleShip.c
 * Uses a PowerTip PG12864K 128x64 Graphical LCD (20 pins) to display the game. Each pin is defined and explained below.
 *
 * Created: 2020-03-29 10:43:48
 * Author : maxbo
 */ 

#include <avr/io.h>
#include <math.h>
#define D0 PA0		//Data bit 0
#define D1 PA1		//Data bit 1
#define D2 PA2		//Data bit 2
#define D3 PA3		//Data bit 3
#define D4 PA4		/*Data bit 4, RESET flag:		HIGH: System is being initialized. No instructions except status read can be accepted
													LOW: Initialize finished - System is in usual operation*/

#define D5 PA5		/*Data bit 5, ON/OFF flag:		HIGH: Display is OFF
													LOW: Display is ON*/
#define D6 PA6		//Data bit 6

#define D7 PA7		/*Data bit 7, BUSY flag			HIGH: Chip is executing operation - No incoming instructions accepted
													LOW: Chip is ready to accept incoming instructions*/
					
#define DIN			/*Data/Instruction (aka RS):	Tells LCD whether or not data is being written to the screen 
													or if the MCU is using the data bits to perform an instruction.
													HIGH: Data register (read), LOW: Instruction register (write)*/
					
#define RW PC1		/*Read/Write:					Selects which type of instruction is being performed on the LCD
													HIGH: Read from LCD to MCU, LOW: Write from MCU to LCD.*/
					
#define EN PC2		/*Enable:						Is used to clock operations to the LCD sequentially*/

#define CS1 PC3		/*Column (or Chip) Select 1:	Enables the left side of the screen (0-63)
													HIGH: Enabled, LOW: Disabled*/
#define CS2 PC4		/*Column (or Chip) Select 2:	Enables the right side of the screen (64-127)
													HIGH: Enabled, LOW: Disabled*/


int main(void)
{
	initLCD();
    while (1)
    {
		screenLeftOn();
    }
}

void initLCD(){
	DDRA |= 0xFF;
	DDRC |= 0xFF;
	PORTA = 0x00;
	PORTC = 0x00;
}

void displayOn(){
	PORTA = (1<<D5) | (1<<D4) | (1<<D3) | (1<<D2) | (1<<D1) | (1<<D0);
	PORTC = 0x00;
}
void displayOff(){
	PORTA = (1<<D5) | (1<<D4) | (1<<D3) | (1<<D2) | (1<<D1);
	PORTC |= 0x00;
}

void screenLeftOn(){
	PORTC = (1<<CS1);
}

void screenRightOn(){
	PORTC = (1<<CS2);
}

void setAdressY(){
	
}
