#include <bits/stdc++.h>
#include <regex>
using namespace std;
//Regex ([\w]{3}) = \(([\w]{3}), ([\w]{3})\)
string reg = "([\\w]{3}) = \\((\\w{3}), (\\w{3})\\)";



long long lcm(long long a, long long b){
    return a * b / __gcd(a, b);
}






int find_zzz(unordered_map<string, pair<string, string>> &mp, string &moves){
    string curr = "AAA";
    int index = 0;
    int count = 0;
    while (curr != "ZZZ"){
        if (moves[index] == 'L'){
            curr = mp[curr].first;
        }
        else if (moves[index] == 'R'){
            curr = mp[curr].second;
        }
        index = (index + 1) % moves.length();
        count++;
    }
    return count;
}

int find_zzz(unordered_map<string, pair<string, string>> &mp, string &moves,string curr){
    int index = 0;
    int count = 0;
    while (curr.back() != 'Z'){
        if (moves[index] == 'L'){
            curr = mp[curr].first;
        }
        else if (moves[index] == 'R'){
            curr = mp[curr].second;
        }
        index = (index + 1) % moves.length();
        count++;
    }
    return count;
}



int main(){
    string moves;
    ifstream file;
    string line;
    unordered_map<string,pair<string,string>> mp;
    file.open("input.txt");
    getline(file, moves);
    getline(file, line);
    while (getline(file, line)){
        regex r(reg);
        smatch m;
        if (regex_search(line, m, r)){
            mp[m[1]] = {m[2], m[3]};
        }
    }
    file.close();
    cout << "Part 1: " << find_zzz(mp, moves) << endl; //Please comment this while trying Part 2 test case
    vector<int> v;
    for (auto &x: mp){
        if (x.first.back() == 'A'){
            v.push_back(find_zzz(mp, moves, x.first));
        }
    }
    long long ans = 1;
    for (auto &x: v){
        ans = lcm(ans, static_cast<long long>(x));
    }
    cout << "Part 2: " << ans << endl;
    return 0;
}