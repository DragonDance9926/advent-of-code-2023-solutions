#include <bits/stdc++.h>
using namespace std;


long long next_val(vector<long long> &seq){
    vector<vector<long long>> grid;
    grid.push_back(seq);
    int prev_i = 0;
    bool isAllZero = false;
    while (!isAllZero){
        isAllZero = true;
        vector<long long> diff;
        for (int i = 1; i < grid[prev_i].size(); i++){
            diff.push_back(grid[prev_i][i] - grid[prev_i][i-1]);
            //Alignment like %2d
            //cout << setfill(' ') << setw(6) << grid[prev_i][i] - grid[prev_i][i-1]; 
            if (diff.back() != 0){
                isAllZero = false;
            }
            //cout << endl;
        }
        grid.push_back(diff);
        prev_i++;
    }


    grid[grid.size() - 1].push_back(0);
    for (int i = grid.size() - 2; i >= 0 ; i--){
        grid[i].push_back(grid[i].back() + grid[i+1].back());
    }
    /*
    for (auto &row: grid){
    for (auto &x: row){
        cout << setfill(' ') << setw(6) << x << " ";
    }
    cout << endl;
    }*/
    return grid[0].back();
}



int main(){
    vector<vector<long long>> sequence;
    ifstream file;
    string line;
    file.open("input.txt");
    while (getline(file, line)){
        long long num;
        stringstream ss(line);
        vector<long long> row;
        while (ss >> num){
            //cout << num << " ";
            row.push_back(num);
        }
        //cout << endl;
        sequence.push_back(row);
    }
    
    file.close();
    long long sum = 0;
    long long sum2 = 0;
    for (auto &x: sequence){
        sum += next_val(x);
        reverse(x.begin(), x.end());
        sum2 += next_val(x);
    }
    cout << "Part 1: " << sum << endl;
    cout << "Part 2: " << sum2 << endl;
    return 0;
}