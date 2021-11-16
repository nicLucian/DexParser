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
    uint bits_count = 1;
    uint result = 0;
    while (true) {
        bool need_break = !(content[offset] & 0x80);
        result = result | ((content[offset] & 0x7f) << (bits_count - 1) * 7);
        bits_count++;
        offset++;
        if (need_break) {
            break;
        }
    }
    return make_pair(result, bits_count - 1);
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
    parseFields();
    parseMethods();
    parseClasses();
}

void DexParser::parseHead() {
    dex_header.magic = readChars(content, current_offset, 8);
    current_offset += 8;
    dex_header.checksum = readUInt(content, current_offset);
    dex_header.signature = readChars(content, current_offset + 4, 20);
    dex_header.file_size = readUInt(content, current_offset + 24);
    dex_header.header_size = readUInt(content, current_offset + 28);
    dex_header.endian_tag = readUInt(content, current_offset + 32);
    dex_header.link_size = readUInt(content, current_offset + 36);
    dex_header.link_off = readUInt(content, current_offset + 40);
    dex_header.map_off = readUInt(content, current_offset + 44);
    dex_header.string_ids_size = readUInt(content, current_offset + 48);
    dex_header.string_ids_off = readUInt(content, current_offset + 52);
    dex_header.type_ids_size = readUInt(content, current_offset + 56);
    dex_header.type_ids_off = readUInt(content, current_offset + 60);
    dex_header.proto_ids_size = readUInt(content, current_offset + 64);
    dex_header.proto_ids_off = readUInt(content, current_offset + 68);
    dex_header.field_ids_size = readUInt(content, current_offset + 72);
    dex_header.field_ids_off = readUInt(content, current_offset + 76);
    dex_header.method_ids_size = readUInt(content, current_offset + 80);
    dex_header.method_ids_off = readUInt(content, current_offset + 84);
    dex_header.class_defs_size = readUInt(content, current_offset + 88);
    dex_header.class_defs_off = readUInt(content, current_offset + 92);
    dex_header.data_size = readUInt(content, current_offset + 96);
    dex_header.data_off = readUInt(content, current_offset + 100);
    current_offset += 100;
}

void DexParser::parseStrings() {
    uint current_string_id_offset = dex_header.string_ids_off;
    uint string_data_offset = readUInt(content, current_string_id_offset);
    for (int i = 0; i < dex_header.string_ids_size; i++) {
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
    uint current_types_id_offset = dex_header.type_ids_off;
    uint types_id_size = dex_header.type_ids_size;
    for (uint i = 0; i < types_id_size; i++) {
        uint type_id = readUInt(content, current_types_id_offset);
        types.push_back(type_id);
        current_types_id_offset += 4;
    }
}

void DexParser::parseProtos() {
    uint proto_id_offset = dex_header.proto_ids_off;
    uint proto_id_size = dex_header.proto_ids_size;
    for (uint i = 0; i < proto_id_size; i++) {
        proto_id_item proto;
        proto.shorty_idx = readUInt(content, proto_id_offset);
        proto.return_type_id = readUInt(content, proto_id_offset + 4);
        uint parameters_offset = readUInt(content, proto_id_offset + 8);
        if (parameters_offset) {
            uint param_size = readUInt(content, parameters_offset);
            for (uint i = 0; i < param_size; i++) {
                ushort type_id =
                    readUShort(content, parameters_offset + i * 2 + 4);
                proto.params_type_id.push_back(type_id);
            }
        }
        protos.push_back(proto);
        proto_id_offset += 12;
    }
}

void DexParser::parseFields() {
    uint field_ids_offset = dex_header.field_ids_off;
    uint field_ids_size = dex_header.field_ids_size;
    for (int i = 0; i < field_ids_size; i++) {
        field_id_item item;
        item.class_idx = readUShort(content, field_ids_offset);
        item.type_idx = readUShort(content, field_ids_offset + 2);
        item.name_idx = readUInt(content, field_ids_offset + 4);
        fields.push_back(item);
        field_ids_offset += 8;
    }
}

void DexParser::parseMethods() {
    uint method_ids_offset = dex_header.method_ids_off;
    uint method_ids_size = dex_header.method_ids_size;
    for (int i = 0; i < method_ids_size; i++) {
        method_id_item item;
        item.class_idx = readUShort(content, method_ids_offset);
        item.proto_idx = readUShort(content, method_ids_offset + 2);
        item.name_idx = readUInt(content, method_ids_offset + 4);
        method_ids_offset += 8;
        methods.push_back(item);
    }
}

void DexParser::parseClasses() {
    uint classes_size = dex_header.class_defs_size;
    uint class_def_offset = dex_header.class_defs_off;
    for (int i = 0; i < classes_size; i++) {
        class_def_item class_item = parseSingleClass(class_def_offset);
        classes.push_back(class_item);
        class_def_offset += (8 * 4);
    }
}

class_def_item DexParser::parseSingleClass(uint offset) {
    class_def_item class_item;
    class_item.class_idx = readUInt(content, offset);
    class_item.access_flags = readUInt(content, offset + 4);

    class_item.superclass_idx = readUInt(content, offset + 8);
    uint interfaces_offset = readUInt(content, offset + 12);
    if (interfaces_offset != 0) {
        uint interfaces_size = readUInt(content, interfaces_offset);
        for (uint i = 0; i < interfaces_size; i++) {
            ushort type_idx = readUShort(content, 4 + interfaces_offset);
            class_item.interfaces_idx.push_back(type_idx);
            interfaces_offset += 2;
        }
    }

    class_item.source_file_idx = readUInt(content, offset + 16);

    // todo parse annotations

    class_item.class_data = parseClassData(offset + 24);

    uint static_field_offset = readUInt(content, offset + 28);
    // todo parse static fields;
    return class_item;
}

class_data_item DexParser::parseClassData(uint class_data_offset) {
    class_data_item class_data;
    pair<uint, uint> static_fields_size = readUleb128(content, class_data_offset);
    class_data.static_fields_size = static_fields_size.first;
    
    return class_data;
}