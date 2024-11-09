#include "sort.h"
/*================================================================*/
int analyze_emmaa_fragment(emmaa_event* ptr)
{
  int i;

  for(i=0;i<32;i++)
    if((ptr->adchitpattern &(1<<i))!=0)
      h->Fill(i,ptr->adcf[i]);
   

  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{

  TCanvas *c;
  TApplication *theApp;
  int ac;
  char *av[1];

  ac=0;
  av[0]=(char*) malloc(sizeof(char));
  if(argc!=2)
    {
      printf("project_emma_adc_HP midas_data_file\n");
      exit(-1);
    }
  printf("Program sorts DAQ pattern for multiple hits in EMMA ADC.\n");

  h=new TH2D("multiple hits pattern","multiple hits pattern",32,0,32,4,0,4);
  h->Reset();
  
  sort_but_not_assemble(argv[1]);
  
  
  theApp=new TApplication("App", &ac, av);
  c = new TCanvas("fold_hit_pattern", "fold_hit_pattern",10,10, 700, 500);
  c->cd();
  gStyle->SetPalette(1);
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Fold");
  h->GetZaxis()->SetTitle("Counts");
  h->Draw("COLZ");
  theApp->Run(kTRUE);
}
