#include "sort.h"
#define MAXWIN 10000//100 us window to check
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,ref;
  int  trig;
  unsigned long pos;
  unsigned long long dt;
  int found;
  
  son=sizeof(node);
  memset(&ref,0,son);

  if(argc!=2)
    {
      printf("griflist_final_trigger fragment_list\n");
      exit(-1);
    }
  
  printf("Program assignes final trigger numbers based on trig_ts[ns] in a fragment list\n");
    
  if((fl=fopen(argv[1],"r+"))==NULL)
    {
      printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
      exit(-2);
    }
 
  //in the first pass assigned ordered trigger numbers to the first event with trig_tsns in a chronological order
    
    while(1)
      {
	if(fread(&ref,son,1,fl)!=1) break; //stop on incorrect reading
	if(ref.trig_tsns>0) break;
      }
    trig=0;
  
  
    while(1)
      {
	if(feof(fl)) break;
   	pos=ftell(fl);//save current position
	trig++;
	ref.trig=trig;
	fseek(fl,-son,SEEK_CUR);
	fwrite(&ref,son,1,fl);

	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading

	    if(curr.trig_tsns==ref.trig_tsns) //found part of the reference event
		{
		  curr.trig=trig;
		  fseek(fl,-son,SEEK_CUR);
		  fwrite(&curr,son,1,fl);
		}
	    
  	    dt=curr.tsns-ref.tsns;	    
	    if(dt>MAXWIN) //out of coincidence window
	      break;
	  }

	fseek(fl,pos,SEEK_SET);//back to the reference positon

	found=0;
	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	    
	    if(curr.trig_tsns>0)
	      if(curr.trig==-1)
		if(curr.trig_tsns!=ref.trig_tsns) //found next time stamp
		  {
		    memcpy(&ref,&curr,son);
		    found=1;
		    break;
		  }
	  }
	if(found==0) break;
      }
	
    fclose(fl);    
}

