#include "sort.h"
int  print_sclr_sum(int *data, int n)
{
  unsigned long long ts;

  if(last>(unsigned int)data[0])
    wrap++;
  
  ts=0x100000000;
  ts*=wrap;
  ts+=(unsigned int)data[0];
  printf("=Scaler sum bank %8.8ld=============================================\n",counter);
  printf("     Time Stamp:   %16llu         0x%16.16llx\n",ts,ts);
  printf("           Wrap:   %16u                 0x%8.8x\n",wrap,wrap);
  printf("       Scaler T:   %16u                 0x%8.8x\n",data[0],data[0]);
  printf("       Scaler A:   %16u                 0x%8.8x\n",data[1],data[1]);
  printf("       Scaler B:   %16u                 0x%8.8x\n",data[2],data[2]);
  printf("       Scaler C:   %16u                 0x%8.8x\n",data[3],data[3]);
  printf("       Scaler D:   %16u                 0x%8.8x\n",data[5],data[5]);

  last=data[0];
  /* printf("Press ENTER to continue\n"); */
  /* getc(stdin); */
  
  return 0;
}
/*================================================================*/
int get_fragments(long* proc)
{
   int *bank_data, items;
   char *bank_name;

  /* loop over banks, looking for the good ones (or others ...)  */
   while(1){
      if( (items = next_bank( &bank_name, &bank_data )) < 0 ){ return(-1); }
   
 
      if(strcmp(bank_name,"SSUM")==0)
	{ 
	  swapInt( (char *)bank_data, items*sizeof(int) );
	  print_sclr_sum(bank_data, items);
	  counter++;
	}
      
      (*proc)++;
   }
   
   return(-1); /* go to next event */
}

      
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* input;
  long proc=0;
  int stop=0;
  int state=END_OF_RECORD;
  if(argc!=2)
    {
      printf("midas_sclr_sum midas_input_data\n");
      printf("Program prints data from summing scalers in the midas file\n");
      exit(-1);
    }

   /* open the input file*/
  if((input=fopen(argv[1],"r"))==NULL)
    {
      printf("\nI can't open input file %s\n",argv[1]);
      exit(-2);
    }

  counter=0;
  wrap=0;
  last=0;
  
  while(stop==0){
    switch(state){
    case END_OF_RECORD:
      if( next_record(input) <= 0 ){ state = END_OF_FILE;}
      else {state = NEXT_EVENT;}
      break;
    case NEXT_EVENT:
      if( next_event() < 0 ){ state = END_OF_RECORD; }
      else { state = GET_FRAGMENTS; }
      break;
    case GET_FRAGMENTS:
      if( get_fragments(&proc) < 0 ){ state = NEXT_EVENT;}
      else { state = GET_FRAGMENTS;  }
      break;
    case END_OF_FILE:
      fclose(input);
      printf("\n Number of analyzed fragments is %8ld\n",proc);
      printf("\n");
      stop=1;
      break;
    default:
      printf("Unknown case\n");
      exit(0);
      break;
    }
  }
  
  return 0; 
}
