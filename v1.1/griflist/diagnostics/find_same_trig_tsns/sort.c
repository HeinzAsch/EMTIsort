#include "sort.h"
#define MAXWIN 10000//100 us window to check
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,ref;
  unsigned long pos;
  unsigned long long dt;
  int found;
  
  son=sizeof(node);
  memset(&ref,0,son);

  if(argc!=2)
    {
      printf("griflist_find_same_trig_tsns fragment_list\n");
      exit(-1);
    }
  printf("Program finds time stamps which are accidentally the same for triggers of different subsystems\n");
  
  if((fl=fopen(argv[1],"r+"))==NULL)
    {
      printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
      exit(-2);
    }
 
    
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
	    printf("Found multiple events at the same trig_tsns %lld\n",ref.trig_tsns);
	    fseek(fl,pos,SEEK_SET);//back to the reference positon
	    print_list(1,0,&ref);
	    while(1)
	      {
		if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
		if(curr.trig_tsns==ref.trig_tsns) //found part of the reference event
		  print_list(1,0,&curr);
		dt=curr.tsns-ref.tsns;	    
		if(dt>MAXWIN) //out of coincidence window
		  break;
	      }
	    getc(stdin);
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

