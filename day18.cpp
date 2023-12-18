#include <bits/stdc++.h>
#include <regex>
using namespace std;
//Regex: (\w) (\d+) \((\#\w+)\)



long long determinant(long long x1, long long y1, long long x2, long long y2){
    return x1*y2 - x2*y1;
}


long long shoelace(vector<pair<long long,long long>> &points){
    long long lsum = 0, rsum = 0;
    for (int i = 0; i < points.size()-1; i++){
        lsum += points[i].first * points[i+1].second;
        rsum += points[i].second * points[i+1].first;
    }
    return abs(lsum - rsum) / 2;
}

long long area (vector<pair<long long ,long long>> &points){
    long long perimeter = points.size() - 1;
    long long shoe = shoelace(points);
    long long interior = shoe - perimeter/2 + 1;
    return interior + perimeter;
}


long long hextodex (string hex){
    long long dec = 0;
    for (int i = 0; i < hex.size(); i++){
        dec *= 16;
        if (hex[i] >= '0' && hex[i] <= '9'){
            dec += hex[i] - '0';
        }
        else{
            dec += hex[i] - 'a' + 10;
        }
    }
    return dec;
}






int main(){
    string line;
    vector<char> dirs;
    vector<int> steps;
    vector<string> color;
    ifstream file("input.txt");
    while(getline(file, line)){
        regex r("(\\w) (\\d+) \\(\\#(\\w+)\\)");
        smatch m;
        regex_search(line, m, r);
        dirs.push_back(m[1].str()[0]);
        steps.push_back(stoi(m[2].str()));
        color.push_back(m[3].str());
    }
    file.close();
    vector<pair<long long,long long>> marked;
    vector<string> colors;
    long long i = 0, j = 0;
    marked.push_back(make_pair(i,j));
    colors.push_back(color[0]);
    for (int k = 0; k < dirs.size(); k++){
        char dir = dirs[k];
        long long step = steps[k];
        string col = color[k];
        for (long long l = 0; l < step; l++){
            if (dir == 'U'){
                j++;
            }
            else if (dir == 'D'){
                j--;
            }
            else if (dir == 'L'){
                i--;
            }
            else if (dir == 'R'){
                i++;
            }
            marked.push_back(make_pair(i,j));
            colors.push_back(col);
        }
    }
    cout << "Part 1: " << area(marked) << endl;
    marked.clear();
    i = 0, j = 0;
    marked.push_back(make_pair(i,j));
    for (int k = 0; k < dirs.size(); k++){
        char dir;
        long long step = hextodex(color[k].substr(0,color[k].size()-1));
        //cout << step << endl;
        //cout << color[k].back() << endl;
        switch(color[k].back()){
            case '0':
                dir = 'R';
                break;
            case '1':
                dir = 'D';
                break;
            case '2':
                dir = 'L';
                break;
            case '3':
                dir = 'U';
                break;
        }
        for (long long l = 0; l < step; l++){
            if (dir == 'U'){
                j++;
            }
            else if (dir == 'D'){
                j--;
            }
            else if (dir == 'L'){
                i--;
            }
            else if (dir == 'R'){
                i++;
            }
            marked.push_back(make_pair(i,j));
        }
    }
    cout << "Part 2: " << area(marked) << endl;
}