#ifndef DEX_PARSER_H_INCLUDE
#define DEX_PARSER_H_INCLUDE

#include <iostream>
#include <vector>
#include "DexInfo.h"

using namespace std;

class DexParser {
   public:
    DexParser(vector<unsigned char>& content);

    void parse();

    ~DexParser();

   private:
    void parseHead();

   private:
    vector<unsigned char> content;
    int current_offset;
    DexInfo* dex_info;

};
#endif