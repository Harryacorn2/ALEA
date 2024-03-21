#ifndef BN_SPRITE_ITEMS_D4_OLD_H
#define BN_SPRITE_ITEMS_D4_OLD_H

#include "bn_sprite_item.h"

//{{BLOCK(d4_old_bn_gfx)

//======================================================================
//
//	d4_old_bn_gfx, 32x160@4, 
//	+ palette 16 entries, not compressed
//	+ 80 tiles not compressed
//	Total size: 32 + 2560 = 2592
//
//	Time-stamp: 2023-11-15, 13:07:09
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_D4_OLD_BN_GFX_H
#define GRIT_D4_OLD_BN_GFX_H

#define d4_old_bn_gfxTilesLen 2560
extern const bn::tile d4_old_bn_gfxTiles[80];

#define d4_old_bn_gfxPalLen 32
extern const bn::color d4_old_bn_gfxPal[16];

#endif // GRIT_D4_OLD_BN_GFX_H

//}}BLOCK(d4_old_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item d4_old(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(d4_old_bn_gfxTiles, 80), bpp_mode::BPP_4, compression_type::NONE, 5), 
            sprite_palette_item(span<const color>(d4_old_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

