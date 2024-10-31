#ifndef SORT_H
#define SORT_H

#include <time.h>
#include "SFU-common.h"
#include "griflist-format.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"

TH2D *h;
TCanvas *c;  
TApplication *theApp;

unsigned long long window;

int analyze_list(int,int,node*){return -1;};
int analyze_fragment(Grif_event*, short*){return -1;};
#endif
