#include "sort.h"
/*================================================================*/
int analyze_grif_fragment(Grif_event* ptr,short* waveform)
{
  Int_t d;
  WaveFormPar wpar;
  double ch;
  int type;
  
  if( (ptr->chan>=chn_low) && (ptr->chan<=chn_high) )
    {
      //printf("channel number %d\n",ptr->channel);
      if((d=ptr->waveform_length)!=0)
      {
	//printf("d %d\n",d);
	fit_CsI_waveform(d,waveform,par,&wpar);
	ch=par->chisq/par->ndf;
	
	type=par->type;
	//printf("chisq/ndf %10.3f type %d\n",ch,par->type);
	
	if(ch>=chisq_min)
	  if(ch<=chisq_max)
	    {
	      h->Fill(type);
	    }
      }
    }
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  char title[132];
  TCanvas *c;
  TApplication *theApp;
  int ac=0;
  char *av[1];
  char name[128];

 if(argc!=10)
    {
      printf("wfit_show_CsIFit_type midas_input_data_file_name channel_low channel_high tRC tF tS tGamma chisq_min chisq_max\n");
      exit(-1);
    }

  par=(ShapePar*)malloc(sizeof(ShapePar));
  memset(par,0,sizeof(ShapePar));

  h=new TH1D("CsI fit type","CsI fit type",16,-8,8);
  h->Reset();

  strcpy(name,argv[1]);
  chn_low=atoi(argv[2]);
  chn_high=atoi(argv[3]);
  par->t[1]=atof(argv[4]); //set tRC
  par->t[2]=atof(argv[5]); //set tF
  par->t[3]=atof(argv[6]); //set tS
  par->t[4]=atof(argv[7]); //set tGamma
  chisq_min=atof(argv[8]);
  chisq_max=atof(argv[9]);

  theApp=new TApplication("App", &ac, av);

/* do sorting */
  sort_but_not_assemble(name);

  sprintf(title,"type.root");
  TFile f(title, "recreate");

  /* //save results 
  if(h->GetEntries())
    {
      h->GetXaxis()->SetTitle("Fit type");
      h->GetXaxis()->CenterTitle(true);
      h->GetYaxis()->SetTitle("Counts");
      h->GetYaxis()->CenterTitle(true);
      h->GetYaxis()->SetTitleOffset(1.5);
      h->SetOption("COLZ");
      h->Write();
    }
  h->Write();
*/

  /*show results*/
  c = new TCanvas("Fold", "Fold",10,10, 700, 500);
  c->cd();
  gPad->SetLogy();
  h->GetXaxis()->SetTitle("Fit type");
  h->GetYaxis()->SetTitle("Counts");
  h->Draw();
  theApp->Run(kTRUE);
}
