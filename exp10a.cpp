# include <bits/stdc++.h>
using namespace std;

vector<int> request_sequence;
vector<int> seek_sequence;
int head = 0;
const int disk_size = 200;
int n;

void initialize(){
    cout<<"Enter number of tracks in request sequence: "; cin>>n;
    cout<<"Enter request sequence: ";
    request_sequence.assign(n, 0);
    for(int i = 0; i < n; i++) cin>>request_sequence[i];
    cout<<"Enter initial head position: "; cin>>head;
}

void fcfs(){
    int seek_time = 0, distance = 0, cur_track = 0;
    for(int i = 0; i < n; i++){
        cur_track = request_sequence[i];
        cout<<"Head has moved from "<<head<<" to "<<cur_track<<endl;
        seek_sequence.push_back(cur_track);
        distance = abs(cur_track - head);
        seek_time += abs(distance);
        head = cur_track;
    }
    cout<<"Total Seek Time: "<<seek_time<<endl;
    cout<<"Seek Sequence:"<<endl;
    for(int i = 0; i < n; i++) cout<<seek_sequence[i]<<" ";
    cout<<endl;
}

int main(){
    initialize();
    fcfs();
}