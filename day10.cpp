#include <bits/stdc++.h>
using namespace std;


vector<string> double_size (vector<string> &mp){
    vector <string> mp2(mp.size() * 2, string (mp[0].size() * 2, '.'));
    /**
     * | is a vertical pipe connecting north and south.
     * - is a horizontal pipe connecting east and west.
     * L is a 90-degree bend connecting north and east.
     * J is a 90-degree bend connecting north and west.
     * 7 is a 90-degree bend connecting south and west.
     * F is a 90-degree bend connecting south and east.
     * . is ground; there is no pipe in this tile.
     */
    for (int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[0].size(); j++){
            mp2[2 * i][2 * j] = mp[i][j];
            if (mp[i][j] == '|'){
                mp2[2 * i + 1][2 * j] = '|';
            }
            else if (mp[i][j] == '-'){
                mp2[2 * i][2 * j + 1] = '-';
            }
            else if (mp[i][j] == 'L'){
                //mp2[2 * i - 1][2 * j] = '|';
                mp2[2 * i][2 * j + 1] = '-';
            }
            else if (mp[i][j] == 'J'){
                //mp2[2 * i - 1][2 * j] = '|';
                //mp2[2 * i][2 * j - 1] = '-';
            }
            else if (mp[i][j] == '7'){
                //mp2[2 * i][2 * j - 1] = '-';
                mp2[2 * i + 1][2 * j] = '|';
            }
            else if (mp[i][j] == 'F'){
                mp2[2 * i + 1][2 * j] = '|';
                mp2[2 * i][2 * j + 1] = '-';
            }
            else{
                continue;
            }
        }
    }
    return mp2;
}


void flood_fill(vector<string> &mp){
    queue<pair<int,int>> q;
    vector <vector<bool>> visited (mp.size(), vector<bool> (mp[0].size(), false));
    q.push({0, 0});
    while (!q.empty()){
        auto curr = q.front();
        q.pop();
        if (visited[curr.first][curr.second]){
            continue;
        }
        visited[curr.first][curr.second] = true;
        if (mp[curr.first][curr.second] != '.'){
            continue;
        }
        mp[curr.first][curr.second] = 'O';
        if (curr.first > 0){
            q.push({curr.first - 1, curr.second});
        }
        if (curr.first < mp.size() - 1){
            q.push({curr.first + 1, curr.second});
        }
        if (curr.second > 0){
            q.push({curr.first, curr.second - 1});
        }
        if (curr.second < mp[0].size() - 1){
            q.push({curr.first, curr.second + 1});
        }
    }
    return;
}



int bfs (vector<string> &mp, pair<int,int> pos){
    deque<pair<int,pair<int,int>>> dq;
    dq.push_back({0, pos});
    vector<vector<bool>> visited (mp.size(), vector<bool> (mp[0].size(), false));
    map<pair<int,int>, int> dist;
    dist[pos] = 0;
    while (!dq.empty()){
        auto [curr_dist, curr] = dq.front();
        dq.pop_front();
        if (dist.find(curr) != dist.end()){
            dist[curr] = min(dist[curr], curr_dist);
        }
        else{
            dist[curr] = curr_dist;
        }
        if (visited [curr.first][curr.second]){
            continue;
        }
        visited [curr.first][curr.second] = true;
        if (mp[curr.first][curr.second] == '.'){
            continue;
        }
        if (mp[curr.first][curr.second] == '|'){
            if (curr.first > 0){
                dq.push_back({curr_dist + 1, {curr.first - 1, curr.second}});
            }
            if (curr.first < mp.size() - 1){
                dq.push_back({curr_dist + 1, {curr.first + 1, curr.second}});
            }
        }
        else if (mp[curr.first][curr.second] == '-'){
            if (curr.second > 0){
                dq.push_back({curr_dist + 1, {curr.first, curr.second - 1}});
            }
            if (curr.second < mp[0].size() - 1){
                dq.push_back({curr_dist + 1, {curr.first, curr.second + 1}});
            }
        }
        else if (mp[curr.first][curr.second] == 'L'){
            if (curr.first > 0){
                dq.push_back({curr_dist + 1, {curr.first - 1, curr.second}});
            }
            if (curr.second < mp[0].size() - 1){
                dq.push_back({curr_dist + 1, {curr.first, curr.second + 1}});
            }
        }
        else if (mp[curr.first][curr.second] == 'J'){
            if (curr.first > 0){
                dq.push_back({curr_dist + 1, {curr.first - 1, curr.second}});
            }
            if (curr.second > 0){
                dq.push_back({curr_dist + 1, {curr.first, curr.second - 1}});
            }
        }
        else if (mp[curr.first][curr.second] == '7'){
            if (curr.first < mp.size() - 1){
                dq.push_back({curr_dist + 1, {curr.first + 1, curr.second}});
            }
            if (curr.second > 0){
                dq.push_back({curr_dist + 1, {curr.first, curr.second - 1}});
            }
        }
        else if (mp[curr.first][curr.second] == 'F'){
            if (curr.first < mp.size() - 1){
                dq.push_back({curr_dist + 1, {curr.first + 1, curr.second}});
            }
            if (curr.second < mp[0].size() - 1){
                dq.push_back({curr_dist + 1, {curr.first, curr.second + 1}});
            }
        }
    }
    int ans = 0;
    for (auto &x: dist){
        ans = max(ans, x.second);
    }
    for(int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[0].size(); j++){
            if (!visited[i][j]){
                mp[i][j] = '.';
            }
        }
    }
    return ans;
}








int main(){
    vector<string> mp;
    ifstream file;
    file.open("input.txt");
    string line;
    while(getline(file, line)){
        mp.push_back(line);
    }
    file.close();
    string blank(mp[0].size(), '.');
    mp.push_back(blank);
    mp.insert(mp.begin(), blank);
    for (int i = 0; i < mp.size(); i++){
        mp[i].push_back('.');
        mp[i].insert(mp[i].begin(), '.');
    }


    pair<int,int> pos = {-1,-1};
    for (int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[i].size(); j++){
            /**
             * | is a vertical pipe connecting north and south.
             * - is a horizontal pipe connecting east and west.
             * L is a 90-degree bend connecting north and east.
             * J is a 90-degree bend connecting north and west.
             * 7 is a 90-degree bend connecting south and west.
             * F is a 90-degree bend connecting south and east.
             * . is ground; there is no pipe in this tile.
             */
            if (mp[i][j] == 'S'){
                pos = {i,j};
                bool north_connect = i > 0 && (mp[i-1][j] == '|' || mp[i - 1][j] == '7' || mp[i - 1][j] == 'F');
                bool south_connect = i < mp.size() - 1 && (mp[i+1][j] == '|' || mp[i + 1][j] == 'L' || mp[i + 1][j] == 'J');
                bool east_connect = j < mp[i].size() - 1 && (mp[i][j+1] == '-' || mp[i][j+1] == 'J' || mp[i][j+1] == '7');
                bool west_connect = j > 0 && (mp[i][j-1] == '-' || mp[i][j-1] == 'L' || mp[i][j-1] == 'F');
                if (north_connect && south_connect){
                    mp[i][j] = '|';
                }
                else if (east_connect && west_connect){
                    mp[i][j] = '-';
                }
                else if (north_connect && east_connect){
                    mp[i][j] = 'L';
                }
                else if (north_connect && west_connect){
                    mp[i][j] = 'J';
                }
                else if (south_connect && east_connect){
                    mp[i][j] = 'F';
                }
                else if (south_connect && west_connect){
                    mp[i][j] = '7';
                }
                else{
                    printf("error\n");
                }
            }
        }
        if (pos.first != -1){
            break;
        }

    }
    //cout << pos.first << " " << pos.second << " " << mp[pos.first][pos.second] << endl;
    cout << "Part 1: " << bfs(mp, pos) << endl;
    vector<string> mp2 = double_size(mp);
    flood_fill(mp2);
    int ans = 0;
    for (int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[0].size(); j++){
            if (mp2[2 * i][2 * j] == '.'){
                ans++;
            }
        }
    }
    cout << "Part 2: " << ans << endl;
    return 0;
}