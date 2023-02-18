//!#define BOARD D501

#include <tv_boards.c>
#include <tv_key4x4.c>

unsigned int8 i,j,mode=1,k,T0,preT0;  

unsigned int8 phut=0,giay=0,gio=0;
unsigned int8 che_do=0,dem = 0;
int1 nn=0;

unsigned int8 bdn;

void d7seg_xoa0VN(unsigned int16 d)
{
   unsigned int8 n = 0;

   do
   {
      d7seg.led[n] = m7d[d % 10];
      d /= 10; n++;
   }while(d != 0);

   for(; n < 4; n++)d7seg.led[n] = 0xff;
   d7seg_display();
}

void check_UP(){
    if(key4x4_read() == OK){
      if(key4x4.key == 0){
         j=0; i=0;
         led32.ledx32 = 0;
         if(mode == 7) mode = 7;
         else mode ++;
      }

      if(key4x4.key == 1){
         j=0; i =0;
         led32.ledx32 = 0;
         if(mode == 1) mode = 1;
         else mode --;
      }

      if(key4x4.key == 2){
         j=0; i=0;
         led32.ledx32 = 0;
         mode = 1;
      }
      if(key4x4.key == 4){
         if(che_do == 0){
            if(giay == 59) giay = 0;
            else giay++;
            s7seg.led[0] = m7d[giay%10];
            s7seg.led[1] = m7d[giay/10];
         }else if(che_do == 2){
            if(phut == 59) phut = 0;
            else phut++;
            s7seg.led[2] = m7d[phut%10];
            s7seg.led[3] = m7d[phut/10];
         }else if(che_do == 4){
            if(gio == 23) gio = 0;
            else gio++;
            s7seg.led[4] = m7d[gio%10];
            s7seg.led[5] = m7d[gio/10];
         }
      }
      if(key4x4.key == 5){
         if(che_do == 0){
            if(giay == 0) giay = 59;
            else giay--;
            s7seg.led[0] = m7d[giay%10];
            s7seg.led[1] = m7d[giay/10];
         }else if(che_do == 2){
            if(phut == 0) phut = 59;
            else phut--;
            s7seg.led[2] = m7d[phut%10];
            s7seg.led[3] = m7d[phut/10];
         }else if(che_do == 4){
            if(gio == 0) gio = 23;
            else gio--;
            s7seg.led[4] = m7d[gio%10];
            s7seg.led[5] = m7d[gio/10];
         }
      }
      if(key4x4.key == 6){
         if(che_do == 6) che_do = 0;
         else che_do += 2;
         nn = 0;
      } 
   }
}



void my_delay(){
   led32_display();
   for(k=0;k<10;k++){
      check_UP();
      
      // timer 0
      T0 = get_timer0();
      if(T0>100){
         T0 = T0 - 100;
         set_timer0(T0);
      }
      if(T0 != preT0){
         preT0 = T0;
         d7seg_xoa0VN(T0);
      }
      
      // timer 1
      if(bdn>=10){
         bdn = bdn - 10;
         if(giay == 59){
            giay = 0;
            if(phut == 59){
               phut = 0;
               if(gio == 23) gio = 0;
               else gio++;
            }
            else phut++;
         }else giay++;
      }
      
      s7seg.led[0] = m7d[giay%10];
      s7seg.led[1] = m7d[giay/10];
      s7seg.led[2] = m7d[phut%10];
      s7seg.led[3] = m7d[phut/10];
      s7seg.led[4] = m7d[gio%10];
      s7seg.led[5] = m7d[gio/10];
      if(nn){
         s7seg.led[che_do]   = 0xff;
         s7seg.led[che_do+1] = 0xff;
      }
      if(che_do < 6)
         if(dem==19){
            dem=0;
            nn = !nn;  
         }
         else dem++;
      s7seg_display();
      
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
   
   setup_timer_0(t0_ext_h_to_l|t0_div_1);
   set_timer0(0);
   
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);
   
   led32.ledx32 = 0;
   led32_display();
   
   d7seg_xoa0VN(T0);
   
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

#INT_TIMER1
void ngat_timer1(){
   set_timer1(3036);
   bdn++;
}
