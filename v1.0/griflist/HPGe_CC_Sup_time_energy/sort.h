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
TH2D *h2;
TCanvas *c;  
TApplication *theApp;

//int hist[S32K];
int hist[NPOSTIGR][S32K];
//int hist[32][S32K];
//int hist[128][S32K];
unsigned long long window;

int analyze_list(int,int,node*){return -1;};
int analyze_fragment(Grif_event*, short*){return -1;};
#endif
