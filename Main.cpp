#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "header/DexParser.h"

using namespace std;

vector<unsigned char> readFile(string path) {
    vector<unsigned char> result;
    ifstream in_file(path);
    unsigned char tmp;
    while (!in_file.eof()) {
        tmp = in_file.get();
        result.push_back(tmp);
    }

    return result;
}

int main() {
    vector<unsigned char> content = readFile("resource/classes3.dex");
    std::cout << "size = " << content.size();
    DexParser parser(content);
    parser.parse();
}