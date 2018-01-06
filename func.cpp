#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"head.h"
#include"func.h"
#include <time.h>
using namespace std;
int para_req(double x,int i)
{
    if((i>=0)&&(i<28))      ///para is k
    {
        if(x>=0)
            return 1;
        else
            return 0;
    }
    else if(i<56)           ///para is v
        return 1;
}
void setup()
{
    srand((unsigned)time(NULL));
    int i,j;
    FILE *fp,*fp2;
    for(i=0;i<7;i++)
    {
        for(j=3;j<7;j++)
        {
            k[i][j]=1.0;
            v[i][j]=3*(2.0*(rand()/2147483647.0)-1.0);
            trainPara[4*i+j-3]=&k[i][j];
            trainPara[28+4*i+j-3]=&v[i][j];
        }
    }
#ifdef read1
    printf("reading data!!!\n\n");
    fp=fopen("k.txt","r");
    fp2=fopen("v.txt","r");
    for(i=0;i<7;i++)
    {
        for(j=0;j<7;j++)
        {
            fscanf(fp,"%lf\t",&k[i][j]);
            fscanf(fp2,"%lf\t",&v[i][j]);
        }
        fscanf(fp,"\n");
        fscanf(fp2,"\n");
    }
#endif
    return;

}
int nextstep(pgene Gene[7])
{
    int posi,i,j;
    for(j=3;j<7;j++)
    {
        for(i=0;i<Nx;i++)
        {
            Gene[j]->c1[i]=Gene[j]->c0[i];
        }
    }
    for(posi=0;posi<Nx;posi++)
    {
        diff(Gene,posi);
        deg(Gene,posi);
        react(Gene,posi);
//        getchar();
    }
}
int diff(pgene Gene[7],int posi)
{
    int j;
    if(posi==0)
    {
        for(j=3;j<7;j++)
        {
            Gene[j]->c1[0]+=d*(Gene[j]->c0[1]-Gene[j]->c0[0]);
        }
    }
    else if(posi==Nx-1)
    {
        for(j=3;j<7;j++)
        {
            Gene[j]->c1[Nx-1]+=d*(Gene[j]->c0[Nx-2]-Gene[j]->c0[Nx-1]);
        }
    }
    else
    {
        for(j=3;j<7;j++)
        {
            Gene[j]->c1[posi]+=d*(Gene[j]->c0[posi-1]+Gene[j]->c0[posi+1]-2*Gene[j]->c0[posi]);
        }
    }
}
int deg(pgene Gene[7],int posi)
{
    int j;
    for(j=3;j<7;j++)
    {
        Gene[j]->c1[posi]-=dt*beta*Gene[j]->c0[posi];
    }
}
int react(pgene Gene[7],int posi)
{
    int a,b;
    double tmp;
    for(b=3;b<7;b++)
    {
        tmp=0;
        for(a=0;a<7;a++)
        {
            tmp+=mut[a][b]*AactB(Gene,a,b,posi);
        }
        tmp*=dt;
        Gene[b]->c1[posi]+=tmp;
        if(Gene[b]->c1[posi]<=0)
            Gene[b]->c1[posi]=0.000001;
    }
}
double AactB(pgene Gene[7],int a,int b,int posi)
{
    return(v[a][b]*((Gene[a]->c0[posi])/(k[a][b]+Gene[a]->c0[posi])));
}
int Sign(double x)
{
    if(x>0)
        return 1;
    else if(x<0)
        return -1;
    else
        return 0;
}
double run(pgene Gene[7])
{
    int i,j;
    double tmp;

    Gene[3]->setvar(kni_in_data);
    Gene[4]->setvar(hb_in_data);
    Gene[5]->setvar(kr_in_data);
    Gene[6]->setvar(gt_in_data);
//    for(i=0;i<7;i++)
//    {
//        for(j=3;j<7;j++)
//            topolo[i][j]=Sign(k[i][j]);
//    }
    for(i=0;i<T;i++)
    {
        nextstep(Gene);
        for(j=3;j<7;j++)
            Gene[j]->next();
    }
    tmp=0.0;
    for(i=3;i<7;i++)
    {
        tmp+=Gene[i]->error(0,100);
    }
//    tmp+=2*Gene[3]->error(50,80);
//    tmp+=2*Gene[4]->error(65,100);
//    tmp+=3*Gene[5]->error(50,70);
    tmp+=1*Gene[3]->error(0,100);
    tmp+=1*Gene[5]->error(0,100);
    return(tmp);
}

void training(pgene Gene[7])
{
    int step,i,j;
    double init_err=0;
    double errL1,errL2,errR1,errR2;
    double delta0,deltaL,deltaR;
    double tmp_err,tmp_delta;
    ln_rate=ln_rate_max;
    for(step=0;step<traintime;step++)
    {
        init_err=run(Gene);
        printf("\n\n\nstep:%d\terror:%.10f\n============k==================",step,init_err);
        for(i=0;i<trainParaN;i++)
        {
            tmp_err=init_err;
            delta0=0.00001*(0.1+fabs(*trainPara[i]));
            *trainPara[i]+=delta0;
            errR1=run(Gene);
            *trainPara[i]-=2*delta0;
            errL1=run(Gene);
            *trainPara[i]+=delta0;
            errR2=2*init_err;
            errL2=2*init_err;
            if((init_err>errR1)&&(errR1>0.0001)&&(para_req(*trainPara[i]+delta0,i)))
            {
                tmp_err=errR1;
                tmp_delta=delta0;

                deltaR=ln_rate*sqrt((init_err-errR1)/delta0);
                *trainPara[i]+=deltaR;
                errR2=run(Gene);
                *trainPara[i]-=deltaR;

                if((tmp_err>errR2)&&(errR2>0.0001)&&(para_req(*trainPara[i]+deltaR,i)))
                {
                    tmp_err=errR2;
                    tmp_delta=deltaR;
                }
            }
            if((init_err>errL1)&&(errL1>0.0001)&&(para_req(*trainPara[i]-delta0,i)))
            {
                if(tmp_err>errL1)
                {
                    tmp_err=errL1;
                    tmp_delta=0.0-delta0;
                }

                deltaL=ln_rate*sqrt((init_err-errL1)/delta0);
                *trainPara[i]-=deltaL;
                errL2=run(Gene);
                *trainPara[i]+=deltaL;

                if((tmp_err>errL2)&&(errL2>0.0001)&&(para_req(*trainPara[i]-deltaL,i)))
                {
                    tmp_err=errL2;
                    tmp_delta=0.0-deltaL;
                }
            }
            if(init_err!=tmp_err)
            {
                init_err=tmp_err;
                *trainPara[i]+=tmp_delta;
            }
            if(i%4==0)
                printf("\n");
            if(i==28)
                printf("=================v================\n");
            printf("\t%f(%f)",*trainPara[i],init_err);
        }
        ln_rate-=D_rate;
    }
}

