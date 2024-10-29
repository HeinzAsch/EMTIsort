#include "sort.h"
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* output;
  static gmap map;
  size_t son;
  node  current,next;
  int   trig,ntrig;
  unsigned long long dt;
  
  if(argc!=4)
    {
      printf("griflist_TIG_trigger_tsdiff griflist_input_data map window_[ns]\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between consecutive TIGRESS events within a time window on the list\n");


  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  son=sizeof(node);
  window=atoi(argv[3]);
  
  read_map(argv[2],&map);
  memset(&hist,0,sizeof(hist));
  theApp=new TApplication("App", &argc, argv);
  if(h!=NULL) delete h;
  h=new TH1D("TSdiff","TSdiff",S16K,0,S16K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);
  
  trig=-1;
  while(1)
    {
      if(fread(&current,son,1,inp)!=1)
      	break;
    
      if(current.tig_trig==1)
	break;
	
    }
  trig=current.tig_trig;
  
  while(1)
    {
      if(fread(&next,son,1,inp)!=1)
	break;
		
      if((ntrig=next.tig_trig)>0)
	if(ntrig!=trig)
	  {

	    dt=next.trig_tsns-current.trig_tsns;
	    h->Fill((int)dt);
	    if(dt<S16K)
	      hist[dt]++;
	    memcpy(&current,&next,son);
	    trig=ntrig;
	
	  }
    }

  
  fclose(inp);

  if((output=fopen("HPGe_TIG_trig_tsdiff.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

  h->Draw("HIST");
  theApp->Run(kTRUE);

  
}
