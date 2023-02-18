
#define   BOARD     D501
#include<tv_boards.c>  

unsigned int16 data;
unsigned int8 i;

void main()
{
      system_init();
      while(true)
      {     
           for(i=0;i<16;i++){
            data = (data<<1)|0x01; // xem them sach  ~(0xffff<n)
            led32.ledx16[0]=data;
            led32.ledx8[3] = ~led32.ledx8[3];
            led32_display();
            delay_ms(500);
           }
           for(i=0;i<16;i++){
            data = (data<<1);
            led32.ledx16[0]=data;
            led32.ledx8[3] = ~led32.ledx8[3];
            led32_display();
            delay_ms(500);
           }
           
      }
}
