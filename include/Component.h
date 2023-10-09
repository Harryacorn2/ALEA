#ifndef COMPONENT_H
#define COMPONENT_H

#include "global.h"

class GameObject;

enum class ComponentType {
	None,
	Sprite,
	Animator
};

class Component {
public:
	Component(GameObject* parent, ComponentType type) : mParent(parent), mType(type) {}
	virtual ~Component() {}
	
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	ComponentType GetType() { return mType; }
	
protected:
	GameObject* mParent;
	ComponentType mType;
};

#endif