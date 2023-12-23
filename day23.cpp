#include <bits/stdc++.h>
using namespace std;

int maxi = 0;
void dfs (int i, int j, vector<string> &mp, vector<vector<bool>> &v, int count){
    if (i < 0 || j < 0 || i >= mp.size() || j >= mp[0].size() || v[i][j] || mp[i][j] == '#'){
        return;
    }
    if (i == mp.size() - 1 && j == mp[0].size() - 2){
    //cout << i << " " << j << endl;
        maxi = max(maxi, count);
        return;
    }
    v[i][j] = true;
    switch (mp[i][j]){
        case '>':
            dfs(i, j+1, mp, v, count+1);
            break;
        case 'v':
            dfs(i+1, j, mp, v, count+1);
            break;
        case '<':
            dfs(i, j-1, mp, v, count+1);
            break;
        case '^':
            dfs(i-1, j, mp, v, count+1);
            break;
        default:
            dfs(i, j+1, mp, v, count + 1);
            dfs(i+1, j, mp, v, count + 1);
            dfs(i, j-1, mp, v, count + 1);
            dfs(i-1, j, mp, v, count + 1);
            break;
    }
    v[i][j] = false;
}


void dfs_2 (int i, int j, vector<string> &mp, vector<vector<bool>> &v, int count){
    if (i < 0 || j < 0 || i >= mp.size() || j >= mp[0].size() || v[i][j] || mp[i][j] == '#'){
        return;
    }
    //cout << i << " " << j << endl;
    if (i == mp.size() - 1 && j == mp[0].size() - 2){
        maxi = max(maxi, count);
        //cout << maxi << endl;
        return;
    }
    v[i][j] = true;
    dfs_2(i, j+1, mp, v, count+1);
    dfs_2(i+1, j, mp, v, count+1);
    dfs_2(i, j-1, mp, v, count+1);
    dfs_2(i-1, j, mp, v, count+1);
    v[i][j] = false;
}




int main(){
    string line;
    vector<string> mp;
    ifstream file;
    file.open("input.txt");
    while (getline(file, line)){
        mp.push_back(line);
    }
    file.close();
    vector<vector<bool>> v(mp.size(), vector<bool>(mp[0].size()));
    dfs(0, 1, mp, v, 0);
    cout << "Part 1: " << maxi << endl;
    maxi = 0;
    vector<vector<bool>> v2(mp.size(), vector<bool>(mp[0].size()));
    dfs_2(0, 1, mp, v2, 0);
    cout << "Part 2: " << maxi << endl;
    return 0;
}