
#include <tv_boards.c>
#include <tv_key4x4.c>

unsigned int8 T0,gioihan;
signed int8 dem;

int1 chieu,sophim; // chieu = 0: dem len, = 1:dem xuong; sophim = 0 :nhan phim dau tien, = 1 :nhan phim thu 2

void kt_mtphim(){
   if(key4x4_read() == OK){
      if(key4x4.key <= 9){
         if(sophim == 0){
            gioihan = key4x4.key*10;
            
            d7seg.led[3] = m7d[gioihan/10];
            d7seg.led[2] = 0xff - 64 - 128;
            d7seg.led[1] = 0xff - 64;
            d7seg.led[0] = 0xff - 64;
            d7seg_display();
            
            setup_timer_0(T0_OFF);
            
            sophim = !sophim;
         }else{
            gioihan += key4x4.key;
            
            if(chieu == 0)dem =0;
            else dem = gioihan;
            
            d7seg.led[3] = m7d[gioihan/10];
            d7seg.led[2] = m7d[gioihan%10] - 128;
            d7seg.led[1] = m7d[dem/10];
            d7seg.led[0] = m7d[dem%10];
            d7seg_display();
            
            setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
            set_timer0(0);
            
            sophim = !sophim;
         }
      }else if(key4x4.key == 0x0D) chieu = !chieu;
   }
}

void main(){
   system_init();
   for(int i=0;i<4;i++)d7seg.led[i] = 0xff-64;
   d7seg.led[2] = 0xff-64-128;
   d7seg_display();
   while(true){
      T0 = get_timer0();
      
      if(T0 >= 1){
         set_timer0(0);
         if(chieu == 0){
            dem++;
            if(dem > gioihan) dem = 1;
         }
         else{
            dem--;
            if(dem < 0) dem = gioihan-1;
         }
         d7seg.led[1] = m7d[dem/10];
         d7seg.led[0] = m7d[dem%10];
         d7seg_display();
      }
      kt_mtphim();
   }
}
