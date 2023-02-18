
#include <tv_boards.c>
#include <tv_lcd.c>

unsigned int8 T0=0,T0_temp=255;
unsigned int8 gtricai=1,gt_temp=99;

void ktnutnhan(){
   if(!inputcd(UP)){
      if(gtricai == 99)gtricai = 1;
      else gtricai++;
   }
   if(!inputcd(DW)){
      if(gtricai == 1)gtricai = 99;
      else gtricai--;
   }
   if(!inputcd(CLR)){
      gtricai = 1;
      T0 = 0;
      set_timer0(T0);
   }
}

void giai_ma7d(unsigned int8 x){
   unsigned int _i=0;
   do{
      d7seg.led[_i] = m7d[x%10];
      s7seg.led[_i] = m7d[x%10];
      x /= 10;
      _i++;
   }while(_i<2);
}

void main(){
   system_init();
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(0);
   
   lcd_setup();

   while(true){
      T0 = get_timer0();
      if(T0 > gtricai){
//!         T0 = T0 - 100;
         T0 = 1;
         set_timer0(T0);   
      }
      if(T0 != T0_temp){
         T0_temp = T0;
         giai_ma7d(T0);
         d7seg_display();
         lcd_goto(9,0);
         printf(lcd_data,"%02u",T0);
      }
      if(gtricai != gt_temp){
         
         gt_temp = gtricai;
         
         d7seg.led[2] = m7d[gtricai%10];
         d7seg.led[3] = m7d[gtricai/10];
         s7seg.led[6] = m7d[gtricai%10];
         s7seg.led[7] = m7d[gtricai/10];
         d7seg_display();
         lcd_goto(9,1);
         printf(lcd_data,"%02u",gtricai);
      }
      
      s7seg_display();
      ktnutnhan();
   }
}

