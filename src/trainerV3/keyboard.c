#include <avr/io.h>

int i=0,j=0;
char portState[4]= {0xEF,0xDF,0xBF,0x7F};
char inputState[4]={0x01,0x02,0x04,0x08};

/* 
	returns (line<<4 | coluumn) 
	values in [0;3]
	no idea why they swap
	j - line
	i - column
*/
char keyboard_get_state(){
 	for(i=0; i<4; i++)
    { 
       PORTA=portState[i];
       for(j=0; j<4; j++)
       { 
          if(((PINA&inputState[j])==0))
          {
		  	return (j*4 + i + 1);
          }
       }                          
    }
	return 0;  
}
