#include "sort.h"
int analyze_list(int limit,int offset,node* curr,gmap* map)
{
  long long diff;
  double energy;

  if(CC_channel(curr,map)==1)
    {
      
      if(offset==0)
	{
	  tsstore=curr->tsns;
	  
	  return 0;
	}
      
      diff=curr->tsns-tsstore;
      
      
      if(diff<0)
	{
	  printf("current %16lld stored %16lld\n",curr->tsns,tsstore);
	  printf("list disordered, diff is %16lld\n",diff);
	  printf("Exiting\n");
	  exit(0);
	}
      
      energy=curr->ch.charge/map->tig_kpar;
      
      if(energy>=Egate_low)
	if(energy<=Egate_high)
	  {
	    h->Fill(diff);
	    if(diff>0)
	      if(diff<S4K)
		hist[(int)diff]++;			
	  }
      
      
      tsstore=curr->tsns;
      
    }
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* output;
  int i;
  size_t son;
  node nd;
  int ac;
  char* av[1];
  static gmap map;
  int window;
  
  ac=0;
  av[0]=0;
  son=sizeof(node);
  
  if(argc!=6)
    {
      printf("griflist_HPGe_CC_time_difference list_input_data map window_[ns] E_gate_low E_gate_high\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between consecutive HPGe CC fragments on the list\n");

  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  window=atoi(argv[3]);
  Egate_low=atoi(argv[4]);
  Egate_high=atoi(argv[5]);

  read_map(argv[2],&map);
  memset(&hist,0,sizeof(hist));
  theApp=new TApplication("App", &ac, av);
  if(h!=NULL) delete h;
  h=new TH1D("TSdiff","TSdiff",window,0,window);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  i=0;
  while(fread(&nd,son,1,inp)==1)
    {     
      analyze_list(1,i,&nd,&map);
      i++;
    };

  fclose(inp);

  if((output=fopen("HPGe_CC_dt.spn","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

  h->Draw("HIST");
  theApp->Run(kTRUE);

  
}
