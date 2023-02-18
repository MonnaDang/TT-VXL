#define BOARD D501
#include <tv_boards.c>
#include <tv_lcd.c>

unsigned int8 bdn=0,dem=0;
unsigned int8 time[3]={0,0,0}; // giay(0) -> phut(1) -> gio(2)
unsigned int8 che_do=0; // che do chay tu 0-6: 0->chinh giay, 2->chinh phut, 4->chinh gio, 6->khong cho chinh
int1 nn;

void check_input(){
   if(!inputcd(UP)){
      if(che_do == 0){
         if(time[0] == 59) time[0] = 0;
         else time[0]++;
         // led quet
         s7seg.led[0] = m7d[time[0]%10];
         s7seg.led[1] = m7d[time[0]/10];
         // lcd
         lcd_goto(11,0);
         printf(lcd_data,"%2u",time[0]);
      }else if(che_do == 2){
         if(time[1] == 59) time[1] = 0;
         else time[0]++;
         // led quet
         s7seg.led[2] = m7d[time[1]%10];
         s7seg.led[3] = m7d[time[1]/10];
         // lcd
         lcd_goto(8,0);
         printf(lcd_data,"%2u",time[1]);
      }else if(che_do == 4){
         if(time[2] == 23) time[2] = 0;
         else time[2]++;
         // led quet
         s7seg.led[4] = m7d[time[2]%10];
         s7seg.led[5] = m7d[time[2]/10];
         // lcd
         lcd_goto(5,0);
         printf(lcd_data,"%2u",time[2]);
      }
   }
   if(!inputcd(DW)){
      if(che_do == 0){
         if(time[0] == 0) time[0] = 59;
         else time[0]--;
         s7seg.led[0] = m7d[time[0]%10];
         s7seg.led[1] = m7d[time[0]/10];
         lcd_goto(11,0);
         printf(lcd_data,"%2u",time[0]);
      }else if(che_do == 2){
         if(time[1] == 0) time[1] = 59;
         else time[0]--;
         s7seg.led[2] = m7d[time[1]%10];
         s7seg.led[3] = m7d[time[1]/10];
         lcd_goto(8,0);
         printf(lcd_data,"%2u",time[1]);
      }else if(che_do == 4){
         if(time[2] == 0) time[2] = 23;
         else time[2]--;
         s7seg.led[4] = m7d[time[2]%10];
         s7seg.led[5] = m7d[time[2]/10];
         lcd_goto(5,0);
         printf(lcd_data,"%2u",time[2]);
      }
   }
   if(!inputcd(MOD)){
      if(che_do == 6) che_do = 0;
      else che_do += 2;
      nn = 0;
   } 
}

void main(){
   system_init();
   
   setup_timer_1(t1_internal|t1_div_by_8); //div_8 de cx
   set_timer1(3036);
   
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   
   lcd_setup();
   
   lcd_goto(5,0);
   printf(lcd_data,"%2u %2u %2u",time[2], time[1], time[0]); 
   
   while(true){
      if(bdn>=10){
         bdn = bdn - 10;
         if(time[0] == 59){
            time[0] = 0;
            if(time[1] == 59){
               time[1] = 0;
               if(time[2] == 23) time[2] = 0;
               else time[2]++;
            }
            else time[1]++;
         }else time[0]++;
         lcd_goto(5,0);
         printf(lcd_data,"%2u %2u %2u",time[2], time[1], time[0]); 
      }
      
      s7seg.led[0] = m7d[time[0]%10];
      s7seg.led[1] = m7d[time[0]/10];
      s7seg.led[2] = m7d[time[1]%10];
      s7seg.led[3] = m7d[time[1]/10];
      s7seg.led[4] = m7d[time[2]%10];
      s7seg.led[5] = m7d[time[2]/10];
      if(nn){
         s7seg.led[che_do]   = 0xff;
         s7seg.led[che_do+1] = 0xff;
      }
      if(che_do < 6)
         if(dem==29){
            dem=0;
            nn = !nn;
            if(!nn && che_do == 0){
               lcd_goto(11,0);
               lcd_data("  ");
            }else if(nn && che_do == 0){
               lcd_goto(11,0);
               printf(lcd_data,"%2u",time[0]);
            }else if(!nn && che_do == 2){
               lcd_goto(8,0);
               lcd_data("  ");
            }else if(nn && che_do == 2){
               lcd_goto(8,0);
               printf(lcd_data,"%2u",time[1]);
            }else if(!nn && che_do == 4){
               lcd_goto(5,0);
               lcd_data("  ");
            }else if(nn && che_do == 4){
               lcd_goto(5,0);
               printf(lcd_data,"%2u",time[2]);
            }
         }
         else dem++;
      
      check_input();
      s7seg_display();
   }
}

#int_timer1
void ngat_timer1(){
   set_timer1(3036);
   bdn++;
}
