#include "sort.h"
/*================================================================*/
Double_t myfunction(Double_t *y, Double_t *par)
{
 
  if(y[0]<=par[2])
    return par[0];
  else
    return par[0]+par[1]*(1-exp(-(y[0]-par[2])/par[3]))*exp(-(y[0]-par[2])/par[4])+par[5]*(1-exp(-(y[0]-par[2])/par[6]))*exp(-(y[0]-par[2])/par[4]);
}

/*================================================================*/
int analyze_grif_fragment(Grif_event* ptr,short* waveform)
{
  int d;
  WaveFormPar wpar;
  int chn_i;
  
  for(chn_i=chnlow;chn_i<=chnhigh;chn_i++)
    {
      if(ptr->chan==chn_i)
	if((d=ptr->waveform_length)!=0)
	  {
	    memset(&wpar,0,sizeof(WaveFormPar));
	    wpar.baseline_range=CSI_BASELINE_RANGE;
	    
	    get_t10t90(d,waveform,&wpar);
	    fit_CsI_waveform(d,waveform,par,&wpar);
	    
	    if(wpar.t10t90_flag==1)
	      {
		/* print_WavePar(&wpar); */
		/* print_ShapePar(par); */
		/* getc(stdin); */
		
		if(par->type==1)
		  {
		    if(h!=NULL) delete h;
		    h=new TH1D("Waveform","Waveform",ptr->waveform_length,0,ptr->waveform_length);
		    
		    for(Int_t i=0;i<ptr->waveform_length;i++)
		      h->Fill(i,waveform[i]);
		    
		    //printf("baseline: %.2f max: %.2f t0: %.2f t10: %.2f t90: %.2f t10t90: %.2f\n",wpar.baseline,wpar.max,wpar.t0,wpar.t10,wpar.t90,wpar.t10t90);
		    
		    f->SetParameter(0,wpar.baseline);
		    f->FixParameter(1,par->am[2]);
		    f->SetParameter(2,wpar.t0);
		    f->FixParameter(3,par->t[2]);
		    f->FixParameter(4,par->t[1]);
		    f->SetParameter(5,par->am[3]);
		    f->SetParameter(6,par->t[3]);
		    
		    //printf("\n par6 init: %.2f\n",f->GetParameter(6));
		    
		    //h->Fit("wfit","N","N",0,d-1); //verbose fit
		    h->Fit("wfit","QN","QN",0,d-1); //quiet fit
		    
		    /* if(c!=NULL) delete c; */
		    /* c = new TCanvas("Waveform", "Waveform",10,10, 700, 500); */
		    /* h->Draw(); */
		    /* f->SetLineColor(kRed); */
		    /* f->Draw("same"); */
		    /* theApp->Run(kTRUE); */
		    
		    //printf("\n par4 fit: %.2f, chisq/ndf: %.2f\n",f->GetParameter(6),f->GetChisquare()/f->GetNDF());
		  
		    g->Fill(f->GetParameter(6));
		  }
	      }
	  }
    }
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{

  int ac=0;
  char *av[1];
  char title[132];

 if(argc!=8)
    {
      printf("\n ./wfit_fit_fast_component midas_input_data_file_name channel_low channel_high TRC TF TS TGamma\n");
      exit(-1);
    }

 par=(ShapePar*)malloc(sizeof(ShapePar));
  memset(par,0,sizeof(ShapePar));

  chnlow=atoi(argv[2]);
  chnhigh=atoi(argv[3]);
  par->t[1]=atof(argv[4]); //set tRC
  par->t[2]=atof(argv[5]); //set tF
  par->t[3]=atof(argv[6]); //set tS
  par->t[4]=atof(argv[7]); //set tGamma

  f=new TF1("wfit",myfunction,0,MAX_SAMPLE_LEN,7);
  g=new TH1D("TS/chisq","TS/chisq",S1K,0,S1K-1);

  theApp=new TApplication("App", &ac, av);
  printf("Program fits slow component on waveforms for selected channel\n");

/* do sorting */
  sort_but_not_assemble(argv[1]);
 /* display results */

//here we write a ROOT file with all the histograms
  sprintf(title,"wfit_fit_slow_component.root");
  TFile f(title, "recreate");

  g->GetXaxis()->SetTitle("slow component rise [10 ns bins]");
  g->GetXaxis()->CenterTitle(true);
  g->GetYaxis()->SetTitle("Chi square/ndf [arb.]");
  g->GetYaxis()->CenterTitle(true);
  g->GetYaxis()->SetTitleOffset(1.5);
  g->SetOption("COLZ");

  g->Write();

  if(c!=NULL) delete c;
  c = new TCanvas("Waveform", "Waveform",10,10, 700, 500);
  g->Draw();
  theApp->Run(kTRUE);
 
}
