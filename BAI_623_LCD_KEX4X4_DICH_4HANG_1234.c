
#include<tv_boards.c> 
#include<tv_lcd.c>
#include<tv_key4x4.c>

unsigned char arr_1[20],arr_2[20],arr_3[20],arr_4[20];
unsigned int8 i;

void main()
{
   system_init();
   lcd_setup();
   
   for(i=0;i<20;i++){
      arr_1[i] = arr_2[i] = arr_3[i] = arr_4[i] = 0x20;
   }
   for(i=0;i<4;i++){
      lcd_goto(0,i);
      for(int j = 0; j<20 ; j++){
         lcd_data(arr_1[j]);
      }
   }
   while(true)
   {
      if(key4x4_read() == OK)
      {
         for(i=0;i<19;i++){
            arr_1[i] = arr_1[i+1];
            arr_2[i] = arr_2[i+1];
            arr_3[i] = arr_3[i+1];
            arr_4[i] = arr_4[i+1];
         }
         if(key4x4.key < 10) arr_1[19] = key4x4.key + 0x30;
         else arr_1[19] = key4x4.key  + 0x37; // xem bang ascii 
         arr_2[19] = arr_1[0];
         arr_3[19] = arr_2[0];
         arr_4[19] = arr_3[0];
         lcd_goto(0,0);
         for(i=0;i<20;i++){
            lcd_data(arr_1[i]);
         }
         lcd_goto(0,1);
         for(i=0;i<20;i++){
            lcd_data(arr_2[i]);
         }
         lcd_goto(0,2);
         for(i=0;i<20;i++){
            lcd_data(arr_3[i]);
         }
         lcd_goto(0,3);
         for(i=0;i<20;i++){
            lcd_data(arr_4[i]);
         }
      }
   }
}

