#ifndef ANIMATOR_CPP
#define ANIMATOR_CPP

#include "Animator.h"
#include "GameObject.h"

void Animator::AddAnimation(Animation* anim) {
	anim->SetObject(mParent);
	if (mAnimations.empty()) anim->Init();
	mAnimations.push_back(anim);
}

void Animator::SkipAnimation() {
	delete mAnimations.front();
	mAnimations.pop_front();
	mAnimations.front()->Init();
}

void Animator::ClearAllAnimations() {
	while (!mAnimations.empty()) {
		delete mAnimations.front();
		mAnimations.pop_front();
	}
}

void Animator::PauseAnimation() { mCurrentlyAnimating = false; }

void Animator::StartAnimation() { mCurrentlyAnimating = true; }

void Animator::Update() {
	if (!mAnimations.empty() && mCurrentlyAnimating) {
		mAnimations.front()->BaseUpdate();
		if (mAnimations.front()->Update()) {
			delete mAnimations.front();
			mAnimations.pop_front();
			if (!mAnimations.empty()) mAnimations.front()->Init();
		}
	}
}

void Animator::Draw() {
	
}

const bn::list<Animation*, 32>& Animator::GetAnimations() {
    return mAnimations;
}

#endif
