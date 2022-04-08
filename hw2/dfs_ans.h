#ifndef DFS_ANS
#define DFS_ANS
#include <string>

class _dfs_ans {
    static constexpr char cut = ' ';
    friend class _Board;
    public:
        _dfs_ans()
        {
            path = "";
            sol = size = 0;
            last_cut = 100000;//big number
        }
        void path_push(std::string );
        std::string path_back();
        int path_size() const;
        bool is_sol() const { return sol; }
        void set_sol(bool b) {sol = b;}
        void path_pop();
        std::string print() {return path;}
    private:
        bool sol;
        std::string path;
        int size, last_cut;
        char path_query(int );
        void path_size_add(int );
        void _path_push(std::string );
};

#endif