#define   BOARD     D501
#include<tv_boards.c>  

unsigned int8 i,j,q;
unsigned int32 data_32;
unsigned int16 data_1,data_2;

void chop_tat5(){
        led32.ledx32 = ~0xffffffff;
     for(i=0;i<10;i++){
        led32.ledx32 = ~led32.ledx32;
        led32_display();
        delay_ms(200); 
     }
}

void main()
{
      system_init();
      while(true)
      {     
      
           chop_tat5();// 1
           for(j=0;j<2;j++){ //2
               data_32 = 0;
               for(i=0;i<64;i++){
                  if(i<32) data_32 = (data_32<<1)|1;
                  else data_32 = (data_32<<1);
                  led32.ledx32 = data_32;
                  led32_display();
                  delay_ms(50);
               }
           }
           chop_tat5();// 3
           for(j=0;j<2;j++){ //4
               data_32 = 0;
               for(i=0;i<64;i++){
                  if(i<32) data_32 = (data_32>>1)|0x80000000;
                  else data_32 = (data_32>>1);
                  led32.ledx32 = data_32;
                  led32_display();
                  delay_ms(50);
               }
           }
           chop_tat5(); // 5
           for(j=0;i<2;j++){ //6
               data_1=data_2=0;
               for(i=0;i<32;i++){
                  if(i<16){
                     data_1 = (data_1<<1)|1;
                     data_2 = (data_2>>1)|0x8000;
                  }else{
                     data_1 = (data_1<<1);
                     data_2 = (data_2>>1);
                  }
                  led32.ledx16[0]=data_1;
                  led32.ledx16[1]=data_2;
                  led32_display();
                  delay_ms(50);
               }
           }
           chop_tat5(); //7
           for(j=0;i<2;j++){ //8
               data_1=data_2=0;
               for(i=0;i<32;i++){
                  if(i<16){
                     data_1 = (data_1<<1)|1;
                     data_2 = (data_2>>1)|0x8000;
                  }else{
                     data_1 = (data_1<<1);
                     data_2 = (data_2>>1);
                  }
                  led32.ledx16[0]=data_2;
                  led32.ledx16[1]=data_1;
                  led32_display();
                  delay_ms(50);
               }
           }
      }
}
