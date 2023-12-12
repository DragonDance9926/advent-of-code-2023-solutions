#include <bits/stdc++.h>
using namespace std;


map<tuple<long long, long long, long long>, long long> cache;

long long getcount(string line, vector<long long> counts, int pos, int current_count, int countpos) {
    if (cache.find({pos, current_count, countpos}) != cache.end()) {
        return cache[{pos, current_count, countpos}];
    }
    if (pos == line.size()) {
        return cache[{pos, current_count, countpos}] = (counts.size() == countpos) ? 1 : 0;
    } else if (line[pos] == '#') {
        return cache[{pos, current_count, countpos}] = getcount(line, counts, pos + 1, current_count + 1, countpos);
    } else if (line[pos] == '.' || countpos == counts.size()) {
        if (countpos < counts.size() && current_count == counts[countpos]) {
            return cache[{pos, current_count, countpos}] = getcount(line, counts, pos + 1, 0, countpos + 1);
        } else if (current_count == 0) {
            return cache[{pos, current_count, countpos}] = getcount(line, counts, pos + 1, 0, countpos);
        } else {
            return cache[{pos, current_count, countpos}] = 0;
        }
    } else {
        long long hash_count = getcount(line, counts, pos + 1, current_count + 1, countpos);
        long long dot_count = 0;
        if (current_count == counts[countpos]) {
            dot_count = getcount(line, counts, pos + 1, 0, countpos + 1);
        } else if (current_count == 0) {
            dot_count = getcount(line, counts, pos + 1, 0, countpos);
        }
        return cache[{pos, current_count, countpos}] = hash_count + dot_count;
    }
    return 0;
}




int main(){
    string line;
    ifstream file;
    file.open("input.txt");
    vector<string> s_v;
    vector<vector<long long>> v_v;
    while (getline(file, line)){
        string mp = line.substr(0, line.find(' '));
        string nums = line.substr(line.find(' '));
        //cout << mp << " " << nums << endl;
        stringstream ss(nums);
        string num;
        vector<long long> v;
        while (getline(ss, num, ',')){
            //cout << num << " ";
            v.push_back(stoll(num));
        }
        s_v.push_back(mp);
        v_v.push_back(v);
    }
    file.close();
    long long sum = 0;
    for (int i = 0; i < s_v.size(); i++){
        cache.clear();
        s_v[i] += '.';
        sum += getcount(s_v[i], v_v[i], 0, 0, 0);
        s_v[i].pop_back();
    }
    //cout << v_v.size() << endl;
    cout << "Part 1: " << sum << endl;
    sum = 0;
    for(int j = 0; j < s_v.size(); j++){
        cache.clear();
        string s_5 = s_v[j];
        vector<long long> v_5 = v_v[j];
        for(int i = 0; i < 4; i++){
            s_5 += '?';
            s_5 += s_v[j];
            v_5.insert(v_5.end(), v_v[j].begin(), v_v[j].end());
        }
        s_5 += '.';
        sum += getcount(s_5, v_5, 0, 0, 0);
    }
    cout << "Part 2: " << sum << endl;
    return 0;
}