#ifndef BOARD
#define BOARD 

#include "dfs_ans.h"
#include <string>

#include <iostream>
using namespace std;

class _Board {
    public:
        //static int constexpr MAX_W = 10, MAX_H = 10, MAX_NUM = 100, steps_x[4] = {0,1,0,-1}, steps_y[4] = {-1,0,1,0};
        _Board() 
        {
            max_num = w = h = 0;
            for(int i = 0; i < 21; ++i) for(int j = 0;j<21;++j) board[i][j] = 0;
            for(int i=0;i<4;++i) for(int j =0;j<21;++j) move[i][j] = 0;
            for(int i=0;i<4;++i) for(int j =0;j<21;++j) for(int k=0;k<21;k++) move_board[i][j][k] = 0;
            for(int i=0;i<21;++i) total[i] = 0;
            limit = 50;
        }
        int query_limit() const
        {
            return limit;
        }
        int query_board(int y, int x) const 
        { 
            return board[y][x];
        }
        int query_h() const 
        { 
            return h;
        }
        int query_w() const 
        { 
            return w;
        }
        bool set_w(int );
        bool set_h(int );
        bool set_board(int , int , int );
        void set_limit(int lim){limit = lim;}
        bool is_overboard(int , int) const;
        int pre(int , int ) const;
        bool is_success()const;
        void reset_move();
        void print() const
        {
            for(int i = 0; i < h;++i) {for(int j = 0; j < w;++j) cout << query_board(i,j) << " "; cout << "\n";}
        }
        _dfs_ans IDA();
        _dfs_ans IDA_start();
        int Count(int y, int x) const{return y*w+x;}
        int g()const;
        bool operator<(const _Board b) const{
            return g() + path.steps() < b.g() + b.path.steps();
        }
        void generate();
    private:
        int w, h, board[21][21], total[21], move[5][21], move_board[5][21][21], max_num, limit;
        mutable int bit[21*21] = {};
        _dfs_ans _IDA(int , int, _dfs_ans);
        _dfs_ans _IDA_start(int );
        _dfs_ans path;
        std::string F(_Board * ,int,int);
        int lowbit(int n) const{
            return n & (-n);
        }
        void change(int id, int k) const{
            //cout << "c" << endl;
            for (int i = id; i <= 21; i += lowbit(i)) {
                //cout << "i:" << i << endl;
                bit[i] += k;
            }
                
        }
        int sum(int k) const{
            //cout << "sum" << endl;
            int re = 0;
            for(int i=k;i>0;i-=lowbit(i)) {
                re += bit[i];
                //cout << "i:" << i << endl;
            }
            return re;
        }
};

#endif