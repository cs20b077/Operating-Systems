#include <bits/stdc++.h>
#include <deque>
#define int long long
#define mod 1000000007
 
using namespace std;
typedef vector<int> ve;
typedef pair <int,int> pa;
typedef priority_queue<int> p;
typedef vector<pair<int,int>> vp;

map<string,int> arrival,burst,burst_1,priority,complete;
map<string,string> name;
map<int,vector<string>> process;
 
struct pid{
    bool operator()(string const& p1,string const& p2)
    {
        int l1 = p1.length();
        int l2 = p2.length();
        string a = p1.substr(1, l1 - 1);
        string b = p2.substr(1, l2 - 1);
        return stoi(a) > stoi(b);
    }
};

struct priority_order{
    bool operator()(string const& p1,string const& p2)
    {
        if(priority[p1]==priority[p2]){
            int l1 = p1.length();
            int l2 = p2.length();
            string a = p1.substr(1, l1 - 1);
            string b = p2.substr(1, l2 - 1);
            return stoi(a) > stoi(b);
        }
        else{
            return priority[p1]>priority[p2];
        }
    }
};

struct burst_t{
    bool operator()(string const& p1,string const& p2)
    {
        bool p;
        if(burst[p1]==burst[p2]){
            int l1 = p1.length();
            int l2 = p2.length();
            string a = p1.substr(1, l1 - 1);
            string b = p2.substr(1, l2 - 1);
            return stoi(a) > stoi(b);
        }
        else{
            return burst[p1]>burst[p2];
        }
    }
};

int quant;

int32_t main()
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    cin>>quant;
    int n,i;        //no.of processes
    cin>>n;
    int tot_time=0,last_burst;
    vector<string> ids;
    int totaltime = 0;
    for(i=0;i<n;i++){
        string p;
        int arr_time;
        int burst_time;
        string pname;
        int pri;
        cin>>p>>arr_time>>burst_time>>pname>>pri;
        if(i == 0){
            totaltime = arr_time+burst_time;
        }
        else {
            if(totaltime < arr_time)
            {
                totaltime = arr_time + burst_time;
            }
            else totaltime = totaltime + burst_time;
        }
        ids.push_back(p);
        arrival[p]=arr_time;
        burst[p]=burst_time;
        burst_1[p]=burst_time;
        priority[p]=pri;
        name[p]=pname;
        process[arr_time].push_back(p);
        tot_time+=burst_time;
    }
    priority_queue<string,vector<string>,priority_order> systemc;
    priority_queue<string,vector<string>,pid> ip,iep;
    priority_queue<string,vector<string>,burst_t> bp,sp;
    
    vector<pair<string,pair<int,int>>> v;
    int t=0,prevt=0,pt=0,comptime=max(tot_time,totaltime),run=0;
    cout<<endl;
    //cout<<comptime<<endl;
    int np = n;
    while(1){
        if(t==comptime){
            break;
        }
        for (int j = 0; j < process[t].size(); j++)
        {
            if (name[process[t][j]]=="sys")
            {
                systemc.push(process[t][j]);
            }
            else if (name[process[t][j]]=="ip")
            {
                ip.push(process[t][j]);
            }
            else if (name[process[t][j]]=="iep")
            {
                iep.push(process[t][j]);
            }
            else if (name[process[t][j]]=="bp")
            {
                bp.push(process[t][j]);
            }
            else if (name[process[t][j]]=="sp")
            {
                sp.push(process[t][j]);
            }
        }

        if(systemc.empty() && ip.empty() && iep.empty() && bp.empty() && sp.empty() && t!=comptime){
            t++;
            prevt=t;
            continue;
        }

        if (pt%5==0)
        {
            if(systemc.empty()){
                    pt++;
                    continue;
            }
            if(t-prevt==quant){
                //cout<<systemc.top()<<": "<<prevt<<" "<<t<<endl;
                /*burst[systemc.top()]--;
                complete[systemc.top()]=t;
                if(burst[systemc.top()]==0){
                    systemc.pop();
                }
                */
                prevt=t;
                pt++;
                continue;
            }
            else{
                if(burst[systemc.top()]==0){
                    //cout<<systemc.top()<<": "<<prevt<<" "<<t<<endl;
                    //complete[systemc.top()]=t;
                    systemc.pop();
                    np--;
                    continue;
                }
                else{
                    //cout<<systemc.top()<<": "<<t<<" "<<t+1<<endl;
                    v.push_back({systemc.top(),{t,t+1}});
                    complete[systemc.top()]=t+1;
                    string temp=systemc.top();
                    burst[temp]--;
                    systemc.pop();
                    systemc.push(temp);
                    t++;
                }
            }
        }

        if (pt%5==1)
        {
            if(ip.empty()){
                    pt++;
                    continue;
            }
            if(t-prevt==quant){
                //cout<<ip.top()<<": "<<prevt<<" "<<t<<endl;
                /*burst[ip.top()]--;
                complete[ip.top()]=t;
                if(burst[ip.top()]==0){
                    ip.pop();
                }
                */
                prevt=t;
                pt++;
                continue;
            }
            else{
                
                if(burst[ip.top()]==0){
                    //cout<<ip.top()<<": "<<prevt<<" "<<t<<endl;
                    //complete[ip.top()]=t;
                    ip.pop();
                    np--;
                    continue;
                }
                else{
                    //cout<<ip.top()<<": "<<t<<" "<<t+1<<endl;
                    v.push_back({ip.top(),{t,t+1}});
                    complete[ip.top()]=t+1;
                    string temp=ip.top();
                    burst[temp]--;
                    ip.pop();
                    ip.push(temp);
                    t++;
                }
            }
        }

        if (pt%5==2)
        {
            if(iep.empty()){
                    pt++;
                    continue;
            }
            if(t-prevt==quant){
                //cout<<iep.top()<<": "<<prevt<<" "<<t<<endl;
                /*burst[iep.top()]--;
                complete[iep.top()]=t;
                if(burst[iep.top()]==0){
                    iep.pop();
                }
                */
                prevt=t;
                pt++;
                continue;
            }
            else{
                
                if(burst[iep.top()]==0){
                    //cout<<iep.top()<<": "<<prevt<<" "<<t<<endl;
                    //complete[iep.top()]=t;
                    iep.pop();
                    np--;
                    continue;
                }
                else{
                    //cout<<iep.top()<<": "<<t<<" "<<t+1<<endl;
                    v.push_back({iep.top(),{t,t+1}});
                    complete[iep.top()]=t+1;
                    string temp=iep.top();
                    burst[temp]--;
                    iep.pop();
                    iep.push(temp);
                    t++;
                }
            }
        }

        if (pt%5==3)
        {
            if(bp.empty()){
                    pt++;
                    continue;
            }
            if(t-prevt==quant){
                //cout<<bp.top()<<": "<<prevt<<" "<<t<<endl;
                /*burst[bp.top()]--;
                complete[bp.top()]=t;
                if(burst[bp.top()]==0){
                    bp.pop();
                }
                */
                prevt=t;
                pt++;
                continue;
            }
            else{
                
                if(burst[bp.top()]==0){
                    //cout<<bp.top()<<": "<<prevt<<" "<<t<<endl;
                    //complete[bp.top()]=t;
                    bp.pop();
                    np--;
                    continue;
                }
                else{
                    //cout<<bp.top()<<": "<<t<<" "<<t+1<<endl;
                    v.push_back({bp.top(),{t,t+1}});
                    complete[bp.top()]=t+1;
                    string temp=bp.top();
                    burst[temp]--;
                    bp.pop();
                    bp.push(temp);
                    t++;
                }
            }
        }

        if (pt%5==4)
        {
            if(sp.empty()){
                    pt++;
                    continue;
            }
            if(t-prevt==quant){
                //cout<<sp.top()<<": "<<prevt<<" "<<t<<endl;
                /*burst[sp.top()]--;
                complete[sp.top()]=t;
                if(burst[sp.top()]==0){
                    sp.pop();
                }
                */
                prevt=t;
                pt++;
                continue;
            }
            else{
                
                if(burst[sp.top()]==0){
                    //cout<<sp.top()<<": "<<prevt<<" "<<t<<endl;
                    //complete[sp.top()]=t;
                    sp.pop();
                    np--;
                    continue;
                }
                else{
                    //cout<<sp.top()<<": "<<t<<" "<<t+1<<endl;
                    v.push_back({sp.top(),{t,t+1}});
                    complete[sp.top()]=t+1;
                    string temp=sp.top();
                    burst[temp]--;
                    sp.pop();
                    sp.push(temp);
                    t++;
                }
            }
        }
    }
    int prev=v[0].second.first;
    for(i=0;i<v.size();i++){
       if(i==v.size()-1){
           cout<<v[i].first<<": "<<prev<<" "<<v[i].second.second<<endl;
       }
       else {
           if(v[i].first==v[i+1].first){

               continue;
           }
           else{
               cout<<v[i].first<<": "<<prev<<" "<<v[i].second.second<<endl;
               prev=v[i+1].second.first;
           }
       }
    }
    cout<<endl;

    for(i=0;i<n;i++){
        cout<<"Process id: "<<ids[i]<<endl;
        cout<<"completion time: "<<complete[ids[i]]<<endl;
        cout<<"Turn around time: "<<complete[ids[i]]-arrival[ids[i]]<<endl;
        cout<<"Waiting time: "<<complete[ids[i]]-arrival[ids[i]]-burst_1[ids[i]]<<endl;
        cout<<endl;
    }
    return 0;
}