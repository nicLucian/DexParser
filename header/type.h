#ifndef TYPE_H_INCLUDE
#define TYPE_H_INCLUDE

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned char uchar;

struct header_item {
    vector<uchar> magic;
    uint checksum;
    vector<uchar> signature;
    uint file_size;
    uint header_size;
    uint endian_tag;
    uint link_size;
    uint link_off;
    uint map_off;
    uint string_ids_size;
    uint string_ids_off;
    uint type_ids_size;
    uint type_ids_off;
    uint proto_ids_size;
    uint proto_ids_off;
    uint field_ids_size;
    uint field_ids_off;
    uint method_ids_size;
    uint method_ids_off;
    uint class_defs_size;
    uint class_defs_off;
    uint data_size;
    uint data_off;
};

struct proto_id_item {
    uint shorty_idx;             // index into the string_ids;
    uint return_type_id;         // index into the types;
    vector<int> params_type_id;  // index into the types
};

struct field_id_item {
    ushort class_idx;  // index into types;
    ushort type_idx;   // index into types;
    uint name_idx;     // index into string_ids;
};

struct method_id_item {
    ushort class_idx;  // index into types;
    ushort proto_idx;  // index into protos;
    uint name_idx;     // index into string_ids;
};

struct encoded_field {
    uint field_idx;     // uleb128, index into fields
    uint access_flags;  // uleb128
};

struct debug_info_item {
    // todo
};

struct type_addr_pair {
    uint type_idx;  // index into the types
    uint addr;
};

struct catch_handler {
    int size;  // sleb128
    vector<type_addr_pair> handlers;
    uint catch_all_addr;  // uleb128
};

struct try_item {
    uint start_addr;
    ushort insn_count;
    catch_handler c_handler;
};

struct code_item {
    ushort register_size;
    ushort ins_size;
    ushort outs_size;
    ushort tries_size;
    debug_info_item debug_info;
    uint insns_size;
    vector<ushort> insns;
    vector<try_item> tries;
};

struct encoded_method {
    uint method_idx;    // uleb128, index info methods;
    uint access_flags;  // uleb128
    code_item code;
};

struct class_data_item {
    uint static_fields_size;
    uint instance_fields_size;
    uint direct_methods_size;
    uint virtual_methods_size;
    vector<encoded_field> static_fields;
    vector<encoded_field> instance_fields;
    vector<encoded_method> direct_methods;
    vector<encoded_method> instance_methods;
};

struct annotations_directory_item{
    //todo
};


struct class_def_item {
    uint class_idx;
    uint access_flags;
    uint superclass_idx;
    vector<ushort> interfaces_idx;
    uint source_file_idx;
    annotations_directory_item annotaions;
    class_data_item class_data;
};

#endif