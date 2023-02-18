
#include <tv_boards.c>

void main(){
   system_init();
   
   while(true){
      if(input(ON) == 0) led32.ledx8[0] = 0xff;
      if(input(OFF) == 0) led32.ledx8[0] = 0;
      led32_display();
   }
}
