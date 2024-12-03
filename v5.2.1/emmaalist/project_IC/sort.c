#include "sort.h"


/*================================================================*/
int main(int argc, char *argv[])
{
  //TIMEKEEPING
  clock_t start, end;
  double timer;
  start=clock();
  
  FILE *eainp;
  size_t eason;
  eanode eand;
  static gmap map;
  unsigned long long pos;
  signed long long adc_val[4];
  signed long long adc_sum,adc_diff[3];
  char histname[32];
    
  eason=sizeof(eanode);

  if(argc!=3)
    {
      printf("emmaalist_project_PGAC emmaA_list_name map\n");
      exit(-1);
    }
 
  printf("Program attempts to project the information from the IC ADC charge.\n");
  
  if((eainp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
   
  read_map(argv[2],&map);

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

  
  for(int i=0;i<3;i++)
    {
      sprintf(histname,"IC deltaE%3d vs. Etot",title[i]);
      h[6+i] = new TH2D(histname,histname,950,200,4000,375,-300,1200);
      h[6+i]->Reset();
    }
  
  while(1)
    {
      if(fread(&eand,eason,1,eainp)!=1)
	break;

      pos=ftell(eainp);//save current position in the EMMAA list

      if((eand.IC[0])>0)
	if((eand.IC[1])>0)
	  if((eand.IC[2])>0)
	    if((eand.IC[3])>0)
	      {
		//Grab the ADC values
		adc_val[0] = eand.IC[0];
		adc_val[1] = eand.IC[1];
		adc_val[2] = eand.IC[2];
		adc_val[3] = eand.IC[3];
		adc_sum = adc_val[0] + adc_val[1] + adc_val[2] + adc_val[3];
		adc_diff[0] = adc_val[0] - adc_val[1];
		adc_diff[1] = adc_val[0] - adc_val[2];
		adc_diff[2] = adc_val[0] - adc_val[3];

		h[0]->Fill(adc_val[0],adc_val[1]);
		h[1]->Fill(adc_val[0],adc_val[2]);
		h[2]->Fill(adc_val[0],adc_val[3]);
		h[3]->Fill(adc_val[1],adc_val[2]);
		h[4]->Fill(adc_val[1],adc_val[3]);
		h[5]->Fill(adc_val[2],adc_val[3]);
		h[6]->Fill(adc_sum,adc_diff[0]);
		h[7]->Fill(adc_sum,adc_diff[1]);
		h[8]->Fill(adc_sum,adc_diff[2]);
	      }
     
      fseek(eainp,pos,SEEK_SET);//back to the reference position for the next EMMAA event
    }

  theApp=new TApplication("App", &argc, argv);
  c = new TCanvas("PID","PID",10,10, 500, 300);
  gPad->SetLogz(1);
  gStyle->SetPalette(1);
  TFile f("emmaalist_IC.root","recreate");
  
  h[0]->GetXaxis()->SetTitle("IC 1");
  h[1]->GetXaxis()->SetTitle("IC 1");
  h[2]->GetXaxis()->SetTitle("IC 1");
  h[3]->GetXaxis()->SetTitle("IC 2");
  h[4]->GetXaxis()->SetTitle("IC 2");
  h[5]->GetXaxis()->SetTitle("IC 3");
  h[6]->GetXaxis()->SetTitle("IC 1+2+3+4");
  h[7]->GetXaxis()->SetTitle("IC 1+2+3+4");
  h[8]->GetXaxis()->SetTitle("IC 1+2+3+4");

  h[0]->GetYaxis()->SetTitle("IC 2");
  h[1]->GetYaxis()->SetTitle("IC 3");
  h[2]->GetYaxis()->SetTitle("IC 4");
  h[3]->GetYaxis()->SetTitle("IC 3");
  h[4]->GetYaxis()->SetTitle("IC 4");
  h[5]->GetYaxis()->SetTitle("IC 4");
  h[6]->GetYaxis()->SetTitle("IC 1-2");
  h[7]->GetYaxis()->SetTitle("IC 1-3");
  h[8]->GetYaxis()->SetTitle("IC 1-4");
  
  for(int i=0;i<9;i++)
    {      
      h[i]->GetXaxis()->CenterTitle(true);
      h[i]->GetYaxis()->CenterTitle(true);
      h[i]->GetYaxis()->SetTitleOffset(0);
      h[i]->SetOption("COLZ");
      h[i]->Write();
    }
   
  fclose(eainp);

  //TIMEKEEPING
  end=clock();
  timer=(double)(end-start)/CLOCKS_PER_SEC;
  printf("\nSorting time %8.2f seconds\n",timer);    
}
