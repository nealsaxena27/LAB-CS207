# include <bits/stdc++.h>
using namespace std;

void initialize(int &n, int &m, int &ri, vector<int> &available,
vector<vector<int>> &allocation, vector<vector<int>> &max,
vector<vector<int>> &need, vector<int> &request){
     cout<<"Enter number of processes"; cin>>n;
     cout<<"Enter number of resource types"; cin>>m;
     allocation.assign(n, vector<int>(m, 0));
     max.assign(n, vector<int>(m, 0));
     need.assign(n, vector<int>(m, 0));
     available.assign(m, 0);
     request.assign(m, 0);
     cout<<"Enter number of available resources of each type:"<<endl;
     for(int i = 0; i < m; i++) cin>>available[i];
     for(int i = 0; i < n; i++){
        cout<<"Enter maximum demand of each resource type for process "<<i+1<<":"<<endl;
        for(int j = 0; j < m; j++) cin>>max[i][j];
     }
     for(int i = 0; i < n; i++){
        cout<<"Enter number of allocated resources of each resource type for process "<<i+1<<":"<<endl;
        for(int j = 0; j < m; j++) cin>>allocation[i][j];
     }
     for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
     }
     cout<<"Enter requesting process id: "; cin>>ri; ri--;
     cout<<"Enter number of instances of each resource type requested by process "<<(ri+1)<<":"<<endl;
     for(int j = 0; j < m; j++) cin>>request[j];
}

bool is_less_equal(vector<int> &x, vector<int> &y){
    int n = x.size();
    for(int i = 0; i < n; i++){
        if(x[i] > y[i]) return false;
    }
    return true;
}

void add(vector<int> &x, vector<int> &y){
    int n = y.size();
    for(int i = 0; i < n; i++){
        x[i] += y[i];
    }
}
void subtract(vector<int> &x, vector<int> &y){
    int n = y.size();
    for(int i = 0; i < n; i++){
        x[i] -= y[i];
    }
}

bool bankers_algorithm(int &n, int &m, vector<int> &available,
vector<vector<int>> &allocation, vector<vector<int>> &max, vector<vector<int>> &need){
    vector<int> work(available.begin(), available.end());
    vector<int> finish(n, false);
    bool found = false;
    do{
        found = false;
        for(int i = 0; i < n; i++){
            if(finish[i]==false){
                if(is_less_equal(need[i], work)){
                    add(work, allocation[i]);
                    finish[i] = true;
                    found = true;
                }
            }
        }
    } while(found);
    bool all_finished = true;
    for(int i = 0; i < n; i++){
        if(finish[i]==false) all_finished = false;
    }
    if(all_finished) return true;
    else return false;
}

void process_request(int &n, int &m, int &ri, vector<int> &available,
vector<vector<int>> &allocation, vector<vector<int>> &max,
vector<vector<int>> &need, vector<int> &request){
    if(is_less_equal(request, need[ri])==false){
        cout<<"Process "<<ri+1<<" has exceeded its maximum claim"<<endl;
        return;
    }
    if(is_less_equal(request, available)==false){
        cout<<"Process "<<ri+1<<" must wait, since resources are not available"<<endl;
        return;
    }
    subtract(available, request);
    add(allocation[ri], request);
    subtract(need[ri], request);
    bool is_safe = bankers_algorithm(n, m, available, allocation, max, need);
    if(is_safe){
        cout<<"Requested resources have been allocated successfully to process "<<ri+1<<endl;
        cout<<"No deadlock has occured"<<endl;
    }
    else{
        cout<<"Requested resources can not be allocated right now, ";
        cout<<"in order to prevent deadlock"<<endl;
        add(available, request);
        subtract(allocation[ri], request);
        subtract(need[ri], request);
    }
}

int main(){
    int n, m, ri;
    vector<int> available;
    vector<int> request;
    vector<vector<int>> allocation, max, need;
    initialize(n, m, ri, available, allocation, max, need, request);
    process_request(n, m, ri, available, allocation, max, need, request);
}