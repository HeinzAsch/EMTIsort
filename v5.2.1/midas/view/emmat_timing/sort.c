#include "sort.h"
/*================================================================*/
int analyze_emmat_fragment(emmat_event* ptr)
{
  unsigned long long ts;
  
  if(ptr->tshigh<last)
    wrap++;

  ts=0x100000000*wrap;
  ts+=(ptr->tshigh)<<5;
  ts+=ptr->tslow;
  ts/=2;
  
  printf("=Event %8.8lld===================================================\n",counter);
  printf("     Time Stamp Low       :   %16u         0x%8.8x\n",ptr->tslow,ptr->tslow);
  printf("     Time Stamp High      :   %16u         0x%8.8x\n",ptr->tshigh,ptr->tshigh);
  printf("     Wrap                 :   %16d         0x%8.8x\n",wrap,wrap);
  printf("     Time Stamp [samples] :   %16llu 0x%16.16llx\n",ts,ts);
  printf("     Time Stamp [ns]      :   %16llu 0x%16.16llx\n",50*ts,50*ts);
  

  last=ptr->tshigh;
  
  counter++;
  return 0;
}

/*================================================================*/
int main(int argc, char *argv[])
{
  int wrapStart;
  
  counter=0;
  wrap=0;
  last=0;

  if((argc!=2)&&(argc!=3))
    {
      printf("view_emmat_fragment midas_input_data [wrap]\n");
      printf("wrap defaults to 0, but may be a larger for subruns beyond the zeroth.\n");
      printf("This corrects the clock resetting, and should be >=0.\n");
      exit(-1);
    }

  if(argc==3)
    if(atoi(argv[2])>=0)
      wrap=atoi(argv[2]);
    
  wrapStart=wrap;
  
  /* do sorting */
  sort_but_not_assemble(argv[1]);
  printf("Program provides information on consecutive fragments.\n");

  printf("\nFile began with wrap = %d\n",wrapStart);
  printf("File ended with wrap = %d\n",wrap);
}
