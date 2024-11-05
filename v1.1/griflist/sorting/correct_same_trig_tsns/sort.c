#include "sort.h"
#define MAXWIN 10000//100 us window to check
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,ref;
  unsigned long pos;
  unsigned long long dt,tsns;
  int found,ff;
  
  son=sizeof(node);
  memset(&ref,0,son);

  if(argc!=2)
    {
      printf("griflist_correct_same_trig_tsns fragment_list\n");
      exit(-1);
    }
  printf("Program corrects time stamps which are accidentally the same for triggers of different subsystems\n");
  
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
  
    while(1)
      {
	if(feof(fl)) break;
   	pos=ftell(fl);//save current position

	found=0;
	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading

	    if(curr.trig_tsns==ref.trig_tsns) //found part of the reference event
	      {
		if(curr.tig_trig!=ref.tig_trig) found=1;
		if(curr.csi_trig!=ref.csi_trig) found=1;
		if(curr.emm_trig!=ref.emm_trig) found=1;
	      }
	    
  	    dt=curr.tsns-ref.tsns;	    
	    if(dt>MAXWIN) //out of coincidence window
	      break;
	  }
	
	if(found==1)
	  {

	    fseek(fl,pos,SEEK_SET);//back to the reference positon
	    while(1)
	      {
		if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading

		if(curr.trig_tsns==ref.trig_tsns) //found part of the reference event
		  {
		    tsns=curr.trig_tsns;
		    ff=0;
		    if(curr.tig_trig!=ref.tig_trig)
		      {
			ff=1;
			tsns+=1;
		      }
		    if(curr.csi_trig!=ref.csi_trig)
		      {
			ff=1;
			tsns+=2;
		      }
		    if(curr.emm_trig!=ref.emm_trig)
		      {
			ff=1;
			tsns+=3;
		      }
		    if(ff==1)
		      {
			curr.trig_tsns=tsns;
			fseek(fl,-son,SEEK_CUR);
			fwrite(&curr,son,1,fl);
		      }
		  }
		dt=curr.tsns-ref.tsns;	    
		if(dt>MAXWIN) //out of coincidence window
		  break;
	      }
	  }
	
	fseek(fl,pos,SEEK_SET);//back to the reference positon

	found=0;
	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	    
	    if(curr.trig_tsns>0)
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

