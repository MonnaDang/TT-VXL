
#define   BOARD     D501
#include <tv_boards.c>
#include <tv_key4x4.c>

void KT_MTP(){
   if(key4x4_read() == OK){
      if(key4x4.key < 8){
         led32.ledx32 = (1<<key4x4.key)|led32.ledx32;
      }else{
         led32.ledx32 = (~(1<<(key4x4.key-8)))&led32.ledx32;
      }
      led32_display();
   }
}

void main(){
   system_init();
   
   while(true){
      KT_MTP();
   }
}
