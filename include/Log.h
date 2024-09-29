#ifndef LOG_H
#define LOG_H

#include "bn_string.h"

class Log {
public:
    static void Raw(const char* cstring[128]);
    static void Raw(bn::string<128> string);
    static void Format(const char* cstring, ...);
    
    static bn::string<128> ToFormat();
};

#endif
