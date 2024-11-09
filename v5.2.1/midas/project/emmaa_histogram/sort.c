#include "sort.h"
/*================================================================*/
int analyze_emmaa_fragment(emmaa_event* ptr)
{
  int ch;
  signed long long adc_val;
  
  for(ch=0;ch<32;ch++)
    if(((ptr->adchitpattern)&(1<<ch))!=0)
      {
	adc_val = ptr->adc[ch];//Grab the current channel's ADC value
	hist[ch][adc_val]++;
	counter[ch]++;
      }
  
  return 0;
}

/*================================================================*/
int main(int argc, char *argv[])
{
  //TIMEKEEPING
  clock_t start, end;
  double timer;
  start=clock();

  int ch;
  FILE *output;

  if(argc!=2)
    {
      printf("view_emmat_fragment midas_input_data\n");
      printf("Program provides information on EMMA ADC outputs.\n");
      printf("Results are stored in: emmaa_histogram.spn\n");
      exit(-1);
    }

  memset(hist,0,sizeof(hist));
  memset(counter,0,sizeof(counter));
    
  /* do sorting */
  sort_but_not_assemble(argv[1]);  

  if((output=fopen("emmaa_histogram.spn","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file!\n");
      exit(EXIT_FAILURE);
    }      
  for(ch=0;ch<32;ch++)
    fwrite(hist[ch],S4K*sizeof(int),1,output);
  fclose(output);  

  printf("\nCounts per channel:\n");
  for(ch=0;ch<32;ch++)
    printf("Channel %2d has: %10d\n",ch,counter[ch]);
  
  //TIMEKEEPING
  end=clock();
  timer=(double)(end-start)/CLOCKS_PER_SEC;
  printf("\nSorting time %8.2f seconds\n",timer);
}
