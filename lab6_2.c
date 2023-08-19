#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void transpose(long** a,int n){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            long temp=a[i][j];
            a[i][j]=a[j][i];
            a[j][i]=temp;
        }
    }
}

int main(int argc,char* argv[])
{
    struct rusage usage;
    int n,i,j,c;
    printf("Enter n value\n");
    //cout<<"Enter n value"<<endl;
    //cin>>n;
    scanf("%d",&n);
    //cout<<"Enter choice:\nMemory Allocated once - 1\nMemory Allocated each time - 2"<<endl;
    printf("Enter choice:\nMemory Allocated once - 1\nMemory Allocated each time - 2\n");
    //cin>>c;
    scanf("%d",&c);
    //cout<<"Output:"<<endl;
    printf("Output:\n");
    srand(time(0));
    if(c==1){
      int basemem;
      getrusage(RUSAGE_SELF,&usage);
      basemem=usage.ru_maxrss;
      long **a=(long**)malloc(n*sizeof(long*));
      long **b=(long**)malloc(n*sizeof(long*));
      long **x=(long**)malloc(n*sizeof(long*));
      long **d=(long**)malloc(n*sizeof(long*));
      long **e=(long**)malloc(n*sizeof(long*));
      for(i=0;i<n;i++){
        a[i]=(long*)malloc(n*sizeof(long));
        b[i]=(long*)malloc(n*sizeof(long));
        x[i]=(long*)malloc(n*sizeof(long));
        d[i]=(long*)malloc(n*sizeof(long));
        e[i]=(long*)malloc(n*sizeof(long));
      }
      for(i=0;i<10;i++){
        if(i==0){
            for(j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    a[j][k]=rand();
                    b[j][k]=rand();
                    x[j][k]=rand();
                    d[j][k]=rand();
                    e[j][k]=rand();
                }
                }
            transpose(a,n);
            transpose(b,n);
            transpose(x,n);
            transpose(d,n);
            transpose(e,n);
        }
        else{
            transpose(a,n);
            transpose(b,n);
            transpose(x,n);
            transpose(d,n);
            transpose(e,n);
        }
        getrusage(RUSAGE_SELF,&usage);
        int pgf=usage.ru_minflt;
        int endmem=usage.ru_maxrss;
        printf("memory usage : %d + %d, page faults: %d\n",basemem,endmem,pgf);
      }
    }
    else{
      //printf("2\n");
      int basemem;
      getrusage(RUSAGE_SELF,&usage);
      basemem=usage.ru_maxrss;
      for(i=0;i<10;i++){
        long **a=(long**)malloc(n*sizeof(long*));
        long **b=(long**)malloc(n*sizeof(long*));
        long **x=(long**)malloc(n*sizeof(long*));
        long **d=(long**)malloc(n*sizeof(long*));
        long **e=(long**)malloc(n*sizeof(long*));
        for(j=0;j<n;j++){
        a[j]=(long*)malloc(n*sizeof(long));
        b[j]=(long*)malloc(n*sizeof(long));
        x[j]=(long*)malloc(n*sizeof(long));
        d[j]=(long*)malloc(n*sizeof(long));
        e[j]=(long*)malloc(n*sizeof(long));
        }
        for(j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    a[j][k]=rand();
                    b[j][k]=rand();
                    x[j][k]=rand();
                    d[j][k]=rand();
                    e[j][k]=rand();
                }
        }
            transpose(a,n);
            transpose(b,n);
            transpose(x,n);
            transpose(d,n);
            transpose(e,n);
        getrusage(RUSAGE_SELF,&usage);
        int pgf=usage.ru_minflt;
        int endmem=usage.ru_maxrss;
        printf("memory usage : %d + %d, page faults: %d\n",basemem,endmem,pgf);
      }
    }
    return 0;
}