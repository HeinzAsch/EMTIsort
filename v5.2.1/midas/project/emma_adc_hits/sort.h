#ifndef SORT_H
#define SORT_H

#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"
#include "SFU-common.h"
#include "sort_but_not_assemble.h"

TH2D *h;

int unpack_griff=0;
int unpack_emmat=0;
int unpack_emmaa=1;
/*================================================================*/
int analyze_emmat_fragment(emmat_event*)
{
  return -1;
}
/*================================================================*/
int analyze_grif_fragment(Grif_event*, short*)
{
  return -1;
}


#endif
