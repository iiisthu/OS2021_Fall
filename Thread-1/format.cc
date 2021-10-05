#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// modify settsing here to check outpput format of other files
std::string filename = "format.out";
int len = 16, lines = 48;

int main(){
    std::string line;
    std::ifstream ifs(filename);
    int length = 0, cnt = 0;
    if (ifs.is_open()) {
        while (std::getline(ifs, line)) {
            if (length == 0) {
                for (char x: line) {
                    if (x == ',' || x == ' ')   ++length;
                }
                ++length;
            }
            if(length != len)throw std::runtime_error("mismatch length!\n ");
            cnt++;
        }
        ifs.close();
    } else {
        throw std::runtime_error("Error opening file " + filename + "!");
    }
    if(cnt != lines)throw std::runtime_error("mismatch output lines!\n ");
    else printf("pass format test!\n");
}
