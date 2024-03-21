#ifndef BN_SPRITE_ITEMS_D6_OLD_H
#define BN_SPRITE_ITEMS_D6_OLD_H

#include "bn_sprite_item.h"

//{{BLOCK(d6_old_bn_gfx)

//======================================================================
//
//	d6_old_bn_gfx, 16x176@4, 
//	+ palette 16 entries, not compressed
//	+ 44 tiles not compressed
//	Total size: 32 + 1408 = 1440
//
//	Time-stamp: 2023-11-15, 13:07:09
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_D6_OLD_BN_GFX_H
#define GRIT_D6_OLD_BN_GFX_H

#define d6_old_bn_gfxTilesLen 1408
extern const bn::tile d6_old_bn_gfxTiles[44];

#define d6_old_bn_gfxPalLen 32
extern const bn::color d6_old_bn_gfxPal[16];

#endif // GRIT_D6_OLD_BN_GFX_H

//}}BLOCK(d6_old_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item d6_old(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(d6_old_bn_gfxTiles, 44), bpp_mode::BPP_4, compression_type::NONE, 11), 
            sprite_palette_item(span<const color>(d6_old_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

