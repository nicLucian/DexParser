#ifndef DEX_PARSER_H_INCLUDE
#define DEX_PARSER_H_INCLUDE

#include <iostream>
#include <vector>

#include "type.h"

using namespace std;

class DexParser {
   public:
    DexParser(vector<uchar>& content);

    void parse();

   private:
    void parseHead();
    void parseStrings();
    void parseTypes();
    void parseProtos();
    void parseFields();
    void parseMethods();
    void parseClasses();
    class_def_item parseSingleClass(uint offset);
    class_data_item parseClassData(uint offset);

   private:
    vector<uchar> content;
    int current_offset;
    header_item dex_header;
    vector<string> strings;
    vector<uint> types;
    vector<proto_id_item> protos;
    vector<field_id_item> fields;
    vector<method_id_item> methods;
    vector<class_def_item> classes;
};
#endif