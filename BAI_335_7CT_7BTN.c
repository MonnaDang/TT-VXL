
//!#define BOARD D501

#include <tv_boards.c>
#include <tv_key4x4.c>

unsigned int8 i,j,mode=1,k;   

void KT_MTP(){
   if(key4x4_read() == OK){
      if( key4x4.key > 0 && key4x4.key < 8){  
         mode = key4x4.key;
         i=j=0;
         led32.ledx32 = 0;
      }
   }
}

void my_delay(){
   led32_display();
   for(k=0;k<100;k++){
      KT_MTP();
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
