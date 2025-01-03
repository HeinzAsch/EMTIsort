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
	//	printf("baseline = %.2f\n",wpar.baseline);
	h->Fill(wpar.baseline);
	g->Fill(wpar.baselineStDev);
      }

  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  char runFile[132];
  
  if(argc!=3)
    {
      printf("wfit_test_CsIBaseline midas_input_data channel\n");
      exit(-1);
    }

  printf("Program tests baseline fitting for CsI waveforms.\n");
  strcpy(runFile,argv[1]);

  chn=atoi(argv[2]);

  h=new TH1D("Constant Baseline","Constant Baseline",S16K,-S8K,S8K);
  h->Reset();

  g=new TH1D("Constant Baseline std. dev.","Constant Baseline std. dev.",S2K,0,200);
  g->Reset();

  sort_but_not_assemble(runFile);

  theApp=new TApplication("App", &argc, argv);
  c = new TCanvas("Constant Baseline", "Constant Baseline",10,10, 700, 1000);
  c->Divide(1,2);
  c->cd(1);
  h->Draw();
  c->cd(2);
  g->Draw();
  theApp->Run(kTRUE);
}
