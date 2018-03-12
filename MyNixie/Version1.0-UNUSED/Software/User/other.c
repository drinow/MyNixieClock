#include "other.h"

void Nixie_Test(void)
{
//  static u8 cnt=0,line=0;
//  u8 i=0;
//  
//  memset(TM1812_RGB,0,sizeof(TM1812_RGB));
//  *(*TM1812_RGB+cnt)=255;
//  if(cnt>0)*(*TM1812_RGB+cnt-1)=0;
//  else TM1812_RGB[3][2]=0;
//  cnt++;
//  if(cnt==12)cnt=0;
//  
//  TM1812_Send_Px();
//  

//  for(i=0;i<12;i++)
//    printf("%d ",*(*TM1812_RGB+i));
//  printf("\r\n");
  memset(TM1812_RGB,0,sizeof(TM1812_RGB));
  TM1812_RGB[0][0]=0xff;TM1812_RGB[0][1]=0;TM1812_RGB[0][2]=0xff;
  TM1812_RGB[1][0]=0;TM1812_RGB[1][1]=0xff;TM1812_RGB[1][2]=0;
  TM1812_RGB[2][0]=0xff;TM1812_RGB[2][1]=0;TM1812_RGB[2][2]=0xff;
  TM1812_RGB[3][0]=0;TM1812_RGB[3][1]=0xff;TM1812_RGB[3][2]=0;
  TM1812_Send_Px();
}
