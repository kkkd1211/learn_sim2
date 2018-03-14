#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include "head.h"
using namespace std;
void setup(char *trainparafile);
int nextstep(pgene Gene[7]);
int diff(pgene Gene[7],int posi);
int deg(pgene Gene[7],int posi);
int react(pgene Gene[7],int posi);
double AactB(pgene Gene[7],int a,int b,int posi);
int Sign(double x);
void training(pgene Gene[7],char *errfile);
double run(pgene Gene[7]);
void print_topo(pgene Gene[7]);
int topo_fig(double x);
#endif
