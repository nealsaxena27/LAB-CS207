# include <bits/stdc++.h>
using namespace std;

class process{
    public:
        int process_id;
        int memory_required;
};

class block{
    public:
        int block_id;
        int memory;
};

void input_processes(int n, process arr[]){
    for(int i = 0; i < n; i++){
        cout<<"Enter memory_required in process "<<i+1<<": "; cin>>arr[i].memory_required;
        arr[i].process_id = i + 1;
    }
};

void input_memory_blocks(int m, block arr[]){
    for(int i = 0; i < m; i++){
        cout<<"Enter memory in block "<<i+1<<": "; cin>>arr[i].memory;
        arr[i].block_id = i + 1;
    }
};

bool compare(block &b1, block &b2){
    if(b1.memory==b2.memory) return b1.block_id < b2.block_id;
    return b1.memory > b2.memory;
}

int main(){
    int n; cout<<"Enter number of processes: "; cin>>n;
    process arr[n];
    input_processes(n, arr);
    int m; cout<<"Enter number of memory blocks: "; cin>>m;
    block arr2[m];
    input_memory_blocks(m, arr2);
    sort(arr2, arr2 + m, compare);
    int i = 0;
    cout<<"Process_ID\tBlock_ID\tMemory_Used\tMemory_wasted\n";
    for(int j = 0; j < n; j++){
        if(i < m && arr2[i].memory >= arr[j].memory_required){
            cout<<arr[j].process_id<<"\t\t"<<arr2[i].block_id<<"\t\t"<<
            arr[j].memory_required<<"\t\t"<<arr2[i].memory - arr[j].memory_required<<endl;
            i++;
        }
        else{
            cout<<arr[j].process_id<<"\t\tNA\t\tNA\t\tNA\n";
        }
    }
}