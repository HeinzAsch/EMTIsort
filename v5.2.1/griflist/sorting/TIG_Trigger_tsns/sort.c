#include "sort.h"
#define MAXWIN 10000
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,ref;
  int trig;
  unsigned long long dt,tsns;
  unsigned long posr;
  int found;
  static gmap map;
  
  son=sizeof(node);
   
  if(argc!=3)
    {
      printf("griflist_TIG_Trigger_tsns fragment_list map\n");
      exit(-1);
    }
  
  
  printf("Program assigns time stamp in ns from the earliest CC fragment in a triggered event to all fragments for events with TIG trigger.\n");
 
  
  if((fl=fopen(argv[1],"r+"))==NULL)
    {
      printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
      exit(-2);
    }
  read_map(argv[2],&map);

  trig=1;
  
  while(1)
    {
      if(fread(&ref,son,1,fl)!=1) break; //stop on incorrect reading
      
      if(ref.tig_trig==trig)
	break;
    }
  posr=ftell(fl);//save current position
  tsns=0xefffffffffffffff;;
  
   
  while(1)
    {
    
      while(1)//find the lowest tsns for a given trigger in the MAXWIN window
	{
	  if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	  
	  if(CC_channel(&curr,&map)==1)
	     if(curr.tig_trig==ref.tig_trig)
	       if(curr.tsns<tsns)
		 tsns=curr.tsns;
	  
	  dt=curr.tsns-ref.tsns;		  
	  if(dt>MAXWIN) break;//too late for coincidence
	}
      
      fseek(fl,posr,SEEK_SET);//back to the reference position

      
      if(ref.trig_tsns!=tsns)
	{
	  ref.trig_tsns=tsns;
	  fseek(fl,-son,SEEK_CUR);
	  fwrite(&ref,son,1,fl);
	}
      
      
      while(1)//assigned trig_tsns to tsns
	{
	  if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	  
	  if(curr.tig_trig==ref.tig_trig)
	    if(curr.trig_tsns!=tsns)
	    {
	      curr.trig_tsns=tsns;
	      fseek(fl,-son,SEEK_CUR);
	      fwrite(&curr,son,1,fl);	      
	    }
	  dt=curr.tsns-ref.tsns;
	  if(dt>MAXWIN) break;//too late for coincidence
	}
      
      
      trig++;//next trigger
      found=0;
      fseek(fl,posr,SEEK_SET);//back to the reference position	
      while(1)//find the reference for the next trigger
	{
	  if(fread(&ref,son,1,fl)!=1) break;
	 
	  if(ref.tig_trig==trig)
	    {
	      found=1;
	      posr=ftell(fl);//save current position
	      if(CC_channel(&ref,&map)==1)
		tsns=ref.tsns;
	      else
		tsns=0xefffffffffffffff;
	      break;
	    }
	}
      
      if(found==0) break;
      fseek(fl,posr,SEEK_SET);//back to the reference position
    }
  
  fclose(fl);  
}
  
 
