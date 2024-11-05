#include "sort.h"
#define MAXWIN 1000
#define NPOS   128
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,ref;
  unsigned long long pos;
  unsigned long long dt;
  int trig;
  int nt;
  unsigned long long time[NPOS];
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
      printf("griflist_check_TIP_gate fragment_list map\n");
      exit(-1);
    }
   printf("Program sort TIP gate for a list with identified triggers\n");

    
    if((fl=fopen(argv[1],"r"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
    read_map(argv[2],&map);

  theApp=new TApplication("App", &ac, av);
  if(h!=NULL) delete h;
  h=new TH1D("TSdiff","TSdiff",MAXWIN,0,MAXWIN);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);
    
  trig=1;
  while(1)
    {
      if(fread(&ref,son,1,fl)!=1) break; //stop on incorrect reading
      if(TIP_channel(&ref,&map)==1)
	if(ref.csi_trig==trig) break;	
    }
  
  
  while(1)
    {
      if(feof(fl)!=0) break;
      pos=ftell(fl);//save current position
      printf("Sorting trigger %8d time stamp %12lld\r",ref.trig,ref.trig_tsns);
      
      nt=0;
      if(TIP_channel(&ref,&map)==1)
	if(ref.csi_trig==trig)
	  {	    
	    time[nt]=ref.tsns;
	    nt++;
	  }
      
      while(1)
	{
	  if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	  
	  if(curr.csi_trig==ref.csi_trig)	      
	    if(TIP_channel(&curr,&map)==1)
	      if(nt<NPOS)
		{
		  time[nt]=curr.tsns;
		  nt++;
		}
	  dt=curr.tsns-ref.tsns;	    
	  if(dt>MAXWIN) break; //too late for coincidence
	}
      
      
      if(nt>1)
	for(int i=0;i<nt;i++)
	  for(int j=i+1;j<nt;j++)
	    {
	      dt=time[j]-time[i];
	      h->Fill(dt);
	    }
      
      fseek(fl,pos,SEEK_SET);//back to the starting position
      
      trig++;
      found=0;
      
      while(1)
	{
	  if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	  if(feof(fl)) break;
	  if(curr.csi_trig==trig)//new event
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
  
    h->Draw("HIST");
    theApp->Run(kTRUE);

    
}
  
