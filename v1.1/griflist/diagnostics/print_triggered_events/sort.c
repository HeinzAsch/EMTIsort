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
  int trig;
  
  son=sizeof(node);
  memset(&ref,0,son);
  
  if(argc!=2)
    {
      printf("griflist_print_triggered_events fragment_list\n");
      exit(-1);
    }
   printf("Program print nodes for the same trigger number on a list with identified triggers\n");

    
    if((fl=fopen(argv[1],"r+"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
 
 
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
	printf("Checking trigger %8d time stamp %12lld\r",ref.trig,ref.trig_tsns);
	print_list(1,0,&ref);
	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	    if(curr.trig==ref.trig)
	      print_list(1,0,&curr);
	  
	    dt=curr.tsns-ref.tsns;	    
	    if(dt>MAXWIN) break; //too late for coincidence
	  }
	fseek(fl,pos,SEEK_SET);//back to the starting position
	getc(stdin);
	trig++;
	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	      if(curr.trig==trig)//new event
		{
		  memcpy(&ref,&curr,son);
		  break;
		}
	  }
	
      }
 
    fclose(fl);
  
   
    
}
  
