//!#define   BOARD     D501
#include<tv_boards.c>  

unsigned int8 i,j;
unsigned int8 che_do = 1, cap_tocdo = 1;
unsigned int16 k,speed=50;
int1 tt;
unsigned int16 Up_state,Dw_state,Mod_state;

void kt_nutnhan(){
   delay_ms(1);
   Up_state = (Up_state<<1) | input(UP);
   Dw_state = (Dw_state<<1) | input(DW);
   Mod_state = (Mod_state<<1) | input(MOD);
//!   if(!input(UP)){
   if(Up_state == 0x8000){
      if(!tt){
         if(che_do < 10)che_do++;
      }else{
         if(cap_tocdo < 10)cap_tocdo++;
         speed = (int16)cap_tocdo*50;
      }
   }
//!   if(!input(DW)){
   if(Dw_state == 0x8000){
      if(!tt){
         if(che_do > 1)che_do--;
      }else{
         if(cap_tocdo > 1)cap_tocdo--;
         speed = (int16)cap_tocdo*50;
      }
   }
//!   if(!input(MOD)){
   if(Mod_state == 0x8000){
      tt = !tt;
   }
}

void SangDan_TSP(){
   for(i=0;i<=24;i++){
      led32.ledx32 = (~(0x0fffffff>>i)) & 0x0ffffff0 | (int32)tt;
      led32_display();
      for(k=0;k<speed;k++)kt_nutnhan();
   }
}

void SangDan_PST(){
   for(i=0;i<=24;i++){
      led32.ledx32 = (~(0xfffffff0<<i)) & 0x0ffffff0 | (int32)tt;
      led32_display();
      for(k=0;k<speed;k++)kt_nutnhan();
   }
}

void ChopTat_5lan(){
   for(i=0;i<10;i++){
      led32.ledx32 = (~led32.ledx32) & 0x0ffffff0 | (int32)tt;
      led32_display();
      for(k=0;k<speed;k++)kt_nutnhan();
   }
}

void SangDich_TSP(){
   for(i=0;i<24;i++){
      led32.ledx32 = 0x08000000>>i | (int32)tt;
      led32_display();
      for(k=0;k<speed;k++)kt_nutnhan();
   }
}

void SangDich_PST(){
   for(i=0;i<24;i++){
      led32.ledx32 = (int32)0x00000010<<i | (int32)tt;
      led32_display();
      for(k=0;k<speed;k++)kt_nutnhan();
   }
}

void SangDan_ChopTat(){
   led32.ledx16[1] = 0;
   for(i=0;i<=12;i++){
      led32.ledx16[0] = (~(0xfff0<<i)) & 0xfff0 | (int16)tt;
      led32.ledx16[1] = (~led32.ledx16[1]) & 0x0fff;
      led32_display();
      for(k=0;k<speed;k++)kt_nutnhan();
   }
}


void SangDon_TSP(){
   for(i=0;i<=24;i++){
      for(j=0;j<24-i;j++){
         led32.ledx32 = ((~(0x0fffffff>>i))|((int32)0x00000010<<j)) & 0x0ffffff0 | (int32)tt;
         led32_display();
         for(k=0;k<speed;k++)kt_nutnhan();
      }
   }
}

void SangDon_PST(){
   for(i=0;i<=24;i++){
      for(j=0;j<24-i;j++){
         led32.ledx32 = ((~(0xfffffff0<<i))|(0x08000000>>j)) & 0x0ffffff0 | (int32)tt;
         led32_display();
         for(k=0;k<speed;k++)kt_nutnhan();
      }
   }
}

void ChopTatXemKe_5lan(){
   led32.ledx32 = 0x55555555;
   for(i=0;i<10;i++){
      led32.ledx32 = (~led32.ledx32) & 0x0ffffff0 | (int32)tt;
      led32_display();
      for(k=0;k<speed;k++)kt_nutnhan();
   }
}

void SangDanTrongRaNgoai(){
   for(i=0;i<=12;i++){
      led32.ledx16[0] = (~(0xffff>>i))&0xfff0 | (int16)tt;
      led32.ledx16[1] = (~(0xffff<<i))&0x0fff;
      led32_display();
      for(k=0;k<speed;k++)kt_nutnhan();
   }
}

void main()
{
      system_init();
      while(true)
      {     
         if(che_do == 1)       SangDan_TSP();
         else if(che_do == 2)  SangDan_PST();
         else if(che_do == 3)  ChopTat_5lan();
         else if(che_do == 4)  SangDich_TSP();
         else if(che_do == 5)  SangDich_PST();
         else if(che_do == 6)  SangDan_ChopTat();
         else if(che_do == 7)  SangDon_TSP();
         else if(che_do == 8)  SangDon_PST();
         else if(che_do == 9)  ChopTatXemKe_5lan();
         else if(che_do == 10) SangDanTrongRaNgoai();
      }
}