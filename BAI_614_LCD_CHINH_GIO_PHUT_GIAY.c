
#define BOARD D501
#include <tv_boards.c>
#include <tv_lcd.c>

unsigned int8 bdn=0,_q;
unsigned int8 time[3]={0,0,0}; // giay(0) -> phut(1) -> gio(2)
unsigned int8 che_do=3; // che do chay tu 0-3: 0->chinh giay, 1->chinh phut, 2->chinh gio, 3->khong cho chinh
int1 nn=0;
unsigned int16 dem=0;

void check_input(){
   if(!inputcd(UP)){
      if(che_do == 0){
         if(time[0] == 59) time[0] = 0;
         else time[0]++;
         lcd_goto(11,0);
         printf(lcd_data,"%2u",time[0]);
      }else if(che_do == 1){
         if(time[1] == 59) time[1] = 0;
         else time[1]++;
         lcd_goto(8,0);
         printf(lcd_data,"%2u",time[1]);
      }else if(che_do == 2){
         if(time[2] == 23) time[2] = 0;
         else time[2]++;
         lcd_goto(5,0);
         printf(lcd_data,"%2u",time[2]);
      }
   }
   if(!inputcd(DW)){
      if(che_do == 0){
         if(time[0] == 0) time[0] = 59;
         else time[0]--;
         lcd_goto(11,0);
         printf(lcd_data,"%2u",time[0]);
      }else if(che_do == 1){
         if(time[1] == 0) time[1] = 59;
         else time[1]--;
         lcd_goto(8,0);
         printf(lcd_data,"%2u",time[1]);
      }else if(che_do == 2){
         if(time[2] == 0) time[2] = 23;
         else time[2]--;
         lcd_goto(5,0);
         printf(lcd_data,"%2u",time[2]);
      }
   }
   if(!inputcd(MOD)){
      if(che_do == 3) che_do = 0;
      else che_do++;
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
      
      if(che_do < 3)
         if(dem==2000){
            dem=0;
            nn = !nn;
            if(!nn && che_do == 0){
               lcd_goto(11,0);
               lcd_data("  ");
            }else if(nn && che_do == 0){
               lcd_goto(11,0);
               printf(lcd_data,"%2u",time[0]);
            }else if(!nn && che_do == 1){
               lcd_goto(8,0);
               lcd_data("  ");
            }else if(nn && che_do == 1){
               lcd_goto(8,0);
               printf(lcd_data,"%2u",time[1]);
            }else if(!nn && che_do == 2){
               lcd_goto(5,0);
               lcd_data("  ");
            }else if(nn && che_do == 2){
               lcd_goto(5,0);
               printf(lcd_data,"%2u",time[2]);
            }
         }
         else {
         dem++;
         }
      
      check_input();
   }
}

#int_timer1
void ngat_timer1(){
   set_timer1(3036);
   bdn++;
}
