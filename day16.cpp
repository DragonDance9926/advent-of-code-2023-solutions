#include <bits/stdc++.h>
using namespace std;
enum direction {N, E, S, W};
vector<pair<int,int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};


enum direction rotatetomirror1(direction dir){
    // '/'
    switch (dir){
        case N:
            return E;
        case E:
            return N;
        case S:
            return W;
        case W:
            return S;
        default:
            return N;
    }
}
enum direction rotatetomirror2(direction dir){
    // '\'
    switch (dir){
        case N:
            return W;
        case E:
            return S;
        case S:
            return E;
        case W:
            return N;
        default:
            return N;
    }
}

char dirtochar(direction dir){
    switch (dir){
        case N:
            return '^';
        case E:
            return '>';
        case S:
            return 'v';
        case W:
            return '<';
        default:
            return 'N';
    }
}


bool border (int i, int j, vector<string> &mp){
    return (i < 0 || i >= mp.size() || j < 0 || j >= mp[0].size());
}


int bfs (vector<string> &mp, int i = 0, int j = 0, direction dir = E){
    vector<vector<bool>> visited (mp.size(), vector<bool> (mp[0].size(), false));
    queue<pair<pair<int, int>, direction>> q;
    map<pair<int, int>, array<int , 4>> mp2;
    q.push({{i, j}, dir});
    while (!q.empty()){
        auto [pos, dir] = q.front();
        q.pop();
        if (pos.first < 0 || pos.first >= mp.size() || pos.second < 0 || pos.second >= mp[0].size()){
            continue;
        }
        visited[pos.first][pos.second] = true;
        bool border_north = border(pos.first + dirs[N].first, pos.second + dirs[N].second, mp);
        bool border_south = border(pos.first + dirs[S].first, pos.second + dirs[S].second, mp);
        bool border_east = border(pos.first + dirs[E].first, pos.second + dirs[E].second, mp);
        bool border_west = border(pos.first + dirs[W].first, pos.second + dirs[W].second, mp);
        array<bool, 4> borders = {border_north, border_east, border_south, border_west};
        switch (mp[pos.first][pos.second]){
            case '.':
                if (!borders[dir] && mp2[{pos.first + dirs[dir].first, pos.second + dirs[dir].second}][dir] == 0){
                    q.push({{pos.first + dirs[dir].first, pos.second + dirs[dir].second}, dir});
                }
                break;
            case '|':
                if (!borders[N] && mp2[{pos.first + dirs[N].first, pos.second + dirs[N].second}][N] == 0){
                    mp2[{pos.first + dirs[N].first, pos.second + dirs[N].second}][N] = 1;
                    q.push({{pos.first + dirs[N].first, pos.second + dirs[N].second}, N});
                }
                if (!borders[S] && mp2[{pos.first + dirs[S].first, pos.second + dirs[S].second}][S] == 0){
                    mp2[{pos.first + dirs[S].first, pos.second + dirs[S].second}][S] = 1;
                    q.push({{pos.first + dirs[S].first, pos.second + dirs[S].second}, S});
                }
                break;
            case '-':
                if (!borders[E] && mp2[{pos.first + dirs[E].first, pos.second + dirs[E].second}][E] == 0){
                    mp2[{pos.first + dirs[E].first, pos.second + dirs[E].second}][E] = 1;
                    q.push({{pos.first + dirs[E].first, pos.second + dirs[E].second}, E});
                }
                if (!borders[W] && mp2[{pos.first + dirs[W].first, pos.second + dirs[W].second}][W] == 0){
                    mp2[{pos.first + dirs[W].first, pos.second + dirs[W].second}][W] = 1;
                    q.push({{pos.first + dirs[W].first, pos.second + dirs[W].second}, W});
                }
                break;
            case '/':
                if (!borders[rotatetomirror1(dir)] && mp2[{pos.first + dirs[rotatetomirror1(dir)].first, pos.second + dirs[rotatetomirror1(dir)].second}][rotatetomirror1(dir)] == 0){
                    mp2[{pos.first + dirs[rotatetomirror1(dir)].first, pos.second + dirs[rotatetomirror1(dir)].second}][rotatetomirror1(dir)] = 1;
                    q.push({{pos.first + dirs[rotatetomirror1(dir)].first, pos.second + dirs[rotatetomirror1(dir)].second}, rotatetomirror1(dir)});
                }
                break;
            case '\\':
                if (!borders[rotatetomirror2(dir)] && mp2[{pos.first + dirs[rotatetomirror2(dir)].first, pos.second + dirs[rotatetomirror2(dir)].second}][rotatetomirror2(dir)] == 0){
                    mp2[{pos.first + dirs[rotatetomirror2(dir)].first, pos.second + dirs[rotatetomirror2(dir)].second}][rotatetomirror2(dir)] = 1;
                    q.push({{pos.first + dirs[rotatetomirror2(dir)].first, pos.second + dirs[rotatetomirror2(dir)].second}, rotatetomirror2(dir)});
                }
                break;
        }
    }
    int count = 0;
    for (int i = 0; i < visited.size(); i++){
        for (int j = 0; j < visited[0].size(); j++){
            if (visited[i][j]){
                count++;
            }
        }
    }
    return count;
}


int bfs2 (vector<string> &mp){
    int sum = 0;
    for (int i = 0; i < mp.size(); i++){
        sum = max (sum, bfs(mp, i, 0, E));
    }
    for (int i = 0; i < mp[0].size(); i++){
        sum = max (sum, bfs(mp, 0, i, S));
    }
    for (int i = 0; i < mp.size(); i++){
        sum = max (sum, bfs(mp, i, mp[0].size() - 1, W));
    }
    for (int i = 0; i < mp[0].size(); i++){
        sum = max (sum, bfs(mp, mp.size() - 1, i, N));
    }
    return sum;
}


int main(){
    vector<string> mp;
    string line;
    fstream file;
    file.open("input.txt");
    while (getline(file, line)){
        mp.push_back(line);
    }
    file.close();
    cout << "Part 1: " << bfs(mp) << endl;
    cout << "Part 2: " << bfs2(mp) << endl;
}