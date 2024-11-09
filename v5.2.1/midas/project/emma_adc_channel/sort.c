#include "sort.h"

/*================================================================*/
int analyze_emmaa_fragment(emmaa_event* ptr)
{
  float v;
  if((ptr->adchitpattern &(1<<channel))!=0)
      {
	v=(float)ptr->adc[channel];
	h->Fill(v);
      }
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  TCanvas *c;
  TApplication *theApp;
  int ac=0;
  char *av[1];
  char name[132];

  if(argc!=3)
    {
      printf("project_emma_adc midas_input_data channel_id\n");
      exit(-1);
    }
  channel=atoi(argv[2]);
  
  h=new TH1D("","",S4K,0,S4K);
  sprintf(name,"channel_id_%s",argv[2]);
  h->Reset();
  h->SetName(name);
  h->SetTitle(name);

  sort_but_not_assemble(argv[1]);

  printf("Program provides a 1D projection for a selected EMMA ADC channel.\n");

  theApp=new TApplication("App", &ac, av);
  c = new TCanvas(name, name,10,10, 700, 500);
  c->cd();
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Counts");
  h->Draw("HIST");
  theApp->Run(kTRUE);
}
