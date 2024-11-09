#include "sort.h"
/*================================================================*/
int analyze_emmat_fragment(emmat_event* ptr)
{
  int ch;
  signed long long dt;  

  if((ptr->fl[7]+ptr->ft[7])>0)
    if((ptr->fl[8]+ptr->ft[8])>0)
      for(ch=0;ch<=6;ch++)
	if((ptr->fl[ch]+ptr->ft[ch])>0)	  
	  if(ptr->fl[ch]>0)
	    {
	      dt = (long long)ptr->lf[ch]-(long long)ptr->lf[7];//Take the first leading edge between data channel and rf channel (8)
	      dt /= binsize;	      
	      dt += S16K;	      
	      hist[ch][dt]++;
	      hist[7][dt]++;
	    }  
  
  return 0;
}

/*================================================================*/
int main(int argc, char *argv[])
{
  //TIMEKEEPING
  clock_t start, end;
  double timer;
  start=clock();

  int ch;
  FILE *output;

  binsize = 2;

  if(argc!=2)
    {
      printf("view_emmat_fragment midas_input_data\n");
      exit(-1);
    }

  memset(hist,0,sizeof(hist));
    
  /* do sorting */
  sort_but_not_assemble(argv[1]);
  printf("Program provides information on consecutive fragments.\n");  

  if((output=fopen("emmat_timing_histogram.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file!\n");
      exit(EXIT_FAILURE);
    }      
  for(ch=0;ch<=7;ch++)
    fwrite(hist[ch],S32K*sizeof(int),1,output);
  fclose(output);
  

  //TIMEKEEPING
  end=clock();
  timer=(double)(end-start)/CLOCKS_PER_SEC;
  printf("\nSorting time %8.2f seconds\n",timer);
}
