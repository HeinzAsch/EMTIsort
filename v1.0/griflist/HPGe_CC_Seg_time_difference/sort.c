#include "sort.h"
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* output;
  static gmap map;
  size_t son;
  node  current,next;
  int   trig;
  unsigned long long dt;
  unsigned long pos;
  
  if(argc!=6)
    {
      printf("griflist_HPGe_CC_Seg_time_difference list_input_data map window_[ns] Egate_low Egate_high\n");
      printf("Energy gates are on the segments for this one\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between HPGe CC and Seg fragments within a time window on the list\n");


  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  int position;
  //  int colour;
  son=sizeof(node);
  window=atoi(argv[3]);
  read_map(argv[2],&map);
  memset(&hist,0,sizeof(hist));
  Egate_low=atoi(argv[4]);
  Egate_high=atoi(argv[5]);
 

  
  theApp=new TApplication("App", &argc, argv);
  if(h!=NULL) delete h;
  h=new TH1D("TSdiff","TSdiff",S32K,-S16K,S16K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  while(1)
    {
      if(fread(&current,son,1,inp)!=1)
	break;

      if(CC_channel(&current,&map)==1)
	{
	  if((trig=current.tig_trig)<1)
	    {
	      printf("aIncorrect TIGRESS CC trigger %d at tsns %16lld channel %d. Exiting\n",trig,current.tsns,current.chan);
	      exit(0);
	    }
	  pos=ftell(inp);//save current position

	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;
	      dt=next.tsns-current.tsns;
	      if(dt>window)
		break;
	      if(Seg_channel(&next,&map)==1)
		if(next.ch.charge/map.tig_kpar>=Egate_low)
		  if(next.ch.charge/map.tig_kpar<=Egate_high)
		    if(same_HPGe(&current,&next,&map)==1)
		      {
			position=map.hpge_lt[next.chan-map.tig_min].pos;
			//colour=map.hpge_lt[next.chan-map.tig_min].seg;
			h->Fill((int)dt);
			if(dt<S16K)
			  {
			    hist[0][S16K+dt]++;
			    hist[position][S16K+dt]++;
			    //hist[8*(position-1)+colour][S16K+dt]++;
			  }
		      }
	    }
	  fseek(inp,pos,SEEK_SET);
	}

      if(Seg_channel(&current,&map)==1)
	if(current.ch.charge/map.tig_kpar>=Egate_low)
	  if(current.ch.charge/map.tig_kpar<=Egate_high)
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
		    {
		      if((trig=next.tig_trig)<1)
			{
			  printf("bbbIncorrect TIGRESS CC trigger %d at tsns %16lld channel %d. Exiting\n",trig,next.tsns,next.chan);
			  exit(0);
			}
		      if(same_HPGe(&current,&next,&map)==1)
			{
			  position=map.hpge_lt[current.chan-map.tig_min].pos;
			  //colour=map.hpge_lt[current.chan-map.tig_min].seg;
			  h->Fill(-(int)dt);
			  if(dt<S16K)
			    {
			      hist[0][S16K-dt]++;
			      hist[position][S16K-dt]++;
			      //hist[8*(position-1)+colour][S16K-dt]++;
			    }
			}
		    }
		}
	      fseek(inp,pos,SEEK_SET);
	    }
    }

  fclose(inp);

  if((output=fopen("HPGe_CC_Seg_dt.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

  h->Draw("HIST");
  theApp->Run(kTRUE);

  print_map(&map);

  printf("Histogram contains sum in channel 0 and each of the 16 detectors in channels 1-16\n");
  
}
