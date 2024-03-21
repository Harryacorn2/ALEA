#ifndef BN_SPRITE_ITEMS_D10_H
#define BN_SPRITE_ITEMS_D10_H

#include "bn_sprite_item.h"

//{{BLOCK(d10_bn_gfx)

//======================================================================
//
//	d10_bn_gfx, 32x352@4, 
//	+ palette 16 entries, not compressed
//	+ 176 tiles not compressed
//	Total size: 32 + 5632 = 5664
//
//	Time-stamp: 2023-11-15, 13:07:09
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_D10_BN_GFX_H
#define GRIT_D10_BN_GFX_H

#define d10_bn_gfxTilesLen 5632
extern const bn::tile d10_bn_gfxTiles[176];

#define d10_bn_gfxPalLen 32
extern const bn::color d10_bn_gfxPal[16];

#endif // GRIT_D10_BN_GFX_H

//}}BLOCK(d10_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item d10(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(d10_bn_gfxTiles, 176), bpp_mode::BPP_4, compression_type::NONE, 11), 
            sprite_palette_item(span<const color>(d10_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

