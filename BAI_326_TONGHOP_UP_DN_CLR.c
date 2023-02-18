
//!#define BOARD D501

#include <tv_boards.c>

unsigned int16 UP_state,DN_state,CLR_state; // these vars used for debounce btn
unsigned int8 i,j,mode=1,k;   

void check_UP(){
//!   UP_state = (UP_state<<1) | input(UP);
//!   if(UP_state == 0x8000){
    if(!inputcd(UP)){
      j=0; i=0;
      led32.ledx32 = 0;
      if(mode == 7) mode = 7;
      else mode ++;
   }
}

void check_DN(){
//!   DN_state = (DN_state<<1) | input(DW);
//!   if(DN_state == 0x8000){
    if(!inputcd(DW)){
      j=0; i =0;
      led32.ledx32 = 0;
      if(mode == 1) mode = 1;
      else mode --;
   }
}

void check_CLR(){
//!   CLR_state = (CLR_state<<1) | input(CLR);
//!   if(CLR_state == 0x8000){
    if(!inputcd(CLR)){
      j=0; i=0;
      led32.ledx32 = 0;
      mode = 1;
   }
}

void my_delay(){
   led32_display();
   for(k=0;k<100;k++){
      check_UP();
      check_DN();
      check_CLR();
      delay_ms(1);
   }
}

void SangTatDan_PST(){
   if(i<32) led32.ledx32 = (led32.ledx32<<1)|1;
   else led32.ledx32 = led32.ledx32<<1;
   if(i==63)i=0;
   else i++;
   my_delay();
}

void SangTatDan_TSP(){
   if(i<32) led32.ledx32 = (led32.ledx32>>1)|0x80000000;
   else led32.ledx32 = led32.ledx32>>1;
   if(i==63)i=0;
   else i++;
   my_delay();
}

void SangTatDan_N(){
   if(i<16){
      led32.ledx16[0] = (led32.ledx16[0]<<1)|1;
      led32.ledx16[1] = (led32.ledx16[1]>>1)|0x8000;
   }else{
      led32.ledx16[0] = led32.ledx16[0]<<1;
      led32.ledx16[1] = led32.ledx16[1]>>1;
   }
   if(i==31)i=0;
   else i++;
   my_delay();
}

void SangTatDan_T(){
   if(i<16){
      led32.ledx16[1] = (led32.ledx16[1]<<1)|1;
      led32.ledx16[0] = (led32.ledx16[0]>>1)|0x8000;
   }else{
      led32.ledx16[1] = led32.ledx16[1]<<1;
      led32.ledx16[0] = led32.ledx16[0]>>1;
   }
   if(i==31)i=0;
   else i++;
   my_delay();
}

void  SangDon_PST(){
   if(i==32) i = 0;
   else{
      if(j==(32-i)){
         j=0;
         i++;
      }else{
         led32.ledx32 = (~(0xffffffff>>i))|((int32)1<<j);
         j++;
         my_delay();
      }
   }
}

void  SangDon_TSP(){
   if(i==32) i = 0;
   else{
      if(j==(32-i)){
         j=0;
         i++;
      }else{
         led32.ledx32 = (~(0xffffffff<<i))|(0x80000000>>j);
         j++;
         my_delay();
      }
   }
}

void main(){
   system_init();
   led32.ledx32 = 0;
   led32_display();
   while(true){
      if(mode == 1) {
         led32.ledx32 = ~led32.ledx32;
         my_delay();  
      }
      else if (mode == 2) SangTatDan_PST();
      else if (mode == 3) SangTatDan_TSP();
      else if (mode == 4) SangTatDan_N();
      else if (mode == 5) SangTatDan_T();
      else if (mode == 6) SangDon_PST();
      else if (mode == 7) SangDon_TSP();
   }
}
