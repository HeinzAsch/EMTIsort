#include "sort.h"

/*================================================================*/
int analyze_grif_fragment(Grif_event* ptr,short* waveform)
{
  int d;
  WaveFormPar wpar;

  if(ptr->chan==chn)
    if((d=ptr->waveform_length)!=0)
    {
      wpar.baseline_range=CSI_BASELINE_RANGE;
      get_baseline(d,waveform,&wpar); 

      if(wpar.baselineStDev>threshold)
	{
	  print_fragment_info(ptr);
	  printf("Waveform bsq parameter: %f\n",wpar.baselineStDev);
	  if(h!=NULL) delete h;
	  h=new TH1D("Waveform","Waveform",ptr->waveform_length,0,ptr->waveform_length);
	  if(c!=NULL) delete c;
	  c = new TCanvas("Waveform", "Waveform",10,10, 700, 500);
          
	  for(Int_t i=0;i<ptr->waveform_length;i++)
	    h->Fill(i,waveform[i]);
	    
	  h->Draw("HIST");
	  theApp->Run(kTRUE);
	    
	}
    }
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{

  int ac=0;
  char *av[1];

 if(argc!=4)
    {
      printf("wfit_show_bad_baseline midas_input_data_file_name channel threshold\n");
      exit(-1);
    }

  chn=atoi(argv[2]);
  threshold=atof(argv[3]);
  theApp=new TApplication("App", &ac, av);
  printf("Program shows bad baseline events for selected channel\n");

/* do sorting */
  sort_but_not_assemble(argv[1]);
 /* display results */
 
}
