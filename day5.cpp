#include <bits/stdc++.h>
#include <chrono>
using namespace std;
int main(){
    vector<long long> seeds;
    string line;
    ifstream fin;
    fin.open("input.txt");
    getline(fin, line);
    line = line.substr(line.find(" ") + 1);
    //cout << line << endl;
    long long n;
    stringstream ss2(line);
    while (ss2 >> n){
        seeds.push_back(n);
    }
    
    getline(fin, line);
    unordered_map<string, string> mp;
    unordered_map<string, vector<tuple<long long, long long, long long>>> mp2;
    while (!fin.eof()){
        //Check the next line is empty
        getline(fin, line);
        string source = line.substr(0, line.find("-"));
        string dest = line.substr(line.find_last_of("-") + 1);
        dest = dest.substr(0, dest.find(" "));
        mp[source] = dest;
        while (getline(fin, line) && line.length() != 0){
            long long s_range, d_range, c;
            stringstream ss(line);
            ss >> s_range >> d_range >> c;
            mp2[source].push_back({s_range, d_range, c});
        }
        sort(mp2[source].begin(), mp2[source].end(), [](tuple<long long, long long, long long> a, tuple<long long, long long, long long> b){
            return get<1>(a) < get<1>(b);
        });
    }
    fin.close();
    unordered_map<long long, long long> dp;
    auto f_location = [&](long long seed){
        if (dp.find(seed) != dp.end()){
            return dp[seed];
        }
        string curr = "seed";
        long long curr_val = seed;
        //cout << curr << " " << curr_val << endl;
        while (true){
            int l = 0, r = mp2[curr].size() - 1;
            while (l <= r){
                int mid = l + (r - l) / 2;	
                auto [d_range, s_range, c] = mp2[curr][mid];
                //cout << s_range << " " << d_range << " " << c << endl;
                if (curr_val >= s_range && curr_val < s_range + c){
                    //cout << (curr_val - s_range) << endl;
                    curr_val = d_range + (curr_val - s_range);
                    break;
                }
                else if (curr_val < s_range){
                    r = mid - 1;
                }
                else{
                    l = mid + 1;
                }
            }
            curr = mp[curr];
            if (curr == "location"){
                //cout <<"location " << curr_val << endl;
                return dp[seed] = curr_val;
            }
            
        }
        return curr_val;
    };
    long long min_val = LONG_LONG_MAX;
    for(auto &seed: seeds){
        min_val = min(min_val, f_location(seed));
    }
    cout << "Part 1: " << min_val << endl;
    min_val = LONG_LONG_MAX;
    for (int i = 0; i < seeds.size(); i += 2){
        auto time_start = chrono::high_resolution_clock::now();
        cout << seeds[i] << " " << seeds[i + 1] << endl;
        for (long long j = seeds[i]; j < seeds[i] + seeds[i + 1]; j++){
            //cout << j << endl;
            min_val = min(min_val, f_location(j));
        }
        auto time_end = chrono::high_resolution_clock::now();
        //Print in minutes
        auto duration = chrono::duration_cast<chrono::minutes>(time_end - time_start);
        cout << "Time: " << duration.count() << " minutes" << endl;
        cout << min_val << endl;
    }
    cout << "Part 2: " << min_val << endl;
/**
 * string curr = "seed";
    while (true){
        if (mp.find(curr) == mp.end()){
            cout << curr << endl;
            break;
        }
        cout << curr << " ";
        curr = mp[curr];
    }
 * 
 */
    
}