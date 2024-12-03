#include "sort.h"
/*================================================================*/
int analyze_emmaa_fragment(emmaa_event* ptr)
{
  signed long long adc_val[4];



  if(((ptr->adchitpattern)&(1<<16))!=0)
    if(((ptr->adchitpattern)&(1<<17))!=0)
      if(((ptr->adchitpattern)&(1<<18))!=0)
	if(((ptr->adchitpattern)&(1<<19))!=0)  
	  {
	    //Grab the ADC values
	    adc_val[0] = ptr->adc[16];
	    adc_val[1] = ptr->adc[17];
	    adc_val[2] = ptr->adc[18];
	    adc_val[3] = ptr->adc[19];

	    h[0]->Fill(adc_val[0],adc_val[1]);
	    h[1]->Fill(adc_val[0],adc_val[2]);
	    h[2]->Fill(adc_val[0],adc_val[3]);
	    h[3]->Fill(adc_val[1],adc_val[2]);
	    h[4]->Fill(adc_val[1],adc_val[3]);
	    h[5]->Fill(adc_val[2],adc_val[3]);
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

  char histname[32];
  
  if(argc!=2)
    {
      printf("project_emmaa_IC midas_input_data\n");
      printf("Program provides information on EMMA ADC outputs.\n");
      printf("Results are stored in: midas_IC.root\n");
      exit(-1);
    }

  int title[6];
  title[0] = 12;
  title[1] = 13;
  title[2] = 14;
  title[3] = 23;
  title[4] = 24;
  title[5] = 34;
  for(int i=0;i<6;i++)
    {
      sprintf(histname,"IC%3d",title[i]);
      h[i] = new TH2D(histname,histname,475,50,1000,475,50,1000);
      h[i]->Reset();
    }
  
  /* do sorting */
  sort_but_not_assemble(argv[1]);

  theApp=new TApplication("App", &argc, argv);
  c = new TCanvas("PID","PID",10,10, 500, 300);
  gPad->SetLogz(1);
  gStyle->SetPalette(1);
  TFile f("midas_IC.root","recreate");
  
  h[0]->GetXaxis()->SetTitle("IC 1");
  h[1]->GetXaxis()->SetTitle("IC 1");
  h[2]->GetXaxis()->SetTitle("IC 1");
  h[3]->GetXaxis()->SetTitle("IC 2");
  h[4]->GetXaxis()->SetTitle("IC 2");
  h[5]->GetXaxis()->SetTitle("IC 3");

  h[0]->GetYaxis()->SetTitle("IC 2");
  h[1]->GetYaxis()->SetTitle("IC 3");
  h[2]->GetYaxis()->SetTitle("IC 4");
  h[3]->GetYaxis()->SetTitle("IC 3");
  h[4]->GetYaxis()->SetTitle("IC 4");
  h[5]->GetYaxis()->SetTitle("IC 4");
  
  for(int i=0;i<6;i++)
    {      
      h[i]->GetXaxis()->CenterTitle(true);
      h[i]->GetYaxis()->CenterTitle(true);
      h[i]->GetYaxis()->SetTitleOffset(0);
      h[i]->SetOption("COLZ");
      h[i]->Write();
    }
    
  //TIMEKEEPING
  end=clock();
  timer=(double)(end-start)/CLOCKS_PER_SEC;
  printf("\nSorting time %8.2f seconds\n",timer);

  //theApp->Run(kTRUE);
}
