#include "sort_and_assemble_emmaalist.h"

/*================================================================*/
int sort_list(ea_data_pointers* dp, eanode* list)
{
  int i;
  eanode store;
  //position the last element in the right spot
  if(dp->last-1==0)//at the start, nothing to order
    {
      //     printf("on start, no sorting\n");
      return 1;
    }
  
  if(list[dp->last-1].tsns>=list[dp->last-2].tsns)//already in order, do nothing
     {
       //    printf("in order\n");
       return 1;
     } 

 
  memcpy(&store,&list[dp->last-1],sizeof(eanode));//store the last element

  if(dp->last>S8K)
    i=store.tsns/list[dp->last-S1K].tsns*(dp->last-S1K);//approximate position
  else
    i=dp->last-2;//pointer to the position before the last added element
  
  while(store.tsns>list[i].tsns)
    i++;  

  while(store.tsns<list[i].tsns)
    {
      i--;
      if(i==-1) break;
    }
  
  if(i==-1)//shift the whole list
    {
      memmove(&list[1],&list[0],(dp->last-1)*sizeof(eanode));
      memcpy(&list[0],&store,sizeof(eanode));
      return 1;
    }
 
  memmove(&list[i+2],&list[i+1],(dp->last-i-1)*sizeof(eanode));
  memcpy(&list[i+1],&store,sizeof(eanode));

  return 1;
}

/*================================================================*/
int add_eanode(eanode* nd, ea_data_pointers* dp, eanode* list)
{

    if(dp->last==DEPTH)
    {
      memmove(&list[0],&list[SHIFT],(DEPTH-SHIFT)*sizeof(eanode));
      memset(&list[DEPTH-SHIFT],0,SHIFT*dp->son);    
      dp->last-=SHIFT;
      dp->trig+=SHIFT;  
    }

  //if early tsns comes after shifts, warn and terminate
  if(dp->trig!=0)
    if(nd->tsns<list[0].tsns)
      {
	printf("Reconstruction error, early tsns comes late\n");
	printf("Tsns  %16lld  first tsns on list %16lld last tsns on the list %16lld\n",nd->tsns,list[0].tsns,list[dp->last-1].tsns);
	printf("Correct DEPTH and SHIFT, recompile, try again\n");
	printf("Exiting\n");
	exit(0);
      }
 

  memcpy(&list[dp->last],nd,dp->son);
  dp->last++;
  sort_list(dp,list);

  //  print_list(dp->last,0,list);getc(stdin);
  return 0;
}

/*================================================================*/
int analyze_fragment_for_assembly(emmaa_event* ptr, ea_data_pointers* dp, eanode* list,gmap* map)
{
  
  long long tsns;
  eanode nd;
   
 
  tsns=ptr->tshigh;
  tsns*=0x40000000;
  tsns+=+ptr->tslow;
  tsns*=50;
 
  nd.tsns=tsns;
  nd.trig_tsns=0x000000000000; 
  nd.trig=-1;

  nd.trignum=-1;
  nd.tsup=ptr->tshigh;
  nd.ts=ptr->tslow;

  //PGAC Anode
  nd.anodeTop=ptr->adc[0];
  nd.anodeMiddle=ptr->adc[1];
  nd.anodeBottom=ptr->adc[2];

  //SSB
  nd.SSB=ptr->adc[3];

  //IC
  nd.IC[0]=ptr->adc[16];
  nd.IC[1]=ptr->adc[17];
  nd.IC[2]=ptr->adc[18];
  nd.IC[3]=ptr->adc[19];
      
  total_FRAGMENTS++;

  add_eanode(&nd,dp,list);
 
  return 0;
}

/*================================================================*/
void sort_and_assemble(char* inp_name, char* map_name)
{
  FILE* input;
  int state=END_OF_RECORD;
  int stop=0;
  static gmap    map;
  ea_data_pointers* dp=NULL;
  eanode*          list;

 /* open the input file*/
  if((input=fopen(inp_name,"r"))==NULL)
    {
      printf("\nI can't open input file %s\n",inp_name);
      exit(-2);
    }
 
  /*initialize the sort */
  dp=(ea_data_pointers*)malloc(sizeof(ea_data_pointers));
  dp->proc=0;
  dp->son=sizeof(eanode);
  dp->last=0;
  dp->trig=0;

  printf("Allocating %ld MB of RAM for reconstructing events\n",DEPTH*dp->son/sizeof(char)/1024/1024);

  list=(eanode*) malloc(DEPTH*dp->son);
  memset(list,0,DEPTH*dp->son);

  /* get the map */
  read_map(map_name,&map);
  
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
      if( get_fragments_for_assembly(dp,list,&map) < 0 )
	{ state = NEXT_EVENT;}
      else
	{ state = GET_FRAGMENTS;  }
      break;
    case END_OF_FILE:
      fclose(input);
      printf("\n Number of analyzed midas banks is %8ld\n",dp->proc);
      printf("\n");
      analyze_list(dp->last,dp->trig,list);
      stop=1;
      break;
    default:
      printf("Unknown case\n");
      exit(0);
      break;
    }
  }
}
  


/*================================================================*/
int get_fragments_for_assembly(ea_data_pointers* dp, eanode* list,gmap *map)
{
  int *bank_data, items;
  char *bank_name;
  
  
  /* loop over banks, looking for EMMA time data  */
  while(1)
    {
      if((items = next_bank( &bank_name, &bank_data )) < 0 ){ return(-1);}
      if( strcmp(bank_name,"MADC") == 0 )
	{
	  swapInt( (char *)bank_data, items*sizeof(int) );
	  unpack_emmaa_bank_for_assembly( bank_data, items, dp, list, map);
	  
	  if((dp->proc%10000)==0){printf("Number of analyzed EMMAA banks is %8ld\r",dp->proc);}    
	  dp->proc++;
	}
    }
   return(-1); /* go to next event */
}

/*================================================================*/
int unpack_emmaa_bank_for_assembly(int *data, int length, ea_data_pointers* dp, eanode* list, gmap* map)
{
 
   unsigned int *evntbuf = (unsigned *)data;
   emmaa_event emmaa_event;

   if(unpack_emmaa_event(evntbuf, length, &emmaa_event)==0)
     analyze_fragment_for_assembly(&emmaa_event,dp,list,map);


   return(0); 
}

