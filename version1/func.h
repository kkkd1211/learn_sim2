#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include "head.h"
using namespace std;
int nextstep(pgene Gene[7]);
int diff(pgene Gene[7],int posi);
int deg(pgene Gene[7],int posi);
int react(pgene Gene[7],int posi);
double AactB(pgene Gene[7],int a,int b,int posi);
int Sign(double x);
void training(pgene Gene[7]);
double run(pgene Gene[7]);
#endif
