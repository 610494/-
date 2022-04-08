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
            for(int i = 0; i < 10; ++i) for(int j = 0;j<10;++j) board[i][j] = 0;
            for(int i=0;i<4;++i) for(int j =0;j<10;++j) move[i][j] = 0;
            for(int i=0;i<4;++i) for(int j =0;j<10;++j) for(int k=0;k<10;k++) move_board[i][j][k] = 0;
            for(int i=0;i<10;++i) total[i] = 0;
            limit = 5;
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
        _dfs_ans IDS();
        int Count(int y, int x) const{return y*w+x;}
    private:
        int w, h, board[11][11], total[11], move[5][11], move_board[5][11][11], max_num, limit;
        _dfs_ans _IDS(int , int, _dfs_ans);
        std::string F(_Board * ,int,int);
};

#endif