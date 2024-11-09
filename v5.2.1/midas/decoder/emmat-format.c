#include "emmat-format.h"

int unpack_emmat_bank(int *data, int length)
{
 
   unsigned int *evntbuf = (unsigned *)data;
   emmat_event emmat_event;
  
   if(unpack_emmat_event(evntbuf, length, &emmat_event)==0)
     analyze_emmat_fragment(&emmat_event);


   return(0); 
}
/*================================================================*/
int unpack_emmat_event(unsigned *evntbuf, int evntbuflen, emmat_event *ptr)
{
  // CAEN V1290 N
  int  type,value;
  unsigned val32, *evntbufend = evntbuf+evntbuflen;
  static int event_count;
  /* unsigned HAdd,TAdd; */
  unsigned ch,val,tr;
  
 
  ++event_count;
  memset(ptr, 0, sizeof(emmat_event) ); //clear before decoding

  if( ((*evntbuf) & 0xf8000000) != 0x40000000 ){
      printf("emmat_decode: bad header in event %d\n", event_count );
      return -1;
   }
  else
    {
      ptr->trignum=((*evntbuf)>>5) & 0x3fffff;
      ptr->geo=(*evntbuf)&0x1f;
      evntbuf++;
    }
  while( evntbuf < evntbufend )
    {
      val32 = *(evntbuf++);
      type = (val32 >> 27)&0x1F;
      value = val32 & 0x07ffffff;
      switch( type )
	{

	case 0x00://result of a measurement
	  ch=(value>>21)&0x1f;
	  tr=(value>>26)&0x1;
	  val=value&0xfffff;
	  if(ch<0) break;
	  if(ch>=16) break;

	  if(tr==0)
	    {
	      if(ptr->fl[ch]==2)
		{
		  ptr->lt[ch]=val;
		  ptr->fl[ch]=3;
		}
	      if(ptr->fl[ch]==1)
		{
		  ptr->ls[ch]=val;
		  ptr->fl[ch]=2;
		}
	      if(ptr->fl[ch]==0)
		{
		  ptr->lf[ch]=val;
		  ptr->fl[ch]=1;
		}
	    }

	  if(tr==1)	    
	    {
	      if(ptr->ft[ch]==2)
		{
		  ptr->tt[ch]=val;
		  ptr->ft[ch]=3;
		}	  
	      if(ptr->ft[ch]==1)
		{
		  ptr->ts[ch]=val;
		  ptr->ft[ch]=2;
		}
	      if(ptr->ft[ch]==0)
		{
		  ptr->tf[ch]=val;
		  ptr->ft[ch]=1;
		}	      
    
	    }	  
	  
	  /* printf("Result  : 0x%8.8x val:0x%8.8x ch:%4.4d tr:%1.1d fl:%2d\n",val32,val,ch,tr,ptr->fl[ch]); */
	  break;
	  
	case 0x01://TDC header
	  /* HAdd=(value>>24)&0x3; */
	  /* printf("Header Address  : 0x%8.8x 0x%8.8x\n",val32,HAdd); */
	  ptr->chanid=(value>>12)&0xfff;
	  ptr->pcktid=value&0xfff;
	  break;


	case 0x03://TDC event trailer
	  //	  TAdd=(value>>24)&0x3;
	  //	  printf("Trailer Address : 0x%8.8x 0x%8.8x\n",val32,TAdd);	  	  
	  //	  ptr->eflag=value&0xfff;
	  //	  printf("Pileup    Value : 0x%8.8x \n",value&0xfff);
	  break;
	  
	case 0x10:   // trigger time trailer
	  //	  printf("Time stamp low  : 0x%8.8x\n",val32);
	  ptr->tslow=value & 0x1F;
	  break;
	  
	case 0x11:   // extended trigger time
	  //	  printf("Time stamp high : 0x%8.8x\n",val32);
	  ptr->tshigh=value;	  
	  break;
	
      default:
	 printf("Not decoded  : 0x%8.8x\n",val32);	  	  

	break;
      }
    }

  
  
  return 0;
}
