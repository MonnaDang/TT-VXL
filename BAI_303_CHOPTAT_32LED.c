
#define   BOARD     D501
#include<tv_boards.c>  


void main()
{
      system_init();
      while(true)
      {     
           led32.ledx32 = ~led32.ledx32;
           led32_display();
           delay_ms(500);
      }
}
