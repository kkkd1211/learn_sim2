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
    double tmp,tmp2;
    for(b=3;b<7;b++)
    {
        tmp=alpha[b]*dt;
        tmp2=1;
        for(a=0;a<7;a++)
        {
            if(topolo[a][b]!=1)
                tmp*=AactB(Gene,a,b,posi);
            else if(topolo[a][b]==1)
                tmp2*=(1-AactB(Gene,a,b,posi));
        }
        if (tmp2!=1)
            tmp*=(1-tmp2);
        Gene[b]->c1[posi]+=tmp;
    }
}
double AactB(pgene Gene[7],int a,int b,int posi)
{
    if(topolo[a][b]==0)
    {
        return 1;
    }
    else
    {
        double tmp=pow(1+C*fabs(k[a][b])*Gene[a]->c0[posi],n);
        if(topolo[a][b]==1)
        {
            return((tmp-1)/(tmp+C-1));
        }
        else if(topolo[a][b]==-1)
        {
            return(C/(tmp+C-1));
        }
        else if(topolo[a][b]==2)
        {
            return((C*(tmp-1))/((tmp+C-1)*(tmp+C-1)));
        }
        else
            return 1;
    }

}

int Sign(double x)
{
    if(x>0)
    {
            return 1;
    }
    else if(x<0)
    {
            return -1;
    }
    else
        return 0;
}


void training(pgene Gene[7])
{
    int step,i,j;
    double init_err=0;
    double err=0;
    double delta;
    ln_rate=ln_rate_max;
    for(step=0;step<traintime;step++)
    {
        init_err=0;
        err=0;
        init_err=run(Gene);
        printf("step:%d\terr:%.10f\n",step,init_err);
        for(i=0;i<7;i++)
        {
            printf("\t");
            for(j=3;j<7;j++)
            {
                printf("%f\t",k[i][j]);
            }
            printf("\n");
        }
        printf("\t\t");
        for(i=3;i<7;i++)
        {
            printf("%f\t",alpha[i]);
        }
        printf("\n");
        for(i=0;i<7;i++)
        {
            for(j=3;j<7;j++)
            {
                delta=0.000000001*k[i][j]+0.00001;
                k_new[i][j]=k[i][j];
                k[i][j]+=delta;
                err=run(Gene);
                k[i][j]-=delta;
                k_new[i][j]+=(init_err-err)*ln_rate/delta;
            }
        }
        for(i=3;i<7;i++)
        {
            delta=0.000000001*alpha[i];
            alpha_new[i]=alpha[i];
            alpha[i]+=delta;
            err=run(Gene);
            alpha[i]-=delta;
            alpha_new[i]+=(init_err-err)*ln_rate/delta;
        }
        for(i=0;i<7;i++)
        {
            for(j=3;j<7;j++)
                k[i][j]=k_new[i][j];
        }
        for(i=3;i<7;i++)
            alpha[i]=alpha_new[i];
        ln_rate-=D_rate;
    }
}
double run(pgene Gene[7])
{
    int i,j;
    double err=0;
    for(i=3;i<7;i++)
        Gene[i]->setinit();
    Gene[4]->setvar(mhb);
    for(i=0;i<7;i++)
    {
        for(j=3;j<7;j++)
            topolo[i][j]=Sign(k[i][j]);
    }
    for(i=0;i<T;i++)
    {
        nextstep(Gene);
        for(j=3;j<7;j++)
            Gene[j]->next();
    }
    for(i=3;i<7;i++)
    {
        err+=Gene[i]->error();
    }
    return(err);
}




