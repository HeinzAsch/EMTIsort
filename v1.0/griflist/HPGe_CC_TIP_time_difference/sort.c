#include "sort.h"
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* output;
  static gmap map;
  size_t son;
  node  current,next;
  int   trig,CC_trig_store,TIP_trig_store;
  unsigned long long dt;
  unsigned long pos;
  
  if(argc!=4)
    {
      printf("griflist_HPGe_CC_TIP_time_difference griflist_input_data map window_[ns]\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between HPGe CC and TIP fragments within a time window on the list\n");


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
  h=new TH1D("TSdiff","TSdiff",S32K,-S16K,S16K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);
  trig=-1;
  CC_trig_store=-2;
  TIP_trig_store=-3;

  
  while(1)
    {
      if(fread(&current,son,1,inp)!=1)
	break;

      if(TIP_channel(&current,&map)==1)
	if(current.wfit.type==1)
	  if((current.csi_trig)<1)
	    {
	      printf("Incorrect TIP trigger %d at tsns %16lld channel %d. Exiting\n",current.csi_trig,current.tsns,current.chan);
	      exit(0);
	    }

   if(CC_channel(&current,&map)==1)
     if(current.tig_trig<1)
       {
	 printf("Incorrect TIGRESS CC trigger %d at tsns %16lld channel %d. Exiting\n",trig,current.tsns,current.chan);
	 exit(0);
       }
	     
      
      if(CC_channel(&current,&map)==1)
	{
	  trig=current.tig_trig;
	  
	  if(trig!=CC_trig_store)
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
		      if(next.csi_trig!=TIP_trig_store)
			{
			  if((next.csi_trig)<1)
			    {
			      printf("Incorrect TIP trigger %d at tsns %16lld channel %d. Exiting\n",current.csi_trig,current.tsns,current.chan);
			      exit(0);
			    }
			  h->Fill((int)dt);
			  if(dt<S16K)
			    hist[S16K+dt]++;
			  TIP_trig_store=next.emm_trig;
			}
		}
	      CC_trig_store=trig;
	      fseek(inp,pos,SEEK_SET);
	    }
	}

      if(TIP_channel(&current,&map)==1)
	if(current.wfit.type==1)   
	  if(current.csi_trig!=TIP_trig_store)
	    {
	      pos=ftell(inp);//save current position
	      while(1)
		{
		  if(fread(&next,son,1,inp)!=1)
		    break;
		  dt=next.tsns-current.tsns;	      
		  if(dt>window)
		    break;
		  
		  if(CC_channel(&next,&map)==1)
		    if(next.tig_trig!=CC_trig_store)
		      {		  
			h->Fill(-(int)dt);
			if(dt<S16K)
			  hist[S16K-dt]++;
			CC_trig_store=next.tig_trig;
		      }	      
		  
		}
	      TIP_trig_store=current.csi_trig;
	      fseek(inp,pos,SEEK_SET);
	    }
    }
    

  fclose(inp);

  if((output=fopen("HPGe_CC_TIP_dt.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

  h->Draw("HIST");
  theApp->Run(kTRUE);

  
}
