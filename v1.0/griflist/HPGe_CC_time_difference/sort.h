#ifndef SORT_H
#define SORT_H


#include "SFU-common.h"
#include "griflist-format.h"

#include "TH1D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"

TH1D *h;
TCanvas *c;  
TApplication *theApp;

long long tsstore,Estore,Egate_low,Egate_high;
int hist[S4K];

#endif
