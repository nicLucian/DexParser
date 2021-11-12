#include "header/DexParser.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

uint readUInt(vector<uchar>& content, int offset) {
    return (content[offset + 3] << 24) | (content[offset + 2] << 16) |
           (content[offset + 1] << 8) | content[offset];
}

ushort readUShort(vector<uchar>& content, int offset) {
    return (content[offset + 1] << 8) | content[offset];
}

pair<uint, uint> readUleb128(vector<uchar>& content, int offset) {
    int bits_count = 1;
    int result = 0;
    while (true) {
        bool need_break = !(content[offset] & 0x80);
        result = result | ((content[offset] & 0x7f) << (bits_count - 1) * 7);
        bits_count++;
        offset++;
        if (need_break) {
            break;
        }
    }

    return {result, bits_count - 1};
}

vector<uchar> readChars(vector<uchar>& content, int offset, int length) {
    vector<uchar> result;
    for (int i = 0; i < length; i++) {
        result.push_back(content[offset + i]);
    }
    return result;
}

string read_string(vector<uchar>& content, int offset, int length) {
    stringstream ostr;
    for (int i = 0; i < length; i++) {
        ostr << content[offset + i];
    }
    return ostr.str();
}

DexParser::DexParser(vector<uchar>& content) : content(content) {
    current_offset = 0;
};

void DexParser::parse() {
    parseHead();
    parseStrings();
    parseTypes();
    parseProtos();
}

void DexParser::parseHead() {
    vector<uchar> magic = readChars(content, current_offset, 8);
    current_offset += 8;
    uint checksum = readUInt(content, current_offset);
    vector<uchar> signature = readChars(content, current_offset + 4, 20);
    uint file_size = readUInt(content, current_offset + 24);
    uint header_size = readUInt(content, current_offset + 28);
    uint endian_tag = readUInt(content, current_offset + 32);
    uint link_size = readUInt(content, current_offset + 36);
    uint link_off = readUInt(content, current_offset + 40);
    uint map_off = readUInt(content, current_offset + 44);
    uint string_ids_size = readUInt(content, current_offset + 48);
    uint string_ids_off = readUInt(content, current_offset + 52);
    uint type_ids_size = readUInt(content, current_offset + 56);
    uint type_ids_off = readUInt(content, current_offset + 60);
    uint proto_ids_size = readUInt(content, current_offset + 64);
    uint proto_ids_off = readUInt(content, current_offset + 68);
    uint field_ids_size = readUInt(content, current_offset + 72);
    uint field_ids_off = readUInt(content, current_offset + 76);
    uint method_ids_size = readUInt(content, current_offset + 80);
    uint method_ids_off = readUInt(content, current_offset + 84);
    uint class_defs_size = readUInt(content, current_offset + 88);
    uint class_defs_off = readUInt(content, current_offset + 92);
    uint data_size = readUInt(content, current_offset + 96);
    uint data_off = readUInt(content, current_offset + 100);
    current_offset += 100;
    dex_header = new DexHeader(
        magic, checksum, signature, file_size, header_size, endian_tag,
        link_size, link_off, map_off, string_ids_size, string_ids_off,
        type_ids_size, type_ids_off, proto_ids_size, proto_ids_off,
        field_ids_size, field_ids_off, method_ids_size, method_ids_off,
        class_defs_size, class_defs_off, data_size, data_off);
}

void DexParser::parseStrings() {
    uint current_string_id_offset = dex_header->get_string_ids_off();
    uint string_data_offset = readUInt(content, current_string_id_offset);
    for (int i = 0; i < dex_header->get_string_ids_size(); i++) {
        // fisrt:actual result of current uleb128
        // second:bits of current uleb128
        pair<uint, uint> string_data_info =
            readUleb128(content, string_data_offset);

        int string_content_offset =
            string_data_offset + string_data_info.second;
        int string_content_length = string_data_info.first;
        string string_content =
            read_string(content, string_content_offset, string_content_length);

        strings.push_back(string_content);
        string_data_offset +=
            (string_data_info.second + string_data_info.first + 1);
    }
}

void DexParser::parseTypes() {
    uint current_types_id_offset = dex_header->get_type_ids_off();
    uint types_id_size = dex_header->get_type_ids_size();
    for (uint i = 0; i < types_id_size; i++) {
        uint type_id = readUInt(content, current_types_id_offset);
        type_ids.push_back(type_id);
        current_types_id_offset += 4;
    }
}

void DexParser::parseProtos() {
    uint proto_id_offset = dex_header->get_proto_ids_off();
    uint proto_id_size = dex_header->get_proto_ids_size();
    for (uint i = 0; i < proto_id_size; i++) {
        Proto proto;
        proto.shorty_idx = readUInt(content, proto_id_offset);
        proto.return_type_id = readUInt(content, proto_id_offset + 4);
        uint parameters_offset = readUInt(content, proto_id_offset + 8);
        if (parameters_offset) {
            uint param_size = readUInt(content, parameters_offset);
            for (uint i = 0; i < param_size; i++) {
                ushort type_id = readUShort(content, parameters_offset + i * 2 + 4);
                proto.params_type_id.push_back(type_id);
            }
        }
        protos.push_back(proto);
        proto_id_offset += 12;
    }
}

DexParser::~DexParser() {
    if (dex_header) {
        delete dex_header;
    }
}