#include <bits/stdc++.h>
#include <deque>
 
int n=1000;
using namespace std;
typedef vector<int> ve;

 
int main(int argc,char* argv[])
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    //int n;
    //cin>>n;
    int algo,start=2000;
    //start=53;//pp
    //cout<<"1"<<endl;
    if(argc>2)
    {
        start=atoi(argv[1]);
        algo=atoi(argv[2]);
    }
    else{
        algo=atoi(argv[1]);
    }
    //cout<<"2"<<endl;
    srand(time(0));
    int curr=start;
    float seek=0,sum=0;
    int a[n];
    for(int i=0;i<n;i++)
    {
        a[i]=rand()%5000;
        //cin>>a[i];//pp
    }
    if(algo==1){
        for(int i=0;i<n;i++){
            int jump=abs(curr-a[i]);
            if(jump>0)
            {
                seek++;
            }
            sum+=jump;
            curr=a[i];
        }
        seek=1000;
        cout<<"Average Seek Time: "<<(float)(sum/seek)<<endl;
        cout<<"Total Seek Time: "<<(int)sum<<endl;
    }
    else if(algo==2){
        for(int i=0;i<n;i++){
            int jump,s=i;
            for(int j=i;j<n;j++){
                if(j==i){
                    jump=abs(curr-a[j]);
                }
                else{
                    if(abs(curr-a[j])<jump){
                        jump=abs(curr-a[j]);
                        s=j;
                    }
                }
            }
            swap(a[i],a[s]);
            if(jump>0)
            {
                seek++;
            }
            sum+=jump;
            curr=a[i];
        }
        seek=1000;
        cout<<"Average Seek Time: "<<(float)(sum/seek)<<endl;
        cout<<"Total Seek Time: "<<(int)sum<<endl;
    }
    else if(algo==3){
        sort(a,a+n);
        int index;;
        for(int i=0;i<n;i++){
            if(a[i]>curr){
                index=i-1;
                break;
            }
        }
        int i=index;
        while(i>=0){
            int jump=abs(curr-a[i]);
            if(jump>0)
            {
                seek++;
            }
            sum+=jump;
            curr=a[i];
            i--;
        }
        if(curr>0){
            sum+=curr;
            seek++;
            curr=0;
        }
        for(i=index+1;i<n;i++){
            int jump=abs(curr-a[i]);
            if(jump>0)
            {
                seek++;
            }
            sum+=jump;
            curr=a[i];
        }
        seek=1000;
        cout<<"Average Seek Time: "<<(float)(sum/seek)<<endl;
        cout<<"Total Seek Time: "<<(int)sum<<endl;
    }
    else if(algo==4){
        sort(a,a+n);
        int index,i;
        for(i=0;i<n;i++){
            if(a[i]>curr){
                index=i-1;
                break;
            }
        }
        for(i=index+1;i<n;i++){
            int jump=abs(curr-a[i]);
            if(jump>0)
            {
                seek++;
            }
            sum+=jump;
            curr=a[i];
        }
        if(curr<4999){
            sum+=4999-curr;
            seek++;
            curr=4999;
        }
        sum+=4999;
        seek++;
        curr=0;
        for(i=0;i<=index;i++){
            int jump=abs(curr-a[i]);
            if(jump>0)
            {
                seek++;
            }
            sum+=jump;
            curr=a[i];
        }
        seek=1000;
        cout<<"Average Seek Time: "<<(float)(sum/seek)<<endl;
        cout<<"Total Seek Time: "<<(int)sum<<endl;
    }
    else if(algo==5){
        sort(a,a+n);
        int index;;
        for(int i=0;i<n;i++){
            if(a[i]>curr){
                index=i-1;
                break;
            }
        }
        int i=index;
        while(i>=0){
            int jump=abs(curr-a[i]);
            if(jump>0)
            {
                seek++;
            }
            sum+=jump;
            curr=a[i];
            i--;
        }
        for(i=index+1;i<n;i++){
            int jump=abs(curr-a[i]);
            if(jump>0)
            {
                seek++;
            }
            sum+=jump;
            curr=a[i];
        }
        seek=1000;
        cout<<"Average Seek Time: "<<(float)(sum/seek)<<endl;
        cout<<"Total Seek Time: "<<(int)sum<<endl;
    }
    else{
        sort(a,a+n);
        int index,i;
        for(i=0;i<n;i++){
            if(a[i]>curr){
                index=i-1;
                break;
            }
        }
        for(i=index+1;i<n;i++){
            int jump=abs(curr-a[i]);
            if(jump>0)
            {
                seek++;
            }
            sum+=jump;
            curr=a[i];
        }
        for(i=0;i<=index;i++){
            int jump=abs(curr-a[i]);
            if(jump>0)
            {
                seek++;
            }
            sum+=jump;
            curr=a[i];
        }
        seek=1000;
        cout<<"Average Seek Time: "<<(float)(sum/seek)<<endl;
        cout<<"Total Seek Time: "<<(int)sum<<endl;
    }
    return 0;
}