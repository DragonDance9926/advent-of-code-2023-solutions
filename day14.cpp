#include <bits/stdc++.h>
using namespace std;



void north_tilt(vector<string> &mp){
    for(int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[i].size(); j++){
            if (mp[i][j] == 'O'){
                while (i > 0 && mp[i - 1][j] == '.'){
                    mp[i][j] = '.';
                    mp[i - 1][j] = 'O';
                    i--;
                }
            }
        }
    }
    
}

void east_tilt(vector<string> &mp){
    for(int i = 0; i < mp.size(); i++){
        for (int j = mp[i].size() - 1; j >= 0; j--){
            if (mp[i][j] == 'O'){
                while (j < mp[i].size() - 1 && mp[i][j + 1] == '.'){
                    mp[i][j] = '.';
                    mp[i][j + 1] = 'O';
                    j++;
                }
            }
        }
    }
}
void west_tilt(vector<string> &mp){
    for(int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[i].size(); j++){
            if (mp[i][j] == 'O'){
                while (j > 0 && mp[i][j - 1] == '.'){
                    mp[i][j] = '.';
                    mp[i][j - 1] = 'O';
                    j--;
                }
            }
        }
    }
}

void south_tilt(vector<string> &mp){
    for(int i = mp.size() - 1; i >= 0; i--){
        for (int j = 0; j < mp[i].size(); j++){
            if (mp[i][j] == 'O'){
                while (i < mp.size() - 1 && mp[i + 1][j] == '.'){
                    mp[i][j] = '.';
                    mp[i + 1][j] = 'O';
                    i++;
                }
            }
        }
    }
}

long long clac(vector<string> &mp){
    long long sum = 0;
    for(int i = mp.size() - 1; i >= 0; i--){
        int count_rocks = 0;
        for (int j = 0; j < mp[i].size(); j++){
            if (mp[i][j] == 'O'){
                count_rocks++;
            }
        }
        sum += (mp.size() - i) * count_rocks;
    }   
    return sum;
}
string vector_string(vector<string> &mp){
    string str = "";
    for(int i = 0; i < mp.size(); i++){
        str += mp[i];
    }
    return str;
}


int main(){
    vector<string> mp;
    vector<string> tmp;
    ifstream file;
    file.open("input.txt");
    string line;
    while(getline(file, line)){
        mp.push_back(line);
    }
    file.close();
    tmp = mp;
    north_tilt(mp);
    
    cout << "Part 1: " << clac(mp) << endl;
    mp = tmp;
    unordered_map<string, pair<long long, long long>> mp2;
    for(int i = 1; i <= 1000000000;){
        //cout << i << endl;
        north_tilt(mp);
        west_tilt(mp);
        south_tilt(mp);
        east_tilt(mp);
        if (mp2.find(vector_string(mp)) != mp2.end()){
            long long cyclen = i - mp2[vector_string(mp)].first;
            for(auto &[k,v]: mp2){
                if (v.first >= mp2[vector_string(mp)].first && v.first % cyclen == 1000000000 % cyclen){
                    cout << "Part 2: " << v.second << endl;
                    return 0;
                }
            }
        }
        


        mp2[vector_string(mp)] = {i, clac(mp)};
        i++;
    }
    cout << "Part 2: " << clac(mp) << endl;
}