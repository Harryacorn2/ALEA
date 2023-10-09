#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "global.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_unordered_set.h"
#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_sprite_palette_item.h"

#include "Transform.h"

class Component;
class Animator;
class Sprite;

class GameObject {
public:
	GameObject();
	GameObject(bn::fixed scale, bn::fixed rotation, Vector2 position);
	GameObject(bn::fixed scale, bn::fixed rotation, bn::fixed_point position);
	GameObject(bn::fixed scale, bn::fixed rotation, Vector2 position, bn::sprite_ptr sprite);
	
	virtual ~GameObject();
	
	void BaseUpdate();
	virtual void Update();
	
	void BaseDraw();
	virtual void Draw();
	
	// Manage Children
	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	void RemoveAllChildren();
	void DetatchChild(GameObject* child);
	void SetParent(GameObject* parent);
	void RemoveParent();
	GameObject* GetParent();
	const bn::unordered_set<GameObject*, MAX_SPRITES>& GetChildren();
	
	// Manage Components
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	void RemoveAllComponents();
	
	// Manage Animation
	Animator* AddAnimator();
	Animator* GetAnimator(int index = 0);
	
	// Manage Transform
	void LockRotation();
	void UnlockRotation();
	bool IsRotationLocked();
	
	Vector2 GetPosition();
	bn::fixed GetRotation();
	bn::fixed GetScale();
	Transform& GetTransform();
	
	void SetPosition(const Vector2& position);
	void SetPosition(const bn::fixed_point& position); //Legacy
	void SetPosition(const bn::fixed& x, const bn::fixed& y);
	void SetRotation(const bn::fixed& rotation);
	void SetScale(const bn::fixed scale);
	
	Sprite* GetSprite(int index = 0);
	
	static int GetCount();
	static void UpdateAll();
	static void DrawAll();
	static bn::unordered_set<GameObject*, MAX_SPRITES> mAll;
	
protected:
	bn::vector<Component*, 64> mComponents;
	
	Transform mTransform;
	
	GameObject* mParent = NULL;
	bn::unordered_set<GameObject*, MAX_SPRITES> mChildren;
	
	bool mRotationIsLocked = false;
	
private:
	static int mCount;
};

#endif
