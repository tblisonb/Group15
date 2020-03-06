/*** 
 * Author: Jason Guest
 * Version: February 2020
 */

#include <avr/io.h>


// The following constants correspond to the pin in 
// the PORT they are registered to
// RS should connect to pin 1 of PORTx for example
const unsigned char RS_Pin = 0x01; // first pin
const unsigned char RW_Pin = 0x02; // second pin
const unsigned char E_Pin = 0x04; // third pin

// hex DDRAm addresses corresponding to LCD display box:
// 00|01|02|03|04|05|06|07|08|09|0A|0B|0C|0D|0E|0F
// 40|41|42|43|44|45|46|47|48|49|4A|4B|4C|4D|4E|4F

lcd_clearDisplay(){
    /* 0x01 */
}

lcd_display_off(){
    /* hex 0x0C */
}

lcd_go_firstUpper(){
    /*0x80*/
}

lcd_go_firstLower(){
    /*0xC0*/
}

LCD_home(){
    /* 0x02 */
}

LCD_instruction(unsigned char value){
    
    
}

LCD_init(){
    
    
}
