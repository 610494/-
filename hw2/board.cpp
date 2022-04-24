#include "board.h"
#include <queue>
#include <time.h>
#include <stdlib.h>

using namespace std;

int const MAX_W = 20, MAX_H = 20, MAX_NUM = 100, steps_x[4] = {0,1,0,-1}, steps_y[4] = {-1,0,1,0};
// U R D L
bool _Board::set_w(int n) 
{ 
    //constexpr int _Board::MAX_W = 10;
    //cout << "set_w: " << n << endl;
    if(n <= MAX_W)
    {
        w = n;
        return 1;
    }
    return 0;            
}

bool _Board::set_h(int n) 
{ 
    //cout << "set_h: " << n << endl;
    if(n <= MAX_H)
    {
        h = n;
        return 1;
    }
    return 0;            
}

bool _Board::set_board(int y, int x, int m) 
{
    //cout << "set_board: " << m << "\n";
    if(is_overboard(y,x) == 0) 
    {
        board[y][x] = m;
        ++total[m];
        max_num = max(max_num , m);
        return 1;
    }    
    return 0;
}
bool _Board::is_overboard(int y, int x) const
{
    return y < 0 || y >= MAX_H || x < 0 || x >= MAX_W;
}

int _Board::pre(int y, int x) const
{
    if(y == 0 && x == 0) return -1;
    if(x == 0) return query_board(y-1, w-1);
    return query_board(y, x-1);
}

bool _Board::is_success() const
{
    //cout << "q";
    int poi[max_num+1];
    for(int i=0;i<=max_num;i++) poi[i] =-1;
    for(int i=0;i<h;++i)
    {
        for(int j=0;j<w;++j)
        {
            if(poi[query_board(i,j)] == -1) poi[query_board(i,j)] = Count(i,j);
        }
    }
    for(int i=1;i<max_num;++i) if(poi[i] > poi[i+1]) return 0;
    //cout << "success!";
    return 1;
}
_dfs_ans _Board::IDA() 
{
    
    for(int i=1;i<=limit;++i)
    {
        _dfs_ans ori;
        //cout << "\n\n\niii: " << i << "\n\n";
        reset_move();
        _dfs_ans ans = _IDA(0, i, ori);
        if(ans.is_sol()) return ans;
    }
    _dfs_ans ori;
    //ori.set_sol(0);
    return ori;
}
_dfs_ans _Board::_IDA(int dep, int lim, _dfs_ans path) 
{
    _Board now = *this;
    //cout << "dep: " << dep << "\n";
    //now.print();
    cout << endl;
    if(now.is_success()) {
        path.set_sol(1);
        return path;
    }
    //cout << "fall\n";
    if(dep >= lim) 
    {
        path.set_sol(0);
        return path;
    }
    cout << "p" << h << " " << w << "\n";
    for(int i = 0; i < h;++i)
    {
        for(int j = 0;j < w;++j)
        {
            if(now.query_board(i,j)) continue;
            cout << "ix:" << i << " " << j << " " << query_board(i,j) << "\n";
            for(int k=0;k<4;k++)
            {
                int next_x = j + steps_x[k], next_y = i + steps_y[k];
                int the_number = now.query_board(next_y, next_x);
                while(now.is_overboard(next_y,next_x) == 0 && the_number == now.query_board(next_y, next_x)) 
                {
                    //cout << k  << " next:" << next_y << " " << next_x << "\n";
                    if(move_board[(k+2)%4][next_y][next_x] == 0) 
                    {
                        move_board[(k+2)%4][next_y][next_x] = 1;
                        ++move[(k+2)%4][now.query_board(next_y,next_x)];
                    }
                    next_x += steps_x[k];
                    next_y += steps_y[k];
                }
            }
        }
    }
    for(int i=0;i<=max_num;++i)
    {
        cout << i << " total:" << total[i] << "\n";
        for(int j=0;j<4;j++)
        {
            //cout << "is?:" << i << " " << move[j][i] << " " << total[i] << "\n";
            if(move[j][i] != total[i] || total[i] == 0) continue;
            cout << "go:" << i << " " << j << " " << move[j][i] << "\n";
            _Board use = now;
            string str = use.F(&use,j,i);
            path.path_push(str);
            cout << "start\n";
            _dfs_ans ch = use._IDA(dep+1,lim,path);
            cout << "end\n";
            if(ch.is_sol()) return ch;
            path.path_pop();
            //now.F(&now,(j+2)%4,i);
        }
    }
    path.set_sol(0);
    return path;
}

void _Board::reset_move()
{
    for(int i=0;i<4;++i) for(int j =0;j<=max_num;++j) move[i][j] = 0;
    for(int i=0;i<4;++i) for(int j =0;j<h;++j) for(int k=0;k<w;k++) move_board[i][j][k] = 0;
}

string _Board::F(_Board *b ,int dir ,int n) 
{
    int i_s[4] = {1,0,b->query_h()-2,0}, j_s[4] = {0,b->query_w()-2,0,1},
        it[4] = {b->query_h(),b->query_h(),-1,b->query_h()}, 
        jt[4] = {b->query_w(),-1,b->query_w(),b->query_w()},
        i_c[4] = {1,1,-1,1}, j_c[4] = {1,-1,1,1};
    //cout << n << "F" << b->query_h() << " " << b->query_w() << " " << abs(i_s[dir]-it[dir]) << "\n";
    for(int i=i_s[dir];abs(i-it[dir])>=1;i+=i_c[dir])
    {   
        //cout << "=";
        for(int  j=j_s[dir];abs(j-jt[dir])>=1;j+=j_c[dir])
        {
            //cout << "-" << i << " " << j << "\n";
            //cout << "-" << query_board(i,j) << " ";
            if(b->query_board(i,j) == n) 
            {
                int tmp = b->query_board(i,j);
                --total[b->query_board(i,j)];
                b->set_board(i,j,b->query_board(i+steps_y[dir],j+steps_x[dir]));
                --total[b->query_board(i+steps_y[dir],j+steps_x[dir])];
                b->set_board(i+steps_y[dir],j+steps_x[dir],tmp);
                //cout << "+";
            }
        }
    }
    char c[4] = {'U','R','D','L'};
    string str = "", str2 = "";
    //cout << "n: " << n << "\n";
    while(n) 
    {
        str2 += n%10 + '0';
        n/=10;
    }
    for(int i=0;i<str2.size();i++) 
    {
        str += str2.back();
        str2.pop_back();
    }
    //cout << "\nb:\n";
    //b->print();
    str += c[dir];
    //cout << str << "\n";
    return str;
}

_dfs_ans _Board::IDA_start() {
    cout << "start\n";
    for(int i=1;i<=limit;++i)
    {
        //cout << "\n\n\niii: " << i << "\n\n";
        //reset_move();
        _dfs_ans ans = _IDA_start(i);
        if(ans.is_sol()) return ans;
    }
    _dfs_ans ori;
    //ori.set_sol(0);
    return ori;
}

_dfs_ans _Board::_IDA_start(int limit) {
    priority_queue <_Board> pq;
    _Board use = *this, ans;
    bool not_found = true;
    pq.push(use);
    while(pq.size()) {
        _Board now = pq.top();
        pq.pop();
        //now.print();
        //cout << "g:" << now.g() << " steps: " << now.path.steps() << endl;
        if(now.path.steps() > limit) continue;
        if(now.is_success()) {
            now.path.sol = 1;
            if(not_found) {
                ans = now;
                not_found = false;
                //cout << "ok" << endl;
                //cout << ans.path.steps() << "  ";
                //cout << ans.path.print() << endl;
            }
            else if(now.path.steps() < ans.path.steps()) {
                ans = now;
                //cout << "sok\n\n\n" << endl;
                //cout << ans.path.print() << endl;
            }
            continue;
        }
        now.reset_move();
        //cout << "p" << h << " " << w << "\n";
        for(int i = 0; i < h;++i)
        {
            for(int j = 0;j < w;++j)
            {
                if(now.query_board(i,j)) continue;
                //cout << "ix:" << i << " " << j << " " << query_board(i,j) << "\n";
                for(int k=0;k<4;k++)
                {
                    int next_x = j + steps_x[k], next_y = i + steps_y[k];
                    int the_number = now.query_board(next_y, next_x);
                    while(now.is_overboard(next_y,next_x) == 0 && the_number == now.query_board(next_y, next_x)) 
                    {
                        //cout << k  << " next:" << next_y << " " << next_x << "\n";
                        if(now.move_board[(k+2)%4][next_y][next_x] == 0) 
                        {
                            now.move_board[(k+2)%4][next_y][next_x] = 1;
                            ++now.move[(k+2)%4][now.query_board(next_y,next_x)];
                        }
                        next_x += steps_x[k];
                        next_y += steps_y[k];
                    }
                }
            }
        }
        for(int i=0;i<=max_num;++i)
        {
            //cout << i << " total:" << total[i] << "\n";
            for(int j=0;j<4;j++)
            {
                //cout << "is?:" << i << " " << move[j][i] << " " << total[i] << "\n";
                if(now.move[j][i] != now.total[i] || now.total[i] == 0) continue;
                //cout << "go:" << i << " " << j << " " << move[j][i] << "\n";
                _Board use = now;
                string str = use.F(&use,j,i);
                use.path.path_push(str);
                //cout << "start\n";
                if(use.path.steps() == 4) {
                    if(use.g() == 0)    cout << limit << "fuck\n";
                }
                if(use.g()+use.path.steps() <= limit) {
                    //cout << "push\n";
                    //use.print();
                    pq.push(use);
                }
                //_dfs_ans ch = use._IDA(dep+1,lim,path);
                //cout << "end\n";
                //if(ch.is_sol()) return ch;
                //now.path.path_pop();
                //now.F(&now,(j+2)%4,i);
            }  
        }
    }
    return ans.path;
}

// !not finish
int _Board::g() const{
    /*
    int min_x[100] = {}, min_y[100] = {}, max_y[100] = {}, max_x[100] = {};
    int best_x[100] = {}, best_y[100] = {}, b[201][201] = {};
    for(int i=0;i<100;++i) min_x[i] = min_y[i] = 10000;
    for(int i=0;i<h;++i) {
        for(int j=0;j<w;++j) {
            int k = board[i][j];
            min_x[k] = min(min_x[k],j);
            min_y[k] = min(min_y[k],i);
            max_x[k] = max(max_x[k],j);
            max_y[k] = max(max_y[k],i);
        }
    }
    for(int i=1;i<max_num;++i) {
        int size_w = max_x[i] - min_x[i], size_h = max_y[i] - min_y[i];
        if(board[])
    }
    */
    for(int i=0;i<21*21;i++) bit[i] = 0;
    int poi[max_num+1];
    for(int i=0;i<=max_num;i++) poi[i] =-1;
    for(int i=0;i<h;++i)
    {
        for(int j=0;j<w;++j)
        {
            if(poi[query_board(i,j)] == -1) poi[query_board(i,j)] = Count(i,j);
        }
    }
    int re = 0, max_ = 0;
    for(int i=max_num;i;--i) {
        if(poi[i] == -1) continue;
        max_ = max(max_, sum(poi[i]+1));
        re += sum(poi[i]+1);
        change(poi[i]+1,1);
    }
    //cout << "pre:" << re << endl;
    if(max_) return re / max_ + re%max_?1:0;
    return re;
}

void _Board::generate(){
    srand( time(NULL) );
    int now_w = rand() % 20 + 1, now_max_num = rand() % 99 + 1, start_x = 0, start_y = 0;
    int size_[100] = {}, num = 0;
    set_w(now_w);
    while(num < now_max_num){
        int use = rand() % now_max_num + 1;
        while(size_[use]) use = (use+1)%now_max_num+1;
        cout << use << "\n";
        int use_size = rand() % 3 + 1;
        size_[use] = use_size;
        num++;
        for(int i=0;i<use_size;++i) {
            for(int j=0;j<size_[use];++j) set_board(i+start_y,j+start_x,use);
        }
        if(use_size + start_x + 3 < now_w) start_x += use_size;
        else {
            ++start_y;
            start_x = 0;
        }
    }
    set_h(start_y);
}