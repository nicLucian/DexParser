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
}

#endif