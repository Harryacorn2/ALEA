#ifndef BN_SPRITE_ITEMS_EMPTY_H
#define BN_SPRITE_ITEMS_EMPTY_H

#include "bn_sprite_item.h"

//{{BLOCK(empty_bn_gfx)

//======================================================================
//
//	empty_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles not compressed
//	Total size: 32 + 128 = 160
//
//	Time-stamp: 2023-11-15, 13:07:09
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_EMPTY_BN_GFX_H
#define GRIT_EMPTY_BN_GFX_H

#define empty_bn_gfxTilesLen 128
extern const bn::tile empty_bn_gfxTiles[4];

#define empty_bn_gfxPalLen 32
extern const bn::color empty_bn_gfxPal[16];

#endif // GRIT_EMPTY_BN_GFX_H

//}}BLOCK(empty_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item empty(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(empty_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(empty_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

