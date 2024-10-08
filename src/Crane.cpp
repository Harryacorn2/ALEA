#ifndef CRANE_CPP
#define CRANE_CPP

#include "Crane.h"

#include "Die.h"
#include "Animator.h"
#include "Animation.h"
#include "Log.h"

// MARK: - Pillar

Pillar::Pillar(int i, int inc) {
    mDieType = i;
    AddAnimator();
    
    switch (i) {
        case 4:
            mDice.push_back(new D4(0, Vector2(0, 0), 4));
            this->AddChild(mDice[0]);
            
            this->SetPosition(Vector2(Crane::mCloseWidth*inc, Crane::mCloseHeight*inc));
            this->SetScale(0.78125);
            break;
            
        case 6:
            mDice.push_back(new D6(0, Vector2(0, 0), 6));
            this->AddChild(mDice[0]);
            
            this->SetPosition(Vector2(Crane::mFarWidth*inc, Crane::mFarHeight*inc));
            this->SetScale(0.59375);
            break;
            
        case 8:
            mDice.push_back(new D8(0, Vector2(0, 0), 8));
            this->AddChild(mDice[0]);
            
            this->SetPosition(Vector2(0, Crane::mBackHeight*inc));
            this->SetScale(0.52);
            break;
            
        case 10:
            mDice.push_back(new D10(0, Vector2(0, 0), 10));
            this->AddChild(mDice[0]);
            
            this->SetPosition(Vector2(-Crane::mFarWidth*inc, Crane::mFarHeight*inc));
            this->SetScale(0.59375);
            break;
            
        case 12:
            mDice.push_back(new D12(0, Vector2(0, 0), 12));
            this->AddChild(mDice[0]);
            
            this->SetPosition(Vector2(-Crane::mCloseWidth*inc, Crane::mCloseHeight*inc));
            this->SetScale(0.78125);
            break;
            
        case 20:
            mDice.push_back(new D20(0, Vector2(0, 0), 20));
            this->AddChild(mDice[0]);
            
            this->SetPosition(Vector2(0, Crane::mFrontHeight*inc));
            break;
            
        default:
            break;
    }
    
    mDice[0]->AddAnimator();
}

void Pillar::Increment() {
    mStoredValue++;
    
    if (mStoredValue % mDieType == 1 && mStoredValue != 1) {
        mDice.back()->SetDigit(mDieType);
        this->AddDie();
    }
    
    if (mStoredValue % mDieType != 0) {
        mDice.back()->SetDigit(mStoredValue % mDieType);
    } else {
        mDice.back()->SetDigit(mDieType);
    }
}

bool Pillar::Decrement() {
    if (mStoredValue == 0) return false;
    
    mStoredValue--;
    
    if (mStoredValue == 0) {
        mDice[0]->SetDigit(mDieType + 1);
        return true;
    }
    
    if (mStoredValue % mDieType != 0) {
        mDice.back()->SetDigit(mStoredValue % mDieType);
    } else {
        this->RemoveDie();
    }
    
    return true;
}

Die* Pillar::MakeDieOfType() {
    switch (mDieType) {
        case 4:
            return new D4(0, Vector2(0, 0), 4);
            break;
            
        case 6:
            return new D6(0, Vector2(0, 0), 6);
            break;
            
        case 8:
            return new D8(0, Vector2(0, 0), 8);
            break;
            
        case 10:
            return new D10(0, Vector2(0, 0), 10);
            break;
            
        case 12:
            return new D12(0, Vector2(0, 0), 12);
            break;
            
        case 20:
            return new D20(0, Vector2(0, 0), 20);
            break;
            
        default:
            return nullptr;
            break;
    }
}

void Pillar::AddDie() {
    Vector2 lastPos = mDice.back()->GetPosition();
    Vector2 nextPos = lastPos - Vector2(0, 18);
    
    for (int i = 0; i < mDice.size(); i++) {
        Animation* anim = new EaseOut(mDice[i]->GetPosition() + Vector2(0, 18), 10);
        mDice[i]->GetAnimator()->AddAnimation(anim);
    }
    
    Die* die = MakeDieOfType();
    die->AddAnimator();
    die->SetDigit(1);
    die->SetPosition(lastPos);
    
    Animation* anim = new EaseOut(nextPos, 10);
    die->GetAnimator()->AddAnimation(anim);
    
    this->AddChild(die);
    mDice.push_back(die);

    Crane* crane = reinterpret_cast<Crane*>(mParent);
    
    Animation* pillarAnim = new EaseOutAndScale(Vector2(0, crane->mFrontHeight - (mHeightOnAddDie * (mDice.size() - 1))), 1, 20);
    Animator* animator = this->GetAnimator();
    animator->ClearAllAnimations();
    animator->AddAnimation(pillarAnim);
}

void Pillar::RemoveDie() {
    Vector2 lastPos = mDice.back()->GetPosition();
    Vector2 nextPos = lastPos - Vector2(0, -18);
    
    Sprite* dieSprite = mDice.back()->GetSprite();
    dieSprite->SetZOrder(200);
    
    for (int i = 0; i < mDice.size() - 1; i++) {
        Animation* anim = new EaseOut(mDice[i]->GetPosition() + Vector2(0, -18), 10);
        mDice[i]->GetAnimator()->AddAnimation(anim);
    }

    Animation* dieAnim1 = new EaseOut(nextPos, 10);
    Animation* dieAnim2 = new RemoveFromParent();
    Animator* dieAnimnator = mDice.back()->GetAnimator();
    dieAnimnator->AddAnimation(dieAnim1);
    dieAnimnator->AddAnimation(dieAnim2);
    mDice.pop_back();
    
    Crane* crane = reinterpret_cast<Crane*>(mParent);
    
    Animation* pillarAnim = new EaseOutAndScale(Vector2(0, crane->mFrontHeight - (mHeightOnAddDie * (mDice.size() - 1))), 1, 20);
    Animator* animator = this->GetAnimator();
    animator->ClearAllAnimations();
    animator->AddAnimation(pillarAnim);
}

void Pillar::SetZOrder(int z) {
    for (int i = 0; i < mDice.size(); i++) {
        mDice[i]->GetSprite()->SetZOrder(z);
    }
}

void Pillar::ApplyPillarInformation(PillarInformation p) {
    if (p.scale == 1) {
        p.pos.y -= (mHeightOnAddDie * (mDice.size()-1));
    }
    
    Animation* anim = new EaseOutAndScale(p.pos, p.scale, 20);
    
//    Vector2 mod(0, 0);
//    
//    if (p.scale == 1) {
//        mod.y -= (mHeightOnAddDie * (mDice.size()-1));
//    }
//    
//    Animation* anim = new EaseOutAndScaleOnCrane(p.angle, p.scale, 20, mod);
//    currentAngle = p.angle;
    
    Animator* animator = this->GetAnimator();
    
    animator->ClearAllAnimations();
    animator->AddAnimation(anim);
    
    this->SetZOrder(p.z);
}

void Pillar::Incorporate(PillarInformation p) {
    Animation* anim = new EaseOutAndScale(p.pos, p.scale, 60);
    
    Animator* animator = this->GetAnimator();
    
    animator->ClearAllAnimations();
    animator->AddAnimation(anim);
    
    this->SetZOrder(p.z);
}

void Pillar::Seperate(PillarInformation p) {
    Animation* anim = new EaseIn(p.pos, 60);
    
    Animator* animator = this->GetAnimator();
    
    animator->ClearAllAnimations();
    animator->AddAnimation(anim);
    
    this->SetZOrder(p.z);
}

int Pillar::GetStoredValue() {
    return mStoredValue;
}

int Pillar::GetDieType() {
    return mDieType;
}

// MARK: - Crane

bool Crane::mFirst = true;

Crane::Crane() {
    if (mFirst) {
        mPillars[0] = new Pillar(20, 1);
        mPillars[1] = new Pillar(12, 1);
        mPillars[2] = new Pillar(10, 1);
        mPillars[3] = new Pillar(8, 1);
        mPillars[4] = new Pillar(6, 1);
        mPillars[5] = new Pillar(4, 1);
        
        mFirst = false;
        
    } else {
        mPillars[0] = new Pillar(20);
        mPillars[1] = new Pillar(12);
        mPillars[2] = new Pillar(10);
        mPillars[3] = new Pillar(8);
        mPillars[4] = new Pillar(6);
        mPillars[5] = new Pillar(4);
    }
    
    for (int i = 0; i < 6; i++) {
        this->AddChild(mPillars[i]);
    }
    
    // Before angle was added
//    mPillarData.push_back(PillarInformation(Vector2(0, Crane::mFrontHeight), 1, 100));
//    mPillarData.push_back(PillarInformation(Vector2(-Crane::mCloseWidth, Crane::mCloseHeight), 0.78125, 200));
//    mPillarData.push_back(PillarInformation(Vector2(-Crane::mFarWidth, Crane::mFarHeight), 0.59375, 500));
//    mPillarData.push_back(PillarInformation(Vector2(0, Crane::mBackHeight), 0.52, 1000));
//    mPillarData.push_back(PillarInformation(Vector2(Crane::mFarWidth, Crane::mFarHeight), 0.59375, 500));
//    mPillarData.push_back(PillarInformation(Vector2(Crane::mCloseWidth, Crane::mCloseHeight), 0.78125, 200));
    
    mPillarData.push_back(PillarInformation(Vector2(0, Crane::mFrontHeight), 1, 100, 0.25));
    mPillarData.push_back(PillarInformation(Vector2(-Crane::mCloseWidth, Crane::mCloseHeight), 0.78125, 200, 0.41666));
    mPillarData.push_back(PillarInformation(Vector2(-Crane::mFarWidth, Crane::mFarHeight), 0.59375, 500, 0.58333));
    mPillarData.push_back(PillarInformation(Vector2(0, Crane::mBackHeight), 0.52, 1000, .75));
    mPillarData.push_back(PillarInformation(Vector2(Crane::mFarWidth, Crane::mFarHeight), 0.59375, 500, 0.91666));
    mPillarData.push_back(PillarInformation(Vector2(Crane::mCloseWidth, Crane::mCloseHeight), 0.78125, 200, 0.08333));
    
    Incorperate();
}

Crane::~Crane() {
    for (int i = 0; i < 6; i++) {
        delete mPillars[i];
    }
}

void Crane::RotateRight() {
    mPillarData.push_back(mPillarData.front());
    mPillarData.pop_front();
    
    if (mSelectedPillar == 0) {
        mSelectedPillar = 5;
    } else {
        mSelectedPillar--;
    }
    
    ApplyPillarData();
}

void Crane::RotateLeft() {
    mPillarData.push_front(mPillarData.back());
    mPillarData.pop_back();
    
    if (mSelectedPillar == 5) {
        mSelectedPillar = 0;
    } else {
        mSelectedPillar++;
    }
    
    ApplyPillarData();
}

void Crane::ApplyPillarData() {
    auto it = mPillarData.begin();
    for (int i = 0; i < 6; i++) {
        mPillars[i]->ApplyPillarInformation(*it);
        ++it;
    }
}

void Crane::Incorperate() {
    auto it = mPillarData.begin();
    for (int i = 0; i < 6; i++) {
        mPillars[i]->Incorporate(*it);
        ++it;
    }
}

bn::vector<uint, MAX_ROLLABLE_DICE> Crane::Seperate() {
    RollVector retVal;
    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < mPillars[i]->GetStoredValue(); j++) {
            retVal.push_back(mPillars[i]->GetDieType());
        }
    }
    
    if (retVal.size() == 0) {
        return retVal;
    }
    
    auto it = mPillarData.begin();
    for (int i = 0; i < 6; i++) {
        PillarInformation p = *it;
        p.pos *= bn::fixed(6.25);
        mPillars[i]->Seperate(p);
        ++it;
    }
    
    return retVal;
}

void Crane::IncrementSelected() {
    if (mTotalDiceCount < MAX_ROLLABLE_DICE) {
        mPillars[mSelectedPillar]->Increment();
        mTotalDiceCount++;
    }
}

void Crane::DecrementSelected() {
    if (mTotalDiceCount > 0) {
        if (mPillars[mSelectedPillar]->Decrement()) {
            mTotalDiceCount--;
        }
    }
}

void Crane::Skip() {
    for (int i = 0; i < 6; i++) {
        mPillars[i]->GetAnimator()->ClearAllAnimations();
    }
}

// MARK: - EaseOutAndScaleOnCrane
Ellipse EaseOutAndScaleOnCrane::CraneEllipse = Ellipse(80, 46);

EaseOutAndScaleOnCrane::EaseOutAndScaleOnCrane(bn::fixed destPos, bn::fixed destScale, uint time, Vector2 mod, uint delay) : Animation(delay), mModifier(mod){
    mEndScale = destScale;
    mEndPosition = destPos;
    mTime = time;
}

void EaseOutAndScaleOnCrane::Init() {
    mStartScale = mObject->GetScale();
    Vector2 pos = mObject->GetPosition();
    mStartPosition = bn::atan2((pos.y + CraneEllipse.mPosition.y).integer(), (pos.x + CraneEllipse.mPosition.x).integer());
    if (mStartPosition < 0) mStartPosition += 1;
    
    if (bn::abs(mEndPosition - mStartPosition) > 0.5) {
        if (mEndPosition < mStartPosition) {
            mEndPosition += 1;
        } else {
            mStartPosition += 1;
        }
    }
}

bool EaseOutAndScaleOnCrane::Update() {
    if (mCurrentFrame >= mTime) {
        mObject->SetPosition(mModifier + CraneEllipse.GetPointOnEllipse(mEndPosition));
//        mObject->SetScale(mEndScale);
        return true;
    }
    
    bn::fixed s2 = bn::fixed(mCurrentFrame)/bn::fixed(mTime);
    s2 = bn::sqrt(s2);
    
    bn::fixed currentAngle = LerpFixed(mStartPosition, mEndPosition, s2);
    Vector2 currentPos = CraneEllipse.GetPointOnEllipse(currentAngle);
    
//    bn::fixed currentScale = LerpFixed(mStartScale, mEndScale, s2);
    
    bn::fixed v = ((currentPos.y) + (CraneEllipse.mHeight/2)) / CraneEllipse.mHeight; // Represents vertical element 0-1
    bn::fixed scaleDifference = maxScale - minScale;
    bn::fixed currentScale = (scaleDifference * v) + minScale;
    
    mObject->SetPosition(currentPos + (mModifier * s2));
    mObject->SetScale(currentScale);
    
    return false;
}

uint EaseOutAndScaleOnCrane::GetTime() {
    return mTime;
}

void EaseOutAndScaleOnCrane::SetTime(uint time) {
    mTime = time;
}

//bn::fixed mEndPosition;
//bn::fixed mStartPosition;
//bn::fixed mEndScale;
//bn::fixed mStartScale;
//uint mTime;


#endif
