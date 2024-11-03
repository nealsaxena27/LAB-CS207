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
    int time_elapsed = 0;
    int waiting_time = 0;
    int turnaround_time = 0;
    cout<<"Job\tWaiting Time\tBurst Time\tTurn Around Time\n";
    for(int i = 0; i < n; i++){
        time_elapsed = max(time_elapsed, arr[i].arrival_time);
        waiting_time = time_elapsed - arr[i].arrival_time;
        time_elapsed += arr[i].burst_time;
        turnaround_time = time_elapsed - arr[i].arrival_time;
        cout<<arr[i].job_id<<"\t"<<waiting_time<<"\t\t"<<arr[i].burst_time<<"\t\t"<<turnaround_time<<endl;
    }
}