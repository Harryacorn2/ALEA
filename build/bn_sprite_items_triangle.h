#ifndef BN_SPRITE_ITEMS_TRIANGLE_H
#define BN_SPRITE_ITEMS_TRIANGLE_H

#include "bn_sprite_item.h"

//{{BLOCK(triangle_bn_gfx)

//======================================================================
//
//	triangle_bn_gfx, 32x32@4, 
//	+ palette 16 entries, not compressed
//	+ 16 tiles not compressed
//	Total size: 32 + 512 = 544
//
//	Time-stamp: 2023-11-15, 13:07:09
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TRIANGLE_BN_GFX_H
#define GRIT_TRIANGLE_BN_GFX_H

#define triangle_bn_gfxTilesLen 512
extern const bn::tile triangle_bn_gfxTiles[16];

#define triangle_bn_gfxPalLen 32
extern const bn::color triangle_bn_gfxPal[16];

#endif // GRIT_TRIANGLE_BN_GFX_H

//}}BLOCK(triangle_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item triangle(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(triangle_bn_gfxTiles, 16), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(triangle_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

