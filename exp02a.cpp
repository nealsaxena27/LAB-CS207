# include <bits/stdc++.h>
using namespace std;

class job{
    public:
        int arrival_time;
        int burst_time;
        int job_id;
};


void input_jobs(job arr[], int n){
    int r, e;
    for(int i = 0; i < n; i++){
        cout<<"Enter release time: "; cin>>r;
        cout<<"Enter execution time: "; cin>>e;
        arr[i].arrival_time = r;
        arr[i].burst_time = e;
        arr[i].job_id = i + 1;
    }
}

bool compare(job &j1, job &j2){
    if(j1.arrival_time==j2.arrival_time) return j1.burst_time < j2.burst_time;
    return j1.arrival_time < j2.arrival_time;
}

int main(){
    int n; cout<<"Enter number of jobs: "; cin>>n;
    job arr[n];
    input_jobs(arr, n);
    sort(arr, arr + n, compare);
    queue<job> q;
    int time_elapsed = 0;
    int waiting_time = 0;
    int turnaround_time = 0;
    int time_quantum = 2;
    int initial_burst_time = 0;
    q.push(arr[0]);
    int i = 1;
    cout<<"Job\tWaiting Time\tInitial Burst Time\t Final Burst Time\tTurn Around Time\n";
    while(!q.empty()){
        job cur = q.front(); q.pop();
        time_elapsed = max(time_elapsed, cur.arrival_time);
        waiting_time = time_elapsed - cur.arrival_time;
        time_elapsed += min(time_quantum, cur.burst_time);
        initial_burst_time = cur.burst_time;
        cur.burst_time -= min(time_quantum, cur.burst_time);
        turnaround_time = time_elapsed - cur.arrival_time;
        cout<<cur.job_id<<"\t"<<waiting_time<<"\t\t"<<initial_burst_time<<"\t\t\t"<<cur.burst_time<<"\t\t\t"<<turnaround_time<<endl;
        while(i < n && arr[i].arrival_time <= time_elapsed){
            q.push(arr[i++]);
        }
        if(cur.burst_time > 0) q.push(cur);
    }
}