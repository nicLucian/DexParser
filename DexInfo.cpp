#include "header/DexInfo.h"

DexInfo::DexInfo(vector<unsigned char>& magic, unsigned int checksum,
                 vector<unsigned char>& signature, unsigned int file_size,
                 unsigned int header_size, unsigned int endian_tag,
                 unsigned int link_size, unsigned int link_off,
                 unsigned int map_off, unsigned int string_ids_size,
                 unsigned int string_ids_off, unsigned int type_ids_size,
                 unsigned int type_ids_off, unsigned int proto_ids_size,
                 unsigned int proto_ids_off, unsigned int field_ids_size,
                 unsigned int field_ids_off, unsigned int method_ids_size,
                 unsigned int method_ids_off, unsigned int class_defs_size,
                 unsigned int class_defs_off, unsigned int data_size,
                 unsigned int data_off)
    : magic(magic),
      checksum(checksum),
      signature(signature),
      file_size(file_size),
      header_size(header_size),
      endian_tag(endian_tag),
      link_size(link_size),
      link_off(link_off),
      map_off(map_off),
      string_ids_size(string_ids_size),
      string_ids_off(string_ids_off),
      type_ids_size(type_ids_size),
      type_ids_off(type_ids_off),
      proto_ids_size(proto_ids_size),
      proto_ids_off(proto_ids_off),
      field_ids_size(field_ids_size),
      field_ids_off(field_ids_off),
      method_ids_size(method_ids_size),
      method_ids_off(method_ids_off),
      class_defs_size(class_defs_size),
      class_defs_off(class_defs_off),
      data_size(data_size),
      data_off(data_off){};

vector<unsigned char> DexInfo::get_magic() { return magic; }
unsigned int DexInfo::get_checksum() { return checksum; }
vector<unsigned char> DexInfo::get_signature() { return signature; }
unsigned int DexInfo::get_file_size() { return file_size; }
unsigned int DexInfo::get_header_size() { return header_size; }
unsigned int DexInfo::get_endian_tag() { return endian_tag; }
unsigned int DexInfo::get_link_size() { return link_size; }
unsigned int DexInfo::get_link_off() { return link_off; }
unsigned int DexInfo::get_map_off() { return map_off; }
unsigned int DexInfo::get_string_ids_size() { return string_ids_size; }
unsigned int DexInfo::get_string_ids_off() { return string_ids_off; }
unsigned int DexInfo::get_type_ids_size() { return type_ids_size; }
unsigned int DexInfo::get_type_ids_off() { return type_ids_off; }
unsigned int DexInfo::get_proto_ids_size() { return proto_ids_size; }
unsigned int DexInfo::get_proto_ids_off() { return proto_ids_off; }
unsigned int DexInfo::get_field_ids_size() { return field_ids_size; }
unsigned int DexInfo::get_field_ids_off() { return field_ids_off; }
unsigned int DexInfo::get_method_ids_size() { return method_ids_size; }
unsigned int DexInfo::get_method_ids_off() { return method_ids_off; }
unsigned int DexInfo::get_class_defs_size() { return class_defs_size; }
unsigned int DexInfo::get_class_defs_off() { return class_defs_off; }
unsigned int DexInfo::get_data_size() { return data_size; }
unsigned int DexInfo::get_data_off() { return data_off; }
