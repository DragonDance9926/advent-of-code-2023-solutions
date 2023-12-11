#include <bits/stdc++.h>
using namespace std;




int main(){
    vector<string> mp;
    ifstream file;
    file.open("input.txt");
    string line;
    while(getline(file, line)){
        mp.push_back(line);
    }
    file.close();
    vector<int> rows;
    vector<int> cols;
    for(int i = 0; i < mp.size(); i++){
        if (all_of(mp[i].begin(), mp[i].end(), [](char c){return c == '.';})){
            rows.push_back(i);
        }
    }
    for (int j = 0; j < mp[0].size(); j++){
        bool all = true;
        for (int i = 0; i < mp.size(); i++){
            if (mp[i][j] != '.'){
                all = false;
                break;
            }
        }
        if (all){
            cols.push_back(j);
        }
    }
    vector<pair<int, int>> galaxies;
    for (int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[0].size(); j++){
            if (mp[i][j] == '#'){
                galaxies.push_back({i, j});
            }
        }
    }
    long long sum = 0;
    long long sum2 = 0;
    for (int i = 0; i < galaxies.size(); i++){
        for (int j = i + 1; j < galaxies.size(); j++){
            int up = max(galaxies[i].first, galaxies[j].first);
            int down = min(galaxies[i].first, galaxies[j].first);
            int left = min(galaxies[i].second, galaxies[j].second);
            int right = max(galaxies[i].second, galaxies[j].second);
            //cout << up << " " << down << " " << left << " " << right << endl;
            for (int k = up; k > down; k--){
                if (binary_search(rows.begin(), rows.end(), k)){
                    sum += 2;
                    sum2 += 1000000;
                }
                else{
                    sum++;
                    sum2++;
                }
            }
            for (int k = right; k > left; k--){
                if (binary_search(cols.begin(), cols.end(), k)){
                    sum += 2;
                    sum2 += 1000000;
                }
                else{
                    sum++;
                    sum2++;
                }
            }
        }
    }
    cout << "Part 1: " << sum << endl;
    cout << "Part 2: " << sum2 << endl;
}