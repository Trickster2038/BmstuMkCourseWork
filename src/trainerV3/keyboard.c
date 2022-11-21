#include <avr/io.h>

char i=0,j=0;
char portState[4]= {0xEF,0xDF,0xBF,0x7F}; // select active line
char inputState[4]={0x01,0x02,0x04,0x08}; // check column using mask

// returns pressed key N
char keyboard_get_state(){
 	for(i=0; i<4; i++)
    { 
       PORTA=portState[(int) i]; // select active line
       for(j=0; j<4; j++)
       { 
          if(((PINA&inputState[(int) j])==0)) // check column using mask
          {
		  	return (j*4 + i + 1); 
          }
       }                          
    }
	return 0;  
}
