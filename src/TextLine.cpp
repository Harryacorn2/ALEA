#ifndef TEXTLINE_CPP
#define TEXTLINE_CPP

#include "TextLine.h"
#include "Log.h"

TextLine::TextLine(bn::sprite_font font) : mGenerator(font) {
	
}

TextLine::TextLine(bn::fixed scale, bn::fixed rotation, Vector2 position) : GameObject(scale, rotation, position), mGenerator(common::variable_8x8_sprite_font) {
	
}

TextLine::TextLine(bn::string<64> text, bn::sprite_font font) : mGenerator(font) {
	SetText(text);
}

TextLine::~TextLine() {}

void TextLine::SetText(bn::string<64> text) {
    int z = GetZOrder();
	mString = text;
	mSpriteVector.clear();
    mSpritePtrVector.clear();
    RemoveAllComponents();
	mGenerator.generate(0, 0, mString, mSpritePtrVector);
    
    for (int i = 0; i < mSpritePtrVector.size(); i++) {
        Sprite* sprite = new Sprite(this, mSpritePtrVector[i]);
        mSpriteVector.push_back(sprite);
        sprite->SetTransform(Transform(Vector2(mSpritePtrVector[i].position())));
        mSpritePtrVector[i].set_position(0, 0);
        AddComponent(sprite);
    }
    
    SetZOrder(z);
}

void TextLine::AlignLeft() {
	mGenerator.set_left_alignment();
    SetText(mString);
}

void TextLine::AlignCenter() {
	mGenerator.set_center_alignment();
    SetText(mString);
}

void TextLine::AlignRight() {
	mGenerator.set_right_alignment();
	mGenerator.generate(0, 0, mString, mSpritePtrVector);
    SetText(mString);
}

void TextLine::SetOneSpritePerChar(bool choice) {
	mGenerator.set_one_sprite_per_character(choice);
    SetText(mString);
}

void TextLine::SetZOrder(int i) {
    for (int j = 0; j < mSpriteVector.size(); j++) {
        mSpriteVector[j]->SetZOrder(i);
    }
}

int TextLine::GetZOrder() {
    if (mSpriteVector.size() != 0) {
        return mSpriteVector[0]->GetZOrder();
    }
    
    return 0;
}

#endif
