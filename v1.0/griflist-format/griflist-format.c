#include "griflist-format.h"

/*================================================================*/
int print_list(int limit, int offset, node* list)
{
  int i;

  for(i=0;i<limit;i++)
    printf("Frag: %9d Ts[ns] %16u Ch %4d Ts_up %8u Ts %8u CFD %8u TigTrig %8d CsITrig %8d EMMATrig %8d TrigTs[ns] %16lld Trig %8d\n",i+offset,(unsigned int)list[i].tsns,list[i].chan,(unsigned int)list[i].ch.timestamp_up,(unsigned int)list[i].ch.timestamp,(unsigned int)list[i].ch.cfd,list[i].tig_trig,list[i].csi_trig,list[i].emm_trig,list[i].trig_tsns,list[i].trig);
  
  return 0;
}
/*================================================================*/
int store_list(int limit, node* list,FILE* out)
{
  int i;
  size_t son;
  son=sizeof(node);
  for(i=0;i<limit;i++)
    fwrite(&list[i],son,1,out);
  
  return 0;
}
/*================================================================*/
int same_HPGe(node* a, node* b, gmap* map)
{
  if(a->chan>=map->tig_min)
    if(a->chan<=map->tig_max)
      if((a->ch.timestamp|a->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->hpge_lt[a->chan-map->tig_min].pos>0)//valid position for a
	  if(map->hpge_lt[a->chan-map->tig_min].pos<NPOSTIGR)//valid position for a
	    if(b->chan>=map->tig_min)
	      if(b->chan<=map->tig_max)
		if((b->ch.timestamp|b->ch.timestamp_up)!=0)//ignore bad events at the start
		  if(map->hpge_lt[b->chan-map->tig_min].pos>0)//valid position for b
		    if(map->hpge_lt[b->chan-map->tig_min].pos<NPOSTIGR)//valid position for b
		      if(map->hpge_lt[a->chan-map->tig_min].pos==map->hpge_lt[b->chan-map->tig_min].pos)//same position
			if(map->hpge_lt[a->chan-map->tig_min].col==map->hpge_lt[b->chan-map->tig_min].col)//same color		      
			  return 1;
  
  return 0;	      
}
/*================================================================*/
int Seg_channel(node* curr, gmap* map)
{
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if((curr->ch.timestamp|curr->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->hpge_lt[curr->chan-map->tig_min].seg>0)//channel is a segment
	  if(map->hpge_lt[curr->chan-map->tig_min].seg<NSEGTIGR)//channel is a segment 
	    if(map->hpge_lt[curr->chan-map->tig_min].pos>0)//valid position
	      if(map->hpge_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//valid position
		return 1;
  
  return 0;	      
}
/*================================================================*/
int CC_channel(node* curr, gmap* map)
{
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if((curr->ch.timestamp|curr->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->hpge_lt[curr->chan-map->tig_min].seg==0)//channel is the central contact
	  if(map->hpge_lt[curr->chan-map->tig_min].pos>0)//valid position
	    if(map->hpge_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//valid position
	      if(map->hpge_lt[curr->chan-map->tig_min].col>=0)//valid color
		if(map->hpge_lt[curr->chan-map->tig_min].col<NCOL)//valid color      
	      return 1;
  
  return 0;	      
}
/*================================================================*/
int Sup_channel(node* curr, gmap* map)
{
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if((curr->ch.timestamp|curr->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->supp_lt[curr->chan-map->tig_min].seg>0)//channel is a BGO suppressor
	  if(map->supp_lt[curr->chan-map->tig_min].seg<NSUP)//channel is a BGO suppressor
	    if(map->supp_lt[curr->chan-map->tig_min].col>=0)//valid color
	      if(map->supp_lt[curr->chan-map->tig_min].col<NCOL)//valid color  
		if(map->supp_lt[curr->chan-map->tig_min].pos>0)//valid TIGRESS position
		  if(map->supp_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//valid TIGRESS position
		    return 1;
  
  return 0;	      
}
/*================================================================*/
int TIP_channel(node* curr, gmap* map)
{
  if(curr->chan>=map->csiarray_min)
    if(curr->chan<=map->csiarray_max)
      if((curr->ch.timestamp|curr->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->csi_lt[curr->chan-map->csiarray_min]>0)//channel is a valid TIP position
	  if(map->csi_lt[curr->chan-map->csiarray_min]<NCSI)//channel is a valid TIP position 
		return 1;
  
  return 0;	      
}
/*================================================================*/
int EMMA_channel(node* curr, gmap* map)
{
  if(curr->chan==map->emma_channel) return 1;
  return 0;	      
}
