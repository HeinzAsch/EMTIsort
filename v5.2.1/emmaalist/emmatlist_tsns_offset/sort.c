#include "sort.h"


/*================================================================*/
int main(int argc, char *argv[])
{
  FILE *etinp,*eainp;
  size_t etson,eason;
  etnode etnd;
  eanode eand;
  int frag,d;
  int dmin,dmax;
 
  etson=sizeof(etnode);
  eason=sizeof(eanode);

  if(argc!=3)
    {
      printf("emmaalist_emmatlist_tsns_offset emmaA_list_name emmaT_list_name\n");
      exit(-1);
    }
  
 
  printf("Program finds time stamp offset between corresponding fragments in the emmaA and emmaT list.\n");
  
  if((etinp=fopen(argv[2],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[2]);
      exit(-2);
    }
  
   if((eainp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

   frag=0;
   dmax=0;
   dmin=0x0fffffff;
   while(1)
     {
       if(fread(&etnd,etson,1,etinp)!=1)
	 break;
       if(fread(&eand,eason,1,eainp)!=1)
	 break;
       frag++;
       d=etnd.tsns-eand.tsns;
       if(d<dmin)
	 dmin=d;
       if(d>dmax)
	 dmax=d;
     }
   fclose(eainp);
   fclose(etinp);
   printf("Time stamp offset [ns] MIN:%8d MAX:%8d\n",dmin,dmax);
     
 
}
