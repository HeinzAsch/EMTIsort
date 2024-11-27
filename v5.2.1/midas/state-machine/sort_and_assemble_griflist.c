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
int add_node(node* nd, data_pointers* dp, node* list)
{

    if(dp->last==DEPTH)
    {
      analyze_list(SHIFT,0,list);
      memmove(&list[0],&list[SHIFT],(DEPTH-SHIFT)*sizeof(node));
      memset(&list[DEPTH-SHIFT],0,SHIFT*dp->son);    
      dp->last-=SHIFT;
      dp->trig+=SHIFT;  
    }

  //if early tsns comes after shifts, warn and terminate
  if(dp->trig!=0)
    if(nd->tsns<list[0].tsns)
      {
	printf("\nReconstruction error, early tsns comes late\n");
	printf("Tsns  %16lld  first tsns on list %16lld last tsns on the list %16lld\n",nd->tsns,list[0].tsns,list[dp->last-1].tsns);
	printf("tsup is: %d, tslow is: %d, cfd is %d.\n",nd->ch.timestamp_up,nd->ch.timestamp,nd->ch.cfd);
	printf("\nCorrect DEPTH and SHIFT, recompile, try again\n");
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

  //Verify the given fragment even exists on the map
  nd.chan=ptr->chan;  
  if(isonmap(&nd,map)!=1)
    {
      map_DROPPED++;
      return 0;
    }

  //Drop fragments with pileup
  if(ptr->pileup!=1)
    if(ptr->chan!=map->emma_channel)
      {
	pileup_DROPPED++;
	return 0;
      }

  //Make sure the CFD value is valid, CFD <= 5 corresponds to malformed fragments
  if(ptr->cfd<=5)
    {
      cfd_DROPPED++;
      return 0;
    }    
  
  //Grab timestamps to verify the timing information is valid
  nd.ch.timestamp=(int)(ptr->timestamp&0xffffffff);
  nd.ch.timestamp_up=(int)((ptr->timestamp>>32)&0xffff);

  //Establish the first valid prev_TSUP
  if(prev_TSUP<0) //Should be initialized as -1
    {
      if((min_TSUP>=0)&&(max_TSUP>=0))
	if((nd.ch.timestamp_up>=min_TSUP)&&(nd.ch.timestamp_up<=max_TSUP))
	  {	
	    prev_TSUP = nd.ch.timestamp_up;
	  }
    }
  else //Check if the current fragment has a broken tsup
    if(nd.ch.timestamp_up==0) //By this point, we know it's on the map, has CFD>0, and isn't pileup
      if(prev_TSUP>1)//>1 since the boundary between real tsup=0 and tsup=1 isn't smooth and may hurt more than it helps
	{
	  //nd.ch.timestamp_up=prev_TSUP;
	  //printf("Reconstructed tsup for fragment with tsup = %d and tslow = %d and cfd = %d\n",nd.ch.timestamp_up,nd.ch.timestamp,ptr->cfd);
	  //printf("Dropped fragment with tsup = %d and tslow = %d and cfd = %d since prev_TSUP = %d\n",nd.ch.timestamp_up,nd.ch.timestamp,ptr->cfd,prev_TSUP);
	  printf("Dropped misplaced fragment with tsup = 0\n");// and tslow = %d and cfd = %d since prev_TSUP = %d\n",nd.ch.timestamp_up,nd.ch.timestamp,ptr->cfd,prev_TSUP);
	  zero_DROPPED++;
	  return 0;
	}

  //Drop bursts of events or events leftover in buffer from outside of the valid tsup range
  if((min_TSUP>=0)&&(max_TSUP>=0))
    if((nd.ch.timestamp_up<min_TSUP)||(nd.ch.timestamp_up>max_TSUP))
      {
	printf("Dropped out-of-range fragment with tsup = %d\n",nd.ch.timestamp_up);
	minmax_DROPPED++;
	return 0;
      }
   
  //Update prev_TSUP
  if(nd.ch.timestamp_up>prev_TSUP)
    prev_TSUP++; 

  tsns=(ptr->timestamp&0xfffffffffffc0000)<<4;
  tsns+=ptr->cfd;
  tsns*=10;
  tsns/=16;
  nd.tsns=tsns;
  
  nd.trig_tsns=0x000000000000;  

  nd.ch.cfd=ptr->cfd; 
  nd.ch.charge=ptr->energy;
  nd.trig=-1;
  nd.tig_trig=-1;
  nd.csi_trig=-1;
  nd.emm_trig=-1;
  memset(&nd.wfit,0,sizeof(ShapePar));
    
  //for TIP channels do the fits
  if(map->csiarray_fit==1)
    {
      if((d=ptr->waveform_length)!=0)
	if(TIP_channel(&nd,map)==1)
	  {
	    nd.wfit.t[1]=map->csiarray_trc; //set tRC
	    nd.wfit.t[2]=map->csiarray_tf; //set tF
	    nd.wfit.t[3]=map->csiarray_ts; //set tS
	    nd.wfit.t[4]=map->csiarray_tr; //set tGamma
	    fit_CsI_waveform(d,waveform,&nd.wfit,&wpar);
	    //for a fit with type>0 overwrite the timing with the t0 from fit
	    if(nd.wfit.type>0)
	      {		
		tsns=(long long)(10.*((double)ptr->timestamp+nd.wfit.t[0]-(double)map->csiarray_pretrig));		
		if(tsns<0)
		  {
		    printf("Dropping fragment with tsns = %lld as derived from TIP fit.\n",tsns);
		    return 0;
		  }
	      
		nd.tsns=tsns;
	      }
	  }
    }

  total_FRAGMENTS++;
  add_node(&nd,dp,list);
 
  return 0;
}

/*================================================================*/
void sort_and_assemble(char* inp_name, char* map_name)
{
  FILE* input;
  int state=END_OF_RECORD;
  int stop=0,status;
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
      if( next_record(input) <= 0 ){ state = END_OF_SORT;}
      else {state = NEXT_EVENT;}
      break;
    case NEXT_EVENT:
      if( next_event() < 0 )
	{ state = END_OF_RECORD; }
      else
	{ state = GET_FRAGMENTS; }
      break;
    case GET_FRAGMENTS:
      state = GET_FRAGMENTS;
      status=get_fragments_for_assembly(dp,list,&map);
      if(status>0)
	state = NEXT_EVENT;
      if(status==0)
	state = END_OF_SORT;
      break;
    case END_OF_SORT:
      fclose(input);
      printf("\n Number of analyzed midas banks is %8ld\n",dp->proc);
      printf("\n");
      //store_list doesn't use the 'offset' field.
      analyze_list(dp->last,dp->trig,list);//not convinced dp->trig is a relevant parameter here given how store_list works in grif2list
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
      if((items = next_bank( &bank_name, &bank_data )) < 0 ){ return(1);}
      if( strcmp(bank_name,"GRF3") == 0 || strcmp(bank_name,"GRF4") == 0)
	{
	  swapInt( (char *)bank_data, items*sizeof(int) );
	  
	  if(unpack_grif_bank_for_assembly( bank_data, items, dp, list, map)==-1)
	    return 0;//end of the sort
	  
	  if((dp->proc%10000)==0){printf("Number of analyzed GRF3/GRF4 banks is %8ld\r",dp->proc);}    
	  dp->proc++;
	}
    }
   return(1); /* go to next event */
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
	   if(analyze_fragment_for_assembly(&grif_event,waveform,dp,list,map)<0)
	     return -1;
	 evntbuf=ptr;

       }
   

   return(0); 
}

/*================================================================*/
int isonmap(node* node, gmap* map)
{
  int onmap=0;

  if(CC_channel(node,map)==1)
    onmap=1;

  if(Seg_channel(node,map)==1)
    onmap=1;

  if(Sup_channel(node,map)==1)
    onmap=1;

  if(TIP_channel(node,map)==1)
    onmap=1;

  if(EMMA_channel(node,map)==1)
    onmap=1;
  
  return onmap;
}
