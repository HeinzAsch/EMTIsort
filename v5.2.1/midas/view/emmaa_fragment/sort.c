#include "sort.h"
/*================================================================*/
int analyze_emmaa_fragment(emmaa_event* ptr)
{
  unsigned long long ts;
  int i;
 
  
  ts=ptr->tshigh;
  ts*=0x40000000;
  ts+=+ptr->tslow;

 printf("=Event %8.8lld===================================================\n",counter);
 printf("Time Stamp Low               :   %16u         0x%8.8x\n",ptr->tslow,ptr->tslow);
 printf("Time Stamp High              :   %16u         0x%8.8x\n",ptr->tshigh,ptr->tshigh);
 printf("\n");
 printf("Time Stamp [samples]         :   %16llu 0x%16.16llx\n",ts,ts);
 printf("Time Stamp [ns]              :   %16llu 0x%16.16llx\n",50*ts,50*ts);
 printf("ADC fold                     :   %16u         0x%8.8x\n",ptr->adcfold,ptr->adcfold);
 printf("ADC hit pattern              :   %16u         0x%8.8x\n",ptr->adchitpattern,ptr->adchitpattern);
 for(i=0;i<32;i++)
   if(((ptr->adchitpattern)&(1<<i))!=0)
     printf("ADC value for channel %2d     :   %16u         0x%8.8x\n",i,ptr->adc[i],ptr->adc[i]);
   
     
 printf("Press ENTER to continue\n");
 getc(stdin);
 counter++;
  return 0;
}

/*================================================================*/
int main(int argc, char *argv[])
{
 
  counter=0;
  
  if(argc!=2)
    {
      printf("view_emmaa_fragment midas_input_data\n");
      exit(-1);
    }
 
  /* do sorting */
  sort_but_not_assemble(argv[1]);
  printf("Program provides information on consecutive fragments.\n");
}
