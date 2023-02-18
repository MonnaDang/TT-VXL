#define   BOARD     D501
#include<tv_boards.c>  

unsigned int16 data_1,data_2;
unsigned int8 i;

void main()
{
      system_init();
      while(true)
      {     
           data_1=0;
           for(i=0;i<16;i++){
               data_1 = (data_1>>1)|0x8000;
               data_2 = 1<<i;
               led32.ledx16[1]=data_1;
               led32.ledx16[0]=data_2;
               led32_display();
               delay_ms(80);
           }   
           data_1=0;
           for(i=0;i<16;i++){
               data_1 = (data_1<<1)|1;
//!               data_1 = ~(0xffff<<i);
               data_2 = 0x8000>>i;
               led32.ledx16[1]=data_1;
               led32.ledx16[0]=data_2;
               led32_display();
               delay_ms(80);
           }
           
      }
}
