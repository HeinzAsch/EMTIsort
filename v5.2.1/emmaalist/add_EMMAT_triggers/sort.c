#include "sort.h"


/*================================================================*/
int main(int argc, char *argv[])
{
  FILE *etinp, *eainp;
  size_t eason,etson;
  eanode eand;
  etnode etnd;
  int glow,ghigh,d;
  unsigned long long pos;
  int found;
  
  eason=sizeof(eanode);
  etson=sizeof(etnode);
  
  if(argc!=5)
    {
      printf("emmaalist_add_EMMAT_triggers emmaA_list_name emmaT_list_name gate_low_ns gate_high_ns \n");
      exit(-1);
    }
  
 
  printf("Program adds triggers from processed list of EMMAT fragments to the EMMAA list.\n");
  

  if((eainp=fopen(argv[1],"r+"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  
  if((etinp=fopen(argv[2],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[2]);
      exit(-2);
    }
  
   glow=atoi(argv[3]);
   ghigh=atoi(argv[4]);

   while(1)//get to the start
     {
       if(fread(&eand,eason,1,eainp)==1)
	 break;
     }
   
    while(1)
     {
      
       while(1)//gate into the range
	 {	   
	   if(fread(&etnd,etson,1,etinp)!=1)//stop on a incorrect reading
	     break;
	   
	   if((etnd.tsns+GATE)>=eand.tsns)
	     break;
	 }
       
       pos=ftell(etinp);//save current position in the EMMAT list

       found=0;
  
       d=(int)(etnd.tsns-eand.tsns);
       if(d>glow)
	 if(d<ghigh)
	   {
	   
	     eand.trig_tsns=etnd.trig_tsns;
	     eand.trig=etnd.trig;
	     eand.trignum=etnd.trignum;
	     fseek(eainp,-eason,SEEK_CUR);
	     fwrite(&eand,eason,1,eainp);
	     found=1;
	     pos=ftell(etinp);
	   }
	 

       if(found==0)
	 while(1)//check within the range
	   {	   
	     if(fread(&etnd,etson,1,etinp)!=1)//stop on the incorrect reading
	       break;
	     d=(int)(etnd.tsns-eand.tsns);
	     if(-d>GATE)
	       break;
	
	     if(d>glow)
	       if(d<ghigh)
		 {
		   eand.trig_tsns=etnd.trig_tsns;
		   eand.trig=etnd.trig;
		   eand.trignum=etnd.trignum;
		   fseek(eainp,-eason,SEEK_CUR);
		   fwrite(&eand,eason,1,eainp);
		   pos=ftell(etinp);
		   break;
		 }	   
	   
	   }
       
 
       if(fread(&eand,eason,1,eainp)!=1)
	 break;

	fseek(etinp,pos,SEEK_SET);//back to the reference position for the next event

     }
   
  fclose(eainp);
  fclose(etinp);
}
