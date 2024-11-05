#include "sort.h"
#define MAXWIN 10000
#define GATE   2500
#define NG     64
#define NS     128
/*================================================================*/
int main(int argc, char *argv[])
{
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
      printf("griflist_check_HPGe_CC_Sup_gate fragment_list map\n");
      exit(-1);
    }
   printf("Program sort HPGe CC Sup gate for a list with identified triggers\n");

    
    if((fl=fopen(argv[1],"r"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }

    read_map(argv[2],&map);
    
    theApp=new TApplication("App", &ac, av);
    if(hl!=NULL) delete hl;
    hl=new TH1D("TS ll","TS ll",2*GATE+1,-GATE,GATE);
    if(hf!=NULL) delete hf;   
    hf=new TH1D("TS ff","TS ff",2*GATE+1,-GATE,GATE);

   if(h!=NULL) delete h;   
    h=new TH1D("TS","TS",2*GATE+1,-GATE,GATE);

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

	if(CC_channel(&ref,&map)==1)
	  {
	    tg[ng]=ref.tsns;
	    ng++;
	  }	
	if(Sup_channel(&ref,&map)==1)
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
		if(Sup_channel(&curr,&map)==1)
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

    printf("DONE\n");
    //  hl->Draw("HIST");
    //    hl->SetLineColor(kRed);
    //    hf->Draw("HIST SAME");
    //    hf->SetLineColor(kBlue);
    h=(TH1D*)hl->Clone("TS");
    h->Multiply(hf);
    h->SetName("TSdiff");
    h->SetTitle("TSdiff");
    h->Draw("HIST");
    //  h->SetLineColor(kBlack);
    gPad->SetLogy();
    theApp->Run(kTRUE);

    
}
  
