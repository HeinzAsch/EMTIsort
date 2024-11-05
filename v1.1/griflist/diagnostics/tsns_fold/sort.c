#include "sort.h"
#define MAXWIN 200
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,ref;
  unsigned long long pos;
  unsigned long long dt;
  int fold;
  int ac;
  char* av[1];
  
  ac=0;
  av[0]=0;
  son=sizeof(node);
  memset(&ref,0,son);

  theApp=new TApplication("App", &ac, av);
  if(h!=NULL) delete h;
  h=new TH1D("Fragment fold","Fragment fold",MAXWIN,0,MAXWIN);
  if(c!=NULL) delete c;
  c = new TCanvas("Fold", "Fold",10,10, 700, 500);
    
  if(argc!=2)
    {
      printf("griflist_tsns_fold fragment_list\n");
      exit(-1);
    }
   printf("Program sorts spectrum of a fold for fragments with exactly the same time stamp on list\n");

    
    if((fl=fopen(argv[1],"r+"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
 
 

    while(1)
      {
	if(fread(&ref,son,1,fl)!=1) break; //stop on incorrect reading
	if(ref.tsns>0) break;	
      }
 
   
    while(1)
      {
	if(feof(fl)!=0) break;
	pos=ftell(fl);//save current position
	fold=1;
	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	    if(curr.tsns==ref.tsns)
	      fold++;
	  
	    dt=curr.tsns-ref.tsns;	    
	    if(dt>MAXWIN) break; //too late for coincidence
	  }

	h->Fill(fold);
	
	fseek(fl,pos,SEEK_SET);//back to the starting position

	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	      if(curr.tsns!=ref.tsns)//new event
		{
		  memcpy(&ref,&curr,son);
		  break;
		}
	  }
	
      }
 
    fclose(fl);
    gPad->SetLogy();
    h->Draw("HIST");
    theApp->Run(kTRUE);
 
    
}
  
