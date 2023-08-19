#include <bits/stdc++.h>
#include <deque>
#define int long long
 
using namespace std;
typedef vector<int> ve;
 
int32_t main()
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    //cout<<"Enter no.of blocks:";
    printf("Enter no.of blocks:\n");
    int nb,np,i,j;
    //cin>>nb;
    scanf("%lld",&nb);
    //cout<<endl;
    //cout<<"Enter "<<nb<<"block sizes:";
    printf("Enter %lld block sizes:\n",nb);
    int b[nb];
    for(i=0;i<nb;i++){
        cin>>b[i];
    }
    //cout<<endl;
    //cout<<"Enter no.of process:";
    printf("Enter no.of process:\n");
    cin>>np;
    //cout<<endl;
    //cout<<"Enter "<<np<<"process sizes:";
    printf("Enter %lld process sizes:\n",np);
    int p[np];
    for(i=0;i<np;i++){
        cin>>p[i];
    }
    //cout<<endl;
    cout<<"First-Fit:"<<endl;
    cout<<"Process number | Process size | Block size | Block Number"<<endl;
    int vi1[nb]={0},a[np];
    for(i=0;i<np;i++){
        a[i]=-1;
    }
    for(i=0;i<np;i++){
        for(j=0;j<nb;j++){
            if(b[j]>p[i]){
                if(vi1[j]==0){
                    a[i]=j;
                    vi1[j]=1;
                    break;
                }
            }
        }
        if(a[i]!=-1){
            cout<<i+1<<"        "<<p[i]<<"      "<<b[a[i]]<<"       "<<a[i]+1<<endl;
        }
        else{
            cout<<i+1<<"        "<<p[i]<<"      Not Allocated"<<endl;
        }
    }
    
    cout<<endl;
    cout<<"Best-Fit:"<<endl;
    cout<<"Process number | Process size | Block size | Block Number"<<endl;
    int vi2[nb]={0};
    for(i=0;i<np;i++){
        a[i]=-1;
    }
    for(i=0;i<np;i++){
        for(j=0;j<nb;j++){
            if(b[j]>p[i]){
                if(vi2[j]==0){
                    if(a[i]==-1){
                        a[i]=j;
                    }
                    else{
                    if(b[j]<b[a[i]]){
                        a[i]=j;
                    }
                    }
                }
            }
        }
        if(a[i]!=-1){
        vi2[a[i]]=1;
        }
        if(a[i]!=-1){
            cout<<i+1<<"        "<<p[i]<<"      "<<b[a[i]]<<"       "<<a[i]+1<<endl;
        }
        else{
            cout<<i+1<<"        "<<p[i]<<"      Not Allocated"<<endl;
        }
    }
 
    cout<<endl;
    cout<<"Worst-Fit:"<<endl;
    cout<<"Process number | Process size | Block size | Block Number"<<endl;
    int vi3[nb]={0};
    for(i=0;i<np;i++){
        a[i]=-1;
    }
    for(i=0;i<np;i++){
        for(j=0;j<nb;j++){
            if(b[j]>p[i]){
                if(vi3[j]==0){
                    if(a[i]==-1){
                        a[i]=j;
                    }
                    else{
                    if(b[j]>b[a[i]]){
                        a[i]=j;
                    }
                    }
                }
            }
        }
        if(a[i]!=-1){
        vi3[a[i]]=1;
        }
        if(a[i]!=-1){
            cout<<i+1<<"        "<<p[i]<<"      "<<b[a[i]]<<"       "<<a[i]+1<<endl;
        }
        else{
            cout<<i+1<<"        "<<p[i]<<"      Not Allocated"<<endl;
        }
    }
    return 0;
}