#include "griflist-format.h"

int map_event(raw_event* data,node *ptr, gmap* map)
{

  unsigned long long tsns_min,tsns_max;
  int pos,col,seg;
  int take,id;
  unsigned long long int one=1;

  if(data->h.frag_fold==0)
    {
      data->h.trig_num=ptr->trig;
      	data->h.timestamp_min=ptr->tsns&0x00ffffff;
	data->h.timestamp_up_min=(ptr->tsns>>24)&0x00ffffff;
	data->h.timestamp_max=ptr->tsns&0x00ffffff;
	data->h.timestamp_up_max=(ptr->tsns>>24)&0x00ffffff;
    }
  
  
  if(data->h.trig_num!=ptr->trig)
    {
      printf("Error in mapping, wrong trigger %d %d\n", data->h.trig_num,ptr->trig);
      printf("Exiting\n");
      exit(0);
    }
  data->h.frag_fold++;

  tsns_min=(data->h.timestamp_up_min<<31)+data->h.timestamp_min;
  tsns_max=(data->h.timestamp_up_max<<31)+data->h.timestamp_max;


   if(tsns_min<ptr->tsns)
     {
	data->h.timestamp_min=ptr->tsns&0x00ffffff;
	data->h.timestamp_up_min=(ptr->tsns>>24)&0x00ffffff;
      }
   
   if(tsns_max>ptr->tsns)
     {
	data->h.timestamp_max=ptr->tsns&0x00ffffff;
	data->h.timestamp_up_max=(ptr->tsns>>24)&0x00ffffff;
      }
   
   /***************************** Start TIGRESS HPGe ***********************/
   if(ptr->chan>=map->tig_min)
     if(ptr->chan<=map->tig_max)
       {
	 take=0;
	 //map central contacts and segments
	 if((seg=map->hpge_lt[ptr->chan-map->tig_min].seg)>=0)//valid segment
	   if(seg<NSEGTIGR)//valid segment
	      if((pos=map->hpge_lt[ptr->chan-map->tig_min].pos)>0)//valid position
		if(pos<NPOSTIGR)//valid position
		  if((col=map->hpge_lt[ptr->chan-map->tig_min].col)>=0)//valid color
		    if(col<NCOL)//valid color  	       
		      {
			if(ptr->ch.charge>0)
			  {
			    //data->tg.det[pos].ge[col].seg[seg].charge=ptr->ch.charge;
			    data->tg.det[pos].ge[col].seg[seg].charge=ptr->ch.charge/map->tig_kpar;
			    data->tg.det[pos].ge[col].h.EHP|=(one<<seg);
			    data->tg.det[pos].ge[col].h.Efold++;
			    take|=1;
			  }

			if(ptr->ch.cfd>=0)
			  {			
			    data->tg.det[pos].ge[col].seg[seg].cfd=ptr->ch.cfd;
			    data->tg.det[pos].ge[col].h.THP|=(one<<seg);
			    data->tg.det[pos].ge[col].h.Tfold++;
			    take|=1;
			  }		
		      }
	 
	 if(take==1)
	   {
	     data->h.setupHP|=TIGRESS_BIT;
	     
	     data->tg.det[pos].ge[col].seg[seg].timestamp=ptr->ch.timestamp;
	     data->tg.det[pos].ge[col].seg[seg].timestamp_up=ptr->ch.timestamp_up;
	     data->tg.det[pos].ge[col].h.TSHP|=(one<<seg);
	     data->tg.det[pos].ge[col].h.TSfold++;

	     //count crystals
	     id=(pos-1)*NCOL+col;
	     if((data->tg.g.GeHP&(one<<id))==0)
	       {
		 data->tg.g.GeHP|=(one<<id);
		 data->tg.g.Gefold++;
	       }
	     if((data->tg.g.THP&(one<<id))==0)
	       {
		 data->tg.g.THP|=(one<<id);
		 data->tg.g.Tfold++;
	       }
	     //count positions
	     id=pos-1;
	     if((data->tg.g.PosHP&(one<<id))==0)
	       {
		 data->tg.g.PosHP|=(one<<id);
		 data->tg.g.Posfold++;
	       }
	     //count clovers
	     if((data->tg.h.GeHP&(one<<id))==0)
	       {
		 data->tg.h.GeHP|=(one<<id);
		 data->tg.h.Gefold++;
	       }
	     
	     //count crystals within a clover
	     if((data->tg.det[pos].h.GeHP&(one<<col))==0)
	       {
		 data->tg.det[pos].h.GeHP|=(one<<col);
		 data->tg.det[pos].h.Gefold++;
	       }
	     
	   }  
       }
   /***************************** End   TIGRESS HPGe ***********************/

   /***************************** Start TIGRESS BGO  ***********************/

  if(ptr->chan>=map->tig_min)
     if(ptr->chan<=map->tig_max)
       {
	 take=0;
	 if((seg=map->supp_lt[ptr->chan-map->tig_min].seg)>0)//valid segment
	   if(seg<NSUP)//valid segment
	      if((pos=map->supp_lt[ptr->chan-map->tig_min].pos)>0)//valid position
		if(pos<NPOSTIGR)//valid position
		  if((col=map->supp_lt[ptr->chan-map->tig_min].col)>=0)//valid color
		    if(col<NCOL)//valid color  	       
		      {
			if(ptr->ch.charge>0)
			  {
			    data->tg.det[pos].bgo[col].sup[seg].charge=ptr->ch.charge;
			    data->tg.det[pos].bgo[col].h.EHP|=(one<<seg);
			    data->tg.det[pos].bgo[col].h.Efold++;
			    take|=1;
			  }

			if(ptr->ch.cfd>=0)
			  {			
			    data->tg.det[pos].bgo[col].sup[seg].cfd=ptr->ch.cfd;
			    data->tg.det[pos].bgo[col].h.THP|=(one<<seg);
			    data->tg.det[pos].bgo[col].h.Tfold++;
			    take|=1;
			  }		
		      }

	 if(take==1)
	   {
	     data->h.setupHP|=TIGRESS_BIT;		      
	     data->tg.det[pos].bgo[col].sup[seg].timestamp=ptr->ch.timestamp;
	     data->tg.det[pos].bgo[col].sup[seg].timestamp_up=ptr->ch.timestamp_up;
	     data->tg.det[pos].bgo[col].h.TSHP|=(one<<seg);
	     data->tg.det[pos].bgo[col].h.TSfold++;
		      
	     //count crystals
	     id=(pos-1)*NCOL+col;
	     if((data->tg.g.BGOHP&(one<<id))==0)
	       {
		 data->tg.g.BGOHP|=(one<<id);
		 data->tg.g.BGOfold++;
	       }
	     if((data->tg.g.THP&(one<<id))==0)
	       {
		 data->tg.g.THP|=(one<<id);
		 data->tg.g.Tfold++;
	       }
	     //count positions
	     id=pos-1;
	     if((data->tg.g.PosHP&(one<<id))==0)
	       {
		 data->tg.g.PosHP|=(one<<id);
		 data->tg.g.Posfold++;
	       }
	     //count clovers
	     if((data->tg.h.BGOHP&(one<<id))==0)
	       {
		 data->tg.h.BGOHP|=(one<<id);
		 data->tg.h.BGOfold++;
	       }
	     //count crystals within a clover
	     if((data->tg.det[pos].h.BGOHP&(one<<col))==0)
	       {
		 data->tg.det[pos].h.BGOHP|=(one<<col);
		 data->tg.det[pos].h.BGOfold++;
	       }
	   }	 
       }
   
   /***************************** End   TIGRESS BGO  ***********************/
   /***************************** Start TIP           **********************/
 if(ptr->chan>=map->csiarray_min)
    if(ptr->chan<=map->csiarray_max)
      {
	id=ptr->chan-map->csiarray_min;
	pos=map->csi_lt[id];
	if(pos>0)
	  if(pos<NCSI)
	    {
	      take=0;
	      if(ptr->ch.charge>0)
		{
		  data->csiarray.csi[pos].charge=ptr->ch.charge;
		  data->csiarray.h.Efold++;
		  data->csiarray.h.EHP[pos/64]=(one<<pos%64);		 
		  take|=1;
		}
	      if(ptr->ch.cfd>0)
		{
		  data->csiarray.csi[pos].cfd=ptr->ch.cfd;
		  data->csiarray.h.Tfold++;
		  data->csiarray.h.THP[pos/64]|=(one<<pos%64);		 
		  take|=1;
		}
	      if(take==1)
		{
		  data->csiarray.csi[pos].timestamp=ptr->ch.timestamp;
		  data->csiarray.csi[pos].timestamp_up=ptr->ch.timestamp_up;
		  data->csiarray.h.TSfold++;
		  data->csiarray.h.TSHP[pos/64]|=(one<<pos%64);
		  data->h.setupHP|=CsIArray_BIT;
		  memcpy(&data->csiarray.wfit[pos],&ptr->wfit,sizeof(ShapePar));
		  data->csiarray.t0[pos]=ptr->wfit.t[0];
		}
	     
	    }
      }
 /***************************** End TIP             **********************/
 /***************************** Start EMMA ***********************/
 if(ptr->chan==map->emma_channel)
   {
     data->emma.grif.timestamp=ptr->ch.timestamp;
     data->emma.grif.timestamp_up=ptr->ch.timestamp_up;
     data->emma.grif.charge=ptr->ch.charge;
     data->emma.grif.cfd=ptr->ch.cfd;
     data->h.setupHP|=EMMA_BIT;
   }
  /***************************** End EMMA            **********************/
  return 0;
}

/*================================================================*/
int print_list(int limit, int offset, node* list)
{
  int i;

  for(i=0;i<limit;i++)
    printf("Frag: %9d Ts[ns] %16llu Ch %4d Ts_up %8u Ts %8u CFD %8u TigTrig %8d CsITrig %8d EMMATrig %8d TrigTs[ns] %16lld Trig %8d\n",i+offset,list[i].tsns,list[i].chan,(unsigned int)list[i].ch.timestamp_up,(unsigned int)list[i].ch.timestamp,(unsigned int)list[i].ch.cfd,list[i].tig_trig,list[i].csi_trig,list[i].emm_trig,list[i].trig_tsns,list[i].trig);
  
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
