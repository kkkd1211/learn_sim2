#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define kkk printf("!!!\n");
#define trainning1
#define read0
#define write1


//#define mu_type 0       //0:wt  1:B+    2:B-    3:N+    4:N-    5:T-



#define Nx 100
#define T 2000

#define trainParaN 56

//#define delta 0.001
#define traintime 10
#define ln_rate_max 0.7
#define ln_rate_min 0.2
extern int topolo[7][7];
extern int mut[7][7];
extern double v[7][7];
extern double v_new[7][7];
extern double k[7][7];
extern double k_new[7][7];
extern double C;
extern double alpha[7];
extern double alpha_new[7];
extern double beta;
extern int n;
extern double D;
extern double dx;
extern double dt;
extern double d;
extern double ln_rate;
extern double D_rate;
extern double hb_in_data[Nx];
extern double kr_in_data[Nx];
extern double gt_in_data[Nx];
extern double kni_in_data[Nx];
extern double *trainPara[trainParaN];
class gene;
typedef gene *pgene;
class gene
{
    public:
        ~gene();
        gene();
        gene(double ini_c[Nx]);
        double c0[Nx];
        double c1[Nx];
        double target[Nx];

//        void setinit();
        void next();
        void print(char name[20]);
        double error(int x1,int x2);
        void settarget(double t[Nx]);
        void setvar(double var[Nx]);
};
#endif
