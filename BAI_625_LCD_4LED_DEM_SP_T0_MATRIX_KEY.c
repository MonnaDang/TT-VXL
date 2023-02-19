
#include <tv_boards.c>
#include <tv_lcd.c>
#include <tv_key4x4.c>

unsigned int8 T0=0,T0_temp=255;
unsigned int8 gtricai=10,gt_temp=99;

int1 sophim = 0;

void giai_ma7d(unsigned int8 x){
   unsigned int _i=0;
   do{
      d7seg.led[_i] = m7d[x%10];
      s7seg.led[_i] = m7d[x%10];
      x /= 10;
      _i++;
   }while(_i<2);
}

void kt_mtphim(){
   if(key4x4_read() == OK){
      if(key4x4.key <= 9){
         if(!sophim){
            gtricai = key4x4.key*10;
                     
            s7seg.led[0] = 0xff-64;
            s7seg.led[1] = 0xff-64;
            d7seg.led[1] = 0xff-64;
            d7seg.led[0] = 0xff-64;
            d7seg_display();
            lcd_goto(9,0);
            printf(lcd_data,"--");
            
            setup_timer_0(T0_OFF);
            
            sophim = !sophim;
         }else{
            gtricai += key4x4.key;
            setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
            set_timer0(0);
             
            giai_ma7d(0);
            
            d7seg_display();
            lcd_goto(9,0);
            printf(lcd_data,"%02u",0);
            
            d7seg_display();
            lcd_goto(9,1);
            printf(lcd_data,"%02u",gtricai);
            
            sophim = !sophim;
         }
      }
   }
}


void main(){
   system_init();
   
   lcd_setup();

   lcd_goto(0,0);
   lcd_data("GTRI DEM:");
   lcd_goto(0,1);
   lcd_data("GTRI CAI:");
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
      kt_mtphim();
      s7seg_display();
   }
}

