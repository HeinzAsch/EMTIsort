#include "sort.h"
#define MAXWIN 10000
#define GATE   2500
#define NG     64
#define NS     128
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
  int dll,dff;
  unsigned long long tg[NG],ts[NS];
  static gmap map;
  int ac;
  char* av[1];
  int found=0;
  int ng,ns;
  
  ac=0;
  av[0]=0;
  son=sizeof(node);
  memset(&ref,0,son);
  
  if(argc!=3)
    {
      printf("griflist_check_HPGe_CC_TIP_gate fragment_list map\n");
      exit(-1);
    }
   printf("Program sort HPGe CC TIP gate for a list with identified triggers\n");

    
    if((fl=fopen(argv[1],"r"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }

    read_map(argv[2],&map);
    
    theApp=new TApplication("App", &ac, av);
    if(hl!=NULL) delete hl;
    hl=new TH1D("TS ll","TS ll",2*GATE+1,-GATE,GATE);
    hl->Reset();
    if(hf!=NULL) delete hf;   
    hf=new TH1D("TS ff","TS ff",2*GATE+1,-GATE,GATE);
    hf->Reset();
    if(h!=NULL) delete h;   
    h=new TH1D("TS","TS",2*GATE+1,-GATE,GATE);
    h->Reset();
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
	//	printf("Sorting trigger %8d time stamp %12lld\r",ref.trig,ref.trig_tsns);
	
	ng=0;
	ns=0;
	tg[0]=0;
	ts[0]=0;
	
	if(CC_channel(&ref,&map)==1)
	  {
	    tg[ng]=ref.tsns;
	    ng++;
	  }	
	if(TIP_channel(&ref,&map)==1)
	  {
	    ts[ns]=ref.tsns;
	    ns++;
	  }
	
	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	    
	    if(curr.trig==ref.trig)
	      {
		if(CC_channel(&curr,&map)==1)
		  {
		    tg[ng]=curr.tsns;
		    ng++;
		  }	
		if(TIP_channel(&curr,&map)==1)
		  {
		    ts[ns]=curr.tsns;
		    ns++;
		  }
	      }
	    dt=curr.tsns-ref.tsns;	    
	    if(dt>MAXWIN) break; //too late for coincidence
	  }

	if(ns>0)
	  if(ng>0)
	    {
	      dff=(int)(ts[0]-tg[0]);//first to first
	      hf->Fill(dff);
	      dll=(int)(ts[ns-1]-tg[ng-1]);//last to last
	      hl->Fill(dll);

	      /* if(dff==0) */
	      /* 	if(dll==0) */
	      /* 	  printf("zeros at trigger %d\n",ref.trig); */

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

    h=(TH1D*)hl->Clone("TS");
    h->Multiply(hf);
    h->SetName("CC-TIP TSdiff");
    h->SetTitle("CC-TIP TSdiff");
    h->Draw("HIST");
    gPad->SetLogy();
    theApp->Run(kTRUE);
}
  
