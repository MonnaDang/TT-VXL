//!#define   BOARD     D501
#include<tv_boards.c>  

unsigned int8 mode,i,j;
unsigned int16 data_1,data_2;
unsigned int32 data_32;

void chop_tat5(){
      if(i<10){
          led32.ledx32 = ~led32.ledx32;
          led32_display();
          delay_ms(500);
          i++;
      }else{
         i=0;
         led32.ledx32 = 0;
         mode++;
      }
}
void sang_tat_dan_PST(){
      if(i<32)led32.ledx32 = (led32.ledx32<<1)|1;
      else led32.ledx32 = led32.ledx32<<1;
      led32_display();  
      delay_ms(100);
      if(i==63) {
         i = 0;
         mode++;
      }else i++;
}

void sang_tat_dan_TSP(){
      if(i<32)led32.ledx32 = (led32.ledx32>>1)|0x80000000;
      else led32.ledx32 = led32.ledx32>>1;
      led32_display();  
      delay_ms(100);
      if(i==63) {
         i = 0;
         mode++;
      }else i++;
}

void sang_tat_dan_tu_ngoai_vao(){
      if(i<16){
         led32.ledx16[0] = (led32.ledx16[0]<<1)|1;
         led32.ledx16[1] = (led32.ledx16[1]>>1)|0x8000;
      }else{
         led32.ledx16[0] = (led32.ledx16[0]<<1);
         led32.ledx16[1] = (led32.ledx16[1]>>1);
      }
      led32_display();  
      delay_ms(100);
      if(i==31) {
         i = 0;
         mode++;
      }else i++;
      
}  

void sang_tat_dan_tu_trong_ra(){
      if(i<16){
         led32.ledx16[1] = (led32.ledx16[1]<<1)|1;
         led32.ledx16[0] = (led32.ledx16[0]>>1)|0x8000;
      }else{
         led32.ledx16[1] = (led32.ledx16[1]<<1);
         led32.ledx16[0] = (led32.ledx16[0]>>1);
      }
      led32_display();  
      delay_ms(100);
      if(i==31) {
         i = 0;
         mode++;
      }else i++;
      
}  

void main()
{
      system_init();
      delay_ms(1000);
      while(true)
      {        
            if(mode == 0) chop_tat5();
            else if(mode <= 2) sang_tat_dan_PST();
            else if(mode == 3) chop_tat5();
            else if(mode <= 5) sang_tat_dan_TSP();
            else if(mode == 6) chop_tat5();
            else if(mode <= 8) sang_tat_dan_tu_ngoai_vao();
            else if(mode == 9) chop_tat5();
            else if(mode <= 11) sang_tat_dan_tu_trong_ra();
            else mode = 0;
      }
}
