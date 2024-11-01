#include "sort.h"

/*================================================================*/
int analyze_grif_fragment(Grif_event* ptr, short* waveform)
{
  long ts;
  ts=(ptr->timestamp&0xfffffffffffc0000)<<4;
  ts+=ptr->cfd;
  ts*=10;
  ts/=16;
  printf("=========================================================\n");
  printf(" Data Time Stamp [samples]:   %16ld 0x%16.16lx\n",ptr->timestamp,ptr->timestamp);
  printf(" Time Stamp L18B [samples]:   %16ld 0x%16.16lx\n",(ptr->timestamp&0x3ffff),(ptr->timestamp&0x3ffff));
  printf("        CFD T18B [samples]:   %16ld 0x%16.16lx\n",(long)(ptr->cfd>>4),(long)(ptr->cfd>>4));
  printf("          CFD/16 [samples]:   %16ld 0x%16.16lx\n",(long)(ptr->cfd/16),(long)(ptr->cfd/16));
  printf("             CFD [ns]     :   %16ld 0x%16.16lx\n",(long)(ptr->cfd/1.6),(long)(ptr->cfd/1.6));
  printf("      Time Stamp [ns]     :   %16ld 0x%16.16lx\n",ts,ts);
  printf("      Time Stamp [samples]:   %16ld 0x%16.16lx\n",ts/10,ts/10);
 
 
  getc(stdin);
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{

  if(argc!=2)
    {
      printf("view_griff_timing midas_input_data\n");
      exit(-1);
    }
  
 
  /* do sorting */
  sort_but_not_assemble(argv[1]);
  printf("Program provides information on consecutive fragments.\n");
}
