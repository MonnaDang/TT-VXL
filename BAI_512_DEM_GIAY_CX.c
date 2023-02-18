
#include<tv_boards.c> 
unsigned int8 giay=0,bdn=0;

void main()
{
   system_init();
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(int_TIMER1);
   enable_interrupts(GLOBAL);

   while(true)
   {
      if(bdn >= 10)// Tràn d? 10 l?n là du?c 1 giây
      {
         bdn = bdn - 10;
         giay++;
         giay %= 60; // Kh?ng ch? giây trong ph?m vi t? 0 d?n 59
      }

      s7seg.led[4] = m7d[giay / 10 % 10]; // Gi?i mã hàng ch?c c?a giây
      s7seg.led[3] = m7d[giay % 10]; // Gi?i mã hàng don v? c?a giây
      s7seg_display(); // Quét LED
   }
}

#int_TIMER1 // Chuong trình con x? lý ng?t T1
void ngat_timer1() // Không vi?t gì vào gi?a 2 hàng này
{
   set_timer1(3036);
   bdn++;
}

