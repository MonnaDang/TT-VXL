#define BOARD D501
#include<tv_boards.c>

unsigned int8 T0,T0_TAM; 
void d7seg_xoa0VN(unsigned int16 d)
{
   unsigned int8 n = 0;

   do
   {
      d7seg.led[n] = m7d[d % 10];
      d /= 10; n++;
   }while(d != 0);

   for(; n < 4; n++)d7seg.led[n] = 0xff;
   d7seg_display();
}

void main()
{
   system_init();
   setup_timer_0(T0_EXT_H_TO_L|T0_DIV_1);
   set_timer0(240);
   while(true)
   {
     T0 = get_timer0();
     if(T0 == 0){
      set_timer0(240); // co hien thi so 0 khi timer reset nhung thoi gian xl nhanh nen ko thay dc xai ham delay de quan sat
      T0 = 240;         // gan lai de dam bao hien thi dung ke ca bi delay
     }
     if(T0 != T0_TAM){
         T0_TAM = T0;
         d7seg_xoa0VN(T0);
     }
   }
}

