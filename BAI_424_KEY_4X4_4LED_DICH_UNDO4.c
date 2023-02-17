#define BOARD D501

#include <tv_boards.c>
#include <tv_key4x4.c>

unsigned int8 i=0,solan=0,temp[4];

void kt_mtphim(){
   if( key4x4_read() == OK){
      if(key4x4.key <= 9){
         for(i=3;i>=1;i--){
            temp[i] = temp[i-1]; // luu lai cac trang thai truoc 2->3, 1->2, 0->1
         }
         temp[0] = d7seg.led[3]; // luu lai trang thai tu led 3 vao temp 0
         for(i=3;i>=1;i--){
            d7seg.led[i] = d7seg.led[i-1];  
         }
         d7seg.led[0] = m7d[key4x4.key];   // day so tu matran phim vao led 0
         if(solan<4)solan++; // tang so lan len
         d7seg_display();
      }else if( (key4x4.key == 0x0b) && (solan != 0) ){
         for(i=0;i<3;i++){
            d7seg.led[i] = d7seg.led[i+1];  
         }
         d7seg.led[3] = temp[0];
         for(i=0;i<3;i++){
            temp[i] = temp[i+1]; 
         }
         temp[3] = 0xff-128;
         if(solan>0)solan--; // moi lan undo se giam solan 1 lan toi da 4 lan
         d7seg_display();
      }
      else if( key4x4.key == 0x0c ){
         for(i=0;i<4;i++){
            d7seg.led[i] = 0xff - 128;
         }
         solan = 0;
         d7seg_display();
      }
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
