#ifndef ANIMATION_CPP
#define ANIMATION_CPP

#include "Animation.h"
#include "GameObject.h"

Animation::Animation(uint delay) : mDelay(delay) {}

Animation::~Animation() {}

void Animation::SetObject(GameObject* obj) {
	mObject = obj;
}

void Animation::BaseUpdate() {
	if (mDelay > 0) {
		mDelay--;
	} else {
		mCurrentFrame++;
	}
}

void Animation::Init() {}

bool Animation::Update() { return true; }

Lerp::Lerp(Vector2 dest, uint time, uint delay) : Animation(delay),
	mEnd(dest),
	mStart(Vector2(0, 0)),
	mTime(time) {}

void Lerp::Init() {
	mStart = mObject->GetPosition();
}

bool Lerp::Update() {
	if (mCurrentFrame >= mTime) {
		mObject->SetPosition(mEnd);
		return true;
	}
	
	mObject->SetPosition(mStart.Lerp(mEnd, bn::fixed(mCurrentFrame)/bn::fixed(mTime)));
	
	return false;
}

EaseIn::EaseIn(Vector2 dest, uint time, uint delay) : Animation(delay),
	mEnd(dest),
	mStart(Vector2(0, 0)),
	mTime(time) {}

void EaseIn::Init() {
	mStart = mObject->GetPosition();
}

bool EaseIn::Update() {
	if (mCurrentFrame >= mTime) {
		mObject->SetPosition(mEnd);
		return true;
	}
	
	bn::fixed s2 = bn::fixed(mCurrentFrame)/bn::fixed(mTime);
	s2 = s2 * s2;
	
	mObject->SetPosition(mStart.Lerp(mEnd, s2));
	
	return false;
}

EaseOut::EaseOut(Vector2 dest, uint time, uint delay) : Animation(delay),
mEnd(dest),
mStart(Vector2(0, 0)),
mTime(time) {}

void EaseOut::Init() {
	mStart = mObject->GetPosition();
}

bool EaseOut::Update() {
	if (mCurrentFrame >= mTime) {
		mObject->SetPosition(mEnd);
		return true;
	}
	
	bn::fixed s2 = bn::fixed(mCurrentFrame)/bn::fixed(mTime);
	s2 = bn::sqrt(s2);
	
	mObject->SetPosition(mStart.Lerp(mEnd, s2));
	
	return false;
}

RemoveFromParent::RemoveFromParent (uint delay) : Animation(delay) {
    
}

void RemoveFromParent::Init() {
    mObject->GetParent()->RemoveChild(mObject);
}

HoriShake::HoriShake(uint size, uint time, uint delay) : Animation(delay), mSize(size), mTime(time) {}

void HoriShake::Init() {
	mObject->SetPosition(mObject->GetPosition() - Vector2(1, 0));
}

bool HoriShake::Update() {
	if (mCurrentFrame >= mTime) {
		if (!(mCurrentFrame % 2)) {
			mObject->SetPosition(mObject->GetPosition() - Vector2(1, 0));
		} else {
			mObject->SetPosition(mObject->GetPosition() + Vector2(1, 0));
		}
		
		return true;
	}
	
	if (mCurrentFrame % 2) {
		mObject->SetPosition(mObject->GetPosition() + Vector2(mSize, 0));
		
	} else {
		mObject->SetPosition(mObject->GetPosition() - Vector2(mSize, 0));
	}
	
	return false;
}

EaseOutAndScale::EaseOutAndScale(Vector2 dest, bn::fixed scale, uint time, uint delay) : Animation(delay), mEndPosition(dest), mStartPosition(Vector2(0, 0)), mEndScale(scale), mStartScale(1), mTime(time) {}

void EaseOutAndScale::Init() {
    mStartPosition = mObject->GetPosition();
    mStartScale = mObject->GetScale();
}

bool EaseOutAndScale::Update() {
    if (mCurrentFrame >= mTime) {
        mObject->SetPosition(mEndPosition);
        mObject->SetScale(mEndScale);
        return true;
    }
    
    bn::fixed s2 = bn::fixed(mCurrentFrame)/bn::fixed(mTime);
    s2 = bn::sqrt(s2);
    
    mObject->SetPosition(mStartPosition.Lerp(mEndPosition, s2));
    mObject->SetScale(mStartScale + ((mEndScale - mStartScale) * s2));
    
    return false;
}

uint EaseOutAndScale::GetTime() {
    return mTime;
}

void EaseOutAndScale::SetTime(uint time) {
    mTime = time;
}

#endif
