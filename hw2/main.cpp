#include <iostream>
#include "board.h"
#include "dfs_ans.h"
#include <fstream>
#include "fileIO.h"
#include <vector>
#include <string>

using namespace std;

int const steps_x[4] = {0,1,0,-1}, steps_y[4] = {-1,0,1,0};

int main() {
    string input = "input.txt";
    _FileIO fileIO;
    vector <string> sv = fileIO.read(input);
    //for(int i = 0; i < v.size(); ++i) cout << v[i] << "\n";
    //cout << v.size() << "\n";
    //return 0;
    const char cut = ' ';
    _Board board;
    for(int i = 0; i < sv.size(); ++i) {
        vector <string> nv = fileIO.cut(sv[i],cut);
        //cout << "\n\ni: " << i << " " << nv.size() << "\n";
        //for(int j = 0; j < nv.size(); ++j) cout << nv[j] << " ";
        //cout << nv[nv.size()-1] << "\n";
        if(i == 0) {
            board.set_h(fileIO.to_number(nv[0]));
            board.set_w(fileIO.to_number(nv[1]));
            //cout << "\n\nfuck:" << fileIO.to_number(nv[1]) << "\n";
        }
        else {
            for(int j = 0; j < nv.size(); ++j) {
                board.set_board(i-1,j,fileIO.to_number(nv[j]));
            }
        }
    }
    //cout << "h:" << board.query_h() << " w: " << board.query_w() << "\n";
    
    
    /*
    int buf_len = 1000, arr[2], n, m;
    char buffer[buf_len];
    file.getline(buffer,sizeof(buffer),'\n');
    for(int i=0,j=0,k=0;k<2;i++) 
    {
        if(buffer[i] > '9' || buffer[i] < '0')
        {
            if(!j) continue;
            arr[k++] = j;
            j = 0;
        }
        else
        {
            j *= 10;
            j += buffer[i] - '0';
        }
    }
    n = arr[0], m = arr[1];
    _Board board;
    board.set_w(m);
    board.set_h(n);
    //cout << n << " " << m << "\n";
    //return 0;
    for(int i=0;i<n;++i)
    {
        file.getline(buffer,sizeof(buffer),'\n');
        for(int j=0;j<m*2;j+=2)
        {
            int num = 0;
            //cout << "buf:" << buffer[j] << " " << buffer[j+1] << "\n";
            if(buffer[j] == '-') num += buffer[j+1] - '0';
            else num += (buffer[j] - '0') * 10 + (buffer[j+1] - '0');
            //cout << "num:" << num << endl;
            board.set_board(i,j/2,num);
        }
        //cout << "\n";
    }
    */
    //cout << "l\n";
    //for(int i=0;i<board.query_h();i++) {for(int j=0;j<board.query_w();j++) cout << board.query_board(i,j) << " "; cout << "\n";}
    //return 0;
    _dfs_ans ans = board.IDS();
    //cout << "ann\n";
    /*
    while(ans.path_size() > 0) 
    {
        cout << ans.path_back() << " ";
        ans.path_pop();
    }
    cout << "\n";
    */
    string output = "output.txt";
    fileIO.write(output,ans.print());
    cout << "ans:" << ans.print() << "\n";
    return 0;
}