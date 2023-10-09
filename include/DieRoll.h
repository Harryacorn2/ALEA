#ifndef DIEROLL_H
#define DIEROLL_H

#include "global.h"
#include "GameObject.h"

class Die;
class RollResult;

class DieRoll : public GameObject {
public:
    DieRoll(RollVector roll);
    ~DieRoll();
    
    void RollOne();
    void RollAll();
    RollResult StopOne();
    void StopAll();
    
    uint GetRolledValue();
    int GetDieCount();
    
    bool IsFinishedRolling();
    bool IsFinishedStopping();
    
    bn::fixed GetAverageRoll();
    bn::fixed GetGoodRoll();
    
private:
    RollVector mRollVector;
    int mDieToRoll = 0;
    int mDieToStop = 0;
    uint mRolledValue = 0;
    bn::vector<Die*, MAX_ROLLABLE_DICE> mDice;
};

#endif
