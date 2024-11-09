#ifndef SORT_H
#define SORT_H

#include "TH1D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"

TH1D *hl,*hf,*h;
TCanvas *c;  
TApplication *theApp;

#include <time.h>
#include "sort_but_not_assemble.h"

#define S4K 4096

int hist[32][S4K];
int counter[32];

int unpack_griff=0;
int unpack_emmat=0;
int unpack_emmaa=1;

/*================================================================*/
int analyze_grif_fragment(Grif_event* ptr, short* waveform)
{
  return -1;
}

/*================================================================*/
int analyze_emmat_fragment(emmat_event* ptr)
{
  return -1;
}


#endif
