#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "header/DexParser.h"

using namespace std;

vector<uchar> readFile(string path) {
    vector<uchar> result;
    ifstream in_file(path);
    uchar tmp;
    while (!in_file.eof()) {
        tmp = in_file.get();
        result.push_back(tmp);
    }

    return result;
}

int main(int, char**) {
    vector<uchar> content = readFile("../resource/classes3.dex");
    DexParser parser(content);
    parser.parse();
    return 0;
}