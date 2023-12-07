#include <bits/stdc++.h>
using namespace std;


int strengh(char &c){
    switch (c){
        case '2'...'9':
            return c - '2';
        case 'T':
            return 8;
        case 'J':
            return 9;
        case 'Q':
            return 10;
        case 'K':
            return 11;
        case 'A':
            return 12;
        default:
            return 0;
    }

}

int _strengh(char &c){
    switch (c){
        case 'J':
            return 0;
        case '2'...'9':
            return c - '2' + 1;
        case 'T':
            return 9;
        case 'Q':
            return 10;
        case 'K':
            return 11;
        case 'A':
            return 12;
        default:
            return 0;
    }
}

int hand_strengh(string &s){
    array<int , 13> arr = {0};
    for(auto &c: s){
        arr[strengh(c)]++;
    }
    //Sort by descending order
    sort(arr.begin(), arr.end(), greater<int>());
    if (arr[0] == 5){
        return 10; //Five of a kind
    }
    if (arr[0] == 4){
        return 9; //Four of a kind
    }
    if (arr[0] == 3 && arr[1] == 2){
        return 8; //Full house
    }
    if (arr[0] == 3){
        return 7; //Three of a kind
    }
    if (arr[0] == 2 && arr[1] == 2){
        return 6; //Two pairs
    }
    if (arr[0] == 2){
        return 5; //One pair
    }
    return 0;
}


int _hand_strengh(string &s){
    array<int , 12> arr = {0};
    int jokers = 0;
    for(auto &c: s){
        if (c == 'J'){
            jokers++;
        }
        else{
            arr[_strengh(c) - 1]++;
        }
    }
    if(jokers == 0){
        sort (arr.begin(), arr.end(), greater<int>());
        if (arr[0] == 5){
            return 10; //Five of a kind
        }
        if (arr[0] == 4){
            return 9; //Four of a kind
        }
        if (arr[0] == 3 && arr[1] == 2){
            return 8; //Full house
        }
        if (arr[0] == 3){
            return 7; //Three of a kind
        }
        if (arr[0] == 2 && arr[1] == 2){
            return 6; //Two pairs
        }
        if (arr[0] == 2){
            return 5; //One pair
        }
        return 0;
    }
    else{
        int max_pow = -1;
        for (int i = 0; i < 12; i++){
            array<int , 12> arr2 = {0};
            //Copying
            for (int j = 0; j < 12; j++){
                arr2[j] = arr[j];
            }
            arr2[i] += jokers;
            sort (arr2.begin(), arr2.end(), greater<int>());
            if (arr2[0] == 5){
                max_pow = max(max_pow, 10); //Five of a kind
            }
            else if (arr2[0] == 4){
                max_pow = max(max_pow, 9); //Four of a kind
            }
            else if (arr2[0] == 3 && arr2[1] == 2){
                max_pow = max(max_pow, 8); //Full house
            }
            else if (arr2[0] == 3){
                max_pow = max(max_pow, 7); //Three of a kind
            }
            else if (arr2[0] == 2 && arr2[1] == 2){
                max_pow = max(max_pow, 6); //Two pairs
            }
            else if (arr2[0] == 2){
                max_pow = max(max_pow, 5); //One pair
            }
            else{
                max_pow = max(max_pow, 0);
            }
        }
        return max_pow;
    }
}




int main(){
    vector<pair<string,long long>> v;
    ifstream file;
    file.open("input.txt");
    string line;
    while(getline(file, line)){
        v.push_back({line.substr(0, line.find(" ")), stoll(line.substr(line.find(" ") + 1))});
        //cout << v.back().first << " " << v.back().second << " "<< hand_strengh(v.back().first) << endl;
    }
    file.close();
    sort (v.begin(), v.end(), [](pair<string,long long> a, pair<string,long long> b){
        int hand_a = hand_strengh(a.first);
        int hand_b = hand_strengh(b.first);
        if (hand_a == hand_b){
            int i = 0;
            while (i < a.first.length() && strengh(a.first[i]) == strengh(b.first[i])){
                i++;
            }
            return strengh(a.first[i]) < strengh(b.first[i]);
        }
        return hand_a < hand_b;
    });
    long long sum = 0;
    int i = 1;
    for (auto &x: v){
        sum += x.second * i++;
    }
    cout << "Part 1: " << sum << endl;
    sort (v.begin(), v.end(), [](pair<string,long long> a, pair<string,long long> b){
        int hand_a = _hand_strengh(a.first);
        int hand_b = _hand_strengh(b.first);
        if (hand_a == hand_b){
            int i = 0;
            while (i < a.first.length() && _strengh(a.first[i]) == _strengh(b.first[i])){
                i++;
            }
            return _strengh(a.first[i]) < _strengh(b.first[i]);
        }
        return hand_a < hand_b;
    });
    sum = 0;
    i = 1;
    for (auto &x: v){
        //cout << x.first << " " << x.second << " " << _hand_strengh(x.first) << endl;
        sum += x.second * i++;
    }
    cout << "Part 2: " << sum << endl;
    return 0;
}