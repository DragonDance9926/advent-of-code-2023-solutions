#include <bits/stdc++.h>
using namespace std;
pair<char,pair<int,int>> check_adj(vector<string> &mp,int i, int s_j, int e_j){
    for(int di = i - 1; di <= i + 1; di++){
        for (int dj = s_j - 1; dj <= e_j + 1; dj++){
            if (di < 0 || dj < 0 || di >= mp.size() || dj >= mp[0].size()) continue;
            if (mp[di][dj] >= '0' && mp[di][dj] <= '9'){
                continue;
            }
            if (mp[di][dj] != '.'){
                return make_pair(mp[di][dj],make_pair(di,dj));
            }
        }
    }
    return make_pair('.',make_pair(-1,-1));
}

int main(){
    vector<string> mp;
    fstream file;
    file.open("input.txt");
    string line;
    while(getline(file, line)){
        mp.push_back(line);
    }
    file.close();
    int s_j = 0;
    int e_j = 0;
    bool num_seq_start = false;
    int sum_1 = 0;
    map<pair<int,int>, vector<int>> mp2;
    for(int i = 0; i < mp.size(); i++){
        s_j = 0;
        for(int j = 0; j < mp[0].size(); j++){
            if(mp[i][j] >= '0' && mp[i][j] <= '9'){
                if (!num_seq_start){
                    num_seq_start = true;
                    s_j = j;
                }
            }
            else{
                e_j = j - 1;
                if (num_seq_start){
                    //cout << mp[i].substr(s_j, e_j - s_j + 1) << ":" << check_adj(mp, i, s_j, e_j) << endl;
                    auto [c, p] = check_adj(mp, i, s_j, e_j);
                    if (c != '.'){
                        sum_1 += stoi(mp[i].substr(s_j, e_j - s_j + 1));
                    }
                    if (c == '*'){
                        //cout << p.first << " " << p.second << endl;
                        mp2[p].push_back(stoi(mp[i].substr(s_j, e_j - s_j + 1)));
                    }
                }
                num_seq_start = false;
            }
        }
        if (num_seq_start){
            //cout << mp[i].substr(s_j, e_j - s_j + 1) << ":" << check_adj(mp, i, s_j, e_j) << endl;
            auto [c, p] = check_adj(mp, i, s_j, e_j);
            if (c != '.'){
                sum_1 += stoi(mp[i].substr(s_j, e_j - s_j + 1));
            }
            if (c == '*'){
                mp2[p].push_back(stoi(mp[i].substr(s_j, e_j - s_j + 1)));
            }
        }
    }
    num_seq_start = false;
    cout << "Part 1: " << sum_1 << endl;
    long long sum_2 = 0;
    for (auto &[k, v]: mp2){
        if (v.size() == 2){
            sum_2 += v[0] * v[1];
        }
    }
    cout << "Part 2: " << sum_2 << endl;
    return 0;
}