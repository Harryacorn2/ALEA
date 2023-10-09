#ifndef D20_CPP
#define D20_CPP

#include "Random.h"
#include "Die.h"
#include "ColorUtility.h"
#include "bn_span.h"
#include "bn_color.h"

#include "bn_sprite_items_d20.h"

#include <stdio.h>

// Six sided die class
D20::D20(int speed) : Die(speed) {
    Sprite* s = new Sprite(this, bn::sprite_items::d20.create_sprite(0, 0));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d20.tiles_item(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    mAction->update();
}

D20::D20(int speed, const Vector2& position) : D20(speed) {
    SetPosition(position);
}

D20::D20(int speed, const Vector2& position, int init) : Die(speed) {
    mInitFace = init;

    Sprite* s = new Sprite(this, bn::sprite_items::d20.create_sprite(position));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d20.tiles_item(), init, init, init, init, init, init, init, init, init, init, init, init, init, init, init, init, init, init, init, init));
    SetPosition(position);
    mAction->update();
}

D20::D20(int speed, const bn::fixed_point& position) : Die(speed) {
    SetPosition(position);
}

D20::D20(int speed, const bn::fixed_point& position, int init) : Die(speed) {
    mInitFace = init;
    
    Sprite* s = new Sprite(this, bn::sprite_items::d20.create_sprite(position));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d20.tiles_item(), init, init, init, init, init, init, init, init, init, init, init, init, init, init, init, init, init, init, init, init));
    SetPosition(position);
    mAction->update();
}

D20::~D20() {
    delete mAction;
}

void D20::Roll() {
    *mAction = bn::create_sprite_animate_action_forever(
        reinterpret_cast<Sprite*>(mComponents[0])->GetPtr(), mSpeed, bn::sprite_items::d20.tiles_item(), 9, 14, 4, 18, 2, 10, 7, 16, 19, 1, 5, 12, 6, 3, 17, 15, 0, 11, 8, 13);
    currentFrame = 0;
    mAction->update();
    mRolling = true;
}

RollResult D20::Stop() {
    RollResult retval(0, 0);
    
    if (mRolling) {
        Sprite* s = reinterpret_cast<Sprite*>(mComponents[0]);
        
        int cVal = Random::GetInt(20);
        *mAction = bn::create_sprite_animate_action_forever(
            s->GetPtr(), 0, bn::sprite_items::d20.tiles_item(), cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal, cVal);
        mAction->update();
        
        if (cVal < 10) {
            retval.type = 0;
            
        } else if (cVal < 19) {
            retval.type = 1;
            
        } else {
            retval.type = 2;
            
            // Set Palette to red
            bn::color raw[16];
            for (int i = 0; i < 16; i++) {
                raw[i] = Color::Black;
            }
            
            raw[2] = Color::LightRed;
            raw[3] = Color::White;
            
            auto colors = bn::span(raw, 16);
            auto palette = bn::sprite_palette_item(colors, bn::bpp_mode::BPP_4);
            s->SetPalette(palette);
        }
        
        mRolling = false;
        retval.value = cVal + 1;
    }
    
    return retval;
}

void D20::Reset() {
    *mAction = bn::create_sprite_animate_action_forever(reinterpret_cast<Sprite*>(mComponents[0])->GetPtr(), 0, bn::sprite_items::d20.tiles_item(), mInitFace, mInitFace, mInitFace, mInitFace, mInitFace, mInitFace, mInitFace, mInitFace, mInitFace, mInitFace, mInitFace, mInitFace);
    mAction->update();
    currentFrame = mInitFace * mSpeed;
    mRolling = false;
}

void D20::SetDigit(int i) {
    if (i < 1 || i > 21) return;
    int cval = i - 1;
    Sprite* s = reinterpret_cast<Sprite*>(mComponents[0]);
    *mAction = bn::create_sprite_animate_action_forever(
        s->GetPtr(), 0, bn::sprite_items::d20.tiles_item(), cval, cval, cval, cval, cval, cval, cval, cval, cval, cval
                                                         , cval, cval, cval, cval, cval, cval, cval, cval, cval, cval);
    mAction->update();
}

void D20::Update() {
    if (mRolling) {
        currentFrame++;
        if (currentFrame >= mSpeed * 20) {
            currentFrame = 0;
        }
    }
}

void D20::Draw() {
    GameObject::Draw();
    mAction->update();
}

#endif
