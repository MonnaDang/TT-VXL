
#include<tv_boards.c> 
#include<tv_glcd.c> 
unsigned int8 mode=2,bdn=0,giay=0,sp;
void ve_giaodien()
{
   // Xoa man hinh
   glcd_clear(0);
   // Ve thanh chon lua
   // mode 0,1,2 3 hinh chu nhat cung toa do x, khac toa do y
   glcd_rect(0,mode * 20,50,mode * 20 + 20,1,1);
   // mode != 0 kiem tra neu mode = 0, thi bit color = 0, hien thi mau trang
   glcd_text_setup(5,7,1,mode != 0,0);
   glcd_text("COUNTER");
   glcd_text_setup(5,27,1,mode != 1,0);
   glcd_text("TIMER");
   glcd_text_setup(5,47,1,mode != 2,0);
   glcd_text("LOGO");
   // mode = 2 ht logo
   if(mode == 2)glcd_spkt_logo_raw(64);
   // ht hình tròn
   else
   {
      glcd_circle(95,31,20,1,1);
      glcd_circle(95,31,17,1,0);
   }
   glcd_update();
}
void main()
{
   system_init();
   glcd_setup();
   ve_giaodien();
   setup_timer_0(T0_EXT_H_TO_L|T0_DIV_1);
   set_timer0(0);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(int_TIMER1);
   enable_interrupts(GLOBAL);
   while(true)
   {
      // Chú ý m?i l?n nh?n nút m?i v? l?i giao di?n 1 l?n
      // d? tránh trì hoãn các tác v? khác
      if((inputcd(UP) == 0)&&(mode < 2)){mode++; ve_giaodien(); }
      if((inputcd(DW) == 0)&&(mode > 0)){mode--; ve_giaodien(); }
      sp = get_timer0();
      if(sp > 24)set_timer0(1);
      if(bdn >= 10)
      {
         bdn = bdn - 10; giay++;
         giay %= 60;
      }
      glcd_text_setup(85,24,2,1,1);
      if(mode == 0)printf(glcd_text,"%02u",sp);
      else if(mode == 1)printf(glcd_text,"%02u",giay);
      glcd_update();
   }
}
#int_TIMER1
void ngatT1()
{
   set_timer1(3036);
   bdn++;
}
