#include "sort.h"
/*================================================================*/
int analyze_emmat_fragment(emmat_event* ptr)
{
  double xPos, yPos;
  double right, left, top, bottom;
  double rightDelay, leftDelay, topDelay, bottomDelay;
  double xDiff, yDiff, xSum, ySum, ns;
  
  
  ns = 25;
  leftDelay = 40;
  rightDelay = 20;
  topDelay = 10;
  bottomDelay = 20;
  
  if((ptr->fl[7])>0)//Anode trigger leading edge present
    if((ptr->fl[3])>0)//Cathode right present
      if((ptr->fl[4])>0)//Cathode left present
	if((ptr->fl[5])>0)//Cathode top present
	  if((ptr->fl[6])>0)//Cathode bottom present
	    {	      
	      right = ns*((double)ptr->lf[3]-(double)ptr->lf[7]);
	      left = ns*((double)ptr->lf[4]-(double)ptr->lf[7]);
	      top = ns*((double)ptr->lf[5]-(double)ptr->lf[7]);
	      bottom = ns*((double)ptr->lf[6]-(double)ptr->lf[7]);

	      xDiff = left - right;
	      xSum = left + right;
	      yDiff = bottom - top;
	      ySum = bottom + top;

	      xPos = (xDiff/xSum)*PGACWidth;
	      yPos = (yDiff/ySum)*PGACHeight;

	      h->Fill(xPos,yPos);
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

  TApplication *theApp;

  if(argc!=2)
    {
      printf("project_emmat_PGAC midas_input_data\n");
      exit(-1);
    }
  
  //sprintf("PGAC","PID_%3d");
  h = new TH2D("PGAC","PGAC",160,-80,80,60,-30,30);
  h->Reset();
    
  /* do sorting */
  sort_but_not_assemble(argv[1]);
  printf("Program attempts to project the positional information from the PGAC using TDC delays.\n");

  theApp=new TApplication("App", &argc, argv);
  c = new TCanvas("PID","PID",10, 10, 500, 300);
  gPad->SetLogz(1);
  gStyle->SetPalette(1);
  h->Draw("COLZ");

  printf("%s\n","midas_PGAC.root");
  TFile f("midas_PGAC.root","recreate");

  h->GetXaxis()->SetTitle("X Position [mm]");
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->SetTitle("Y Position [mm]");
  h->GetYaxis()->CenterTitle(true);
  h->GetYaxis()->SetTitleOffset(0);
  h->SetOption("COLZ");
  h->Write();

  //TIMEKEEPING
  end=clock();
  timer=(double)(end-start)/CLOCKS_PER_SEC;
  printf("\nSorting time %8.2f seconds\n",timer);
  
  theApp->Run(kTRUE);
}
