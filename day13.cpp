#include <bits/stdc++.h>
using namespace std;


int diff (string &a, string &b){
    int ans = 0;
    for (int i = 0; i < a.size(); i++){
        if (a[i] != b[i]){
            ans++;
        }
    }
    return ans;
}



bool isreflected(vector<string> &mp, int l){
    //cout << l << endl;
    int r = l + 1;
    while (l >= 0 && r < mp.size()){
        if(mp[l] != mp[r]){
            break;
        }
        l--;
        r++;
    }
    return l < 0 || r >= mp.size();
}

bool isreflected_2(vector<string> &mp, int l){
    //cout << l << endl;
    int r = l + 1;
    bool used = false;
    while (l >= 0 && r < mp.size()){
        if(mp[l] != mp[r]){
            if (used){
                return false;
            }
            if (diff (mp[l], mp[r]) == 1){
                used = true;
            }
            else{
                return false;
            }
        }
        l--;
        r++;
    }
    return used && l < 0 || r >= mp.size();
}

bool isreflectedcol(vector<string> &mp, int l){
    int tmp = l;
    //cout << l << endl;
    string l_s, r_s;
    int r = l + 1;
    bool used = false;
    //cout << l << " " << r << endl;
    while (l >= 0 && r < mp[0].size()){
        for (int i = 0; i < mp.size(); i++){
            l_s += mp[i][l];
            r_s += mp[i][r];
        }
        if(l_s != r_s){
            break;
        }
        l--;
        r++;
        l_s = "";
        r_s = "";
    }
    return l < 0 || r >= mp[0].size();
}

bool isreflectedcol_2(vector<string> &mp, int l){
    int tmp = l;
    //cout << l << endl;
    string l_s, r_s;
    int r = l + 1;
    //cout << l << " " << r << endl;
    bool used = false;
    while (l >= 0 && r < mp[0].size()){
        for (int i = 0; i < mp.size(); i++){
            l_s += mp[i][l];
            r_s += mp[i][r];
        }
        if(l_s != r_s){
            if (used){
                return false;
            }
            if (diff (l_s, r_s) == 1){
                used = true;
            }
            else{
                return false;
            }
        }
        l--;
        r++;
        l_s = "";
        r_s = "";
    }
    return used && l < 0 || r >= mp[0].size();
}

int main(){
    vector<vector<string>> mps;
    string line;
    ifstream file;
    file.open("input.txt");
    while(!file.eof()){
        vector<string> mp;
        while(getline(file, line)){
            if(line == "") break;
            //cout << line << endl;
            mp.push_back(line);
        }
        mps.push_back(mp);
    }
    file.close();
    long long sum = 0;
    long long sum2 = 0;
    for (auto &mp: mps){
        for (int i = 0; i < mp.size() - 1; i++){
            if (isreflected(mp, i)){
                //cout << "Row " << i << " is reflected"<< endl;
                sum += (i + 1) * 100;
            }
            else if (isreflected_2(mp, i)){
                //cout << "Row2 "  << i << " is reflected"<< endl;
                sum2 += (i + 1) * 100;
            }
        }
        for (int i = 0; i < mp[0].size() - 1; i++){
            if (isreflectedcol(mp, i)){
                //cout << "Col " << i << " is reflected"<< endl;
                sum += (i + 1);
            }
            else if (isreflectedcol_2(mp, i)){
                //cout << "Col2 " << i << " is reflected"<< endl;
                sum2 += (i + 1);
            }
        }
    }
    cout << "Part 1: " << sum << endl;
    cout << "Part 2: " << sum2 << endl;
    return 0;
}