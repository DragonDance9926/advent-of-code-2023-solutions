#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<int> times = {7,15,30};
    vector<int> dists = {9,40,200};
    int prod = 1;
    for(int i = 0; i < times.size(); i++){
        int curr_time = times[i];
        int curr_dist = dists[i];
        int count = 0;
        for(int hold = 0; hold <= curr_time; hold++){
            if (hold * (curr_time - hold) > curr_dist){
                count++;
            }
        }
        prod *= count;
        cout << count << endl;
    }
    cout << "Part 1: " << prod << endl;
    long long time = 71530;
    long long dist = 940200;
    prod = 0;
    for(int hold = 0; hold <= time; hold++){
        if (hold * (time - hold) > dist){
            prod++;
        }
    }
    cout << "Part 2: " << prod << endl;

}