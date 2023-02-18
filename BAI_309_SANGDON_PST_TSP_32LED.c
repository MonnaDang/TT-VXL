
#define   BOARD     D501
#include<tv_boards.c>  

unsigned int32 x,y,z;
unsigned int8 i,j;

void main()
{
      system_init();
      while(true)
      {     
           x=y=0;
           for(i=0;i<32;i++){
               z=1;
               for(j=i;j<32;j++){
                     y=z|x;
                     z=z<<1;
                     led32.ledx32 = y;
                     led32_display();
                     delay_ms(50);
               }
               x=y;
           }
      }
}
