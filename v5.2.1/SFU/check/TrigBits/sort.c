#include "sort.h"
const char* getType(int i)
{
  static char btype[128];

  memset(btype,0,sizeof(btype));

  if((i&TIGRESS_BIT)==TIGRESS_BIT)
   strcat(btype,"TIGRESS ");
  
  if((i&CsIArray_BIT)==CsIArray_BIT)
   strcat(btype,"TIP ");

  if((i&GRIFFIN_BIT)==GRIFFIN_BIT)
   strcat(btype,"GRIFFIN ");

  if((i&EMMA_BIT)==EMMA_BIT)
    strcat(btype,"EMMA "); 
  return btype;
}
/*=======================================================*/
int analyze_data(raw_event *data)
{
  h->Fill(data->h.setupHP);
  return SEPARATOR_DISCARD;
}
/*=======================================================*/
int main(int argc, char *argv[])
{
  input_names_type* name;
  TCanvas *canvas;
  TApplication *theApp;
  int i;
  int tb;
  double sum;
  int MTB;
  MTB = 321;
  
  if(argc!=2)
    {
      printf("sfu_check_TrigBits SFU_data_file\n");
      exit(-1);
    }
  
  h = new TH1D("TrigBits","TrigBits",MTB+1,0,MTB);
  h->Reset();
  
  printf("Program sorts trigger bits histogram \n");
  
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  strcpy(name->fname.inp_data,argv[1]);
  sort(name); 

  sum=h->Integral();
  printf("Fraction [%%]    Counts  TrigBit    Type\n");
  for(i=0;i<MTB;i++)
    {
      tb=h->GetBinContent(i);
      if(tb!=0)
	printf(" %6.1f      %9d     %4d    %s\n",(100.*tb/sum),tb,i-1,getType(i-1));
    }
  printf("Total counts:%9d\n",(int)sum);
  theApp=new TApplication("App", &argc, argv);
  canvas = new TCanvas("TrigBits", "TrigBits",10,10, 500, 300);
  canvas->cd();
  gPad->SetLogy(1);
  h->Draw();
  
  theApp->Run(kTRUE);
}
