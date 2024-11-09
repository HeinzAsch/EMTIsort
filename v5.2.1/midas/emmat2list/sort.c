#include "sort.h"

int analyze_list(int limit,int offset,etnode* list)
{
 
 
  et_store_list(limit,list,out);

  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  clock_t start,end;
  double time;

  wrap=0;
  tslast=0;
  
  
  if(argc!=4)
    {
      printf("emmat2list midas_input_data list_output_data map\n");
      printf("This code aims to convert and clean .mid files into .list");
      exit(-1);
    }


  if((out=fopen(argv[2],"w"))==NULL)
    {
      printf("ERROR!!! I can't open %s for writing!\n",argv[2]);
      exit(-2);
    }

  printf("Program generates an ordered list of fragments in GRIF3/GRIF4 format from a midas file.\n");
  
  start=clock();
  sort_and_assemble(argv[1],argv[3]);
  end=clock();
  time=(double)(end-start)/CLOCKS_PER_SEC;

  fclose(out);
  printf("Sorting time %8.2f seconds\n",time);

  printf("Total fragments counted: %d\n", total_FRAGMENTS);
  
}
