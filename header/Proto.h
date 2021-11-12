#ifndef PROTO_ID_H_INCLUDE
#define PROTO_ID_H_INCLUDE

#include <iostream>
#include <vector>

using namespace std;

struct Proto {
    uint shorty_idx;             // index into the string_ids;
    uint return_type_id;         // index into the type_ids;
    vector<int> params_type_id;  // index into the type_ids
};

#endif