# include <bits/stdc++.h>
using namespace std;

vector<int> request_sequence;
vector<int> seek_sequence;
string direction = "left";
int head = 0;
const int disk_size = 200;
int n;

void initialize(){
    cout<<"Enter number of tracks in request sequence: "; cin>>n;
    cout<<"Enter request sequence: ";
    request_sequence.assign(n, 0);
    for(int i = 0; i < n; i++) cin>>request_sequence[i];
    cout<<"Enter initial head position: "; cin>>head;
    cout<<"Enter initial direction of movement: "; cin>>direction;
}

void scan(){
    int seek_time = 0, distance = 0, cur_track = 0;
    vector<int> left, right;
    if (direction == "left") left.push_back(0);
    else if (direction == "right") right.push_back(disk_size - 1);
    for (int i = 0; i < n; i++) {
        if (request_sequence[i] < head) left.push_back(request_sequence[i]);
        if (request_sequence[i] > head) right.push_back(request_sequence[i]);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    int run = 2;
    while (run--) {
        if (direction == "left") {
            for (int i = left.size() - 1; i >= 0; i--) {
                cur_track = left[i];
                cout<<"Head has moved from "<<head<<" to "<<cur_track<<endl;
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_time += distance;
                head = cur_track;
            }
            direction = "right";
        }
        else if (direction == "right") {
            for (int i = 0; i < right.size(); i++) {
                cur_track = right[i];
                cout<<"Head has moved from "<<head<<" to "<<cur_track<<endl;
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_time += distance;
                head = cur_track;
            }
            direction = "left";
        }
    }
    cout<<"Total Seek Time: "<<seek_time<<endl;
    cout<<"Seek Sequence:"<<endl;
    for(int i = 0; i < n; i++) cout<<seek_sequence[i]<<" ";
    cout<<endl;
}

int main(){
    initialize();
    scan();
}