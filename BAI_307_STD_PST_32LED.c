
#define   BOARD     D501
#include<tv_boards.c>  

unsigned int32 data;
unsigned int8 i;

void main()
{
      system_init();
      while(true)
      {     
           for(i=0;i<32;i++){
               data = (data>>1)|0x80000000;
               led32.ledx32 = data;
               led32_display();
               delay_ms(80);
           }
           for(i=0;i<32;i++){
               data = (data>>1);
               led32.ledx32 = data;
               led32_display();
               delay_ms(80);
           }
           
      }
}
