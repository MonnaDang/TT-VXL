#define  BOARD D501 
#include <tv_boards.c>
#include <tv_glcd.c>
#include "MATH.h"

#define TAM_X  60
#define TAM_Y  31
#define RAD    30

unsigned int8 bdn,giay=50;

void vehinh(){
   
   glcd_circle(60,31,35,1,0);
   
   glcd_circle(60,31,30,0,1);
   glcd_text_setup(TAM_X-5,1,1,1,1);
   printf(glcd_text,"12");
   glcd_text_setup(TAM_X+RAD-3,TAM_Y-4,1,1,1);
   printf(glcd_text,"3");
   glcd_text_setup(TAM_X,TAM_Y+RAD-5,1,1,1);
   printf(glcd_text,"6");
   glcd_text_setup(TAM_X-RAD-2,TAM_Y-4,1,1,1);
   printf(glcd_text,"9");
   glcd_update();
   
   glcd_line(TAM_X,TAM_Y,TAM_X+(RAD-10)*sin(giay*2*PI/60),TAM_Y-(RAD-10)*cos(giay*2*PI/60),1);
   
   glcd_update();
}

void main(){
   system_init();
   
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);
   
   glcd_setup();
   glcd_circle(60,31,30,0,1);
   glcd_text_setup(TAM_X-5,1,1,1,1);
   printf(glcd_text,"12");
   glcd_text_setup(TAM_X+RAD-3,TAM_Y-4,1,1,1);
   printf(glcd_text,"3");
   glcd_text_setup(TAM_X,TAM_Y+RAD-5,1,1,1);
   printf(glcd_text,"6");
   glcd_text_setup(TAM_X-RAD-2,TAM_Y-4,1,1,1);
   printf(glcd_text,"9");
   glcd_update();
   vehinh();
   
   while(true){
      if(bdn >= 10){
         bdn = bdn - 10;
         if(giay == 59) giay = 0;
         else giay ++;
         vehinh();
      }
   }
}

#int_timer1
void timer1_isr(){
   bdn++;
   set_timer1(3036);
}

