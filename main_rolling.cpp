#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "head.h"
#include "func.h"
#include <sys/stat.h>
#include <time.h>
using namespace std;
#define K0 1.0  //7.3
#define K1 6.31 //8.1
#define K2 10.0 //8.3
//#define T 2000

//#define traintime 10
//#define ln_rate_max 0.8
//#define ln_rate_min 0.1
//#define delta 0.01

int topolo[7][7];
int mut[7][7]={     0,  0,  0,  1,  1,  1,  1,
                    0,  0,  0,  1,  1,  1,  1,
                    0,  0,  0,  1,  1,  1,  1,
                    0,  0,  0,  1,  1,  1,  1,
                    0,  0,  0,  1,  1,  1,  1,
                    0,  0,  0,  1,  1,  1,  1,
                    0,  0,  0,  1,  1,  1,  1,
                };

double k[7][7]={    0, 0, 0, K0, K0,  0, K0,
                    0, 0, 0,  0,  0,  0, K0,
                    0, 0, 0,-K0, K0,  0,-K0,
                    0, 0, 0,  0,-K0,  0,  0,
                    0, 0, 0,-K1, K0, K0,  0,
                    0, 0, 0,  0,  0,  0,-K2,
                    0, 0, 0,  0,  0,-K0,  0
                    };
double v[7][7]={    0,  0,  0,  1, -1,  0,  1,
                    0,  0,  0,  5,  0,  0,  1,
                    0,  0,  0, -1,  0,  0, -1,
                    0,  0,  0,  0,  -3,  0,  0,
                    0,  0,  0, -1,  1,  1,  0,
                    0,  0,  0,  0,  0,  0, -1,
                    0,  0,  0,  0,  0, -1,  0
                    };

double *trainPara[trainParaN];


double C=1; //3.31;  //0.52;
double alpha[7]={0,0,0,50,0.1,10,100};//0.13;  //2.9;
double beta=0.13;
int n=4;
double hill_para;
double D=0.2;//0.65;
double dx=0.1;
double dt=0.0005;
double d=D*dt/(dx*dx);
double hb_in_data[Nx],kr_in_data[Nx],kni_in_data[Nx],gt_in_data[Nx];
double v_new[7][7];
double k_new[7][7];
double alpha_new[7];
double ln_rate;
double D_rate=(ln_rate_max-ln_rate_min)/traintime;

int main(int argc,char *argv[])
{
	int i,j;
    FILE *fp,*fp2;
    setup();

    mkdir("output",0777);
    char kni[35]="output/kni.txt";
    char hb[35]="output/hb.txt";
    char kr[35]="output/kr.txt";
    char gt[35]="output/gt.txt";
    char fi[35]="output/final.txt";

    char kni_tg[35]="data_final/kni_target.txt";
    char hb_tg[35]="data_final/hb_target.txt";
    char kr_tg[35]="data_final/kr_target.txt";
    char gt_tg[35]="data_final/gt_target.txt";

    for(i=0;i<7;i++)
    {
        for(j=3;j<7;j++)
        {
            mut[i][j]=1;
        }
    }
    char kni_in[40];
    char hb_in[40];
    char kr_in[40];
    char gt_in[40];
    int mu_type=0;
    if(argc==2)
    {
        sscanf(argv[1],"%d",&mu_type);
        if((mu_type>5))
        {
            mu_type=0;
        }
    }
    else
    {
        mu_type=0;
    }
#ifdef trainning1
    if(mu_type!=0)
        return 0;
#endif
    if(mu_type==0)
    {
        printf("\nWT!\n\n");
        strcpy(kni_in,"input/kni_in_wt.txt");
        strcpy(hb_in,"input/hb_in_wt.txt");
        strcpy(kr_in,"input/kr_in_wt.txt");
        strcpy(gt_in,"input/gt_in_wt.txt");

        strcpy(kni,"output/kni.txt");
        strcpy(hb,"output/hb.txt");
        strcpy(kr,"output/kr.txt");
        strcpy(gt,"output/gt.txt");
        strcpy(fi,"output/final.txt");
    }
    else if(mu_type==1)
    {
        printf("\nBcd+!\n\n");
        strcpy(kni_in,"input/kni_in_B+.txt");
        strcpy(hb_in,"input/hb_in_B+.txt");
        strcpy(kr_in,"input/kr_in_B+.txt");
        strcpy(gt_in,"input/gt_in_B+.txt");
        for(i=3;i<7;i++)
        {
            mut[1][i]=0;
            mut[2][i]=0;
        }

        strcpy(kni,"mut/OB+/kni.txt");
        strcpy(hb,"mut/OB+/hb.txt");
        strcpy(kr,"mut/OB+/kr.txt");
        strcpy(gt,"mut/OB+/gt.txt");
        strcpy(fi,"mut/OB+/final.txt");
    }
    else if(mu_type==2)
    {
        printf("\nBcd-!\n\n");
        strcpy(kni_in,"input/kni_in_B-.txt");
        strcpy(hb_in,"input/hb_in_B-.txt");
        strcpy(kr_in,"input/kr_in_B-.txt");
        strcpy(gt_in,"input/gt_in_B-.txt");
        for(i=3;i<7;i++)
        {
            mut[0][i]=0;
        }

        strcpy(kni,"mut/OB-/kni.txt");
        strcpy(hb,"mut/OB-/hb.txt");
        strcpy(kr,"mut/OB-/kr.txt");
        strcpy(gt,"mut/OB-/gt.txt");
        strcpy(fi,"mut/OB-/final.txt");

    }
    else if(mu_type==3)
    {
        printf("\nNos+!\n\n");
        strcpy(kni_in,"input/kni_in_N+.txt");
        strcpy(hb_in,"input/hb_in_N+.txt");
        strcpy(kr_in,"input/kr_in_N+.txt");
        strcpy(gt_in,"input/gt_in_N+.txt");
        for(i=3;i<7;i++)
        {
            mut[0][i]=0;
            mut[2][i]=0;
        }
        strcpy(kni,"mut/ON+/kni.txt");
        strcpy(hb,"mut/ON+/hb.txt");
        strcpy(kr,"mut/ON+/kr.txt");
        strcpy(gt,"mut/ON+/gt.txt");
        strcpy(fi,"mut/ON+/final.txt");

    }
    else if(mu_type==4)
    {
        printf("\nNos-!\n\n");
        strcpy(kni_in,"input/kni_in_N-.txt");
        strcpy(hb_in,"input/hb_in_N-.txt");
        strcpy(kr_in,"input/kr_in_N-.txt");
        strcpy(gt_in,"input/gt_in_N-.txt");
        for(i=3;i<7;i++)
        {
            mut[1][i]=0;
        }
        strcpy(kni,"mut/ON-/kni.txt");
        strcpy(hb,"mut/ON-/hb.txt");
        strcpy(kr,"mut/ON-/kr.txt");
        strcpy(gt,"mut/ON-/gt.txt");
        strcpy(fi,"mut/ON-/final.txt");

    }
    else if(mu_type==5)
    {
        printf("\nTll-!\n\n");
        strcpy(kni_in,"input/kni_in_T-.txt");
        strcpy(hb_in,"input/hb_in_T-.txt");
        strcpy(kr_in,"input/kr_in_T-.txt");
        strcpy(gt_in,"input/gt_in_T-.txt");
        for(i=3;i<7;i++)
        {
            mut[2][i]=0;
        }
        strcpy(kni,"mut/OT-/kni.txt");
        strcpy(hb,"mut/OT-/hb.txt");
        strcpy(kr,"mut/OT-/kr.txt");
        strcpy(gt,"mut/OT-/gt.txt");
        strcpy(fi,"mut/OT-/final.txt");

    }
    else
    {
        printf("no mut type!!!!!!!!!!\n\n");
        return 0;
    }
    fp=fopen(kni,"w");
    fclose(fp);
    fp=fopen(hb,"w");
    fclose(fp);
    fp=fopen(kr,"w");
    fclose(fp);
    fp=fopen(gt,"w");
    fclose(fp);
    fp=fopen(fi,"w");
    fclose(fp);
    pgene Gene[7];
    double tmp[Nx];
//Bcd
    fp=fopen("input/Bcd.txt","r");
    for(i=0;i<Nx;i++)
        fscanf(fp,"%lf\t",&tmp[i]);
    Gene[0]=new gene(tmp);
    fclose(fp);
//Nos
    for(i=0;i<Nx;i++)
        tmp[i]=Gene[0]->c0[Nx-1-i];
    Gene[1]=new gene(tmp);
//Tll
    fp=fopen("input/Tll.txt","r");
    for(i=0;i<Nx;i++)
        fscanf(fp,"%lf\t",&tmp[i]);
    Gene[2]=new gene(tmp);
    fclose(fp);
//Kni
    fp=fopen(kni_in,"r");
    for(i=0;i<Nx;i++)
        fscanf(fp,"%lf\t",&kni_in_data[i]);
    Gene[3]=new gene(kni_in_data);
    fclose(fp);
//Hb
    fp=fopen(hb_in,"r");
    for(i=0;i<100;i++)
        fscanf(fp,"%lf\t",&hb_in_data[i]);
    Gene[4]=new gene(hb_in_data);
    fclose(fp);
//Kr
    fp=fopen(kr_in,"r");
    for(i=0;i<Nx;i++)
        fscanf(fp,"%lf\t",&kr_in_data[i]);
    Gene[5]=new gene(kr_in_data);
    fclose(fp);
//Gt
    fp=fopen(gt_in,"r");
    for(i=0;i<Nx;i++)
        fscanf(fp,"%lf\t",&gt_in_data[i]);
    Gene[6]=new gene(gt_in_data);
    fclose(fp);
//kni_target
    fp=fopen(kni_tg,"r");
    for(i=0;i<Nx;i++)
        fscanf(fp,"%lf\t",&tmp[i]);
    Gene[3]->settarget(tmp);
    fclose(fp);
//hb_target
    fp=fopen(hb_tg,"r");
    for(i=0;i<Nx;i++)
        fscanf(fp,"%lf\t",&tmp[i]);
    Gene[4]->settarget(tmp);
    fclose(fp);
//kr_target
    fp=fopen(kr_tg,"r");
    for(i=0;i<Nx;i++)
        fscanf(fp,"%lf\t",&tmp[i]);
    Gene[5]->settarget(tmp);
    fclose(fp);
//gt_target
    fp=fopen(gt_tg,"r");
    for(i=0;i<Nx;i++)
        fscanf(fp,"%lf\t",&tmp[i]);
    Gene[6]->settarget(tmp);
    fclose(fp);

#ifdef trainning1
training(Gene);
#endif

    Gene[3]->setvar(kni_in_data);
    Gene[4]->setvar(hb_in_data);
    Gene[5]->setvar(kr_in_data);
    Gene[6]->setvar(gt_in_data);

    for(i=0;i<T;i++)
    {
        if((i%(T/50)==0)||(i==0))
        {
            Gene[3]->print(kni);
            Gene[4]->print(hb);
            Gene[5]->print(kr);
            Gene[6]->print(gt);
        }
        nextstep(Gene);
        for(j=3;j<7;j++)
        {
            Gene[j]->next();
        }
    }

    Gene[3]->print(fi);
    Gene[4]->print(fi);
    Gene[5]->print(fi);
    Gene[6]->print(fi);
#ifdef write1
    fp=fopen("k.txt","w");
    for(i=0;i<7;i++)
    {
        for(j=0;j<7;j++)
        {
            fprintf(fp,"%f\t",k[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    fp=fopen("v.txt","w");
    for(i=0;i<7;i++)
    {
        for(j=0;j<7;j++)
        {
            fprintf(fp,"%f\t",v[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    fp=fopen("training_data.txt","w");
    for(i=0;i<trainParaN;i++)
    {
        fprintf(fp,"%f\n",*trainPara[i]);
    }
    fclose(fp);
#endif
    print_topo(Gene);
    return 0;

}
