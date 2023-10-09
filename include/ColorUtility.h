#ifndef COLOR_UTILITY_H
#define COLOR_UTILITY_H

#include "bn_span.h"
#include "bn_color.h"

//bn::color raw[16];
//raw[14] = bn::color(31, 0, 0);
//
//auto colors = bn::span(raw, 16);
//auto palette = bn::sprite_palette_item(colors, bn::bpp_mode::BPP_4);

struct Color {
public:
    Color();
    
//    static bn::sprite_palette_item CreatePalette(bn::vector<bn::color, 16> colors) {
//        
//    }
    
    constexpr static bn::color White = bn::color(31, 31, 31);
    constexpr static bn::color Black = bn::color(0, 0, 0);
    
    constexpr static bn::color Red = bn::color(31, 0, 0);
    constexpr static bn::color Green = bn::color(0, 31, 0);
    constexpr static bn::color Blue = bn::color(0, 0, 31);
    
    constexpr static bn::color LightRed = bn::color(31, 6, 0);
    
    constexpr static bn::color LightBlue = bn::color(0, 20, 31);
};

#endif
