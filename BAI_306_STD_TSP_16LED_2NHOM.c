#define   BOARD     D501
#include<tv_boards.c>  

unsigned int16 data_1,data_2;
unsigned int8 i;

void main()
{
      system_init();
      while(true)
      {     
           for(i=0;i<16;i++){
               data_1 = (data_1<<1)|0x0001;
               data_2 = (data_2>>1)|0x8000;
               led32.ledx16[0]=data_2;
               led32.ledx16[1]=data_2;
               led32_display();
               delay_ms(100);
           }
           for(i=0;i<16;i++){
               data_1 = (data_1<<1);
               data_2 = (data_2>>1);
               led32.ledx16[0]=data_2;
               led32.ledx16[1]=data_2;
               led32_display();
               delay_ms(100);
           }
//!           for(i=0;i<16;i++){
//!               data_1 = (data_1<<1)|0x0001;
//!               data_2 = (data_2>>1)|0x8000;
//!               led32.ledx16[0]=data_2;
//!               led32.ledx16[1]=data_1;
//!               led32_display();
//!               delay_ms(100);
//!           }
//!           for(i=0;i<16;i++){
//!               data_1 = (data_1<<1);
//!               data_2 = (data_2>>1);
//!               led32.ledx16[0]=data_2;
//!               led32.ledx16[1]=data_1;
//!               led32_display();
//!               delay_ms(100);
//!           }
           
      }
}
