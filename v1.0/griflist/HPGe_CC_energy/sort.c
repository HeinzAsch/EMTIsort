#include "sort.h"
int analyze_list(int limit,int offset,node* curr,gmap* map)
{
  //  long long diff;
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if(map->hpge_lt[curr->chan-map->tig_min].seg==0)//channel is the central contact
	if(map->hpge_lt[curr->chan-map->tig_min].pos>0)//channel present on the CC list
	  if(map->hpge_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//channel present on the CC list   
	    {
	      
	      if(offset==0)
		{
		  //tsstore=curr->tsns;
		  //Estore=curr->ch.charge;
		  return 0;
		}
	      
	      //diff=curr->tsns-tsstore;
	      
	      
	      /* if(diff<0) */
	      /* 	{ */
	      /* 	  printf("current %16lld stored %16lld\n",curr->tsns,tsstore); */
	      /* 	  printf("list disordered, diff is %16lld\n",diff); */
	      /* 	  printf("Exiting\n"); */
	      /* 	  exit(0); */
	      /* 	} */
	      h->Fill(curr->ch.charge/map->tig_kpar);
	      
	      //if(diff>0)
	      //if(diff<S4K)
	      //  hist[(int)diff]++;
	      
	      //tsstore=curr->tsns;
	      //Estore=curr->ch.charge;
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
  
  ac=0;
  av[0]=0;
  son=sizeof(node);
  
  if(argc!=3)
    {
      printf("griflist_HPGe_CC_energy griflist_input_data map\n");
      exit(-1);
    }
  
 
  printf("Program sorts energy histogram for HPGe CC fragments on the list\n");

  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  read_map(argv[2],&map);
  memset(&hist,0,sizeof(hist));
  theApp=new TApplication("App", &ac, av);
  if(h!=NULL) delete h;
  h=new TH1D("Energy","Energy",65536,0,65536);
  if(c!=NULL) delete c;
  c = new TCanvas("Energy", "Energy",10,10, 700, 500);

  i=0;
  while(fread(&nd,son,1,inp)==1)
    {     
      analyze_list(1,i,&nd,&map);
      i++;
    };

  fclose(inp);

  if((output=fopen("HPGe_CC_E.spn","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

  h->Draw("HIST");
  theApp->Run(kTRUE);

  
}
