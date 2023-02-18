
#define   BOARD     D501
#include<tv_boards.c>  


void main()
{
      system_init();
      while(true)
      {     
           static unsigned int8 data=0,i=0;
           for(i=0;i<8;i++){
            data = (data<<1)|0x01;
            led32.ledx8[0] = data;
            led32_display();
            delay_ms(500);
           }
           for(i=0;i<8;i++){
            data = (data<<1);
            led32.ledx8[0] = data;
            led32_display();
            delay_ms(500);
           }
           
      }
}
