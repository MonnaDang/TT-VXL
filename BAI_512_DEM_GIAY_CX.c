
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
      if(bdn >= 10)// Tr�n d? 10 l?n l� du?c 1 gi�y
      {
         bdn = bdn - 10;
         giay++;
         giay %= 60; // Kh?ng ch? gi�y trong ph?m vi t? 0 d?n 59
      }

      s7seg.led[4] = m7d[giay / 10 % 10]; // Gi?i m� h�ng ch?c c?a gi�y
      s7seg.led[3] = m7d[giay % 10]; // Gi?i m� h�ng don v? c?a gi�y
      s7seg_display(); // Qu�t LED
   }
}

#int_TIMER1 // Chuong tr�nh con x? l� ng?t T1
void ngat_timer1() // Kh�ng vi?t g� v�o gi?a 2 h�ng n�y
{
   set_timer1(3036);
   bdn++;
}

