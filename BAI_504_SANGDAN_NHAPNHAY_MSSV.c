#define BOARD D501
#include<tv_boards.c>
unsigned int8 mssv[8] = {2,0,1,4,2,4,7,3};
unsigned int8 i,k;
signed int8 sodich = 7;
int1 tt=0,nn=0;

void Check_ON(){
   if(!inputcd(ON)){
      tt = 0;
      nn = 0;
      sodich = 7;                // xoa trang thai sodich
      for(i=0;i<8;i++)           // tat het cac led
         s7seg.led[i] = 0xff;
   }
}

void Check_OFF(){
   if(!inputcd(OFF)){
      tt = 1;
   }
}

void kt_nutnhan(){
   Check_ON();
   Check_OFF();
}

void main()
{
   system_init();
   while(true)
   {   
         if(!tt){
            if(sodich>=0){
               for(i=0;i<7;i++)
               s7seg.led[i] = s7seg.led[i+1]; 
               s7seg.led[7] = m7d[mssv[sodich]]; // cho led 0 = mssv o vi tri cua sodich
               sodich--;
            }else nn = !nn; 
         }
         for(k=0;k<100;k++){
            if(!tt) {
               if(!nn)s7seg_display();
               else delay_ms(10);
            }
            kt_nutnhan();
         }
   }
}
