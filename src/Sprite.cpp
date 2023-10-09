#ifndef SPRITE_CPP
#define SPRITE_CPP

#include "Sprite.h"
#include "GameObject.h"

void Sprite::Update() {
	
}

void Sprite::Draw() {
	auto parent = mParent->GetParent();
	auto matrix = mParent->GetTransform().GetMatrix();
    
    if (mTransform.has_value()) {
        matrix = mTransform.value().GetMatrix() * matrix;
    }
	
	while (parent != NULL) {
		matrix *= parent->GetTransform().GetMatrix();
		parent = parent->GetParent();
	}
	
	matrix.ApplyToSprite(mSpritePtr, mParent->IsRotationLocked());
}

bn::sprite_ptr Sprite::GetPtr() {
	return mSpritePtr;
}

void Sprite::SetPalette(const bn::sprite_palette_item& palette_item) {
		mSpritePtr.set_palette(palette_item);
}

void Sprite::SetPalette(const bn::sprite_palette_ptr& palette) {
		mSpritePtr.set_palette(palette);
}

void Sprite::SetTiles(const bn::sprite_tiles_item& tileitem, int index) {
    mSpritePtr.set_tiles(tileitem, index);
    mTilesPtr = mSpritePtr.tiles();
}

void Sprite::SetTiles(const bn::sprite_tiles_ptr& tileptr) {
    mSpritePtr.set_tiles(tileptr);
    mTilesPtr = tileptr;
}

void Sprite::SetZOrder(int i) {
    mSpritePtr.set_z_order(i);
}

int Sprite::GetZOrder() {
    return mSpritePtr.z_order();
}

void Sprite::SetTransform(Transform transform) {
    mTransform = bn::make_optional<Transform>(transform);
}

bn::optional<Transform> Sprite::GetTransform() {
    return mTransform;
}

#endif
