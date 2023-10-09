#ifndef BN_SPRITE_ITEMS_DIGITS_H
#define BN_SPRITE_ITEMS_DIGITS_H

#include "bn_sprite_item.h"

//{{BLOCK(digits_bn_gfx)

//======================================================================
//
//	digits_bn_gfx, 16x160@4, 
//	+ palette 16 entries, not compressed
//	+ 40 tiles not compressed
//	Total size: 32 + 1280 = 1312
//
//	Time-stamp: 2023-09-30, 18:20:34
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_DIGITS_BN_GFX_H
#define GRIT_DIGITS_BN_GFX_H

#define digits_bn_gfxTilesLen 1280
extern const bn::tile digits_bn_gfxTiles[40];

#define digits_bn_gfxPalLen 32
extern const bn::color digits_bn_gfxPal[16];

#endif // GRIT_DIGITS_BN_GFX_H

//}}BLOCK(digits_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item digits(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(digits_bn_gfxTiles, 40), bpp_mode::BPP_4, compression_type::NONE, 10), 
            sprite_palette_item(span<const color>(digits_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

