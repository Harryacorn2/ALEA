#include <cstdarg>

#include "Log.h"

#include "bn_log.h"
#include "bn_fixed.h"
#include "engineMath.h"


void Log::Raw(const char* cstring[64]) {
    bn::log(bn::string<64>(*cstring));
}

void Log::Raw(bn::string<64> string) {
    bn::log(string);
}

void Log::Format(const char* cstring, ...) {
    bn::string<64> retVal;

    va_list args;
    va_start(args, cstring);
    
    while (*cstring != '\0') {
        if (*cstring == '%') {
            Vector2 vec(0, 0);
            char marker = *(cstring + 1);
            switch (marker) {
                case 'd':
                    retVal.append(bn::to_string<64>(va_arg(args, int)));
                    break;
                    
                case 'i':
                    retVal.append(bn::to_string<64>(va_arg(args, int)));
                    break;
                
                case 's':
                    retVal.append(bn::to_string<64>(va_arg(args, char*)));
                    break;
                    
                case 'f':
                    retVal.append(bn::to_string<64>(va_arg(args, bn::fixed)));
                    break;
                    
                case 'v':
                    vec = va_arg(args, Vector2);
                    retVal.append(bn::to_string<64>("("));
                    retVal.append(bn::to_string<64>(vec.x));
                    retVal.append(bn::to_string<64>(", "));
                    retVal.append(bn::to_string<64>(vec.y));
                    retVal.append(bn::to_string<64>(")"));
                    break;
                    
                default:
                    retVal.push_back('%');
                    cstring--;
                    break;
            }
            
            cstring++;
            
        } else {
            retVal.push_back(*cstring);
        }
        
        cstring++;
    }
    
    va_end(args);
    
    Log::Raw(retVal);
}
