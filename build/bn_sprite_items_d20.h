#ifndef BN_SPRITE_ITEMS_D20_H
#define BN_SPRITE_ITEMS_D20_H

#include "bn_sprite_item.h"

//{{BLOCK(d20_bn_gfx)

//======================================================================
//
//	d20_bn_gfx, 32x672@4, 
//	+ palette 16 entries, not compressed
//	+ 336 tiles not compressed
//	Total size: 32 + 10752 = 10784
//
//	Time-stamp: 2023-09-30, 18:20:34
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_D20_BN_GFX_H
#define GRIT_D20_BN_GFX_H

#define d20_bn_gfxTilesLen 10752
extern const bn::tile d20_bn_gfxTiles[336];

#define d20_bn_gfxPalLen 32
extern const bn::color d20_bn_gfxPal[16];

#endif // GRIT_D20_BN_GFX_H

//}}BLOCK(d20_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item d20(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(d20_bn_gfxTiles, 336), bpp_mode::BPP_4, compression_type::NONE, 21), 
            sprite_palette_item(span<const color>(d20_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

