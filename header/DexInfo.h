#ifndef DEX_INFO_H_INCLUDE
#define DEX_INFO_H_INCLUDE

#include <iostream>
#include <vector>

using namespace std;

class DexInfo {
   private:
    vector<unsigned char> magic;
    unsigned int checksum;
    vector<unsigned char> signature;
    unsigned int file_size;
    unsigned int header_size;
    unsigned int endian_tag;
    unsigned int link_size;
    unsigned int link_off;
    unsigned int map_off;
    unsigned int string_ids_size;
    unsigned int string_ids_off;
    unsigned int type_ids_size;
    unsigned int type_ids_off;
    unsigned int proto_ids_size;
    unsigned int proto_ids_off;
    unsigned int field_ids_size;
    unsigned int field_ids_off;
    unsigned int method_ids_size;
    unsigned int method_ids_off;
    unsigned int class_defs_size;
    unsigned int class_defs_off;
    unsigned int data_size;
    unsigned int data_off;

   public:
    DexInfo(vector<unsigned char>& magic, unsigned int checksum,
            vector<unsigned char>& signature, unsigned int file_size,
            unsigned int header_size, unsigned int endian_tag,
            unsigned int link_size, unsigned int link_off, unsigned int map_off,
            unsigned int string_ids_size, unsigned int string_ids_off,
            unsigned int type_ids_size, unsigned int type_ids_off,
            unsigned int proto_ids_size, unsigned int proto_ids_off,
            unsigned int field_ids_size, unsigned int field_ids_off,
            unsigned int method_ids_size, unsigned int method_ids_off,
            unsigned int class_defs_size, unsigned int class_defs_off,
            unsigned int data_size, unsigned int data_off);

    vector<unsigned char> get_magic();
    unsigned int get_checksum();
    vector<unsigned char> get_signature();
    unsigned int get_file_size();
    unsigned int get_header_size();
    unsigned int get_endian_tag();
    unsigned int get_link_size();
    unsigned int get_link_off();
    unsigned int get_map_off();
    unsigned int get_string_ids_size();
    unsigned int get_string_ids_off();
    unsigned int get_type_ids_size();
    unsigned int get_type_ids_off();
    unsigned int get_proto_ids_size();
    unsigned int get_proto_ids_off();
    unsigned int get_field_ids_size();
    unsigned int get_field_ids_off();
    unsigned int get_method_ids_size();
    unsigned int get_method_ids_off();
    unsigned int get_class_defs_size();
    unsigned int get_class_defs_off();
    unsigned int get_data_size();
    unsigned int get_data_off();

    friend ostream &operator<<(ostream &output, const DexInfo &dex_info) {
        for (unsigned char ch : dex_info.magic) {
            output << ch;
        }
        output << " ";
        output << dex_info.checksum;
        for (unsigned char ch : dex_info.signature) {
            output << ch;
        }
        output << " ";
        output << dex_info.file_size << " " << dex_info.header_size << " "
               << dex_info.endian_tag << " " << dex_info.link_size << " "
               << dex_info.link_off << " " << dex_info.map_off << " "
               << dex_info.string_ids_size << " " << dex_info.string_ids_off
               << " " << dex_info.type_ids_size << " " << dex_info.type_ids_off
               << " " << dex_info.proto_ids_size << " "
               << dex_info.proto_ids_off << " " << dex_info.field_ids_size
               << " " << dex_info.field_ids_off << " "
               << dex_info.method_ids_size << " " << dex_info.method_ids_off
               << " " << dex_info.class_defs_size << " "
               << dex_info.class_defs_off << " " << dex_info.data_size << " "
               << dex_info.data_off;
        return output;
    }
};

#endif