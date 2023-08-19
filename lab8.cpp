#include <bits/stdc++.h>
#include <ctime>
#include <deque>

using namespace std;
typedef vector<int> ve;

class inode{
    public:
    string name;
    int size;
    bool type;
    string date_created;
    string date_modified;
    int data_block1;
    int data_block2;
    int data_block3;
    int index_block;
    inode(){
        name="";
        size=0;
        type=-1;
        date_created="";
        date_modified="";
        data_block1=-1;
        data_block2=-1;
        data_block3=-1;
        index_block=-1;
    }
};

int main(int argc,char* argv[])
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int i,j;
    string diskfile;
    int disksize;
    diskfile=argv[1];
    ofstream myfile(diskfile+".txt");
    disksize=stoi(argv[2]);
    int blocks=8*disksize;
    int inodeblocks=(15*blocks)/100;
    if((15*blocks)%100!=0){
        inodeblocks++;
    }
    int currentinode=0;
    int currdatanode=inodeblocks;
    queue<int> freeinode,freedatablock;
    for(i=0;i<inodeblocks;i++){
        freeinode.push(i);
    }
    for(i=inodeblocks;i<blocks;i++){
        freedatablock.push(i);
    }
    map<string,int> fileinode;  //maps filename to inode number
    map<int,string> filedata;   //maps inode number to filedata
    map<int,vector<int>> indexblock;    //maps index block to data blocks
    map<int,inode> inodetable;  //maps inode number to inode
    map<int,int> freespace;     //maps data block to free space
    for(i=0;i<blocks;i++){
        int temp = i;
        freespace[temp]=128;
    }
    for(i=0;i<inodeblocks;i++){
        filedata[i]="";
    }
    while(1){
        string query;
        cin>>query;
        if(query=="exit"){
            break;
        }
        else if(query=="load"){
            string name;
            cin>>name;
            if(freeinode.size()==0){
                cout<<"ERROR: no free inodeblocks"<<endl;
            }
            fileinode[name]=freeinode.front();
            freespace[freeinode.front()]=0;
            inode temp;
            temp.name=name;
            //temp.type=0;
            time_t tim;
            time(&tim);
            temp.date_created=ctime(&tim);
            temp.date_modified=ctime(&tim);
            inodetable[freeinode.front()]=temp;
            freeinode.pop();
        }
        else if(query=="delete"){
            string name;
            cin>>name;
            if(fileinode.find(name)==fileinode.end()){
                cout<<"ERROR: file not found"<<endl;
            }
            else{
                int inode=fileinode[name];
                fileinode.erase(name);
                freeinode.push(inode);
                filedata.erase(inode);
                if(inodetable[inode].data_block1!=-1){
                    freedatablock.push(inodetable[inode].data_block1);
                    freespace[inodetable[inode].data_block1]=128;
                }
                if(inodetable[inode].data_block2!=-1){
                    freedatablock.push(inodetable[inode].data_block2);
                    freespace[inodetable[inode].data_block2]=128;
                }
                if(inodetable[inode].data_block3!=-1){
                    freedatablock.push(inodetable[inode].data_block3);
                    freespace[inodetable[inode].data_block3]=128;
                }
                if(inodetable[inode].index_block!=-1){
                    freedatablock.push(inodetable[inode].index_block);
                    freespace[inodetable[inode].index_block]=128;
                }
                if(inodetable[inode].index_block!=-1){
                    for(i=0;i<indexblock[inodetable[inode].index_block].size();i++){
                        freedatablock.push(indexblock[inodetable[inode].index_block][i]);
                        freespace[indexblock[inodetable[inode].index_block][i]]=128;
                    }
                }
                freeinode.push(inode);
                freespace[inode]=128;
                inodetable.erase(inode);
                indexblock.erase(inode);
            }
        }
        else if(query=="print"){
            string name;
            cin>>name;
            if(fileinode.find(name)==fileinode.end()){
                cout<<"ERROR: file not found"<<endl;
            }
            else{
                int inode=fileinode[name];
                cout<<filedata[inode]<<endl;
            }
        }
        else if(query=="append"){
            string name;
            cin>>name;
            if(fileinode.find(name)==fileinode.end()){
                cout<<"ERROR: file not found"<<endl;
            }
            else{
                int inode=fileinode[name];
                string data;
                getline(cin,data);
                data=data.substr(1,data.length());
                int siz=data.size();
                if(inodetable[inode].size==4480){
                    cout<<"ERROR: file size limit exceeded"<<endl;
                }
                else{
                    if(inodetable[inode].size+data.size()>4480){
                        data=data.substr(0,4480-inodetable[inode].size);
                    }
                //filedata[inode]+=data;
                int initial_data=inodetable[inode].size;  //remember this
                //inodetable[inode].size+=data.size();
                if(inodetable[inode].data_block1!=-1){
                    if(siz>0){

                    if(freespace[inodetable[inode].data_block1]>=siz){
                        freespace[inodetable[inode].data_block1]-=siz;
                        inodetable[inode].size+=siz;
                        siz=0;
                    }
                    else{
                        siz-=freespace[inodetable[inode].data_block1];
                        inodetable[inode].size+=freespace[inodetable[inode].data_block1];
                        freespace[inodetable[inode].data_block1]=0;
                    }
                    }
                }
                else{
                    if(siz>0){
                    if(freedatablock.size()==0){
                        cout<<"ERROR: no free datablocks"<<endl;
                    }
                    else{
                        inodetable[inode].data_block1=freedatablock.front();
                        freedatablock.pop();
                        if(freespace[inodetable[inode].data_block1]>=siz){
                            freespace[inodetable[inode].data_block1]-=siz;
                            inodetable[inode].size+=siz;
                            siz=0;
                        }
                        else{
                            siz-=freespace[inodetable[inode].data_block1];
                            inodetable[inode].size+=freespace[inodetable[inode].data_block1];
                            freespace[inodetable[inode].data_block1]=0;
                        }
                    }
                    }
                }
                if(inodetable[inode].data_block2!=-1){
                    if(siz>0){
                    if(freespace[inodetable[inode].data_block2]>=siz){
                        freespace[inodetable[inode].data_block2]-=siz;
                        inodetable[inode].size+=siz;
                        siz=0;
                    }
                    else{
                        siz-=freespace[inodetable[inode].data_block2];
                        inodetable[inode].size+=freespace[inodetable[inode].data_block2];
                        freespace[inodetable[inode].data_block2]=0;
                    }
                    }
                }
                else{
                    if(siz>0){
                    if(freedatablock.size()==0){
                        cout<<"ERROR: no free datablocks"<<endl;
                    }
                    else{
                        inodetable[inode].data_block2=freedatablock.front();
                        freedatablock.pop();
                        if(freespace[inodetable[inode].data_block2]>=siz){
                            freespace[inodetable[inode].data_block2]-=siz;
                            inodetable[inode].size+=siz;
                            siz=0;
                        }
                        else{
                            siz-=freespace[inodetable[inode].data_block2];
                            inodetable[inode].size+=freespace[inodetable[inode].data_block2];
                            freespace[inodetable[inode].data_block2]=0;
                        }
                    }
                    }
                }
                if(inodetable[inode].data_block3!=-1){
                    if(siz>0){
                    if(freespace[inodetable[inode].data_block3]>=siz){
                        freespace[inodetable[inode].data_block3]-=siz;
                        inodetable[inode].size+=siz;
                        siz=0;
                    }
                    else{
                        siz-=freespace[inodetable[inode].data_block3];
                        inodetable[inode].size+=freespace[inodetable[inode].data_block3];
                        freespace[inodetable[inode].data_block3]=0;
                    }
                    }
                }
                else{
                    if(siz>0){
                    if(freedatablock.size()==0){
                        cout<<"ERROR: no free datablocks"<<endl;
                    }
                    else{
                        inodetable[inode].data_block3=freedatablock.front();
                        freedatablock.pop();
                        if(freespace[inodetable[inode].data_block3]>=siz){
                            freespace[inodetable[inode].data_block3]-=siz;
                            inodetable[inode].size+=siz;
                            siz=0;
                        }
                        else{
                            siz-=freespace[inodetable[inode].data_block3];
                            inodetable[inode].size+=freespace[inodetable[inode].data_block3];
                            freespace[inodetable[inode].data_block3]=0;
                        }
                    }
                    }
                }
                if(inodetable[inode].index_block!=-1){
                    if(siz>0){
                      int num=indexblock[inodetable[inode].index_block].size();
                      int sum=freespace[indexblock[inodetable[inode].index_block][num-1]]+(32-num)*128;
                      inodetable[inode].size+=min(siz,freespace[indexblock[inodetable[inode].index_block][num-1]]);
                        siz-=freespace[indexblock[inodetable[inode].index_block][num-1]];
                        int count=num;
                        while(siz>0){
                            if(count==32){
                                cout<<"ERROR: file limit exceeded"<<endl;
                                break;
                            }
                            if(freedatablock.size()==0){
                                cout<<"ERROR: no free datablocks"<<endl;
                                break;
                            }
                            else{
                                indexblock[inodetable[inode].index_block].push_back(freedatablock.front());
                                count++;
                                freedatablock.pop();
                                if(freespace[indexblock[inodetable[inode].index_block][num]]>=siz){
                                    freespace[indexblock[inodetable[inode].index_block][num]]-=siz;
                                    inodetable[inode].size+=siz;
                                    siz=0;
                                }
                                else{
                                    siz-=freespace[indexblock[inodetable[inode].index_block][num]];
                                    inodetable[inode].size+=freespace[indexblock[inodetable[inode].index_block][num]];
                                    freespace[indexblock[inodetable[inode].index_block][num]]=0;
                                }
                                num++;
                            }
                        }
                    }
                }
                else{
                    if(siz>0){
                    if(freedatablock.size()==0){
                        cout<<"ERROR: no free datablocks"<<endl;
                    }
                    else{
                        int count=0;
                        inodetable[inode].index_block=freedatablock.front();
                        freespace[inodetable[inode].index_block]=0;
                        freedatablock.pop();
                        while(siz>0){
                            if(count==32){
                                cout<<"ERROR: file limit exceeded"<<endl;
                                break;
                            }
                            if(freedatablock.size()==0){
                                cout<<"ERROR: no free datablocks"<<endl;
                                break;
                            }
                            else{
                                indexblock[inodetable[inode].index_block].push_back(freedatablock.front());
                                count++;
                                freedatablock.pop();
                                if(freespace[indexblock[inodetable[inode].index_block].back()]>=siz){
                                    freespace[indexblock[inodetable[inode].index_block].back()]-=siz;
                                    inodetable[inode].size+=siz;
                                    siz=0;
                                }
                                else{
                                    siz-=freespace[indexblock[inodetable[inode].index_block].back()];
                                    inodetable[inode].size+=freespace[indexblock[inodetable[inode].index_block].back()];
                                    freespace[indexblock[inodetable[inode].index_block].back()]=0;
                                }
                            }
                        }
                    }
                    }
                }
                int addedsize=inodetable[inode].size-initial_data;
                data=data.substr(0,addedsize);
                filedata[inode]+=data;
                time_t tim;
                time(&tim);
                inodetable[inode].date_modified=ctime(&tim);
            }
            }
        }
        else if(query=="display"){
            for(auto i:fileinode){
                cout<<"filename :"<<i.first<<" ,size :"<<inodetable[i.second].size<<endl;
            }
        }
        else if(query=="freespace"){
            int n=0,space=0;
            for(auto i:freespace){
                if(i.second==128){
                    n++;
                }
                space+=i.second;
            }
            cout<<"available free blocks :"<<n<<" , available free space(in bytes) :"<<space<<endl;
        }
        else if(query=="printinode"){
            string name;
            cin>>name;
            if(fileinode.find(name)==fileinode.end()){
                cout<<"ERROR: file not found"<<endl;
            }
            else{
                int inode=fileinode[name];
                cout<<"Filename: "<<name<<endl;
                cout<<"Size: "<<inodetable[inode].size<<endl;
                cout<<"Date created: "<<inodetable[inode].date_created;
                cout<<"Date Last modified: "<<inodetable[inode].date_modified;
                vector<int> d;
                //if(inodetable[inode].data_block1!=-1){
                    d.push_back(inodetable[inode].data_block1);
                //}
                //if(inodetable[inode].data_block2!=-1){
                    d.push_back(inodetable[inode].data_block2);
                //}
                //if(inodetable[inode].data_block3!=-1){
                    d.push_back(inodetable[inode].data_block3);
                //}
                cout<<"Data blocks: ";
                for(auto i:d){
                    cout<<i<<" ";
                }
                cout<<endl;
                //if(inodetable[inode].index_block!=-1){
                    cout<<"Index block is stored in: "<<inodetable[inode].index_block<<endl;
                    cout<<"Index block contents: ";
                    if(inodetable[inode].index_block!=-1){
                    for(auto i:indexblock[inodetable[inode].index_block]){
                        cout<<i<<" ";
                    }
                    }
                    cout<<endl;
                //}
            }
        }
        else{
            cout<<"ERROR: invalid query"<<endl;
        }
    }
    myfile<<"File Information on the disk:"<<endl;
    myfile<<endl;
    for(auto i:fileinode){
        myfile<<"Filename :"<<i.first<<endl;
        myfile<<"Inode block address :"<<i.second<<endl;
        myfile<<"File Size :"<<inodetable[i.second].size<<endl;
        myfile<<"Date created :"<<inodetable[i.second].date_created;
        myfile<<"Date Last modified :"<<inodetable[i.second].date_modified;
        myfile<<"Direct Data blocks :"<<inodetable[i.second].data_block1<<" "<<inodetable[i.second].data_block2<<" "<<inodetable[i.second].data_block3<<"(-1 means no data block)"<<endl;
        myfile<<"Index block :"<<inodetable[i.second].index_block<<"(-1 means no index block)"<<endl;
        myfile<<"Index block contents :";
        if(inodetable[i.second].index_block!=-1){
            for(auto j:indexblock[inodetable[i.second].index_block]){
                myfile<<j<<" ";
            }
        }
        myfile<<endl;
        myfile<<"File data :"<<filedata[i.second]<<endl;
        myfile<<endl;
    }
    myfile<<"Free space information on the disk:"<<endl;
    for(auto i:freespace){
        myfile<<"Block number :"<<i.first<<" ,Free space (in bytes):"<<i.second<<endl;
    }
    myfile.close();
    return 0;
}