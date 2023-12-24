#include <bits/stdc++.h>
using namespace std;
#define TEST_LOWER_BOUND 200000000000000
#define TEST_UPPER_BOUND 400000000000000

bool willcollapse(pair<tuple<double, double, double>, tuple<double, double, double>> a, pair<tuple<double, double, double>, tuple<double, double, double>> b){
    double x1 = get<0>(a.first);
    double x2 = get<0>(a.first) + get<0>(a.second);
    double x3 = get<0>(b.first);
    double x4 = get<0>(b.first) + get<0>(b.second);
    double y1 = get<1>(a.first);
    double y2 = get<1>(a.first) + get<1>(a.second);
    double y3 = get<1>(b.first);
    double y4 = get<1>(b.first) + get<1>(b.second);
    double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (den == 0) return false;
    double px =((x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4)) / ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
    double py =((x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)) / ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
    bool va = (px > x1) == (x2 > x1);
    bool vb = (px > x3) == (x4 > x3);
    if (va && vb){
        return px >= TEST_LOWER_BOUND && px <= TEST_UPPER_BOUND && py >= TEST_LOWER_BOUND && py <= TEST_UPPER_BOUND;
    }
    return false;
}




int main(){
    string s;
    ifstream f("input.txt");
    vector<pair<tuple<double, double, double>, tuple<double, double, double>>> vi;
    while (getline(f, s)){
        //cout << s << endl;
        string a = s.substr(0, s.find('@'));
        string b = s.substr(s.find('@') + 1);
        stringstream ss(a);
        string c;
        vector<double> v;
        while (getline(ss, c, ',')){
            v.push_back(stoll(c));
            //cout << stoll(c) << endl;
        }
        ss = stringstream(b);
        while (getline(ss, c, ',')){
            v.push_back(stoll(c));
            //cout << stoll(c) << endl;
        }
        vi.push_back({{v[0], v[1], v[2]}, {v[3], v[4], v[5]}});
    }
    double sum = 0;
    for (int i = 0; i < vi.size(); i++){
        for (int j = i + 1; j < vi.size(); j++){
            if (willcollapse(vi[i], vi[j])){
                sum++;
            }
        }
    }
    cout << TEST_LOWER_BOUND << " " << TEST_UPPER_BOUND << endl;
    cout << "Part 1: " << sum << endl;

}