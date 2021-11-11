#include "header/DexParser.h"

#include <iostream>
#include <vector>

using namespace std;

unsigned int readUInt(vector<unsigned char>& content, int offset) {
    return (content[offset + 3] << 24) | (content[offset + 2] << 16) |
           (content[offset + 1] << 8) | content[offset];
}

vector<unsigned char> readChars(vector<unsigned char>& content, int offset, int length) {
    vector<unsigned char> result;
    for (int i = 0; i < length; i++) {
        result.push_back(content[offset + i]);
    }
    return result;
}

DexParser::DexParser(vector<unsigned char>& content) : content(content){
    current_offset = 0;
};

void DexParser::parse() { parseHead(); }

void DexParser::parseHead() {
    // skip magic:dex\n035\0
    current_offset += 8;

    unsigned int checksum = readUInt(content, current_offset);
    vector<unsigned char> signature = readChars(content, current_offset + 4, 20);
    unsigned int file_size = readUInt(content, current_offset + 24);
    unsigned int header_size = readUInt(content, current_offset + 28);
    unsigned int endian_tag = readUInt(content, current_offset + 32);
    unsigned int link_size = readUInt(content, current_offset + 36)
}