#include <bits/stdc++.h>
#include <deque>
#define int long long
 
using namespace std;
typedef vector<int> ve;

 
int32_t main()
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int l,ps,type,pgf=0,i,j;
    printf("Sequence length:\n");
    cin>>l;
    printf("Enter Sequence:\n");
    int p[l];
    for(int i=0;i<l;i++){
        cin>>p[i];
    }
    printf("Page-frame size:\n");
    cin>>ps;
    cout<<"Enter Page replacement strategy: 1.FIFO 2.Optimal 3.LRU"<<endl;
    cin>>type;
    if(type==1){
        cout<<"FIFO"<<endl;
        int c=0;
        map<int,int> m;
        queue<int> q;
        for(i=0;i<l;i++){
           if(m[p[i]]==0){
           if(c==ps){
               m[p[i]]=1;
               int x=q.front();
               m[x]=0;
               q.pop();
               q.push(p[i]);
               pgf++;
           }
           else{
               m[p[i]]=1;
               q.push(p[i]);
               pgf++;
               c++;
           }
           queue<int> q1=q;
           while(!q1.empty()){
               cout<<q1.front()<<" ";
               q1.pop();
           }
           cout<<endl;
           }
           else{
            cout<<"No page fault"<<endl;
           }
        }
        cout<<"Total number of page faults = "<<pgf<<endl;
    }
    else if(type==2){
        cout<<"Optimal"<<endl;
        int c=0;
        map<int,int> m;
        ve v;
        for(i=0;i<l;i++){
            if(m[p[i]]==0){
                if(c==ps){
                  int pos,y=-1;
                  for(j=0;j<v.size();j++){
                        int x=-1;
                        for(int k=i+1;k<l;k++){
                            if(v[j]==p[k]){
                                if(k-i>y){
                                    y=k-i;
                                    pos=j;
                                }
                                x=k-i;
                            }
                        }
                        if(x==-1){
                            pos=j;
                            break;
                        }
                  }
                  m[v[pos]]=0;
                  v.erase(v.begin()+pos);
                  m[p[i]]=1;
                  v.push_back(p[i]);
                  pgf++;  
                }
                else{
                    m[p[i]]=1;
                    v.push_back(p[i]);
                    pgf++;  
                    c++;
                }
                for(j=0;j<v.size();j++){
                    if(m[v[j]]!=0){
                        cout<<v[j]<<" ";
                    }
                }
                cout<<endl;
            }
            else{
                cout<<"No page fault"<<endl;
            }
        }
        cout<<"Total number of page faults = "<<pgf<<endl;
    }
    else{
        cout<<"LRU"<<endl;
        int c=0;
        map<int,int> m;
        ve v;
        for(i=0;i<l;i++){
            if(m[p[i]]==0){
                if(c==ps){
                  int x=0,pos;
                  for(j=0;j<v.size();j++){
                      if(m[v[j]]>x){
                            x=m[v[j]];
                            pos=j;
                      }
                  }
                  m[v[pos]]=0;
                  v.erase(v.begin()+pos);
                  for(j=0;j<v.size();j++){
                        if(m[v[j]]!=0){
                         m[v[j]]++;
                        }
                  }
                  m[p[i]]=1;
                  v.push_back(p[i]);
                  pgf++;  
                }
                else{
                    for(j=0;j<v.size();j++){
                        if(m[v[j]]!=0){
                         m[v[j]]++;
                        }
                    }
                    m[p[i]]=1;
                    v.push_back(p[i]);
                    pgf++;  
                    c++;
                }
                for(j=0;j<v.size();j++){
                    if(m[v[j]]!=0){
                        cout<<v[j]<<" ";
                    }
                }
                cout<<endl;
            }
            else{
                for(j=0;j<v.size();j++){
                        if(m[v[j]]!=0){
                         m[v[j]]++;
                        }
                }
                m[p[i]]=1;
                cout<<"No page fault"<<endl;
            }
        }
        cout<<"Total number of page faults = "<<pgf<<endl;
    }
    return 0;
}