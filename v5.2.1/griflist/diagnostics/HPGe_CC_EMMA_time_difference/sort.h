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

int hist[S32K];
unsigned long long window;

int analyze_list(int,int,node*){return -1;};
int analyze_fragment(Grif_event*, short*){return -1;};
#endif
