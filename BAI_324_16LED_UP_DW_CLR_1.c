
#define   BOARD     D501
#include <tv_boards.c>


unsigned int8 i;

void main(){
   system_init();
   
   while(true){
   
      if(!inputcd(ON))led32.ledx16[0] = (led32.ledx16[0]<<1)|0x0001;
      if(!inputcd(OFF))led32.ledx16[0] = (led32.ledx16[0]>>1);
      if(!inputcd(CLR)) led32.ledx16[0] = 0;
      
      led32_display();
   }
}
