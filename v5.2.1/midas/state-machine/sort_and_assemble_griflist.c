#include "sort_and_assemble_griflist.h"

/*================================================================*/
int sort_list(data_pointers* dp, node* list)
{
  int i;
  node store;
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

 
  memcpy(&store,&list[dp->last-1],sizeof(node));//store the last element

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
      memmove(&list[1],&list[0],(dp->last-1)*sizeof(node));
      memcpy(&list[0],&store,sizeof(node));
      return 1;
    }
 
  memmove(&list[i+2],&list[i+1],(dp->last-i-1)*sizeof(node));
  memcpy(&list[i+1],&store,sizeof(node));

  return 1;
}
/*================================================================*/
/* void sort_and_assemble_subruns(char* subrun_list_name, char* map_name) */
/* { */
/*   FILE* subrun_list; */
/*   FILE* input; */
/*   char name[132]; */
/*   static gmap map; */
/*   int state=END_OF_RECORD; */
/*   int stop=0; */
/*   data_pointers* dp=NULL; */
/*   node*          list; */

/*  /\* open the list of subrun midas files *\/ */
/*   if((subrun_list=fopen(subrun_list_name,"r"))==NULL) */
/*     { */
/*       printf("ERROR!!! I can't open the subrun midas file list!\n"); */
/*       exit(-2); */
/*     } */

/*   /\* read name of first input file *\/ */
/*   if(fscanf(subrun_list,"%s",name)==EOF) */
/*     { */
/*       printf("ERROR!!! the subrun file name not read properly!\n"); */
/*       exit(-2); */
/*     } */

/*  /\* open the first input file*\/ */
/*   if((input=fopen(name,"r"))==NULL) */
/*     { */
/*       printf("\nI can't open input file %s\n",name); */
/*       exit(-2); */
/*     } */
/*    /\*initialize the sort *\/ */
/*   dp=(data_pointers*)malloc(sizeof(data_pointers)); */
/*   dp->proc=0; */
/*   dp->son=sizeof(node); */
/*   dp->last=0; */
/*   dp->trig=0; */

  
/*   printf("Allocating %ld MB of RAM for reconstructing events\n",DEPTH*dp->son/sizeof(char)/1024/1024); */

/*   list=(node*) malloc(DEPTH*dp->son); */
/*   memset(list,0,DEPTH*dp->son); */

/* /\* get the map *\/ */
/*   read_map(map_name,&map); */
  
/*   while(stop==0){ */
/*     switch(state){ */
/*     case END_OF_RECORD: */
/*       if( next_record(input) <= 0 ){ state = END_OF_FILE;} */
/*       else {state = NEXT_EVENT;} */
/*       break; */
/*     case NEXT_EVENT: */
/*       if( next_event() < 0 ){ state = END_OF_RECORD; } */
/*       else { state = GET_FRAGMENTS; } */
/*       break; */
/*     case GET_FRAGMENTS: */
/*       if( get_fragments_for_assembly(dp,list,&map) < 0 ) */
/* 	{ state = NEXT_EVENT;} */
/*       else { state = GET_FRAGMENTS;  } */
/*       break; */
/*     case END_OF_FILE: */
/*       fclose(input); */
/*       printf("\n Number of analyzed midas banks is %8ld\n",dp->proc); */
/*       printf("\n"); */
/*       /\* read the name of the next input file *\/ */
/*       if(fscanf(subrun_list,"%s",name)==EOF){ state = END_OF_SORT; } */
/*       else */
/* 	{ */
/* 	  /\* open the next file *\/ */
/* 	  if((input=fopen(name,"r"))==NULL) */
/* 	    { */
/* 	      printf("\nI can't open input file %s\n",name); */
/* 	      exit(-2); */
/* 	    } */
/* 	  /\* sort next file *\/ */
/* 	  state = END_OF_RECORD; */
/* 	} */
/*       break; */
/*     case END_OF_SORT: */
/*       /\* close the midas list *\/ */
/*       fclose(subrun_list); */
/*       /\* analyze the last data assembly buffer *\/ */
/*       analyze_list(dp->last,dp->trig,list);   */
/*       stop=1; */
/*       break; */
/*     default: */
/*       printf("Unknown case\n"); */
/*       exit(0); */
/*       break; */
/*     } */
/*   } */

  
/* } */
/*================================================================*/
int add_node(node* nd, data_pointers* dp, node* list)
{

    if(dp->last==DEPTH)
    {
      memmove(&list[0],&list[SHIFT],(DEPTH-SHIFT)*sizeof(node));
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
int analyze_fragment_for_assembly(Grif_event* ptr, short* waveform,data_pointers* dp, node* list,gmap* map)
{
  long long tsns;
  node nd;
  WaveFormPar wpar;
  int d;
  
  //CFD timing from online DAQ CFD
  tsns=(ptr->timestamp&0xfffffffffffc0000)<<4;
  tsns+=ptr->cfd;
  tsns*=10;
  tsns/=16;
  nd.tsns=tsns;

  nd.trig_tsns=0x000000000000;
  //nd.csi_tsns=0x000000000000;

  // nd.ts=ptr->timestamp;
  nd.ch.cfd=ptr->cfd;
  nd.chan=ptr->chan;
  nd.ch.charge=ptr->energy;
  nd.ch.timestamp=(int)(ptr->timestamp&0xffffffff);
  nd.ch.timestamp_up=(int)((ptr->timestamp>>32)&0xffff);
  nd.trig=-1;
  nd.tig_trig=-1;
  nd.csi_trig=-1;
  nd.emm_trig=-1;
  memset(&nd.wfit,0,sizeof(ShapePar));

  //verify that upper bits of the timestamp, tsup, is being correctly written by the DAQ
  //this chunk of code relies on set up that occurs in midas2list
  //initialization should have prev_TSUP = 0 and max_TSUP < 0

  total_FRAGMENTS++;

  if(ptr->pileup!=1)
    if(ptr->chan!=map->emma_channel)
      {
	pileup_DROPPED++;
	return 0;
      }
  
  /* if(buffer_TSUP>=0) */
  /*   { */
  /*     if(nd.ch.timestamp_up>=buffer_TSUP) */
  /* 	{ */
  /* 	  printf("Dropping fragment from previous run as %d >= %d.\n", nd.ch.timestamp_up, buffer_TSUP); */
  /* 	  buffer_DROPPED++; */
  /* 	  return 0; */
  /* 	} */

  /*     buffer_TSUP=-1; */
  /*     printf("The dropped buffer should be %d fragments long.\n", buffer_DROPPED); */
  /*     prev_TSUP=nd.ch.timestamp_up; */
  /*     printf("The first prev_TSUP value has been set to %d\n", prev_TSUP); */
  /*   } */
  
  if((min_TSUP>=0)&&(max_TSUP>=0))
    if((nd.ch.timestamp_up<min_TSUP)||(nd.ch.timestamp_up>max_TSUP))
      {
	/* printf("Dropping fragment due to an incorrect tsup value.\n"); */
	/* printf("TSUP: %d is not in range: [%d, %d]\n", nd.ch.timestamp_up, min_TSUP, max_TSUP); */
	minmax_DROPPED++;
	return 0;
      }

  /* if(prev_TSUP>=0) */
  /*   { */
  /*     if(abs(nd.ch.timestamp_up-prev_TSUP)>1) */
  /* 	{ */
  /* 	  printf("Dropping fragment due to an incorrect tsup value.\n"); */
  /* 	  printf("Current TSUP %d and previous TSUP %d differ by a magnitude larger than 1\n", nd.ch.timestamp_up, prev_TSUP); */
  /* 	  //printf("Value tested: %d\n", abs(prev_TSUP-nd.ch.timestamp_up)); */
  /* 	  prev_DROPPED++; */
  /* 	  return 0; */
  /* 	} */

  /*     if(min_TSUP==0) */
  /* 	if(prev_TSUP==1) */
  /* 	  if(nd.ch.timestamp_up==1) */
  /* 	    min_TSUP++; */

  /*     prev_TSUP=nd.ch.timestamp_up;  */
  /*   }   */
      
  
  
  //for TIP channels do the fits
  if(nd.chan>=map->csiarray_min)
    if(nd.chan<=map->csiarray_max)
      if(map->csiarray_fit==1)
	if(map->csi_lt[nd.chan-map->csiarray_min]>0)
	  if(map->csi_lt[nd.chan-map->csiarray_min]<NCSI)
	    if((d=ptr->waveform_length)!=0)
	      {
		nd.wfit.t[1]=map->csiarray_trc; //set tRC
		nd.wfit.t[2]=map->csiarray_tf; //set tF
		nd.wfit.t[3]=map->csiarray_ts; //set tS
		nd.wfit.t[4]=map->csiarray_tr; //set tGamma
		fit_CsI_waveform(d,waveform,&nd.wfit,&wpar);
		//for a fit with type>0 overwrite the timing with the t0 from fit
		if(nd.wfit.type>0)
		  {
		    //		    printf("Old tsns %16lld   ",tsns);
		    tsns=(long long)(10.*((double)ptr->timestamp+nd.wfit.t[0]-(double)map->csiarray_pretrig));
		    if(tsns<0)
		      {
			printf("Dropping fragment with tsns = %lld as derived from TIP fit.\n",tsns);
			return 0;
		      }
		    nd.tsns=tsns;
		    //		    printf("New tsns %16lld\n",tsns);
		    //		    getc(stdin);
		  }
		
		/* print_ShapePar(&nd.wfit); */
		/* getc(stdin); */
	      }
	      
  /* if(nd.ch.cfd<2) */
  /*   return 0; */
  
  add_node(&nd,dp,list);
 

  return 0;
}

/*================================================================*/
void sort_and_assemble(char* inp_name, char* map_name)
{
  FILE* input;
  int state=END_OF_RECORD;
  int stop=0;
  static gmap    map;
  data_pointers* dp=NULL;
  node*          list;

 /* open the input file*/
  if((input=fopen(inp_name,"r"))==NULL)
    {
      printf("\nI can't open input file %s\n",inp_name);
      exit(-2);
    }
 
  /*initialize the sort */
  dp=(data_pointers*)malloc(sizeof(data_pointers));
  dp->proc=0;
  dp->son=sizeof(node);
  dp->last=0;
  dp->trig=0;

  printf("Allocating %ld MB of RAM for reconstructing events\n",DEPTH*dp->son/sizeof(char)/1024/1024);

  list=(node*) malloc(DEPTH*dp->son);
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
int get_fragments_for_assembly(data_pointers* dp, node* list,gmap *map)
{
  int *bank_data, items;
  char *bank_name;
  
  
  /* loop over banks, looking for GRFFIN   */
  while(1)
    {
      if((items = next_bank( &bank_name, &bank_data )) < 0 ){ return(-1);}
      if( strcmp(bank_name,"GRF3") == 0 || strcmp(bank_name,"GRF4") == 0)
	{
	  swapInt( (char *)bank_data, items*sizeof(int) );
	  
	  unpack_grif_bank_for_assembly( bank_data, items, dp, list, map);
	  
	  if((dp->proc%10000)==0){printf("Number of analyzed GRF3/GRF4 banks is %8ld\r",dp->proc);}    
	  dp->proc++;
	}
    }
   return(-1); /* go to next event */
}

/*================================================================*/
int unpack_grif_bank_for_assembly(int *data, int length, data_pointers* dp, node* list, gmap* map)
{
 
   unsigned int *evntbufend = (unsigned *)data + length;
   unsigned int *evntbuf = (unsigned *)data;
   unsigned *ptr = evntbuf;
   Grif_event grif_event;
   short waveform[MAX_SAMPLE_LEN];
   int process_waveforms=1;
 
   while( evntbuf < evntbufend ) //scan the bank until the end given by length
     if( ((*(ptr++)>>28)&0xff) == 0xE )//advance the ptr until the end of the header
       {
	 //unpack if the end of the header has been reached
	 if(unpack_grif3_event(evntbuf, ptr-evntbuf, &grif_event, process_waveforms,waveform)==0)
	   analyze_fragment_for_assembly(&grif_event,waveform,dp,list,map);
	   
	 evntbuf=ptr;

       }
   

   return(0); 
}
