#ifndef DIEROLL_CPP
#define DIEROLL_CPP

#include "DieRoll.h"
#include "Die.h"

DieRoll::DieRoll(RollVector roll) : mRollVector(roll) {
    bn::vector<Vector2, MAX_ROLLABLE_DICE> locations;
    Die::GenerateDistribution(roll.size(), locations);
    int i = 0;
    
    for (auto loc : locations) {
        switch (roll[i]) {
            case 4:
                mDice.push_back(new D4(2, loc, 4));
                break;
                
            case 6:
                mDice.push_back(new D6(2, loc, 6));
                break;
                
            case 8:
                mDice.push_back(new D8(2, loc, 8));
                break;
                
            case 10:
                mDice.push_back(new D10(2, loc, 10));
                break;
                
            case 12:
                mDice.push_back(new D12(2, loc, 12));
                break;
                
            case 20:
                mDice.push_back(new D20(2, loc, 20));
                break;
                
            default:
                break;
        }
        
        i++;
    }
    
    for (int j = 0; j < mDice.size(); j++) {
        this->AddChild(mDice[j]);
    }
}

DieRoll::~DieRoll() {
    
//    for (int i = 0; i < )
}

void DieRoll::RollOne() {
    if (mDieToRoll == mDice.size()) {
        return;
    }
    
    mDice[mDieToRoll]->Roll();
    mDieToRoll++;
}

void DieRoll::RollAll() {
    if (mDieToRoll == mDice.size()) {
        return;
    }
    
    for (int i = 0; i < mDice.size(); i++) {
        mDice[i]->Roll();
    }
    
    mDieToRoll = mDice.size();
}

RollResult DieRoll::StopOne() {
    if (mDieToStop == mDice.size()) {
        return RollResult(0, 0);
    }
    
    RollResult retVal = mDice[mDieToStop]->Stop();
    mRolledValue += retVal.value;
    mDieToStop++;
    
    return retVal;
}

void DieRoll::StopAll() {
    if (mDieToStop == mDice.size()) {
        return;
    }
    
    for (int i = 0; i < mDice.size(); i++) {
        mRolledValue += mDice[i]->Stop().value;
    }
    
    mDieToStop = mDice.size();
}

uint DieRoll::GetRolledValue() {
    return mRolledValue;
}

int DieRoll::GetDieCount() {
    return mDice.size();
}

bool DieRoll::IsFinishedRolling() {
    return mDieToRoll == mDice.size();
}

bool DieRoll::IsFinishedStopping() {
    return mDieToStop == mDice.size();
}

bn::fixed DieRoll::GetAverageRoll() {
    bn::fixed total = 0;
    
    for (uint i : mRollVector) {
        total += i/2;
        total += 0.5;
    }
    
    return total;
}

bn::fixed DieRoll::GetGoodRoll() {
    bn::fixed total = 0;
    
    for (uint i : mRollVector) {
        bn::fixed sub = (i / 4);
        total += (i - sub);
    }
    
    return total;
}

#endif
