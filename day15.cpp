#include <bits/stdc++.h>
using namespace std;




long long _hash (string line){
    long long hash = 0;
    for (int i = 0; i < line.length(); i++){
        hash = ((hash + line[i]) * 17) % 256;
    }
    return hash;
}




int main(){
    string line;
    fstream file;
    file.open("input.txt");
    getline(file, line);
    file.close();
    stringstream ss(line);
    stringstream ss2(line);
    string token;
    long long sum = 0;
    while (getline(ss, token, ',')) {
        //cout << token << " " << _hash(token) << endl;
        sum += _hash(token);
    }
    cout << "Part 1: " << sum << endl;
    vector<vector<pair<string, long long>>> v(256);
    while (getline(ss2, token, ',')) {
        if (token.back() == '-'){
            string tmp = token.substr(0, token.length() - 1);
            bool found = false;
            for (auto it = v[_hash(tmp)].begin(); it != v[_hash(tmp)].end(); it++){
                if (it->first == tmp){
                    found = true;
                    //Delete
                    v[_hash(tmp)].erase(it);
                    break;
                }
            }
        }
        else{
            string tmp = token.substr(0, token.find('='));
            long long val = stoll(token.substr(token.find('=') + 1));
            bool found = false;
            for (auto it = v[_hash(tmp)].begin(); it != v[_hash(tmp)].end(); it++){
                if (it->first == tmp){
                    it->second = val;
                    found = true;
                    break;
                }
            }
            if (!found){
                v[_hash(tmp)].push_back({tmp, val});
            }
        }
    }
    //Print all
    long long sum2 = 0;
    for (int i = 0; i < 256; i++){
        if (!v[i].empty()){
            //cout << i << ": ";
            for (int j = 0; j < v[i].size(); j++){
                //cout << v[i][j].first << " " << v[i][j].second << " ";
                sum2 += (v[i][j].second * (i + 1) * (j + 1));
            }
            //cout << endl;
            
        }
    }
    cout << "Part 2: " << sum2 << endl;
}