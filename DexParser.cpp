#include "header/DexParser.h"

#include <iostream>
#include <vector>

using namespace std;

unsigned int readUInt(vector<unsigned char>& content, int offset) {
    return (content[offset + 3] << 24) | (content[offset + 2] << 16) |
           (content[offset + 1] << 8) | content[offset];
}

vector<unsigned char> readChars(vector<unsigned char>& content, int offset,
                                int length) {
    vector<unsigned char> result;
    for (int i = 0; i < length; i++) {
        result.push_back(content[offset + i]);
    }
    return result;
}

DexParser::DexParser(vector<unsigned char>& content) : content(content) {
    current_offset = 0;
};

void DexParser::parse() { parseHead(); }

void DexParser::parseHead() {
    vector<unsigned char> magic = readChars(content, current_offset, 8);
    current_offset += 8;
    unsigned int checksum = readUInt(content, current_offset);
    vector<unsigned char> signature =
        readChars(content, current_offset + 4, 20);
    unsigned int file_size = readUInt(content, current_offset + 24);
    unsigned int header_size = readUInt(content, current_offset + 28);
    unsigned int endian_tag = readUInt(content, current_offset + 32);
    unsigned int link_size = readUInt(content, current_offset + 36);
    unsigned int link_off = readUInt(content, current_offset + 40);
    unsigned int map_off = readUInt(content, current_offset + 44);
    unsigned int string_ids_size = readUInt(content, current_offset + 48);
    unsigned int string_ids_off = readUInt(content, current_offset + 52);
    unsigned int type_ids_size = readUInt(content, current_offset + 56);
    unsigned int type_ids_off = readUInt(content, current_offset + 60);
    unsigned int proto_ids_size = readUInt(content, current_offset + 64);
    unsigned int proto_ids_off = readUInt(content, current_offset + 68);
    unsigned int field_ids_size = readUInt(content, current_offset + 72);
    unsigned int field_ids_off = readUInt(content, current_offset + 76);
    unsigned int method_ids_size = readUInt(content, current_offset + 80);
    unsigned int method_ids_off = readUInt(content, current_offset + 84);
    unsigned int class_defs_size = readUInt(content, current_offset + 88);
    unsigned int class_defs_off = readUInt(content, current_offset + 92);
    unsigned int data_size = readUInt(content, current_offset + 96);
    unsigned int data_off = readUInt(content, current_offset + 100);
    current_offset += 100;
    dex_info = new DexInfo(
        magic, checksum, signature, file_size, header_size, endian_tag,
        link_size, link_off, map_off, string_ids_size, string_ids_off,
        type_ids_size, type_ids_size, proto_ids_size, proto_ids_off,
        field_ids_size, field_ids_off, method_ids_size, method_ids_off,
        class_defs_size, class_defs_off, data_size, data_off);
    std::cout << "dex_info = " << (dex_info->get_field_ids_size());
}

DexParser::~DexParser() {
    if (dex_info) { 
        delete dex_info;
    }
}