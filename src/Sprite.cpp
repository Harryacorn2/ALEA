#ifndef SPRITE_CPP
#define SPRITE_CPP

#include "Sprite.h"
#include "GameObject.h"
#include "Profiler.h"

void Sprite::Update() {
	
}

void Sprite::Draw() {
    PROFILE_SCOPE(Draw_Sprite);
    
    auto parent = mParent->GetParent();
    auto matrix = mParent->GetTransform().GetMatrix();
    Matrix3 ownMatrix = Matrix3::Identity;
    
    if (mTransform.has_value()) {
        ownMatrix = mTransform.value().GetMatrix();
    }
    
    {
        PROFILE_SCOPE(Matrix_Mult);
        matrix = ownMatrix * matrix;
    }
    
    while (parent != NULL) {
        auto parentMatrix = parent->GetTransform().GetMatrix();
        {
            PROFILE_SCOPE(Matrix_Mult);
            matrix *= parentMatrix;
        }
        parent = parent->GetParent();
    }
    
    PROFILE_SCOPE(Apply_To_Sprite);
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
