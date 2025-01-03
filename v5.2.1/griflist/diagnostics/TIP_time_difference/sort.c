#include "sort.h"
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* output;
  static gmap map;
  size_t son;
  node  current,next;
  unsigned long long dt;
  unsigned long pos;
  
  if(argc!=4)
    {
      printf("griflist_TIP_time_difference griflist_input_data map window_[ns]\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between  TIP fragments within a time window on the list\n");


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
  h=new TH1D("TSdiff","TSdiff",window,0,window);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  while(1)
    {
      if(fread(&current,son,1,inp)!=1)
	break;

      if(TIP_channel(&current,&map)==1)
	if(current.wfit.type==1)
	  {
	    pos=ftell(inp);//save current position
	    while(1)
	      {
		if(fread(&next,son,1,inp)!=1)
		  break;
		dt=next.tsns-current.tsns;
		if(dt>window)
		  break;
		if(TIP_channel(&next,&map)==1)
		  if(next.wfit.type==1)
		    {
		      h->Fill((int)dt);
		      if(dt<S32K)
			hist[dt]++;
		    }
	      }
	    fseek(inp,pos,SEEK_SET);
	  }
    }

  fclose(inp);

  if((output=fopen("TIP_dt.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

  h->Draw("HIST");
  theApp->Run(kTRUE);

  
}
