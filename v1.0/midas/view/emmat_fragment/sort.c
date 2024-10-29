#include "sort.h"
/*================================================================*/
int analyze_emmat_fragment(emmat_event* ptr)
{
  unsigned long long ts;
  int ch;
  
  if(ptr->tshigh<last)
    wrap++;

  ts=0x100000000*wrap;
  ts+=(ptr->tshigh)<<5;
  ts+=ptr->tslow;
  ts/=2;
  
  printf("=Event %8.8lld===================================================\n",counter);
  printf("     GEO Address          :   %16u         0x%8.8x\n",ptr->geo,ptr->geo);
  printf("     Time Stamp Low       :   %16u         0x%8.8x\n",ptr->tslow,ptr->tslow);
  printf("     Time Stamp High      :   %16u         0x%8.8x\n",ptr->tshigh,ptr->tshigh);
  printf("     Wrap                 :   %16d         0x%8.8x\n",wrap,wrap);
  printf("     Time Stamp [samples] :   %16llu 0x%16.16llx\n",ts,ts);
  printf("     Time Stamp [ns]      :   %16llu 0x%16.16llx\n",50*ts,50*ts);
  printf("     Trigger Number       :   %16u         0x%8.8x\n",ptr->trignum,ptr->trignum);
  printf("     Channel Id           :   %16u         0x%8.8x\n",ptr->chanid,ptr->chanid);
  printf("     Network Packet Id    :   %16u         0x%8.8x\n",ptr->pcktid,ptr->pcktid);
  //  printf("     Error Flag           :   %16u         0x%8.8x\n",ptr->eflag,ptr->eflag); 
  for(ch=0;ch<16;ch++)
    if((ptr->fl[ch]+ptr->ft[ch])>0)
      {
	printf("     Channel %2d           :",ch);
	/* printf(" LE fold %2d TE fold %2d\n",ptr->fl[ch],ptr->ft[ch]); */
	if(ptr->fl[ch]>0)
	  printf(" L1 %6d",ptr->lf[ch]);
	if(ptr->ft[ch]>0)
	  printf(" T1 %6d",ptr->tf[ch]);
	if(ptr->fl[ch]>1)
	  printf(" L2 %6d",ptr->ls[ch]);
	if(ptr->ft[ch]>1)
	  printf(" T2 %6d",ptr->ts[ch]);
	if(ptr->fl[ch]>2)
	  printf(" L3 %6d",ptr->lt[ch]);
	if(ptr->ft[ch]>2)
	  printf(" T3 %6d",ptr->tt[ch]);	
	printf("\n");
      }
  

  printf("Press ENTER to continue\n");
  getc(stdin);

  last=ptr->tshigh;
  
  counter++;
  return 0;
}

/*================================================================*/
int main(int argc, char *argv[])
{
 
  counter=0;
  wrap=0;
  last=0;

  if(argc!=2)
    {
      printf("view_emmat_fragment midas_input_data\n");
      exit(-1);
    }
 
  /* do sorting */
  sort_but_not_assemble(argv[1]);
  printf("Program provides information on consecutive fragments.\n");
}
