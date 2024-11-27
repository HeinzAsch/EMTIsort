#include "sort.h"


/*================================================================*/
int main(int argc, char *argv[])
{
  FILE *etinp,*inp;
  size_t etson,son;
  etnode etnd;
  node nd;
  int d;
  static gmap map;
  int ac;
  char* av[1];
  unsigned long long pos;
  
  ac=0;
  av[0]=0;
  
  etson=sizeof(etnode);
  son=sizeof(nd);

  if(argc!=4)
    {
      printf("emmatlist_project_PGAC emmaT_list_name\n");
      exit(-1);
    }
  
 
  printf("Program attempts to project the positional information from the PGAC using TDC delays.\n");
  
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

   theApp=new TApplication("App", &ac, av);
   if(h!=NULL) delete h;   
    h=new TH1D("TSDIFF","TSDIFF",2*GATE+1,-GATE,GATE);
    if(c!=NULL) delete c;
    c = new TCanvas("TSDIF", "TSDIF",10,10, 700, 500);
  
  
   while(1)
     {
       if(fread(&etnd,etson,1,etinp)!=1)
	 break;
 
  
       while(1)//gate into the range
	 {	   
	   if(fread(&nd,son,1,inp)!=1)//stop on the incorrect reading
	     break;
	   
	   if((nd.tsns+GATE)>=etnd.tsns)
	     break;
	 }
  
       pos=ftell(inp);//save current position in the GRIF list
       
       if(EMMA_channel(&nd,&map)==1)//in case this one is emmat
	 {
	   d=etnd.tsns-nd.tsns;
	   h->Fill(d);
	 }
       
       while(1)//check within the range
	 {	   
	   if(fread(&nd,son,1,inp)!=1)//stop on the incorrect reading
	     break;

	   d=nd.tsns-etnd.tsns;
	   if(d>GATE)
	     break;

	   if(EMMA_channel(&nd,&map)==1)
	     {
	       d=etnd.tsns-nd.tsns;
	       h->Fill(d);
	     }
	 }

     
       	fseek(inp,pos,SEEK_SET);//back to the reference position for the next EMMAT event

     }
   
   fclose(etinp);
   fclose(inp);
      
   h->Draw("HIST");
   theApp->Run(kTRUE);
    
}
