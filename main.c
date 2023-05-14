#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
typedef struct arguments{
    int n,num;
    int* state;
    int* used;
}arguments;
void * philosoph(void* p_arg){
    arguments* arg=(arguments*)p_arg;
    int num=arg->num;
    int r=num+1;
    if(r>=arg->n)r-=arg->n;
    int ran;
    while(1){
        ran=rand();
        sleep(ran%10+15);
        arg->state[num]=1;
        printf("Ph%d is hungry\n",num);
        while(arg->state[num]!=2){}
        arg->used[num]=num;
        printf("Ph%d is taking fork%d\n",num,num);
        arg->used[r]=num;
        printf("Ph%d is taking fork%d\n",num,r);
        ran=rand();
        printf("Ph%d is eating for %d seconds\n",num,ran%10);
        sleep(ran%10);
        arg->used[num]=0;
        printf("Fork%d is free\n",num);
        arg->used[r]=0;
        printf("Fork%d is free\n",r);
        arg->state[num]=0;
        printf("Ph%d is thinking\n\n",num);

    }
    return NULL;
}
int main()
{
    srand(time(NULL));
    int n;
    scanf("%d",&n);
    pthread_t* threads=malloc(sizeof(pthread_t)*n);
    int* used=malloc(sizeof(int)*n);
    int* state=malloc(sizeof(int)*n);
    arguments* arg=malloc(sizeof(arguments)*n);
    int i,l,r;
    for(i=0;i<n;i++){
        state[i]=0;
        used[i]=0;
    }
    for(i=0;i<n;i++){
        arg[i].n=n;
        arg[i].num=i;
        arg[i].state=state;
        arg[i].used=used;
        pthread_create(threads+i,NULL,philosoph,&arg[i]);
    }
    int iter=100;
    i=0;
    while(iter>0){
        i++;
        if(i>=n)i-=n;
        if(state[i]==1){
            state[i]=2;
            while(state[i]!=0){}
            iter--;
        }
    }
}
