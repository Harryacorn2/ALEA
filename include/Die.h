#ifndef DIE_H
#define DIE_H

#include "global.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_random.h"
#include "bn_vector.h"
#include "engineMath.h"

#include "bn_sound_items.h"

#include "GameObject.h"
#include "Sprite.h"

struct RollResult {
    int value;
    int type; // 0 = good, 1 = great, 2 == excellent
};

class Die : public GameObject {
public:
	Die(int speed = 1);
	virtual ~Die();
	
	virtual void Roll() = 0;
	virtual RollResult Stop() = 0;
	virtual void Reset() = 0;
    virtual void SetDigit(int i) = 0;
	
	static void GenerateDistribution(int runningCount, bn::vector<Vector2, MAX_ROLLABLE_DICE>& locationVector, uint spacing = 4);
	
protected:
	int currentFrame = 0;
	int mSpeed;
	int mInitFace = 0;
	bool mRolling = false;
};

class OldD6 : public Die {
public:
    OldD6(int speed = 1);
    OldD6(int speed, const Vector2& position);
    OldD6(int speed, const Vector2& position, int init);
    OldD6(int speed, const bn::fixed_point& position); // Legacy
    OldD6(int speed, const bn::fixed_point& position, int init); // Legacy
    ~OldD6();
    
    void Roll() override;
    RollResult Stop() override;
    void Reset() override;
    void SetDigit(int i) override;
    
    void Update() override;
    void Draw() override;
    
private:
    bn::sprite_animate_action<6>* mAction = NULL;
};

class D4 : public Die {
public:
    D4(int speed = 1);
    D4(int speed, const Vector2& position);
    D4(int speed, const Vector2& position, int init);
    D4(int speed, const bn::fixed_point& position); // Legacy
    D4(int speed, const bn::fixed_point& position, int init); // Legacy
    ~D4();
    
    void Roll() override;
    RollResult Stop() override;
    void Reset() override;
    void SetDigit(int i) override;
    
    void Update() override;
    void Draw() override;
    
private:
    bn::sprite_animate_action<4>* mAction = NULL;
};

class D6 : public Die {
public:
	D6(int speed = 1);
	D6(int speed, const Vector2& position);
	D6(int speed, const Vector2& position, int init);
	D6(int speed, const bn::fixed_point& position); // Legacy
	D6(int speed, const bn::fixed_point& position, int init); // Legacy
	~D6();
	
    void Roll() override;
    RollResult Stop() override;
    void Reset() override;
    void SetDigit(int i) override;
    
    void Update() override;
    void Draw() override;
	
private:
	bn::sprite_animate_action<6>* mAction = NULL;
};

class D8 : public Die {
public:
    D8(int speed = 1);
    D8(int speed, const Vector2& position);
    D8(int speed, const Vector2& position, int init);
    D8(int speed, const bn::fixed_point& position); // Legacy
    D8(int speed, const bn::fixed_point& position, int init); // Legacy
    ~D8();
    
    void Roll() override;
    RollResult Stop() override;
    void Reset() override;
    void SetDigit(int i) override;
    
    void Update() override;
    void Draw() override;
    
private:
    bn::sprite_animate_action<8>* mAction = NULL;
};

class D10 : public Die {
public:
    D10(int speed = 1);
    D10(int speed, const Vector2& position);
    D10(int speed, const Vector2& position, int init);
    D10(int speed, const bn::fixed_point& position); // Legacy
    D10(int speed, const bn::fixed_point& position, int init); // Legacy
    ~D10();
    
    void Roll() override;
    RollResult Stop() override;
    void Reset() override;
    void SetDigit(int i) override;
    
    void Update() override;
    void Draw() override;
    
private:
    bn::sprite_animate_action<10>* mAction = NULL;
};

class D12 : public Die {
public:
    D12(int speed = 1);
    D12(int speed, const Vector2& position);
    D12(int speed, const Vector2& position, int init);
    D12(int speed, const bn::fixed_point& position); // Legacy
    D12(int speed, const bn::fixed_point& position, int init); // Legacy
    ~D12();
    
    void Roll() override;
    RollResult Stop() override;
    void Reset() override;
    void SetDigit(int i) override;
    
    void Update() override;
    void Draw() override;
    
private:
    bn::sprite_animate_action<12>* mAction = NULL;
};

class D20 : public Die {
public:
    D20(int speed = 1);
    D20(int speed, const Vector2& position);
    D20(int speed, const Vector2& position, int init);
    D20(int speed, const bn::fixed_point& position); // Legacy
    D20(int speed, const bn::fixed_point& position, int init); // Legacy
    ~D20();
    
    void Roll() override;
    RollResult Stop() override;
    void Reset() override;
    void SetDigit(int i) override;
    
    void Update() override;
    void Draw() override;
    
private:
    bn::sprite_animate_action<20>* mAction = NULL;
};

#endif
