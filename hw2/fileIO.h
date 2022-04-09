#ifndef FILEIO_
#define FILEIO_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class _FileIO{
public:
    void write(std::string fileName, std::string content, std::string mode) {
        std::ofstream file;
        if(mode == "out") file.open(fileName,std::ios::out);
        else if(mode == "app") file.open(fileName,std::ios::app);
        else std::cout << "writes error\n";
        file << content;
        file.close();
    };
    void write(std::string fileName, double content, std::string mode) {
        std::ofstream file;
        if(mode == "out") file.open(fileName,std::ios::out);
        else if(mode == "app") file.open(fileName,std::ios::app);
        else std::cout << "writed error\n";
        file << content;
        file.close();
    };
    void write(std::string fileName, int content, std::string mode) {
        std::ofstream file;
        if(mode == "out") file.open(fileName,std::ios::out);
        else if(mode == "app") file.open(fileName,std::ios::app);
        else std::cout << "writei error\n";
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