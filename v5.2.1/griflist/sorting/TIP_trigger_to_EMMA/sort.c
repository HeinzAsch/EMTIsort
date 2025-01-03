#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  //TIMEKEEPING
  clock_t start, end;
  double timer;
  start=clock();
  
  FILE* inp;
  static gmap map;
  size_t son;
  node  current, next;
  unsigned long pos;
  int save;
  
  if(argc!=5)
    {
      printf("griflist_TIP_trigger_to_EMMA fragment_list map gate_low[ns] gate_high[ns]\n");
      exit(-1);
    }
  
 
  printf("Program assigns trigger number to EMMA channels based on HPGe central contact trigger number on a list of fragments created from GRIF3/GRIF4 midas file.\n");

  son=sizeof(node);
  read_map(argv[2],&map);
    
  if((inp=fopen(argv[1],"r+"))==NULL)
    {
      printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
      exit(-2);
    }
  
  gate_low=atoi(argv[3]);
  gate_high=atoi(argv[4]);

  while(1)
    {
      if(fread(&current,son,1,inp)!=1)
	break;

      if(TIP_channel(&current,&map)==1)
	if(current.wfit.type==1)
	  if(current.tig_trig==-1)//only events not assigned to TIGRESS-TIP coincidences
	    {
	      if(current.csi_trig<1)
		{
		  printf("Incorrect TIP trigger %d at tsns %16lld channel %d. Exiting\n",current.trig,current.tsns,current.chan);
		  exit(0);
		}
	      pos=ftell(inp);//save current position
	      
	      while(1)
		{
		  if(fread(&next,son,1,inp)!=1)
		    break;
		  
		  dt=next.tsns-current.tsns;
		  
		  if(dt>MAXWIN)
		    break;
		  
		  if(EMMA_channel(&next,&map)==1)
		    if(next.tig_trig==-1)//not assigned to a TIG event
		      if(dt>=gate_low && dt<=gate_high)//arrives after TIP
			{
			  next.csi_trig=current.csi_trig;
			  next.trig_tsns=current.trig_tsns;
			  fseek(inp,-son,SEEK_CUR);
			  fwrite(&next,son,1,inp);
			}
		}
	      
	      fseek(inp,pos,SEEK_SET);
	    }
      
      if(EMMA_channel(&current,&map)==1)
	if(current.tig_trig==-1)//not assigned to a TIG event
	  {
	    pos=ftell(inp);//save current position
	    save=0;
	    while(1)
	      {
		if(fread(&next,son,1,inp)!=1)
		  break;
		
		dt=next.tsns-current.tsns;
		
		if(dt>MAXWIN)
		  break;
		
		if(TIP_channel(&next,&map)==1)
		  if(next.wfit.type==1)
		    if(current.tig_trig==-1)//only events not assigned to TIGRESS-TIP coincidences
		      if((-dt)>=gate_low && (-dt)<=gate_high)//arrives before TIP, flip sign
			{
			  current.tig_trig=next.tig_trig;
			  current.trig_tsns=next.trig_tsns;
			  save=1;
			  break;
			}	      
	      }
	    fseek(inp,pos,SEEK_SET);
	    if(save==1)
	      {
		fseek(inp,-son,SEEK_CUR);
		fwrite(&current,son,1,inp);
	      }
	  }
    }
  
  fclose(inp);

  //TIMEKEEPING
  end=clock();
  timer=(double)(end-start)/CLOCKS_PER_SEC;
  printf("\nSorting time %8.2f seconds\n",timer);
}
