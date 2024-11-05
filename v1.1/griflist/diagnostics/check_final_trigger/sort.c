#include "sort.h"
#define MAXWIN 10000
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,ref;
  unsigned long long pos;
  unsigned long long dt;
  int err;
  
  son=sizeof(node);
  memset(&ref,0,son);
  
  if(argc!=2)
    {
      printf("griflist_check_final_trigger fragment_list\n");
      exit(-1);
    }
   printf("Program checks time-stamp order for the final trigger on a list of fragments created from GRIF3/GRIF4 midas file.\n");

    
    if((fl=fopen(argv[1],"r+"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
 
 
    
    while(1)
      {
	if(fread(&ref,son,1,fl)!=1) break; //stop on incorrect reading
	if(ref.trig!=0) break;	
      }
 
    err=0;
    while(1)
      {
	if(feof(fl)!=0) break;
	pos=ftell(fl);//save current position
	printf("Checking trigger %8d time stamp %12lld\r",ref.trig,ref.trig_tsns);

	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading

	    if(curr.trig==ref.trig)
	      if(curr.trig_tsns!=ref.trig_tsns)
		{
		  printf("Error in trigger time stamp assignments\n");
		  print_list(1,0,&ref);
		  print_list(1,0,&curr); 
		  err++;
		}	
	    

	    if(ref.trig>curr.trig)
	      if(ref.trig_tsns<curr.trig_tsns)
		{
		  printf("Error in ordering\n");
		  print_list(1,0,&ref);
		  print_list(1,0,&curr);
		  err++;
		}
	
	    if(ref.trig<curr.trig)
	      if(ref.trig_tsns>curr.trig_tsns)
		{
		  printf("Error in ordering\n");
		  print_list(1,0,&ref);
		  print_list(1,0,&curr);
		  err++;
		}
	    
	    dt=curr.tsns-ref.tsns;
	    
	    if(dt>MAXWIN) break; //too late for coincidence
	  }
	fseek(fl,pos,SEEK_SET);//back to the starting position
	
	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	    if(curr.trig>0)
	      if(curr.trig!=ref.trig)//new event
		{
		  memcpy(&ref,&curr,son);
		  break;
		}
	  }
	
      }
 
    fclose(fl);
  
    if(err==0)
      printf("\nNo errors detected\n");
    else
      printf("\nFound %d errors\n",err);
    
}
  
