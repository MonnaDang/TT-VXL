#define   BOARD     D501
#include<tv_boards.c>  

unsigned int8 i;
unsigned int32 data;

void main()
{
      system_init();
      while(true)
      {     
           if(i<32)data=(data<<1)|1;
           else data = data<<1;
           led32.ledx32 = data;
           led32_display();
           delay_ms(500);
           if(i==63  )i=0;
           else i++;
      }
}
