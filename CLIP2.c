
#include<tv_boards.c>  
unsigned int8 i,j,mode=1,toc_do=1;
unsigned int16 k,speed=50;
int1 doi_mode;
/*
   doi_mode = 0 => doi hieu ung led
   doi_mode = 1 => doi thoi gian delay
   10 cap: 50 -> 500 ms
*/

void my_delay(){
   delay_ms(1);
   if(!inputcd(UP)){
      if(!doi_mode)
         if(mode == 10) mode=10;
         else mode++;
      else 
         if(toc_do == 10) toc_do = 10 ;
         else {
            toc_do++;
            speed = (int16)toc_do*50;
         }
   }
   if(!inputcd(DW)){
      if(!doi_mode)
         if(mode == 1) mode=1;
         else mode--;
      else 
         if(toc_do == 1) toc_do = 1 ;
         else toc_do--;
         speed = (int16)toc_do*50;
   }
   if(!inputcd(MOD)){
      doi_mode = !doi_mode;
   }
   
}


void SangDan_TSP(){
   for(i=0;i<=24;i++){
      for(k=0;k<speed;k++) my_delay();
      led32.ledx32 = (~(0x0fffffff>>i)) & 0x0ffffff0 | (int32)doi_mode;
      led32_display();
   }
}

void SangDan_PST(){
   for(i=0;i<=24;i++){
      for(k=0;k<speed;k++) my_delay();
      led32.ledx32 = (~(0xfffffff0<<i)) & 0x0ffffff0 | (int32)doi_mode;
      led32_display();
   }
}

void ChopTat_5lan(){
   for(i=0;i<10;i++){
      for(k=0;k<speed;k++) my_delay();
      led32.ledx32 = (~led32.ledx32) & 0x0ffffff0 | (int32)doi_mode;
      led32_display();
   }
}

void SangDich_TSP(){
   for(i=0;i<24;i++){
      for(k=0;k<speed;k++) my_delay();
      led32.ledx32 = (0x08000000>>i) | (int32)doi_mode;
      led32_display();
   }
}

void SangDich_PST(){
   for(i=0;i<24;i++){
      for(k=0;k<speed;k++) my_delay();
      led32.ledx32 = ((int32)0x00000010<<i) | (int32)doi_mode;
      led32_display();
   }
}

void SangDan_ChopTat(){
   led32.ledx16[1] = 0;
   for(i=0;i<=12;i++){
      for(k=0;k<speed;k++) my_delay();
      led32.ledx16[0] = (~(0xfff0<<i)) & 0xfff0 | (int16)doi_mode;
      led32.ledx16[1] = (~led32.ledx16[1]) & 0x0fff;
      led32_display();
   }
}


void SangDon_TSP(){
   for(i=0;i<=24;i++){
      for(j=0;j<24-i;j++){
         for(k=0;k<speed;k++) my_delay();
         led32.ledx32 = ((~(0x0fffffff>>i))|((int32)0x00000010<<j)) & 0x0ffffff0 | (int32)doi_mode;
         led32_display();
 
      }
   }
}

void SangDon_PST(){
   for(i=0;i<=24;i++){
      for(j=0;j<24-i;j++){
         for(k=0;k<speed;k++) my_delay();
         led32.ledx32 = ((~(0xfffffff0<<i))|((int32)0x08000000>>j)) & 0x0ffffff0 | (int32)doi_mode;
         led32_display();
      }
   }
}

void ChopTatXemKe_5lan(){
   led32.ledx32 = 0x55555555;
   for(i=0;i<10;i++){
      for(k=0;k<speed;k++) my_delay();
      led32.ledx32 = (~led32.ledx32) & 0x0ffffff0 | (int32)doi_mode;
      led32_display();
   }
}

void SangDanTrongRaNgoai(){
   for(i=0;i<=12;i++){
      for(k=0;k<speed;k++) my_delay();
      led32.ledx16[0] = (~(0xffff>>i)) & 0xfff0 | (int16)doi_mode;
      led32.ledx16[1] = (~(0xffff<<i)) & 0x0fff;
      led32_display();
   }
}

void main()
{
      system_init();
      while(true)
      {     
         if(mode == 1)      SangDan_TSP();
         else if(mode == 2) SangDan_PST();
         else if(mode == 3) ChopTat_5lan();
         else if(mode == 4) SangDich_TSP();
         else if(mode == 5) SangDich_PST();
         else if(mode == 6) SangDan_ChopTat();
         else if(mode == 7) SangDon_TSP();
         else if(mode == 8) SangDon_PST();
         else if(mode == 9) ChopTatXemKe_5lan();
         else if(mode == 10) SangDanTrongRaNgoai();

      }
}