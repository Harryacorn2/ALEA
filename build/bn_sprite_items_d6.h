#ifndef BN_SPRITE_ITEMS_D6_H
#define BN_SPRITE_ITEMS_D6_H

#include "bn_sprite_item.h"

//{{BLOCK(d6_bn_gfx)

//======================================================================
//
//	d6_bn_gfx, 32x224@4, 
//	+ palette 16 entries, not compressed
//	+ 112 tiles not compressed
//	Total size: 32 + 3584 = 3616
//
//	Time-stamp: 2023-11-15, 13:07:09
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_D6_BN_GFX_H
#define GRIT_D6_BN_GFX_H

#define d6_bn_gfxTilesLen 3584
extern const bn::tile d6_bn_gfxTiles[112];

#define d6_bn_gfxPalLen 32
extern const bn::color d6_bn_gfxPal[16];

#endif // GRIT_D6_BN_GFX_H

//}}BLOCK(d6_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item d6(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(d6_bn_gfxTiles, 112), bpp_mode::BPP_4, compression_type::NONE, 7), 
            sprite_palette_item(span<const color>(d6_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

