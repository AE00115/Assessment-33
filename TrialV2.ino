#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "ADC.h"
//Preprocessor Directives///
//Pre-defined header files///
void init();
////////////////////////Decleration Section////////////////////////

// int is the main fuction return type
// main() is program main function 

int sensor = 2; // the sensor is on A2

int x =  ADC_Read(0); // a function to read the ADC component (buttons) and expecting an integer 
int main(void){
  //BODY OF MAIN FUNCTION//

unsigned char Temperature[4];
unsigned char upp[6];
// wanted temperature = counter
int counter = 17 ; // giving the wanted temperature starting value of 17




float celsius;  

  init(); // For initialization
  

  while (1) //Never Ending while loop (so it can keep on working all the time)
  {
    int x =  ADC_Read(0);// a function to read the ADC component (buttons) and expecting an integer = x
    int t =  ADC_Read(sensor);// a function to read the ADC component (sensor) and expecting an integer = t
    t = (t*500)/1023; // equation to convert the Analogue value to Celsius (temperature reading)

    //To convert a 10-bit ADC value into a string of readable numbers
    // We  use a function called itoa (short for Integer TO ASCII)
    // This function takes three input parameters
    //(value we want to convert, input parameter of base of conversion 10 in this case (decimal in this case))
    //The string is placed in the buffer passed, which must be large enough to hold the output.
    
     LCD_String_xy(0,0,"Temperature:"); // LCD displaying "Temperature:" on the given place 
     itoa (t , Temperature , 10); // conversion to understand the value
	   LCD_String_xy(1,0,Temperature);  // LCD displaying the VALUE of the temperature on the given place
     LCD_String_xy(1,4,"Degree C"); // LCD displaying "Degree C" on the given place
     itoa(counter,upp,10); // conversion to understand the value
     

  _delay_ms(200);
  
  // We tested the analogue value of each button to be able to control the action of each one
  // UP = <200
  // DOWN = <400
  // RIGHT = <60
  // LEFT = <600
  // SELECT = <800
    
    if(x < 60){  //RIGHT
    // if right button is pressed  motor on ( clockwise direction ) and off the other direcion and turn on the LED and print on the LCD a message that motor is on
   
    PORTD = PORTD | (1 <<3);
    PORTB = PORTB &! (1 <<3); 
    PORTB = PORTB | (1 <<5);   
    LCD_String_xy(0,0,"Motor ON C");
    _delay_ms(1000);   
    LCD_Clear(); // clear the screen

  }
    else if( x<200  ) {  //UP
    // if up button is pressed motor on ( anti-clockwise direction ) and off the other direcion and turn on the LED and print on the LCD a message that motor is on
    
    PORTB = PORTB | (1 <<3);    
    PORTD = PORTD &! (1 <<3);
    PORTB = PORTB | (1 <<5);      
    LCD_String_xy(0,0,"Motor ON A-C");
    _delay_ms(1000);
     LCD_Clear(); // clear the screen 
    }  
    else if( x<400) { //DOWN
    // if up button is pressed decrease the value of counter by 2 
   
    counter = counter -2 ;
    LCD_Clear(); // clear the screen
      }

    else if(x<600) { //LEFT
    // if leftbutton is pressed decrease the value of counter2 by 2 
    
     counter = counter +2 ;
    LCD_Clear(); // clear the screen
     }
    else if(x<800) { //SELECT
    //if select button is pressed print on the LCD the following 
   
    LCD_Clear();
    PORTB = PORTB &! (1 <<3); 
    PORTD = PORTD &! (1 <<3); // clear the screen
    LCD_String_xy(1,0,"Set Temp:");   // 1. print on the LCD "Set Temp:"
    LCD_String_xy(1,6,upp);        // 1. print on the LCD the Value of the upper limit
    LCD_String_xy(0,0,"Motor OFF"); // print on the LCD "Motor OFF"
    _delay_ms(1000);
    LCD_Clear(); // clear the screen
    }  
     
   if(counter<t){  // if t (temperature) exceeded the wanted temperature
        
         PORTD = PORTD  | (1 <<2);  // BLUE LED ON
      }

    else { // if t (temperature) did not exceed the wanted temperature

      PORTD = PORTD &! (1 <<2); // BLUE LED OFF
    }
  }
  

}
void init()
{
  DDRB = DDRB | (1 << 5);  // Make PB5 ( RED LED ) output
  DDRC &= ~(1 << 2);   // Make temperature sensor input
  DDRD = DDRD | (1 << 3); // Make PD3 ( MOTOR PIN1 ) output 
  DDRB = DDRB | (1 << 3); // Make PB3 ( MOTOR PIN1 ) output
  DDRD = DDRD | (1 << 2); // make PD2 ( BLUE LED ) output 
  
      LCD_Init ();
      ADC_Init();
}
