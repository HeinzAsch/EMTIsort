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
  int fold,thr;
  
  son=sizeof(node);
  if(argc!=3)
    {
      printf("griflist_remove_tsns_bursts fragment_list threshold\n");
      exit(-1);
    }
   printf("Program sets to zero trig_tsns for events with tsns fold above the threshold\n");

   thr=atoi(argv[2]);
    
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

	if(fold>thr)
	  {	
	    fseek(fl,pos,SEEK_SET);//back to the starting position
	    ref.trig_tsns=0;
	    fseek(fl,-son,SEEK_CUR);
	    fwrite(&ref,son,1,fl);	    
	    while(1)
	      {
		if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
		if(curr.tsns==ref.tsns)
		  {
		    curr.trig_tsns=0;
		    fseek(fl,-son,SEEK_CUR);
		    fwrite(&curr,son,1,fl);
		  }
		
		dt=curr.tsns-ref.tsns;	    
		if(dt>MAXWIN) break; //too late for coincidence
	      }
	  }
	
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
  
 
    
}
  
