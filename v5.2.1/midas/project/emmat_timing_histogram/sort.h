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

#define S32K 32768
#define S16K 16384

int hist[8][S32K];
int binsize;

int unpack_griff=0;
int unpack_emmat=1;
int unpack_emmaa=0;

/*================================================================*/
int analyze_grif_fragment(Grif_event* ptr, short* waveform)
{
  return -1;
}

/*================================================================*/
int analyze_emmaa_fragment(emmaa_event* ptr)
{
  return -1;
}


#endif
