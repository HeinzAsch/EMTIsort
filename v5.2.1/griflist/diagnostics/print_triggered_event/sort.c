#include "sort.h"
#define MAXWIN 10000
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr;
  int trig;
  
  son=sizeof(node);
  
  if(argc!=3)
    {
      printf("griflist_print_triggered_event fragment_list trigger_number\n");
      exit(-1);
    }
   printf("Program print nodes for the same trigger number on a list with identified triggers\n");

    
    if((fl=fopen(argv[1],"r+"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
 
 
    trig=atoi(argv[2]);
    
    while(1)
      {	
	if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	if(curr.trig==trig)
	  print_list(1,0,&curr);
      }
 
    fclose(fl);
  
   
    
}
  
