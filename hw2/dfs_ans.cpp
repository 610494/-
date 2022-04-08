#include "dfs_ans.h"
#include "iostream"
using namespace std;
void _dfs_ans::_path_push(string str) 
{
    path += str;
}
void _dfs_ans::path_push(string str) 
{
    if(path_size())
    {
        last_cut = path_size();
        string Str = "";
        Str += cut;
        _path_push(Str);
        //_path_push(str);
        path_size_add(1);
    }
    _path_push(str);
    path_size_add(str.size());
}
string _dfs_ans::path_back()
{
    //cout << last_cut << endl;
    string str = "";
    for(int i=last_cut+1;i<=path_size();i++)
    {
        if(i == path_size()) {
            last_cut -= (str.size()+1);
            return str;
        }
            
        str += path_query(i);
    }
    return "error~";//沒啥用
}
int _dfs_ans::path_size() const 
{ 
    return size;
}

char _dfs_ans::path_query(int n) 
{
    return path[n];//沒做檢查
}
void _dfs_ans::path_size_add(int n) 
{
    size += n;
}

void _dfs_ans::path_pop()
{
    if(path_size() == 0) return ;
    while(path_size() && path.back() != cut) {
        path_size_add(-1);
        path.pop_back();
    }
    if(path_size())
    {
        path_size_add(-1);
        path.pop_back();
    }
}