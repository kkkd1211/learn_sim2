#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"head.h"
#include"func.h"
using namespace std;
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
void training(pgene Gene[7])
{
    int step,i,j;
    double init_err=0;
    double err=0;
    double err2=0;
    double delta,tmp,de;
    ln_rate=ln_rate_max;
    for(step=0;step<traintime;step++)
    {
        init_err=0;
        err=0;
        init_err=run(Gene);
        printf("step:%d\terr:%.10f\n",step,init_err);
        for(i=0;i<7;i++)
        {
            for(j=3;j<7;j++)
            {
                delta=0.00001*k[i][j]+0.000001;
                
                k[i][j]+=delta;
                err=run(Gene);
                k[i][j]-=delta;
                de=(init_err-err)/delta;

                if((de>0)&&(err>0.0001))
                {
                    tmp=ln_rate*sqrt(de);
                    k[i][j]+=tmp;
                    err2=run(Gene);
                    if((init_err-err2<0)||(err2<0.0001))
                    {
                        k[i][j]=k[i][j]-tmp+delta;
                        init_err=err;
                    }
                    else
                        init_err=err2;
                }
                else if(de<0)
                {

                    k[i][j]-=delta;
                    err=run(Gene);
                    k[i][j]+=delta;
                    de=(init_err-err)/delta;
                    if((de>0)&&(err>0.0001))
                    {
                        tmp=ln_rate*sqrt(de);
                        k[i][j]-=tmp;
                        if(k[i][j]<0)
                        {
                            k[i][j]+=tmp;
                            tmp=k[i][j]*0.5;
                            k[i][j]-=tmp;
                        }
                        err2=run(Gene);
                        if((init_err-err2<0)||(err2<0.0001))
                        {
                            k[i][j]=k[i][j]+tmp-delta;
                            init_err=err;
                        }
                        else
                            init_err=err2;
                    }
                }
                printf("%f(%f)\t",k[i][j],init_err);
            }
            printf("\n");
        }




        for(i=0;i<7;i++)
        {
            for(j=3;j<7;j++)
            {
                delta=0.00001*fabs(v[i][j])+0.00001;
                v[i][j]+=delta;
                err=run(Gene);
                v[i][j]-=delta;
                de=(init_err-err)/delta;
                if((de>0)&&(err>0.0001))
                {
                    tmp=ln_rate*(de);                           //sqrt
                    v[i][j]+=tmp;
                    err2=run(Gene);
                    if((init_err-err2<0)||(err2<0.0001))
                    {
                        v[i][j]=v[i][j]-tmp+delta;
                        init_err=err;
                    }
                    else
                        init_err=err2;
                }
                else if(de<0)
                {
                    v[i][j]-=delta;
                    err=run(Gene);
                    v[i][j]+=delta;
                    de=(init_err-err)/delta;
                    if((de>0)&&(err>0.0001))
                    {
                        tmp=ln_rate*(de);                       //sqrt
                        v[i][j]-=tmp;
                        err2=run(Gene);
                        if((init_err-err2<0)||(err2<0.0001))
                        {
                            v[i][j]=v[i][j]+tmp-delta;
                            init_err=err;
                        }
                        else
                            init_err=err2;
                    }
                }
                printf("\t%f(%f)",v[i][j],init_err);
            }
            printf("\n");
        }
        ln_rate-=D_rate;
    }
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
//    tmp+=2*Gene[4]->error(0,100);
    tmp+=2*Gene[4]->error(65,100);
    tmp+=2*Gene[3]->error(50,80);
    tmp+=3*Gene[5]->error(50,70);
    return(tmp);
}




