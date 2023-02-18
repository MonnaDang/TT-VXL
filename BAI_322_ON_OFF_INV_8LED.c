#include <tv_boards.c>

void main(){
   system_init();
   
   while(true){
      if(input(ON) == 0) led32.ledx8[0] = 0x0f;
      if(input(OFF) == 0) led32.ledx8[0] = 0;
      if((inputcd(INV) == 0) && (led32.ledx8[0] != 0)) // cho phep dao khi on, off ko con hieu luc
               led32.ledx8[0] = ~led32.ledx8[0];
      
      led32_display();
   }
}
