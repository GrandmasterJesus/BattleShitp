/*
 * BattleShip.c
 * Uses a PowerTip PG12864K 128x64 Graphical LCD (20 pins) to display the game. Each pin is defined and explained below.
 *
 * Created: 2020-03-29 10:43:48
 * Author : maxbo
 */ 


#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#define F_CPU 8000000UL;

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
					
#define DIN PC0		/*Data/Instruction (aka RS):	Tells LCD whether or not data is being written to the screen 
													or if the MCU is using the data bits to perform an instruction.
													HIGH: Data register (read), LOW: Instruction register (write)*/
					
#define RW PC1		/*Read/Write:					Selects which type of instruction is being performed on the LCD
													HIGH: Read from LCD to MCU, LOW: Write from MCU to LCD.*/
					
#define EN PC2		/*Enable:						Is used to clock operations to the LCD sequentially. NOTE: Positive edge triggered!*/

#define CS1 PC3		/*Column (or Chip) Select 1:	Enables the left side of the screen (0-63)
													HIGH: Enabled, LOW: Disabled*/
#define CS2 PC4		/*Column (or Chip) Select 2:	Enables the right side of the screen (64-127)
													HIGH: Enabled, LOW: Disabled*/

#define RESET 0b00010000 //

int main(void)
{
	initLCD();
	displayOn();
	screenRightOn();
	addr_Y(3);
	addr_X(7);
    while (1)
    {
		
	writeData();
    }
}

/*Initialize ports connected to the LCD display*/
void initLCD(){
	DDRA |= 0xFF;
	DDRC |= 0xFF;
	PORTA = 0x00;
	PORTC = 0x00 | RESET;
	clkLCD();
}

/*Enables the pixels on the LCD display */
void displayOn(){
	PORTA = (1<<D5) | (1<<D4) | (1<<D3) | (1<<D2) | (1<<D1) | (1<<D0);
	PORTC = 0x00;
	clkLCD();
}

/*Disables the pixels on the LCD display */
void displayOff(){
	PORTA = ((1<<D5) | (1<<D4) | (1<<D3) | (1<<D2) | (1<<D1)) & ~(1<<D0);
	PORTC |= 0x00;
	clkLCD();
}

/*Enables the leftmost 64 pixels on the x-axis on the LCD display*/
void screenLeftOn(){
	PORTC |= (1<<CS1) & ~(1<<CS2);
}

/*Enables the rightmost 64 pixels on the x-axis on the LCD display*/
void screenRightOn(){
	PORTC |= (1<<CS2) & ~(1<<CS1);
}

/*positive edge clock cycle, enables incoming operations to the LCD*/
void clkLCD(){
	PORTC &= ~(1<<EN);
	_delay_ms(2);
	PORTC |= (1<<EN);
}

/*Command for setting the "cursor" on the Y-axis. 0 < y < 63*/
void addr_Y(uint8_t y){
	PORTC &= ~(1<<DIN) | ~(1<<RW);
	PORTA = (1<<D6) | y;
	clkLCD();
}

/*Command for setting the "cursor" on the X-axis. 0 < x < 7*/
void addr_X(uint8_t x){
	PORTC &= ~(1<<DIN) | ~(1<<RW);
	PORTA = (1<<D7) | (1<<D5) | (1<<D4) | (1<<D3) | x;
	clkLCD();
}

void writeData(){
	PORTC |= (1<<DIN) & ~(1<<RW);
	clkLCD();
}





