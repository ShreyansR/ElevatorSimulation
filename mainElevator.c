//TEJ3M mainElevator.c
/*********************************************************************
Module: Elevator Simulator
 main()

Author - Shreyans Rishi
Date - May 14, 2014

Explain Operation of Program here:
 This program creates an elevator simulator for 4 Floors.
 It also has an emergency button, when pressed takes back to level One.

Hardware Notes:
 * PIC used
     * eg. PIC24FV32KA302 operating at 8MHz
 * I/O ports used and hardware attached
     * eg. Output:
           * RB6 connected to green LED

********************************************************************/

/*******************************************************************
	Include Files
********************************************************************/

#include "p24FV32KA302.h"
#include "configBits.h"
#include "delay.h"

/*******************************************************************
                Symbolic Constants used by main()
********************************************************************/
//delay constant used for various delays
#define SHORT_DELAY 2000
#define LONG_DELAY 250
/*******************************************************************
                Local Function Prototypes
********************************************************************/
void initTimer (void);
void delay (unsigned long milli);
void levelOne();
void levelTwo();
void levelThree();
void levelFour();
int currentFloor = 1;
int destFloor = 0;
void emergency();
void Up();
void down();
void one();
void two();
void three();
void four();
/*******************************************************************
                Global Variable Declarations
********************************************************************/
//declare variable used in loops
unsigned int counter;
/*******************************************************************
 main() function
********************************************************************/
int main (void)
{
//initialize peripherals
   initTimer();
//PORTB all outputs
    TRISB=0;
// initialize PORTB
    LATB=0;

//PORTA all digital inputs
    TRISA=0xFF;
    ANSA=0;

one();
//continuously scanning for button inputs
while (1)
{
    
   // When button0 is pressed, the elevator goes up to level one.
  while (PORTAbits.RA0 == 1 && PORTAbits.RA1==0 && PORTAbits.RA2==0 && PORTAbits.RA3==0)
    levelOne();

  // When button1 is pressed, the elevator goes up to level two.
  while (PORTAbits.RA0 == 0 && PORTAbits.RA1==1 && PORTAbits.RA2==0 && PORTAbits.RA3==0)
    levelTwo();

  // When button2 is pressed, the elevator goes up to level three.
  while (PORTAbits.RA0 == 0 && PORTAbits.RA1==0 && PORTAbits.RA2==1 && PORTAbits.RA3==0)
    levelThree();

  // When button3 is pressed, the elevator goes up to level four.
  while (PORTAbits.RA0 == 0 && PORTAbits.RA1==0 && PORTAbits.RA2==0 && PORTAbits.RA3==1)
    levelFour();

  // When button4 is pressed, there is an emergency and the elevator returns to level one.
  while (PORTAbits.RA0 == 0 && PORTAbits.RA1==0 && PORTAbits.RA2==0 && PORTAbits.RA3==0 && PORTAbits.RA4==1)
    emergency();

}
}//end mainElevator.c

//The simulator goes up or down to the level 1.
void levelOne (void)
{
    destFloor = 1;
    delay(SHORT_DELAY);
    if(currentFloor == 2 && destFloor == 1)
    {
        down();
        one();
    }
    else if(currentFloor == 3 && destFloor == 1)
    {
        down();
        two();
        down();
        one();
    }
    else if(currentFloor == 4 && destFloor == 1)
    {
        down();
        three();
        down();
        two();
        down();
        one();
    }
    currentFloor = 1;
}
//The simulator goes up or down to the level 2.
void levelTwo (void)
{
    destFloor = 2;
    delay(SHORT_DELAY);
    if(currentFloor == 0 && destFloor == 2)
    {
        Up();
        one();
        Up();
        two();   
    }
    else if(currentFloor == 1 && destFloor == 2)
    {
        Up();
        two();
        
    }
    else if(currentFloor == 3 && destFloor == 2)
    {
        down();
        two();
    }
    else if(currentFloor == 4 && destFloor == 2)
    {
        down();
        three();
        down();
        two(); 
    }
    currentFloor = 2;
}
//The simulator goes up or down to the level 3.
void levelThree (void)
{
    destFloor = 3;
    delay(SHORT_DELAY);
    if(currentFloor == 0 && destFloor == 3)
    {
        Up();
        one();
        Up();
        two();
        Up();
        three();
    }
    else if(currentFloor == 1 && destFloor == 3)
    {
        Up();
        two();
        Up();
        three();
    }
    else if(currentFloor == 2 && destFloor == 3)
    {
        Up();
        three();
    }
    else if(destFloor == 3 && currentFloor == 4) 
    {
        down();
        three();     
}
    currentFloor = 3;
}
//The simulator goes to the level 4.
void levelFour (void)
{
    destFloor = 4;
    delay(SHORT_DELAY);
    if(destFloor == 4 && currentFloor == 0)
    {
        Up();
        one();
        Up();
        two();
        Up();
        three();
        Up();
        four();
    }
    else if(destFloor == 4 && currentFloor == 1)
    {
        Up();
        two();
        Up();
        three();
        Up();
        four();
    }
    else if(destFloor == 4 && currentFloor == 2)
    {
        Up();
        three();
        Up();
        four();
    }
    else if(destFloor == 4 && currentFloor == 3)
    {
        Up();
        four();
    }
    currentFloor = 4;
}
// Emergency. Flashes E and Red LED 5 times then goes back to level 1.
void emergency (void)
{
    for(counter=0; counter < 5; counter++){
        LATBbits.LATB12=1; //Emergency LED ON
        LATBbits.LATB10=1; //A
        LATBbits.LATB9=1; //B
        LATBbits.LATB4=1; //G
        LATBbits.LATB5=0; //F
        LATBbits.LATB6=0; //E
        LATBbits.LATB7=1; //D
        LATBbits.LATB8=1; //C
        delay(500);
        LATBbits.LATB12=0;//Emergency LED OFF
        LATBbits.LATB10=0; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=0; //G
        LATBbits.LATB5=0; //F
        LATBbits.LATB6=0; //E
        LATBbits.LATB7=0; //D
        LATBbits.LATB8=0; //C
        delay(500);
        }
    levelOne();
    one();
}
// Animation for elevator going up
void Up (void)
{
        delay(500);
        LATBbits.LATB10=1; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=0; //G
        LATBbits.LATB5=0; //F
        LATBbits.LATB6=0; //E
        LATBbits.LATB7=0; //D
        LATBbits.LATB8=0; //C
        delay(500);
        LATBbits.LATB10=1; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=1; //G
        LATBbits.LATB5=0; //F
        LATBbits.LATB6=0; //E
        LATBbits.LATB7=0; //D
        LATBbits.LATB8=0; //C
        delay(500);
        LATBbits.LATB10=1; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=1; //G
        LATBbits.LATB5=0; //F
        LATBbits.LATB6=0; //E
        LATBbits.LATB7=1; //D
        LATBbits.LATB8=0; //C
        delay(500);
        LATBbits.LATB10=0; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=0; //G
        LATBbits.LATB5=0; //F
        LATBbits.LATB6=0; //E
        LATBbits.LATB7=0; //D
        LATBbits.LATB8=0; //C
}
// Animation for elevator going down
void down (void)
{
        delay(500);
        LATBbits.LATB10=0; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=0; //G
        LATBbits.LATB5=0; //F
        LATBbits.LATB6=0; //E
        LATBbits.LATB7=1; //D
        LATBbits.LATB8=0; //C
        delay(500);
        LATBbits.LATB10=0; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=1; //G
        LATBbits.LATB5=0; //F
        LATBbits.LATB6=0; //E
        LATBbits.LATB7=1; //D
        LATBbits.LATB8=0; //C
        delay(500);
        LATBbits.LATB10=1; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=1; //G
        LATBbits.LATB5=0; //F
        LATBbits.LATB6=0; //E
        LATBbits.LATB7=1; //D
        LATBbits.LATB8=0; //C
        delay(500);
        LATBbits.LATB10=0; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=0; //G
        LATBbits.LATB5=0; //F
        LATBbits.LATB6=0; //E
        LATBbits.LATB7=0; //D
        LATBbits.LATB8=0; //C
}
//Display One
void one (void)
{
        LATBbits.LATB10=0; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=0; //G
        LATBbits.LATB5=1; //F
        LATBbits.LATB6=1; //E
        LATBbits.LATB7=0; //D
        LATBbits.LATB8=0; //C
}
//Display Two
void two (void)
{
        LATBbits.LATB10=1; //A
        LATBbits.LATB9=1; //B
        LATBbits.LATB4=1; //G
        LATBbits.LATB5=0; //F
        LATBbits.LATB6=1; //E
        LATBbits.LATB7=1; //D
        LATBbits.LATB8=0; //C
}
//Display Three
void three (void)
{
        LATBbits.LATB10=1; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=1; //G
        LATBbits.LATB5=1; //F
        LATBbits.LATB6=1; //E
        LATBbits.LATB7=1; //D
        LATBbits.LATB8=0; //C
}
//Display Four
void four (void)
{
        LATBbits.LATB10=0; //A
        LATBbits.LATB9=0; //B
        LATBbits.LATB4=1; //G
        LATBbits.LATB5=1; //F
        LATBbits.LATB6=1; //E
        LATBbits.LATB7=0; //D
        LATBbits.LATB8=1; //C
}
//45, 48