
#include<tv_boards.c> 
#include<tv_glcd.c> 

unsigned int8 dem=0;

void main()
{
   system_init();

   // C?u h?nh GLCD � Thi?u h�m n�y GLCD kh�ng ch?y
   glcd_setup();

   // 1. V? logo STKT(64x64)t?i t?a �? X  = 0
   glcd_spkt_logo_raw(0);

   // 1. C?p nh?t logo SPKT ra m�n h?nh
   glcd_update();

   // 2. V? h?nh tr?n c� t�m t?i (70,7) , b�n k�nh 6, t� k�n, m�u tr?ng
   glcd_circle(70,7,6,1,1);

   // 2. C?p nh?t h?nh tr?n ra m�n h?nh
   glcd_update();

   // 3. V? h?nh ch? nh?t t?i(81,1),(97,13),t� k�n,m�u tr?ng
   glcd_rect(85,1,97,13,1,1);

   // 3. C?p nh?t h?nh ch? nh?t ra m�n h?nh
   glcd_update();

   // 4. V? h?nh tam gi�c t� k�n,m�u tr?ng
   glcd_triangle(103,13,110,1,117,13,1,1);

   // 4. C?p nh?t h?nh tam gi�c ra m�n h?nh
   glcd_update();

   // 5. V? �o?n th?ng
   glcd_line(64,15,118,15,1);

   // 5.C?p nh?t �o?n th?ng ra m�n h?nh
   glcd_update();

   // 6. V? thanh c� �? d�y l� 3
   glcd_bar(64,53,118,53,3,1);

   // 6. C?p nh?t thanh ra m�n h?nh
   glcd_update();

   // 7. C?u h?nh chu?i t?i(80,57),font1(5x7),m�u tr?ng,kh�ng ghi ��
   glcd_text_setup(80,56,1,1,0);

   // 7. Hi?n th? chu?i SPKT
   glcd_text("SPKT");

   // 7. C?p nh?t chu?i SPKT ra m�n h?nh
   glcd_update();

   while(true)
   {
      // 8. Chu?i t?i(70,20),font 4x(5x7) = 20x28,m�u tr?ng,c� ghi ��
      glcd_text_setup(70,20,4,1,1);

      // 8. Hi?n th? gi� tr? c?a bi?n
      printf(glcd_text,"%02d",dem);
      glcd_update();
      dem++; dem %= 100;
      delay_ms(200);
   }
}

