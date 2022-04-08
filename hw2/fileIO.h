#ifndef FILEIO_
#define FILEIO_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class _FileIO{
public:
    void write(std::string fileName, std::string content) {
        std::ofstream file;
        file.open(fileName);
        file << content;
        file.close();
    };
    // !要怎樣告知使用者檔案路徑不存在?
    std::vector<std::string> read(std::string fileName) {
        std::ifstream file(fileName);
        //file.open(fileName,ios::in);
        std::vector<std::string> result;
        if(file.is_open() == 0) {
            std::cout << "file isn't exists\n";
            file.close();
            return result;
        }
        std::string buffer = "";
        while(getline(file,buffer)) {
            result.push_back(buffer);
            //cout << buffer << " ";
        }
        file.close();
        //cout << result.size() << "\nend\n";
        return result;
    }
    std::vector <std::string> cut(const std::string &, char );
    int to_number(const std::string & );
private:
    

};

#endif // FILEIO_