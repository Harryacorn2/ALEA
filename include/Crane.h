#ifndef CRANE_H
#define CRANE_H

#include "GameObject.h"

#include "bn_vector.h"
#include "bn_list.h"
#include "Animation.h"

class Die;

struct PillarInformation {
    Vector2 pos;
    bn::fixed scale;
    int z;
    
    bn::fixed angle;
};

class Pillar : public GameObject {
public:
    Pillar(int i, int inc = 6);
    
    void Increment();
    bool Decrement();
    
    Die* MakeDieOfType();
    void AddDie();
    void RemoveDie();
    
    void SetZOrder(int z);
    
    void ApplyPillarInformation(PillarInformation p);
    
    void Incorporate(PillarInformation p);
    void Seperate(PillarInformation p);
    
    int GetStoredValue();
    int GetDieType();
    
private:
    const int mHeightOnAddDie = 8;
    int mDieType;
    int mStoredValue = 0;
    bn::vector<Die*, 4> mDice;
    
    bn::fixed currentAngle = 0;
};

class Crane : public GameObject {
public:
    Crane();
    ~Crane();
    
    void RotateRight();
    void RotateLeft();
    
    void ApplyPillarData();
    void Incorperate();
    bn::vector<uint, MAX_ROLLABLE_DICE> Seperate();
    
    void IncrementSelected();
    void DecrementSelected();
    
    void Skip();
    
    constexpr static bn::fixed mFrontHeight = 24;
    constexpr static bn::fixed mCloseHeight = 8;
    constexpr static bn::fixed mCloseWidth = 31;
    constexpr static bn::fixed mFarHeight = -16;
    constexpr static bn::fixed mFarWidth = 24;
    constexpr static bn::fixed mBackHeight = -23;

private:
    uint mSelectedPillar = 0;
    uint mTotalDiceCount = 0;
    Pillar* mPillars[6];
    bn::list<PillarInformation, 7> mPillarData;
    
    static bool mFirst;
};

class EaseOutAndScaleOnCrane : public Animation {
public:
    EaseOutAndScaleOnCrane(bn::fixed destPos, bn::fixed destScale, uint time, Vector2 mod = Vector2(0, 0), uint delay = 0);
    
    void Init() override;
    bool Update() override;
    
    uint GetTime();
    void SetTime(uint time);
    
private:
    static Ellipse CraneEllipse;
    constexpr static bn::fixed maxScale = 1;
    constexpr static bn::fixed minScale = 0.5;
    
    bn::fixed mEndPosition;
    bn::fixed mStartPosition;
    bn::fixed mEndScale;
    bn::fixed mStartScale;
    Vector2 mModifier;
    uint mTime;
};

#endif
