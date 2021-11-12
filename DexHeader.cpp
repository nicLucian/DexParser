#include "header/DexHeader.h"

DexHeader::DexHeader(vector<uchar>& magic, uint checksum,
                 vector<uchar>& signature, uint file_size,
                 uint header_size, uint endian_tag,
                 uint link_size, uint link_off,
                 uint map_off, uint string_ids_size,
                 uint string_ids_off, uint type_ids_size,
                 uint type_ids_off, uint proto_ids_size,
                 uint proto_ids_off, uint field_ids_size,
                 uint field_ids_off, uint method_ids_size,
                 uint method_ids_off, uint class_defs_size,
                 uint class_defs_off, uint data_size,
                 uint data_off)
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

vector<uchar> DexHeader::get_magic() { return magic; }
uint DexHeader::get_checksum() { return checksum; }
vector<uchar> DexHeader::get_signature() { return signature; }
uint DexHeader::get_file_size() { return file_size; }
uint DexHeader::get_header_size() { return header_size; }
uint DexHeader::get_endian_tag() { return endian_tag; }
uint DexHeader::get_link_size() { return link_size; }
uint DexHeader::get_link_off() { return link_off; }
uint DexHeader::get_map_off() { return map_off; }
uint DexHeader::get_string_ids_size() { return string_ids_size; }
uint DexHeader::get_string_ids_off() { return string_ids_off; }
uint DexHeader::get_type_ids_size() { return type_ids_size; }
uint DexHeader::get_type_ids_off() { return type_ids_off; }
uint DexHeader::get_proto_ids_size() { return proto_ids_size; }
uint DexHeader::get_proto_ids_off() { return proto_ids_off; }
uint DexHeader::get_field_ids_size() { return field_ids_size; }
uint DexHeader::get_field_ids_off() { return field_ids_off; }
uint DexHeader::get_method_ids_size() { return method_ids_size; }
uint DexHeader::get_method_ids_off() { return method_ids_off; }
uint DexHeader::get_class_defs_size() { return class_defs_size; }
uint DexHeader::get_class_defs_off() { return class_defs_off; }
uint DexHeader::get_data_size() { return data_size; }
uint DexHeader::get_data_off() { return data_off; }
