# include <bits/stdc++.h>
using namespace std;

class job{
    public:
        int arrival_time;
        int burst_time;
        int priority; // 1 - highest priority.
        int job_id;
};


void input_jobs(job arr[], int n){
    int r, e, p;
    for(int i = 0; i < n; i++){
        cout<<"Enter release time: "; cin>>r;
        cout<<"Enter execution time: "; cin>>e;
        cout<<"Enter priority: "; cin>>p;
        arr[i].arrival_time = r;
        arr[i].burst_time = e;
        arr[i].priority = p;
        arr[i].job_id = i + 1;
    }
}

bool compare_arrival(job &j1, job &j2){
    if(j1.arrival_time==j2.arrival_time) return j1.burst_time < j2.burst_time;
    return j1.arrival_time < j2.arrival_time;
}

class compare_priority {
public:
    bool operator()(job j1, job j2)
    {
        if(j1.priority==j2.priority) return j1.arrival_time > j2.arrival_time;
        return j1.priority > j2.priority;
    }
};

int main(){
    int n; cout<<"Enter number of jobs: "; cin>>n;
    job arr[n];
    input_jobs(arr, n);
    sort(arr, arr + n, compare_arrival);
    int time_elapsed = 0;
    int waiting_time = 0;
    int turnaround_time = 0;
    int initial_burst_time = 0;
    cout<<"Job\tWaiting Time\tInitial Burst Time\t Final Burst Time\tTurn Around Time\n";
    priority_queue<job, vector<job>, compare_priority> pq;
    pq.push(arr[0]);
    int i = 1;
    while(i < n && arr[i].arrival_time == pq.top().arrival_time) pq.push(arr[i++]);
    while(i < n){
        if(pq.empty()){
            time_elapsed = max(time_elapsed, arr[i].arrival_time);
            pq.push(arr[i++]);
        }
        while(i < n && arr[i].arrival_time <= time_elapsed){
            pq.push(arr[i++]);
        }
        job cur = pq.top(); pq.pop();
        time_elapsed = max(time_elapsed, cur.arrival_time);
        waiting_time = time_elapsed - cur.arrival_time;
        time_elapsed += 1;
        initial_burst_time = cur.burst_time;
        cur.burst_time -= 1;
        if(cur.burst_time > 0){
            pq.push(cur);
        }
        turnaround_time = time_elapsed - cur.arrival_time;
        cout<<cur.job_id<<"\t"<<waiting_time<<"\t\t"<<initial_burst_time<<"\t\t\t"<<cur.burst_time<<"\t\t\t"<<turnaround_time<<endl;
    }
    while(!pq.empty()){
        job cur = pq.top(); pq.pop();
        time_elapsed = max(time_elapsed, cur.arrival_time);
        waiting_time = time_elapsed - cur.arrival_time;
        time_elapsed += cur.burst_time;
        initial_burst_time = cur.burst_time;
        cur.burst_time = 0;
        turnaround_time = time_elapsed - cur.arrival_time;
        cout<<cur.job_id<<"\t"<<waiting_time<<"\t\t"<<initial_burst_time<<"\t\t\t"<<cur.burst_time<<"\t\t\t"<<turnaround_time<<endl;
        while(i < n && arr[i].arrival_time <= time_elapsed){
            pq.push(arr[i++]);
        }
    }
}