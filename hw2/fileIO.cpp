#include "fileIO.h"
#include <iostream>

using std::string;
using std::vector;
using std::cout;

vector <string>_FileIO::cut(const string & input, char c) {
    vector <string> result;
    string tmp;
    //cout << "start\n";
    for(int i = 0; i < input.size(); ++i) {
        //cout << input[i] << "+";
        if(input[i] == c) {
            //cout << "size: " << tmp.size() << "\n";
            if(tmp.size()) result.push_back(tmp);
            tmp = "";
        }
        else if(int(input[i]) != 13){
            //cout << "else: ";
            tmp.push_back(input[i]);
            //cout << tmp.size() << "\n";
        }
    }
    if(tmp.size()) {
        result.push_back(tmp);
        //cout << " last: " << tmp << "+ ";
        //cout << tmp.size() << "\n";
    }
    //cout << "end\n";
    return result;
}

int _FileIO::to_number(const std::string &str) {
    // !沒有檢查是不是都是數字
    //cout << "to: " << str << " ";
    int result = 0;
    for(int i = 0; i < str.size();++i) {
        if(str[i] < '0' || str[i] > '9') {
            cout << "e:" << int(str[i]) << "r\n";
            continue;
        }
        result *= 10;
        result += (str[i] - '0');
    }
    cout << result << "\n";
    return result;
}