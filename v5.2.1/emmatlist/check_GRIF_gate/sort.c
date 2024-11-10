#include "sort.h"


/*================================================================*/
int main(int argc, char *argv[])
{
  FILE *etinp, *inp;
  size_t son,etson;
  node nd;
  etnode etnd;
  static gmap map;
  int d;
  int ac;
  char* av[1];
  int i;
  
  ac=0;
  av[0]=0;
  
  
  son=sizeof(node);
  etson=sizeof(etnode);
  
  if(argc!=4)
    {
      printf("emmatlist_check_GRIF_gate EMMAT_list_name GRIF_list_name map\n");
      exit(-1);
    }
  
 
  printf("Program sorts a histogram of time difference between EMMAT and GRIF events corresponding to the same trigger.\n");

  theApp=new TApplication("App", &ac, av);
  if(h!=NULL) delete h;   
  h=new TH1D("TSDIFF","TSDIFF",2*GATE+1,-GATE,GATE);
  if(c!=NULL) delete c;
  c = new TCanvas("TSDIF", "TSDIF",10,10, 700, 500);
  
  

  if((etinp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  
  if((inp=fopen(argv[2],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[2]);
      exit(-2);
    }
  
  
   read_map(argv[3],&map);

   i=0;
   while(1)
     {
       if(fread(&etnd,etson,1,etinp)!=1)//stop on a incorrect reading 
	 break;

       if(etnd.trig>0)
	 while(1)
	   {
	     if(fread(&nd,son,1,inp)!=1)//stop on a incorrect reading 
	       break;
	     if(nd.trig==etnd.trig)
	       if(EMMA_channel(&nd,&map)==1)
		 {
		   d=(int)(etnd.tsns-nd.tsns);
		  h->Fill(d);
		  i++;
		  break;
		 }
	   }
     }
   
   fclose(inp);
   fclose(etinp);

   printf("analyzed %d triggers\n",i);
   h->Draw("HIST");
   theApp->Run(kTRUE);
    
}
