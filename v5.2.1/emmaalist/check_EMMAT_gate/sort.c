#include "sort.h"


/*================================================================*/
int main(int argc, char *argv[])
{
  FILE *eainp, *etinp;
  size_t etson,eason;
  etnode etnd;
  eanode eand;
  int d;
  int ac;
  char* av[1];
  int i;
  
  ac=0;
  av[0]=0;
  
  
  etson=sizeof(etnode);
  eason=sizeof(eanode);
  
  if(argc!=3)
    {
      printf("emmaalist_check_EMMAT_gate EMMAA_list_name EMMAT_list_name\n");
      exit(-1);
    }
  
 
  printf("Program sorts a histogram of time difference between EMMAA and EMMAT events corresponding to the same trigger.\n");

  theApp=new TApplication("App", &ac, av);
  if(h!=NULL) delete h;   
  h=new TH1D("TSDIFF","TSDIFF",2*GATE+1,-GATE,GATE);
  if(c!=NULL) delete c;
  c = new TCanvas("TSDIF", "TSDIF",10,10, 700, 500);
  
  

  if((eainp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  
  if((etinp=fopen(argv[2],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[2]);
      exit(-2);
    }
 

   i=0;
   while(1)
     {
       if(fread(&eand,eason,1,eainp)!=1)//stop on a incorrect reading 
	 break;

       if(eand.trig>0)
	 while(1)
	   {
	     if(fread(&etnd,etson,1,etinp)!=1)//stop on a incorrect reading 
	       break;
	     if(etnd.trig==eand.trig)
		 {
		   d=(int)(etnd.tsns-eand.tsns);
		  h->Fill(d);
		  i++;
		  break;
		 }
	   }
     }
   
   fclose(etinp);
   fclose(eainp);

   printf("analyzed %d triggers\n",i);
   h->Draw("HIST");
   theApp->Run(kTRUE);
    
}
