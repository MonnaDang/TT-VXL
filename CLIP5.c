
#include <tv_boards.c>
#include <tv_key4x4.c>

unsigned int8 T0,gioihan;
signed int8 dem;

unsigned int8 bdn, giay,gio,phut,che_do,dem_nn;

int1 nn,demsp_dongho;

int1 chieu,sophim; // chieu = 0: dem len, = 1:dem xuong; sophim = 0 :nhan phim dau tien, = 1 :nhan phim thu 2

void kt_mtphim(){
   if(key4x4_read() == OK){
      if(key4x4.key <= 9){
         if(sophim == 0){
            if(demsp_dongho == 0){
               gioihan = key4x4.key*10;
               setup_timer_0(T0_OFF);
            }else{
               if(che_do == 6){
                  if(key4x4.key > 2) gio = 20;
                  else gio = key4x4.key*10;
               }else if(che_do == 4){
                  if(key4x4.key > 5) phut = 50;
                  else phut = key4x4.key*10;
               }else if(che_do == 2){
                  if(key4x4.key > 5) giay = 50;
                  else giay = key4x4.key*10;
               }
            }
            sophim = !sophim;
         }else{
            if(demsp_dongho == 0){
               gioihan += key4x4.key;
               
               if(chieu == 0)dem =0;
               else dem = gioihan;
               
               setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
               set_timer0(0);
            }else{
               if(che_do == 6){
                  if((gio == 20) && (key4x4.key > 3)) gio = 23;
                  else gio += key4x4.key;
               }else if(che_do == 4){
                  phut += key4x4.key;
               }else if(che_do == 2){
                  giay += key4x4.key;
               }
            }
            sophim = !sophim;
         }
      }else if((key4x4.key == 0x0D) && (demsp_dongho==0)) chieu = !chieu;
      else if(key4x4.key == 0x0C) demsp_dongho = !demsp_dongho;
      else if((key4x4.key == 0x0e) && (demsp_dongho==1)){
         if(che_do == 0)che_do=6;
         else che_do-=2;
         if(che_do > 0) disable_interrupts(INT_TIMER1);
         else enable_interrupts(INT_TIMER1);
      }
   }
}

void main(){
   system_init();
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);
   
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
      }
      if(bdn >=10){
         bdn = bdn - 10;
         if(giay == 59){
            giay = 0;
            if(phut == 59){
               phut = 0;
               if(gio == 23){
                  gio = 0;
               }gio++;
            }phut++;
         }giay++;
      }
      
      if(demsp_dongho == 0){
         s7seg.led[0] = 0xff;
         s7seg.led[1] = 0xff;
         s7seg.led[2] = m7d[dem%10];
         s7seg.led[3] = m7d[dem/10];
         s7seg.led[4] = m7d[gioihan%10]-128;
         s7seg.led[5] = m7d[gioihan/10];
         s7seg.led[6] = 0xff;
         s7seg.led[7] = 0xff;
      }else{
         s7seg.led[0] = 0xff;
         s7seg.led[1] = m7d[giay%10];
         s7seg.led[2] = m7d[giay/10];
         s7seg.led[3] = m7d[phut%10];
         s7seg.led[4] = m7d[phut/10];
         s7seg.led[5] = m7d[gio%10];
         s7seg.led[6] = m7d[gio/10];
         s7seg.led[7] = 0xff;
         
         if(nn){
            s7seg.led[che_do] = 0xff;
            s7seg.led[che_do - 1] = 0xff;
         }
         if(che_do > 0){
            if(dem_nn == 29){
               dem_nn = 0;
               nn = !nn;
            }else dem_nn++;
         }else nn = 0;
      }
      
      s7seg_display();
      kt_mtphim();
   }
}

#int_timer1
void timer1_ngat(){
   set_timer1(3036);
   bdn++;
}
