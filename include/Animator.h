#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "global.h"
#include "bn_list.h"
#include "Animation.h"
#include "Component.h"

class GameObject;

class Animator : public Component {
public:
	Animator(GameObject* parent) : Component(parent, ComponentType::Animator) {}
	
	~Animator() {
		ClearAllAnimations();
	}
	
	void AddAnimation(Animation* anim);
	void SkipAnimation();
	void ClearAllAnimations();
	void PauseAnimation();
	void StartAnimation();
		
	void Update() override;
	void Draw() override;
    
    const bn::list<Animation*, 32>& GetAnimations();
	
private:
	bn::list<Animation*, 32> mAnimations;
	bool mCurrentlyAnimating = true;
};

#endif
