#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  //TIMEKEEPING
  clock_t start, end;
  double timer;
  start=clock();
  
  FILE* fl;
  size_t son;
  node curr,prev;
  static gmap map;
  long long dt;
  int trigger;
  
  son=sizeof(node);
  memset(&prev,0,son);
  prev.tig_trig=-1;
 
  if(argc!=4)
    {
      printf("griflist_HPGe_CC_trigger fragment_list map gate_in_ns\n");
      exit(-1);
    }
  
 
  printf("Program assigns trigger number to HPGe central contact events on a list of fragments created from GRIF3/GRIF4 midas file.\n");


  read_map(argv[2],&map);

  trigger=-1;
    
    if((fl=fopen(argv[1],"r+"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
  
    gate=atoi(argv[3]);

  
    
     while(1)
       {
	 if(fread(&curr,son,1,fl)!=1)
	   break;//stop on incorrect reading

	 if((curr.ch.timestamp|curr.ch.timestamp_up)!=0)//ignore bad events at the start
	   if(CC_channel(&curr, &map)==1)
	     {
	       if(prev.tsns==0)//the first channel since previous not stored
		 {
		   trigger=1;
		   curr.tig_trig=trigger;
		   fseek(fl,-son,SEEK_CUR);
		   fwrite(&curr,son,1,fl);
		   memcpy(&prev,&curr,son);//store to the previous
		 }
	       dt=curr.tsns-prev.tsns;
	       
	       if(dt<=gate)//coincidence with the event stored in previous
		 {
		   curr.tig_trig=trigger;
		   fseek(fl,-son,SEEK_CUR);
		   fwrite(&curr,son,1,fl);
		   /* memcpy(&prev,&curr,son);//store to the previous      // Commented so does not reset gate if finds new gamma within	    */
		 }
	       else//new event
		 {
		   trigger++;
		   curr.tig_trig=trigger;
		   fseek(fl,-son,SEEK_CUR);
		   fwrite(&curr,son,1,fl);
		   memcpy(&prev,&curr,son);//store to the previous	   
		 }
	       
	     }
	 
       }

 
    fclose(fl); 


    //TIMEKEEPING
    end=clock();
    timer=(double)(end-start)/CLOCKS_PER_SEC;
    printf("\nSorting time %8.2f seconds\n",timer);
}
