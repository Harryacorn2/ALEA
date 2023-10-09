#ifndef LOG_H
#define LOG_H

#include "bn_string.h"

class Log {
public:
    static void Raw(const char* cstring[64]);
    static void Raw(bn::string<64> string);
    static void Format(const char* cstring, ...);
    
    static bn::string<64> ToFormat();
};

#endif
