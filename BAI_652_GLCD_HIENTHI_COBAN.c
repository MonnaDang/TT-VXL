
#include<tv_boards.c> 
#include<tv_glcd.c> 

unsigned int8 dem=0;

void main()
{
   system_init();

   // C?u h?nh GLCD – Thi?u hàm này GLCD không ch?y
   glcd_setup();

   // 1. V? logo STKT(64x64)t?i t?a ð? X  = 0
   glcd_spkt_logo_raw(0);

   // 1. C?p nh?t logo SPKT ra màn h?nh
   glcd_update();

   // 2. V? h?nh tr?n có tâm t?i (70,7) , bán kính 6, tô kín, màu tr?ng
   glcd_circle(70,7,6,1,1);

   // 2. C?p nh?t h?nh tr?n ra màn h?nh
   glcd_update();

   // 3. V? h?nh ch? nh?t t?i(81,1),(97,13),tô kín,màu tr?ng
   glcd_rect(85,1,97,13,1,1);

   // 3. C?p nh?t h?nh ch? nh?t ra màn h?nh
   glcd_update();

   // 4. V? h?nh tam giác tô kín,màu tr?ng
   glcd_triangle(103,13,110,1,117,13,1,1);

   // 4. C?p nh?t h?nh tam giác ra màn h?nh
   glcd_update();

   // 5. V? ðo?n th?ng
   glcd_line(64,15,118,15,1);

   // 5.C?p nh?t ðo?n th?ng ra màn h?nh
   glcd_update();

   // 6. V? thanh có ð? dày là 3
   glcd_bar(64,53,118,53,3,1);

   // 6. C?p nh?t thanh ra màn h?nh
   glcd_update();

   // 7. C?u h?nh chu?i t?i(80,57),font1(5x7),màu tr?ng,không ghi ðè
   glcd_text_setup(80,56,1,1,0);

   // 7. Hi?n th? chu?i SPKT
   glcd_text("SPKT");

   // 7. C?p nh?t chu?i SPKT ra màn h?nh
   glcd_update();

   while(true)
   {
      // 8. Chu?i t?i(70,20),font 4x(5x7) = 20x28,màu tr?ng,có ghi ðè
      glcd_text_setup(70,20,4,1,1);

      // 8. Hi?n th? giá tr? c?a bi?n
      printf(glcd_text,"%02d",dem);
      glcd_update();
      dem++; dem %= 100;
      delay_ms(200);
   }
}

