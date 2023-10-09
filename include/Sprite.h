#ifndef SPRITE_H
#define SPRITE_H

#include "bn_sprite_ptr.h"
#include "bn_color.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_tiles_item.h"

#include "Component.h"
#include "Transform.h"

class Sprite : public Component {
public:
	Sprite(GameObject* parent, bn::sprite_ptr spriteptr) : Component(parent, ComponentType::Sprite), mSpritePtr(spriteptr), mTilesPtr(spriteptr.tiles()) {};
	
	void Update() override;
	void Draw() override;
	
	bn::sprite_ptr GetPtr();
	
	void SetPalette(const bn::sprite_palette_item& palette_item);
	void SetPalette(const bn::sprite_palette_ptr& palette);
    
    void SetTiles(const bn::sprite_tiles_item& tileitem, int index = 0);
    void SetTiles(const bn::sprite_tiles_ptr& tileptr);
    
    void SetZOrder(int i);
    int GetZOrder();
    
    void SetTransform(Transform transform);
    bn::optional<Transform> GetTransform();
	
private:
	bn::sprite_ptr mSpritePtr;
    bn::sprite_tiles_ptr mTilesPtr;
    bn::optional<Transform> mTransform;
};

#endif
