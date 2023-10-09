#ifndef BN_SPRITE_ITEMS_DIGITS2_H
#define BN_SPRITE_ITEMS_DIGITS2_H

#include "bn_sprite_item.h"

//{{BLOCK(digits2_bn_gfx)

//======================================================================
//
//	digits2_bn_gfx, 16x176@4, 
//	+ palette 16 entries, not compressed
//	+ 44 tiles not compressed
//	Total size: 32 + 1408 = 1440
//
//	Time-stamp: 2023-09-30, 18:20:34
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_DIGITS2_BN_GFX_H
#define GRIT_DIGITS2_BN_GFX_H

#define digits2_bn_gfxTilesLen 1408
extern const bn::tile digits2_bn_gfxTiles[44];

#define digits2_bn_gfxPalLen 32
extern const bn::color digits2_bn_gfxPal[16];

#endif // GRIT_DIGITS2_BN_GFX_H

//}}BLOCK(digits2_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item digits2(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(digits2_bn_gfxTiles, 44), bpp_mode::BPP_4, compression_type::NONE, 11), 
            sprite_palette_item(span<const color>(digits2_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

