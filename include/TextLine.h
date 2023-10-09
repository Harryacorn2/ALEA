#ifndef TEXTLINE_H
#define TEXTLINE_H

#include "GameObject.h"
#include "bn_vector.h"
#include "bn_string.h"
#include "bn_sprite_font.h"
#include "bn_sprite_text_generator.h"
#include "common/common_variable_8x8_sprite_font.h"
#include "yobani_sprite_font.h"
#include "bn_sprite_palette_item.h"

#include "Sprite.h"

// WARNING: Will not scale or rotate
class TextLine : public GameObject {
public:
	TextLine(bn::sprite_font font = yobani_variable_8x8_sprite_font);
	TextLine(bn::fixed scale, bn::fixed rotation, Vector2 position);
	TextLine(bn::string<64> text, bn::sprite_font font = yobani_variable_8x8_sprite_font);
	~TextLine();
	
	void SetText(bn::string<64> text);
	void AlignLeft();
	void AlignCenter();
	void AlignRight();
	void SetOneSpritePerChar(bool choice);
	
	void SetPaletteOfChar(uint index, const bn::sprite_palette_item& palette_item);
    
    void SetZOrder(int i);
    int GetZOrder();
	
//	void Draw() override;
	
private:
	bn::sprite_text_generator mGenerator;
	bn::string<64> mString;
    bn::vector<Sprite*, MAX_SPRITES> mSpriteVector;
	bn::vector<bn::sprite_ptr, MAX_SPRITES> mSpritePtrVector;
    
//	bn::vector<bn::fixed_point, MAX_SPRITES> mPositionVector;
};

#endif
