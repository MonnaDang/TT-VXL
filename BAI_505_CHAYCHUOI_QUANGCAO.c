#define BOARD D501
#include<tv_boards.c> 

#define H 137
#define E 134
#define L 199
#define Y 153
#define F 142
#define A m7d[0x0a]
#define O m7d[0]
#define C m7d[0x0c]


unsigned int8 dlht[19] = {H,E,L,L,O-128,0xff,C,H,O,0xff,m7d[1],0xff,L,Y,0xff,C,A,F,E};
unsigned int8 i,sodich,k;

void main()
{
   system_init();
   

   while(true)
   {   
      for(i=8;i>=1;i--)
         s7seg.led[i] = s7seg.led[i-1];
      if(sodich<19)s7seg.led[0] = dlht[sodich]; // mang tu 0-18
      else s7seg.led[0] = 0xff;
      
      if(sodich==22)sodich = 0; // toi 18 la het, cach 4 chu roi lap lai ct
      else sodich++;
      
      for(k=0;k<100;k++){
         s7seg_display();
      }
   }
}
