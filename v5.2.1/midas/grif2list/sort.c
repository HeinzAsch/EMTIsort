#include "sort.h"

int analyze_list(int limit,int offset,node* list)
{

  store_list(limit,list,out);
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  //TIMEKEEPING
  clock_t start,end;
  double time;
  start=clock();
  
  min_TSUP = -1;
  max_TSUP = -1;
  prev_TSUP = -1;

  minmax_DROPPED = 0;
  pileup_DROPPED = 0;
  cfd_DROPPED = 0;
  map_DROPPED = 0;
  zero_DROPPED = 0;
  
  if(argc!=6)
    {
      printf("grif2list midas_input_data list_output_data map min_TSUP max_TSUP\n");
      printf("This code aims to convert and clean .mid files into .list\n");
      exit(-1);
    }  

  min_TSUP=atoi(argv[4]);
  max_TSUP=atoi(argv[5]);
  
  if((out=fopen(argv[2],"w"))==NULL)
    {
      printf("ERROR!!! I can't open %s for writing!\n",argv[2]);
      exit(-2);
    }

  printf("Program generates an ordered list of fragments in GRIF3/GRIF4 format from a midas file.\n");
  printf("Current parameters: min_TSUP = %d, and max_TSUP = %d\n", min_TSUP, max_TSUP);

  sort_and_assemble(argv[1],argv[3]);
  fclose(out);

  printf("Total fragments counted: %d\n", total_FRAGMENTS);
  printf("\nIn the order of appearance in state-machine:\n");
  printf("Total fragments dropped by being off-map: %d\n", map_DROPPED);
  printf("Total fragments dropped by pileup != 1: %d\n", pileup_DROPPED);
  printf("Total fragments dropped by CFD <= 5: %d\n", cfd_DROPPED);
  printf("Total fragments dropped by tsup == 0: %d\n", zero_DROPPED);  
  printf("Total fragments dropped by minmax_TSUP: %d\n", minmax_DROPPED);
  printf("\nTotal fragments dropped: %d\n", (minmax_DROPPED+pileup_DROPPED+map_DROPPED+cfd_DROPPED+zero_DROPPED));
  printf("Percentage dropped: %.2f%%\n", (100*((float)(minmax_DROPPED+pileup_DROPPED+map_DROPPED+cfd_DROPPED+zero_DROPPED))/((float)(total_FRAGMENTS))));

  //TIMEKEEPING
  end=clock();
  time=(double)(end-start)/CLOCKS_PER_SEC;
  printf("\nSorting time %8.2f seconds\n",time);
}
