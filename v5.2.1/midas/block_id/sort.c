#include "sort.h"

/*================================================================*/
int get_fragments(long* proc)
{
   int *bank_data, items;
   char *bank_name;
   int i;
   int found;
   
  /* loop over banks, print name  */
   while(1){
     if( (items = next_bank( &bank_name, &bank_data )) < 0 ){ return(-1); }

     if(blocks==NULL)
       {
	 nbid=1;
	 blocks=(struct bid*) malloc(sizeof(bid));
	 strcpy(blocks[0].name,bank_name);
	 blocks[0].cts=1;
       }

     found=0;
     for(i=0;i<nbid;i++)
       {
	 
       	 if(strcmp(bank_name,blocks[i].name)==0)
	   {
	     blocks[i].cts++;
	     found=1;
	   }
       }
     
     if(found==0)
       {
	 nbid++;
	 blocks=(struct bid*) realloc((struct bid*)blocks,nbid*sizeof(bid));
	 strcpy(blocks[nbid-1].name,bank_name);
	 blocks[nbid-1].cts=1;
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
  long sum;
  
  int state=END_OF_RECORD;
  if(argc!=2)
    {
      printf("midas_block_id midas_input_data\n");
      printf("Program prints bank identifiers in a midas file\n");
      exit(-1);
    }

   /* open the input file*/
  if((input=fopen(argv[1],"r"))==NULL)
    {
      printf("\nI can't open input file %s\n",argv[1]);
      exit(-2);
    }

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
      if(get_fragments(&proc) < 0 ){ state = NEXT_EVENT;}
      else { state = GET_FRAGMENTS; }
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

  sum=0;
  for(int i=0;i<nbid;i++)
    {
      sum+=blocks[i].cts;
    }

  printf("Found %8ld midas banks\n",sum);
  printf("Found       %2d midas bank types\n",nbid);

  
  for(int i=0;i<nbid;i++)
    {
      printf("bank %s counts %ld\n",blocks[i].name,blocks[i].cts);
    }

  return 0; 

  
}
