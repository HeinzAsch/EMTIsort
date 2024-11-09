#include "sort.h"
#define MAXWIN 1000
#define NPOS   64
/*================================================================*/
int main(int argc, char *argv[])
{
  //TIMEKEEPING
  clock_t start, end;
  double timer;
  start=clock();
  
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
      printf("griflist_check_HPGe_CC_gate fragment_list map\n");
      exit(-1);
    }
   printf("Program sort HPGe CC gate for a list with identified triggers\n");

    
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
      if(ref.trig==trig) break;	
    }
  
  
  while(1)
    {
      if(feof(fl)!=0) break;
      pos=ftell(fl);//save current position
      printf("Sorting trigger %8d time stamp %12lld\r",ref.trig,ref.trig_tsns);
      
      nt=0;
      if(CC_channel(&ref,&map)==1)
	{	    
	  time[nt]=ref.tsns;
	  nt++;
	}
      
      while(1)
	{
	  if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	  
	  if(curr.trig==ref.trig)	      
	    if(CC_channel(&curr,&map)==1)
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
	      if(dt<0)
		{
		  printf("Sorting error dt=%lld\n",dt);
		  exit(0);
		}
	      
	      if(dt>MAXWIN)
		{
		  printf("Sorting error dt=%lld\n",dt);
		  exit(0);
		}

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
  
  //TIMEKEEPING
  end=clock();
  timer=(double)(end-start)/CLOCKS_PER_SEC;
  printf("\nSorting time %8.2f seconds\n",timer);

  //h->Multiply(hf);
  h->SetName("CC-CC TSdiff");
  h->SetTitle("CC-CC TSdiff");
  h->Draw("HIST");
  gPad->SetLogy();
  theApp->Run(kTRUE);

}
  
