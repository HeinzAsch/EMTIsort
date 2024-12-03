#include "sort.h"


/*================================================================*/
int main(int argc, char *argv[])
{
  //TIMEKEEPING
  clock_t start, end;
  double timer;
  start=clock();
  
  FILE *etinp;
  size_t etson;
  etnode etnd;
  static gmap map;
  unsigned long long pos;
  double xPos, yPos;
  double right, left, top, bottom;
  double rightDelay, leftDelay, topDelay, bottomDelay;
  double xDiff, yDiff, xSum, ySum, ns;  
  
  ns = 25;
  leftDelay = 40;
  rightDelay = 20;
  topDelay = 10;
  bottomDelay = 20;  
  
  etson=sizeof(etnode);

  if(argc!=4)//REMOVE DELAY BIT AFTER TESTING
    {
      printf("emmatlist_project_PGAC emmaT_list_name map delayBit\n");//REMOVE DELAY BIT AFTER TESTING
      exit(-1);
    }
   
  printf("Program attempts to project the positional information from the PGAC using TDC delays.\n");
  
  if((etinp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
   
  read_map(argv[2],&map);

  h = new TH2D("PGAC","PGAC",160,-80,80,60,-30,30);
  h->Reset();  
  
  while(1)
    {
      if(fread(&etnd,etson,1,etinp)!=1)
	break;

      pos=ftell(etinp);//save current position in the EMMAT list

      if((etnd.anodeTrigger)>0)//Anode trigger present
	if((etnd.cathodeBottom)>0)//Cathode bottom present
	  if((etnd.cathodeRight)>0)//Cathode right present
	    if((etnd.cathodeLeft)>0)//Cathode left present
	      if((etnd.cathodeTop)>0)//Cathode top present
		{
		  bottom = ns*((double)etnd.cathodeBottom-(double)etnd.anodeTrigger);
		  right = ns*((double)etnd.cathodeRight-(double)etnd.anodeTrigger);
		  left = ns*((double)etnd.cathodeLeft-(double)etnd.anodeTrigger);
		  top = ns*((double)etnd.cathodeTop-(double)etnd.anodeTrigger);		  

		  xDiff = left - right;
		  xSum = left + right;
		  yDiff = bottom - top;
		  ySum = bottom + top;

		  //REMOVE DELAY BIT AFTER TESTING
		  if(atoi(argv[3])==1)
		    {
		      xDiff += leftDelay - rightDelay;
		      yDiff += bottomDelay - topDelay;
		    }

		  xPos = (xDiff/xSum)*PGACWidth;
		  yPos = (yDiff/ySum)*PGACHeight;

		  h->Fill(xPos,yPos);
		}
     
      fseek(etinp,pos,SEEK_SET);//back to the reference position for the next EMMAT event
    }

  theApp=new TApplication("App", &argc, argv);
  c = new TCanvas("PID","PID",10, 10, 500, 300);
  gPad->SetLogz(1);
  gStyle->SetPalette(1);
  h->Draw("COLZ");

  //REMOVE DELAY BIT AFTER TESTING
  /* if(atoi(argv[3])==1) */
  /*   { */
      printf("%s\n","emmatlist_PGAC_DELAYED.root");
      TFile f("emmatlist_PGAC_DELAYED.root","recreate");
  /*   } */
  /* else */
  /*   { */
  /*     printf("%s\n","emmatlist_PGAC.root"); */
  /*     TFile f("emmatlist_PGAC.root","recreate"); */
  /*   } */

  h->GetXaxis()->SetTitle("X Position [mm]");
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->SetTitle("Y Position [mm]");
  h->GetYaxis()->CenterTitle(true);
  h->GetYaxis()->SetTitleOffset(0);
  h->SetOption("COLZ");
  h->Write();
   
  fclose(etinp);

  //TIMEKEEPING
  end=clock();
  timer=(double)(end-start)/CLOCKS_PER_SEC;
  printf("\nSorting time %8.2f seconds\n",timer);    
}
