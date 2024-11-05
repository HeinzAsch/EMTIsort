#include "sort.h"
#define MAXWIN 10000
#define GATE   2500

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,ref;
  unsigned long long pos;
  unsigned long long dt;
  int dtt;
  int trig;
  static gmap map;
  int ac;
  char* av[1];
  int found=0;
  
  ac=0;
  av[0]=0;
  son=sizeof(node);
  memset(&ref,0,son);
  
  if(argc!=3)
    {
      printf("griflist_check_HPGe_CC_Seg_gate fragment_list map\n");
      exit(-1);
    }
   printf("Program sort HPGe CC Seg gate for a list with identified triggers\n");

    
    if((fl=fopen(argv[1],"r"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }

    read_map(argv[2],&map);
    
    theApp=new TApplication("App", &ac, av);
    if(h!=NULL) delete h;
    h=new TH1D("TSdiff","TSdiff",2*GATE+1,-GATE,GATE);
    if(c!=NULL) delete c;
    c = new TCanvas("TS", "TS",10,10, 700, 500);
    
    trig=1;
    while(1)
      {
	if(fread(&ref,son,1,fl)!=1) break; //stop on incorrect reading
	if(ref.trig==trig) break;	
      }
    
    
    while(1)
      {
	if(feof(fl)!=0) break;
	pos=ftell(fl);//save current position
	printf("Sorting trigger %8d time stamp %12lld\r",ref.trig,ref.trig_tsns);
	
	
	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	    
	    if(curr.trig==ref.trig)
	      {
		if(CC_channel(&curr,&map)==1)
		  if(Seg_channel(&ref,&map)==1)
		    if(same_HPGe(&curr,&ref,&map)==1)
		      {
			dtt=(int)(ref.tsns-curr.tsns);
			h->Fill(dtt);
		      }
		
		if(Seg_channel(&curr,&map)==1)
		  if(CC_channel(&ref,&map)==1)
		    if(same_HPGe(&ref,&curr,&map)==1)
		      {
			dtt=(int)(curr.tsns-ref.tsns);
			h->Fill(dtt);		      
		      }	
	      }
	  
	    dt=curr.tsns-ref.tsns;	    
	    if(dt>MAXWIN) break; //too late for coincidence
	}
      
      
      fseek(fl,pos,SEEK_SET);//back to the starting position
      
      trig++;
      found=0;
      
      while(1)
	{
	  if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	  if(feof(fl)) break;
	  if(curr.trig==trig)//new event
	    {
	      memcpy(&ref,&curr,son);
	      found=1;
	      break;
	    }
	}
      
      if(found==0)
	break;
    }
  
    fclose(fl);
    gPad->SetLogy();
    printf("DONE\n");
    h->Draw("HIST");
    theApp->Run(kTRUE);

    
}
  
