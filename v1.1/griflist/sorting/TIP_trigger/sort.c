#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,prev;
  int  gate;
  static gmap map;
  long long dt;
  
  son=sizeof(node);
  memset(&prev,0,son);
  prev.csi_trig=-1;
  
  if(argc!=4)
    {
      printf("griflist_TIP_trigger fragment_list map gate_in_ns\n");
      printf("Program assigns trigger number to TIP type-1 events on a list of fragments created from GRIF3/GRIF4 midas file.\n");
      exit(-1);
    }
  
 
  printf("Program assigns trigger number to TIP type-1 events on a list of fragments created from GRIF3/GRIF4 midas file.\n");


  read_map(argv[2],&map);

 
    
    if((fl=fopen(argv[1],"r+"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
  
    gate=atoi(argv[3]);

    while(1)
       {
	 if(fread(&prev,son,1,fl)!=1) break;//stop on incorrect reading

	 if(TIP_channel(&prev,&map)==1)
	   if(prev.wfit.type==1)
	     if(prev.tig_trig==-1)//the first trigger
	       if(prev.trig_tsns==0)//the first trigger	 
		 {
		   trigger=1;
		   prev.csi_trig=trigger;
		   fseek(fl,-son,SEEK_CUR);
		   fwrite(&prev,son,1,fl);
		   break;
		 }
       }

     while(1)
       {
	 if(fread(&curr,son,1,fl)!=1) break;//stop on incorrect reading

	 if(TIP_channel(&curr,&map)==1)
	   if(curr.wfit.type==1)
	     if(curr.tig_trig==-1)//take only events not assigned to TIGRESS-TIP coincidences
	       {	
		 
		 dt=curr.tsns-prev.tsns;
		 
		 if((int)dt<=gate)//coincidence with the event stored in previous
		   {
		     curr.csi_trig=trigger;
		     fseek(fl,-son,SEEK_CUR);
		     fwrite(&curr,son,1,fl);
		   }
		 else//new event
		   {
		     trigger++;
		     curr.csi_trig=trigger;
		     fseek(fl,-son,SEEK_CUR);
		     fwrite(&curr,son,1,fl);
		     memcpy(&prev,&curr,son);//store to the previous	   
		   }
	       
	     }
	 
       }

 
    fclose(fl);
  

    
}
