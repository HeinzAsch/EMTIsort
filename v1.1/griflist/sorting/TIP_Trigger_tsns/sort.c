#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,prev;
  
  son=sizeof(node);
  memset(&prev,0,son);
  
  if(argc!=2)
    {
      printf("griflist_TIP_Trigger_tsns fragment_list\n");
      exit(-1);
    }
  

  printf("Program assigns time stamp in ns from first fragment in trigger to all fragments in trigger for TIP events.\n");
 
 
    
    if((fl=fopen(argv[1],"r+"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
  
 
    prev.tsns=-1;
    prev.csi_trig=-1;

    while(1)
      {
	if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	if(curr.csi_trig>0) //look for tip events 
	  {
	    if(curr.csi_trig==prev.csi_trig) //if in coincidence
	      {
		curr.trig_tsns=prev.tsns;
		fseek(fl,-son,SEEK_CUR);
		fwrite(&curr,son,1,fl);
	      }
	    else
	      {
		curr.trig_tsns=curr.tsns;
		fseek(fl,-son,SEEK_CUR);
		fwrite(&curr,son,1,fl);
		memcpy(&prev,&curr,son);//store to previous
	      }
	  }
      }

  
    
  
 
    fclose(fl);
  

    
}
