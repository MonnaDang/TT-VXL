#define BOARD D501

#include<tv_boards.c> 

unsigned int8 gio,phut,giay;

void main()
{
   system_init();

   while(true)
   {
      if(giay == 59){
         giay = 0;
         if(phut == 59){
            phut = 0;
         }else phut++;
      }else giay++;
      
      d7seg.led[0] = m7d[giay%10];
      d7seg.led[1] = m7d[giay/10%10];
      d7seg.led[2] = m7d[phut%10]-128;
      d7seg.led[3] = m7d[phut/10%10];
      
      d7seg_display();
      delay_ms(100);
   }
}
