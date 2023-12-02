#include <bits/stdc++.h>
using namespace std;


int main(){

    fstream file;
    file.open("input.txt");
    string line;
    int sum = 0;
    while(getline(file, line)){
        bool flag = true;
        //cout << line << endl;
        string buffer = line.substr(0, line.find(":"));
        int number = stoi(buffer.substr(buffer.find(" ") + 1));
        //cout << number << endl;
        string sets = line.substr(line.find(":") + 2);
        stringstream ss(sets);
        while (flag && getline(ss, buffer, ';')){
            int t = 0;
            //Remove leading whitespace
            while(buffer[t] == ' ') t++;
            buffer = buffer.substr(t);
            string buffer2;
            stringstream ss2(buffer);
            while (flag && getline(ss2, buffer2, ',')){
                int t = 0;
                //Remove leading whitespace
                while(buffer2[t] == ' ') t++;
                buffer2 = buffer2.substr(t);
                int s_num = stoi(buffer2.substr(0, buffer2.find(" ")));
                string s_color = buffer2.substr(buffer2.find(" ") + 1);
                //cout << s_num << " " << s_color << endl;
                if (s_color == "red"){
                    //cout << s_num << "<= 12" << endl;
                    flag = s_num <= 12;
                }
                if (s_color == "green"){
                    //cout << s_num << "<= 13" << endl;
                    flag = s_num <= 13;
                }
                if (s_color == "blue"){
                    //cout << s_num << "<= 14" << endl;
                    flag = s_num <= 14;
                }
            }          
        }
        if(flag){
            //cout << "Valid" << endl;
            sum += number;
        }
    }
    cout << "Part 1: " << sum << endl;
    file.close();
    file.open("input.txt");
    sum = 0;
    while(getline(file, line)){
        int r = 0, g = 0, b = 0;
        //cout << line << endl;
        string buffer = line.substr(0, line.find(":"));
        int number = stoi(buffer.substr(buffer.find(" ") + 1));
        //cout << number << endl;
        string sets = line.substr(line.find(":") + 2);
        stringstream ss(sets);
        while (getline(ss, buffer, ';')){
            int t = 0;
            //Remove leading whitespace
            while(buffer[t] == ' ') t++;
            buffer = buffer.substr(t);
            string buffer2;
            stringstream ss2(buffer);
            while (getline(ss2, buffer2, ',')){
                int t = 0;
                //Remove leading whitespace
                while(buffer2[t] == ' ') t++;
                buffer2 = buffer2.substr(t);
                int s_num = stoi(buffer2.substr(0, buffer2.find(" ")));
                string s_color = buffer2.substr(buffer2.find(" ") + 1);
                //cout << s_num << " " << s_color << endl;
                if (s_color == "red"){
                    //cout << s_num << "<= 12" << endl;
                    r = max(r, s_num);
                }
                if (s_color == "green"){
                    //cout << s_num << "<= 13" << endl;
                    g = max(g, s_num);
                }
                if (s_color == "blue"){
                    //cout << s_num << "<= 14" << endl;
                    b = max(b, s_num);
                }
            }          
        }
        //cout << r << " " << g << " " << b << endl;
        sum += (r * g * b);
    }
    cout << "Part 2: " << sum << endl;
}