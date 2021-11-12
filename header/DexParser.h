#ifndef DEX_PARSER_H_INCLUDE
#define DEX_PARSER_H_INCLUDE

#include <iostream>
#include <vector>
#include "DexHeader.h"
#include "type.h"
#include "Proto.h"

using namespace std;

class DexParser {
   public:
    DexParser(vector<uchar>& content);

    void parse();

    ~DexParser();

   private:
    void parseHead();
    void parseStrings();
    void parseTypes();
    void parseProtos();

   private:
    vector<uchar> content;
    int current_offset;
    DexHeader* dex_header;
    vector<string> strings;
    vector<uint> type_ids;
    vector<Proto> protos;

};
#endif