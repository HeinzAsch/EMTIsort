#ifndef SORT_H
#define SORT_H

#include "TH1D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"
#include "SFU-common.h"
#include "sort_but_not_assemble.h"

int hist[S2K];
TH1D *h;


int unpack_griff=1;
int unpack_emmat=0;
int unpack_emmaa=0;
/*================================================================*/
int analyze_emmat_fragment(emmat_event* ptr)
{
  return -1;
}
/*================================================================*/
int analyze_emmaa_fragment(emmaa_event* ptr)
{
  return -1;
}


#endif
