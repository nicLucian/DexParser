#ifndef DEX_INFO_H_INCLUDE
#define DEX_INFO_H_INCLUDE

#include <iostream>
#include <vector>
#include "type.h"

using namespace std;

class DexHeader {
   private:
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

   public:
    DexHeader(vector<uchar>& magic, uint checksum,
            vector<uchar>& signature, uint file_size,
            uint header_size, uint endian_tag,
            uint link_size, uint link_off, uint map_off,
            uint string_ids_size, uint string_ids_off,
            uint type_ids_size, uint type_ids_off,
            uint proto_ids_size, uint proto_ids_off,
            uint field_ids_size, uint field_ids_off,
            uint method_ids_size, uint method_ids_off,
            uint class_defs_size, uint class_defs_off,
            uint data_size, uint data_off);

    vector<uchar> get_magic();
    uint get_checksum();
    vector<uchar> get_signature();
    uint get_file_size();
    uint get_header_size();
    uint get_endian_tag();
    uint get_link_size();
    uint get_link_off();
    uint get_map_off();
    uint get_string_ids_size();
    uint get_string_ids_off();
    uint get_type_ids_size();
    uint get_type_ids_off();
    uint get_proto_ids_size();
    uint get_proto_ids_off();
    uint get_field_ids_size();
    uint get_field_ids_off();
    uint get_method_ids_size();
    uint get_method_ids_off();
    uint get_class_defs_size();
    uint get_class_defs_off();
    uint get_data_size();
    uint get_data_off();

    friend ostream &operator<<(ostream &output, const DexHeader &dex_header) {
        for (uchar ch : dex_header.magic) {
            output << ch;
        }
        output << " ";
        output << dex_header.checksum;
        for (uchar ch : dex_header.signature) {
            output << ch;
        }
        output << " ";
        output << dex_header.file_size << " " << dex_header.header_size << " "
               << dex_header.endian_tag << " " << dex_header.link_size << " "
               << dex_header.link_off << " " << dex_header.map_off << " "
               << dex_header.string_ids_size << " " << dex_header.string_ids_off
               << " " << dex_header.type_ids_size << " " << dex_header.type_ids_off
               << " " << dex_header.proto_ids_size << " "
               << dex_header.proto_ids_off << " " << dex_header.field_ids_size
               << " " << dex_header.field_ids_off << " "
               << dex_header.method_ids_size << " " << dex_header.method_ids_off
               << " " << dex_header.class_defs_size << " "
               << dex_header.class_defs_off << " " << dex_header.data_size << " "
               << dex_header.data_off;
        return output;
    }
};

#endif