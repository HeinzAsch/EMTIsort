#ifndef SORT_H
#define SORT_H

#include "SFU-common.h"
#include "sort_but_not_assemble.h"
#include "waveform_analyzer.h"

#include "TH1D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"
#include "TF1.h"
#include "TROOT.h"
#include "math.h"

TH1D *h,*g;
TCanvas *c;
ShapePar* par;
int  chn;
double chmin,chmax;
TApplication *theApp;

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
