#define BOARD D501
#include<tv_boards.c>
unsigned int8 mssv[8] = {2,0,1,4,2,4,7,3};
unsigned int8 i,sodich=0,k;
int1 tt=0;

void Check_ON(){
   if(!inputcd(ON)){
      tt = 0;
      sodich = 0;                // xoa trang thai sodich
      for(i=0;i<8;i++)           // tat het cac led
         s7seg.led[i] = 0xff;
   }
}

void Check_OFF(){
   if(!inputcd(OFF)){
      tt = 1;
//!      sodich = 0;
//!      for(i=0;i<8;i++)
//!         s7seg.led[i] = 0xff;
   }
}

void kt_nutnhan(){
   Check_ON();
   Check_OFF();
   if(!tt) s7seg_display();
   else delay_ms(10); // trong ham s7seg_display() co delay nen khi bo ham thi them delay
}

void main()
{
   system_init();
//!   d7seg.led[0] = m7d[tt];
//!   d7seg_display();

   while(true)
   {   
      if(sodich<8){
         for(i=8;i>=1;i--)
            s7seg.led[i] = s7seg.led[i-1]; // day cac so len
         s7seg.led[0] = m7d[mssv[sodich]]; // cho led 0 = mssv o vi tri cua sodich
         sodich++;
      }else{
         tt = !tt;
//!         d7seg.led[0] = m7d[tt];
//!         d7seg_display();s
      }
      for(k=0;k<100;k++){
         kt_nutnhan();
      }
   }
}
