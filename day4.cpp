#include <bits/stdc++.h>
using namespace std;


unordered_map<int,long long> memo;
long long find_sum(vector<vector<int>> &your_numbers,vector<vector<int>> &win_numbers,int curr_tic){
    if (memo.find(curr_tic) != memo.end()){
        return memo[curr_tic];
    }
    long long sum = 0;
    int k = 0;
    unordered_set<int> s;
    for (auto &x: win_numbers[curr_tic]){
        s.insert(x);
    }
    for (auto &x: your_numbers[curr_tic]){
        if (s.find(x) != s.end()){
            k++;
        }
    }
    sum += k;
    //cout << curr_tic << " " << k << endl;
    for (int i = curr_tic + 1; i < win_numbers.size() && k > 0; i++, k--){
        sum += find_sum(your_numbers, win_numbers, i); 
    }
    return memo[curr_tic] = sum;
}





int main(){
    vector<vector<int>> your_numbers;
    vector<vector<int>> win_numbers;
    fstream file;
    file.open("input.txt");
    string line;
    while (getline(file, line)){
        string buff = line.substr(line.find(":") + 1);
        string wins = buff.substr(0, buff.find("|"));
        string you = buff.substr(buff.find("|") + 2);
        stringstream ss(wins), ss2(you);
        vector<int> v;
        vector<int> v2;
        int buf2;
        while (ss >> buf2){
            v.push_back(buf2);
        }
        while (ss2 >> buf2){
            v2.push_back(buf2);
        }
        your_numbers.push_back(v2);
        win_numbers.push_back(v);
    }
    file.close();
    long long sum = 0;
    for (int i = 0; i < your_numbers.size(); i++){
        int matched = 0;
        unordered_map<int, int> s;
        for(auto &x: win_numbers[i]){
            s[x]++;
        }
        for (auto &x: your_numbers[i]){
            if (s.find(x) != s.end()){
                matched += s[x];
            }
        }
        //cout << matched << endl;
        if (matched > 0){
            sum += (1LL << (matched - 1));
        }
    }
    cout << "Part 1:" << sum << endl;
    sum = 0;
    for (int i = 0; i < your_numbers.size(); i++){
        sum += 1 + find_sum(your_numbers, win_numbers, i);
    }
    cout << "Part 2:" << sum << endl;
}