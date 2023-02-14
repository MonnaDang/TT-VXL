#define BOARD D501
#include <tv_boards.c>
#include <tv_key4x4.c>

unsigned int8 i;

void kt_mtphim(){
   if( key4x4_read() == OK){
      for(i=3;i>=1;i--){
         d7seg.led[i] = d7seg.led[i-1]; // gan lai cac so ben phai cho ben trai 2->3, 1->2,0->1
      }
      d7seg.led[0] = m7d[key4x4.key];   // day so tu matran phim vao led 0
      d7seg_display();
   }
}

void main(){
   system_init();
   for(i=0;i<4;i++){
      d7seg.led[i] = 0xff - 128;
   }
   d7seg_display();
   while(true){
      kt_mtphim();
   }  
}
