#ifndef BN_SPRITE_ITEMS_D12_H
#define BN_SPRITE_ITEMS_D12_H

#include "bn_sprite_item.h"

//{{BLOCK(d12_bn_gfx)

//======================================================================
//
//	d12_bn_gfx, 32x416@4, 
//	+ palette 16 entries, not compressed
//	+ 208 tiles not compressed
//	Total size: 32 + 6656 = 6688
//
//	Time-stamp: 2023-09-30, 18:20:34
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_D12_BN_GFX_H
#define GRIT_D12_BN_GFX_H

#define d12_bn_gfxTilesLen 6656
extern const bn::tile d12_bn_gfxTiles[208];

#define d12_bn_gfxPalLen 32
extern const bn::color d12_bn_gfxPal[16];

#endif // GRIT_D12_BN_GFX_H

//}}BLOCK(d12_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item d12(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(d12_bn_gfxTiles, 208), bpp_mode::BPP_4, compression_type::NONE, 13), 
            sprite_palette_item(span<const color>(d12_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

