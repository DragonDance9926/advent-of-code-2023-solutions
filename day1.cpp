#include <bits/stdc++.h>
using namespace std;

int find_first_occ(string haystack,string needle){
    return haystack.find(needle);
}
int find_last_occ(string haystack,string needle){
    return haystack.rfind(needle);
}



int main(){
    fstream file;
    file.open("input.txt");
    string line;
    int sum = 0;
    while(getline(file, line)){
        int f = 0, l = line.length() - 1;
        while (line[f] < '0' || line[f] > '9') f++;
        while (line[l] < '0' || line[l] > '9') l--;
        sum += (line[f] - '0') * 10 + (line[l] - '0');
    }
    cout << "Part 1: " << sum << endl;
    file.close();
    file.open("input.txt");
    const vector<string> digits = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    sum = 0;
    while(getline(file, line)){
        int f = 0, l = line.length() - 1;
        while (line[f] < '0' || line[f] > '9') f++;
        while (line[l] < '0' || line[l] > '9') l--;
        int f_val = line[f] - '0';
        int l_val = line[l] - '0';
        for(int i = 0;i < digits.size();i++){
            int first = find_first_occ(line, digits[i]);
            int last = find_last_occ(line, digits[i]);
            if(first != -1 && first < f){
                f = first;
                f_val = i + 1;
            }
            if(last != -1 && last > l){
                l = last;
                l_val = i + 1;
            }
        }
        sum += (f_val * 10 + l_val);
    }
    cout << "Part 2: " << sum << endl;
}