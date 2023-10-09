#ifndef GAMEOBJECT_CPP
#define GAMEOBJECT_CPP

#include "GameObject.h"

#include "Component.h"
#include "Sprite.h"
#include "Animator.h"
#include "bn_format.h"
#include "Random.h"

int GameObject::mCount = 0;
bn::unordered_set<GameObject*, MAX_SPRITES> GameObject::mAll;

GameObject::GameObject() {
	mAll.insert(this);
	mCount++;
}

GameObject::GameObject(bn::fixed scale, bn::fixed rotation, bn::fixed_point position) {
	mAll.insert(this);
	mCount++;
	
	mTransform.SetScale(scale);
	mTransform.SetRotation(rotation);
	mTransform.SetTranslation(Vector2(position.x(), position.y()));
}

GameObject::GameObject(bn::fixed scale, bn::fixed rotation, Vector2 position) {
	mAll.insert(this);
	mCount++;
	
	mTransform.SetScale(scale);
	mTransform.SetRotation(rotation);
	mTransform.SetTranslation(position);
}

GameObject::GameObject(bn::fixed scale, bn::fixed rotation, Vector2 position, bn::sprite_ptr sprite) {
	mAll.insert(this);
	mCount++;
	
	mTransform.SetScale(scale);
	mTransform.SetRotation(rotation);
	mTransform.SetTranslation(position);
	
	mComponents.push_back(new Sprite(this, sprite));
}

GameObject::~GameObject() {
    
	if (mParent != NULL) {
		mParent->DetatchChild(this);
	}
    
    bn::vector<GameObject*, MAX_SPRITES> childObjectsToDelete;
    
    for (auto child = mChildren.cbegin(); child != mChildren.cend(); ++child) {
        childObjectsToDelete.push_back(*child);
	}
    
    for (int i = 0; i < childObjectsToDelete.size(); i++) {
        delete childObjectsToDelete[i];
    }
    
	mChildren.clear();
	
	for (int i = 0; i < mComponents.size(); i++) {
		delete mComponents[i];
	}
	
	mComponents.clear();
	
	mAll.erase(this);
	mCount--;
}

void GameObject::BaseUpdate() {
//	mAnimator.Update();
	
	for (int i = 0; i < mComponents.size(); i++) {
		mComponents[i]->Update();
	}
}

void GameObject::Update() {
	
}

void GameObject::BaseDraw() {
	for (int i = 0; i < mComponents.size(); i++) {
		mComponents[i]->Draw();
	}
}

void GameObject::Draw() {
    
}

void GameObject::LockRotation() {
	mRotationIsLocked = true;
}

void GameObject::UnlockRotation() {
	mRotationIsLocked = false;
}

bool GameObject::IsRotationLocked() {
	return mRotationIsLocked;
}

void GameObject::AddChild(GameObject* child) {
	mChildren.insert(child);
	child->mParent = this;
}

void GameObject::RemoveChild(GameObject* child) {
	mChildren.erase(child);
	delete child;
}

void GameObject::DetatchChild(GameObject* child) {
	mChildren.erase(child);
	child->mParent = NULL;
}

void GameObject::RemoveAllChildren() {
	for (auto child : mChildren) {
		delete child;
	}
}

void GameObject::SetParent(GameObject* parent) {
	mParent = parent;
	parent->mChildren.insert(this);
}

void GameObject::RemoveParent() {
	mParent->mChildren.erase(this);
	mParent = NULL;
}

GameObject* GameObject::GetParent() {
	return mParent;
}

const bn::unordered_set<GameObject*, MAX_SPRITES>& GameObject::GetChildren() {
	return mChildren;
}

// Components

void GameObject::AddComponent(Component* component) {
	mComponents.push_back(component);
}

void GameObject::RemoveComponent(Component* component) {
	for (auto it = mComponents.begin(); it != mComponents.end(); it++) {
		if (*it == component) {
			mComponents.erase(it);
			delete component;
			break;
		}
	}
}

void GameObject::RemoveAllComponents() {
    for (int i = 0; i < mComponents.size(); i++) {
        delete mComponents[i];
    }
    
    mComponents.clear();
}

// Animation

Animator* GameObject::AddAnimator() {
	Animator* anim = new Animator(this);
	AddComponent(anim);
	return anim;
}

Animator* GameObject::GetAnimator(int index) {
	for (int i = 0; i < mComponents.size(); i++) {
		if (mComponents[i]->GetType() == ComponentType::Animator) {
			if (index == 0) {
				return reinterpret_cast<Animator*>(mComponents[i]);
			} else {
				index--;
			}
		}
	}
	
	return nullptr;
}

// Sprite

Sprite* GameObject::GetSprite(int index) {
	for (int i = 0; i < mComponents.size(); i++) {
		if (mComponents[i]->GetType() == ComponentType::Sprite) {
			if (index == 0) {
				return reinterpret_cast<Sprite*>(mComponents[i]);
			} else {
				index--;
			}
		}
	}
	
	return nullptr;
}

Vector2 GameObject::GetPosition() { return mTransform.GetTranslation(); }
bn::fixed GameObject::GetRotation() { return mTransform.GetRotation(); }
bn::fixed GameObject::GetScale() { return mTransform.GetScale(); }
Transform& GameObject::GetTransform() { return mTransform; }

void GameObject::SetPosition(const Vector2& position) { mTransform.SetTranslation(position); }
void GameObject::SetPosition(const bn::fixed_point& position) { mTransform.SetTranslation(Vector2(position.x(), position.y())); }
void GameObject::SetPosition(const bn::fixed& x, const bn::fixed& y) { mTransform.SetTranslation(Vector2(x, y)); }
void GameObject::SetRotation(const bn::fixed& rotation) { mTransform.SetRotation(rotation); }
void GameObject::SetScale(const bn::fixed scale) { mTransform.SetScale(scale); }

// Palette
//void GameObject::SetPalette(const bn::sprite_palette_item& palette_item) {
//	if (mSprite.has_value()) {
//		mSprite.value().set_palette(palette_item);
//	}
//}
//
//void GameObject::SetPalette(const bn::sprite_palette_ptr& palette) {
//	if (mSprite.has_value()) {
//		mSprite.value().set_palette(palette);
//	}
//}


//bn::optional<bn::sprite_ptr> GameObject::GetSpritePtr() { return mSprite; }

int GameObject::GetCount() { return mCount; }

void GameObject::UpdateAll() {
	for (auto obj : mAll) {
		obj->Update();
		obj->BaseUpdate();
	}
}

void GameObject::DrawAll() {
	for (auto obj : mAll) {
		obj->Draw();
		obj->BaseDraw();
	}
}

#endif
