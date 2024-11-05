#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr;
  static gmap map;
 
  
  son=sizeof(node);
  
  if(argc!=3)
    {
      printf("griflist_EMMA_trigger fragment_list map\n");
      printf("Program assigns trigger number to EMMA  events on a list of fragments created from GRIF3/GRIF4 midas file.\n");
      exit(-1);
    }
  
 
  printf("Program assigns trigger number to EMMA events on a list of fragments created from GRIF3/GRIF4 midas file.\n");


  read_map(argv[2],&map);


    if((fl=fopen(argv[1],"r+"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
    
    while(1)
      {
	if(fread(&curr,son,1,fl)!=1) break;//stop on incorrect reading

	if((curr.ch.timestamp|curr.ch.timestamp_up)!=0)//ignore bad events at the start
	  if(EMMA_channel(&curr,&map))//id for the emma channel
	    if(curr.tig_trig==-1)//not assigned to coincidence with TIGRESS
	      if(curr.csi_trig==-1)//not assigned to coincidences with TIP
		{
		  trigger++;
		  curr.emm_trig=trigger;
		  fseek(fl,-son,SEEK_CUR);
		  fwrite(&curr,son,1,fl);
		}	 
       }

 
    fclose(fl);
  

    
}
