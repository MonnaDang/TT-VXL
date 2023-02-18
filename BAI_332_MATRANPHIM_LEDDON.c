
#include<tv_boards.c> 
#include<tv_key4x4.c> 

void main()
{
   system_init();

   while(true)
   {
      if(key4x4_read() == OK)
      {
         led32.ledx32 = key4x4.key;
         led32_display();
      }
   }
}

