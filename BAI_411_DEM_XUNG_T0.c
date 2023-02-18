
#define BOARD D501
#include<tv_boards.c> 
unsigned int8 T0; 

void main()
{
   system_init();
   setup_timer_0(t0_ext_l_to_h|t0_div_1);
   set_timer0(90); // Khi test SV thay d?i giá tr? d?t cho nhanh
   while(true)
   {
      T0 = get_timer0();
      if(T0 > 100)set_timer0(1);
      d7seg.led[2] = m7d[T0 / 100 % 10];
      d7seg.led[1] = m7d[T0 / 10 % 10];
      d7seg.led[0] = m7d[T0 % 10];
      d7seg_display();
   }
}

