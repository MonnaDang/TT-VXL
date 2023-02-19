
#include <tv_boards.c>
#include <tv_glcd.c>
#include "MATH.h"

#define TAM_X  60
#define TAM_Y  31
#define RAD    30

unsigned int8 bdn,giay;
unsigned int8 x_cor,x_cor_temp,y_cor,y_cor_temp;

void vehinh(){
   x_cor = TAM_X+(RAD-10)*sin(giay*2*PI/60);
   y_cor = TAM_Y-(RAD-10)*cos(giay*2*PI/60);
   
   glcd_bar(TAM_X,TAM_Y,x_cor_temp,y_cor_temp,1,0);
   glcd_bar(TAM_X,TAM_Y,x_cor,y_cor,1,1);
   
   x_cor_temp = x_cor;
   y_cor_temp = y_cor;
  
  glcd_text_setup(110,0,4,1,1);
  printf(glcd_text,"%02u",giay);
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
