#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr;
  
  son=sizeof(node);
   
  if(argc!=2)
    {
      printf("griflist_EMMA_Trigger_tsns fragment_list\n");
      exit(-1);
    }
  

  printf("Program assigns time stamp in ns from first fragment in trigger to all fragments in trigger for EMMA events.\n");
  
    
    if((fl=fopen(argv[1],"r+"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
  
    
    

    while(1)
      {
	if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading

	if(curr.emm_trig>0) //look for emma events with triggers
	  {
	    curr.trig_tsns=curr.tsns;
	    fseek(fl,-son,SEEK_CUR);
	    fwrite(&curr,son,1,fl);
	  }

      }
      
    
    fclose(fl);
  

    
}
