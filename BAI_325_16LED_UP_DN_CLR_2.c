#define BOARD D501
#include <tv_boards.c>


unsigned int8 i;
unsigned int1 tt=0;
unsigned int16 state;

void main(){
   system_init();
   
   while(true){
      if(!inputcd(ON)){
         if(tt == 0) led32.ledx32 = (led32.ledx32<<1)|1;
         else led32.ledx32 = (led32.ledx32>>1)|0x80000000;
      }
      if(!inputcd(OFF)){
         if(tt == 0) led32.ledx32 = (led32.ledx32>>1);
         else led32.ledx32 = (led32.ledx32<<1);
      }

//!      state=(state<<1) | input(CLR);
//!      
//!      if(state == 0x8000) {
      if(!inputcd(CLR)){
         tt = !tt;
         led32.ledx32 = 0;
      }
      
      led32_display();
   }
}
