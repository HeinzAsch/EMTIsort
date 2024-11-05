#include "emmaa-format.h"

int unpack_emmaa_bank(int *data, int length)
{
 
   unsigned int *evntbuf = (unsigned *)data;
   emmaa_event emmaa_event;
  
   if(unpack_emmaa_event(evntbuf, length, &emmaa_event)==0)
     analyze_emmaa_fragment(&emmaa_event);


   return(0); 
}
/*================================================================*/
int unpack_emmaa_event(unsigned *evntbuf, int evntbuflen, emmaa_event *ptr)
{

  int  type,value;
  unsigned val32, *evntbufend = evntbuf+evntbuflen;
  static int event_count;
  int channel,adcdata;
 
  ++event_count;
  memset(ptr, 0, sizeof(emmaa_event) ); //clear before decoding

  if( ((*evntbuf) & 0xf0000000) != 0x40000000 ){
      printf("emmaa_decode: bad header in event %d\n", event_count );
   }
  // this is a multiple-hit ADC, the current algorithm takes the latest hit
  // the rate on EMMA is usually low, the probability is the highes for a single hit
  // if this is not true the decoding algorithm has to be adjusted
  while( evntbuf < evntbufend )
    {
      val32 = *(evntbuf++);
      type = (val32 >> 28)&0xc;
      value = val32;
      switch( type ){

      case 0xc:   // Last 30 bits of timestamp
	ptr->tslow=value & 0x3FFFFFFF;
	break;
	
      case 0x0:
	if((value & 0x00800000) != 0)
	  {
	    ptr->tshigh=value & 0xffff;
	  }
	else if ((value & 0x04000000) != 0)
	  {
	    channel=(val32>>16) & 0x1F;
	    adcdata=val32 & 0xfff;
	    if(channel>-1)
	      if(channel<32)
		{		  
		  ptr->adc[channel]=adcdata;
		  ptr->adcf[channel]++;
		  ptr->adchitpattern|=(1<<channel);
		  ptr->adcfold++;
		}
	  }	  	
	break;
	
      default:
	break;
      }
    }

  
  
  return 0;
}
