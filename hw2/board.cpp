#include "board.h"

using namespace std;

int const MAX_W = 10, MAX_H = 10, MAX_NUM = 100, steps_x[4] = {0,1,0,-1}, steps_y[4] = {-1,0,1,0};
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
    for(int i=1;i<max_num;++i) {cout << poi[i] << " ";if(poi[i] > poi[i+1]) {cout << poi[i+1] << "\n";return 0;}}
    cout << "success!";
    return 1;
}
_dfs_ans _Board::IDS() 
{
    
    for(int i=1;i<limit;++i)
    {
        _dfs_ans ori;
        cout << "\n\n\niii: " << i << "\n\n";
        reset_move();
        _dfs_ans ans = _IDS(0, i, ori);
        if(ans.is_sol()) return ans;
    }
    _dfs_ans ori;
    //ori.set_sol(0);
    return ori;
}
_dfs_ans _Board::_IDS(int dep, int lim, _dfs_ans path) 
{
    _Board now = *this;
    if(path.path_size() && path.path[0] == '5')
    {
        cout << "dep: " << dep << "\n";
        now.print();
        cout << "\n";
        if(now.is_success()) {
            path.set_sol(1);
            return path;
        }
    }
    //cout << "fall\n";
    if(dep >= lim) 
    {
        path.set_sol(0);
        return path;
    }
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
        //cout << i << " total:" << total[i] << "\n";
        for(int j=0;j<4;j++)
        {
            //cout << "is?:" << i << " " << move[j][i] << " " << total[i] << "\n";
            if(move[j][i] != total[i] || total[i] == 0) continue;
            //cout << "go:" << i << " " << j << " " << move[j][i] << "\n";
            _Board use = now;
            string str = use.F(&use,j,i);
            path.path_push(str);
            //cout << "start\n";
            _dfs_ans ch = use._IDS(dep+1,lim,path);
            //cout << "end\n";
            if(ch.is_sol()) {cout << "good" << ch.path << "\n";return ch;}
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