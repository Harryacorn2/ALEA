#ifndef ANIMATION_H
#define ANIMATION_H

#include "global.h"
#include "bn_vector.h"
#include "engineMath.h"

class GameObject;

class Animation {
public:
	Animation(uint delay = 0);
	virtual ~Animation();
	
	void SetObject(GameObject* obj);
	void BaseUpdate();
	
	virtual void Init();
	virtual bool Update();
	
protected:
	uint mCurrentFrame = 0;
	uint mDelay = 0;
	GameObject* mObject = NULL;
};

class Lerp : public Animation {
public:
	Lerp(Vector2 dest, uint time, uint delay = 0);
	
	void Init() override;
	bool Update() override;
	
private:
	Vector2 mEnd;
	Vector2 mStart;
	uint mTime;
};

// Starts slow
class EaseIn : public Animation {
public:
	EaseIn(Vector2 dest, uint time, uint delay = 0);
	
	void Init() override;
	bool Update() override;
	
private:
	Vector2 mEnd;
	Vector2 mStart;
	uint mTime;
};

class EaseOut : public Animation {
public:
	EaseOut(Vector2 dest, uint time, uint delay = 0);
	
	void Init() override;
	bool Update() override;
	
private:
	Vector2 mEnd;
	Vector2 mStart;
	uint mTime;
};

class RemoveFromParent : public Animation {
public:
    RemoveFromParent(uint delay = 0);
    void Init() override;
};

class HoriShake : public Animation {
public:
	HoriShake(uint size, uint time, uint delay = 0);
	
	void Init() override;
	bool Update() override;
	
private:
	uint mSize;
	uint mTime;
};

class EaseOutAndScale : public Animation {
public:
    EaseOutAndScale(Vector2 dest, bn::fixed scale, uint time, uint delay = 0);
    
    void Init() override;
    bool Update() override;
    
    uint GetTime();
    void SetTime(uint time);
    
private:
    Vector2 mEndPosition;
    Vector2 mStartPosition;
    bn::fixed mEndScale;
    bn::fixed mStartScale;
    uint mTime;
};

#endif
