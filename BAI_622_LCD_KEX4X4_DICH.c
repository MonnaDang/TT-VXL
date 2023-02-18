
#include<tv_boards.c> 
#include<tv_lcd.c>
#include<tv_key4x4.c>

unsigned char arr[20];
unsigned int8 i;

void main()
{
   system_init();
   lcd_setup();
   lcd_goto(3,0);
   lcd_data("HAY NHAN PHIM");
   
   for(i=0;i<20;i++){
      arr[i] = 0x20;
   }

   while(true)
   {
      if(key4x4_read() == OK)
      {
         for(i=0;i<19;i++){
            arr[i] = arr[i+1];
         }
         if(key4x4.key < 10) arr[19] = key4x4.key + 0x30;
         else arr[19] = key4x4.key  + 0x37; // xem bang ascii 
         lcd_goto(0,1);
         for(i=0;i<20;i++){
            lcd_data(arr[i]);
         }
      }
   }
}

