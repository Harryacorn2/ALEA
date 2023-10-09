#ifndef BN_SPRITE_ITEMS_D8_H
#define BN_SPRITE_ITEMS_D8_H

#include "bn_sprite_item.h"

//{{BLOCK(d8_bn_gfx)

//======================================================================
//
//	d8_bn_gfx, 32x288@4, 
//	+ palette 16 entries, not compressed
//	+ 144 tiles not compressed
//	Total size: 32 + 4608 = 4640
//
//	Time-stamp: 2023-09-30, 18:20:34
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_D8_BN_GFX_H
#define GRIT_D8_BN_GFX_H

#define d8_bn_gfxTilesLen 4608
extern const bn::tile d8_bn_gfxTiles[144];

#define d8_bn_gfxPalLen 32
extern const bn::color d8_bn_gfxPal[16];

#endif // GRIT_D8_BN_GFX_H

//}}BLOCK(d8_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item d8(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(d8_bn_gfxTiles, 144), bpp_mode::BPP_4, compression_type::NONE, 9), 
            sprite_palette_item(span<const color>(d8_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

