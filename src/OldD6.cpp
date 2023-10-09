#ifndef OldD6_CPP
#define OldD6_CPP

#include "Random.h"
#include "Die.h"
#include "ColorUtility.h"
#include "bn_span.h"
#include "bn_color.h"

#include "bn_sprite_items_d6_old.h"

#include <stdio.h>

// Six sided die class
OldD6::OldD6(int speed) : Die(speed) {
    Sprite* s = new Sprite(this, bn::sprite_items::d6_old.create_sprite(0, 0));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d6_old.tiles_item(), 0, 0, 0, 0, 0, 0));
    mAction->update();
    
    Transform t;
    t.SetScale(2);
    s->SetTransform(t);
}

OldD6::OldD6(int speed, const Vector2& position) : Die(speed) {
    Sprite* s = new Sprite(this, bn::sprite_items::d6_old.create_sprite(position));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d6_old.tiles_item(), 0, 0, 0, 0, 0, 0));
    SetPosition(position);
    mAction->update();
    
    Transform t;
    t.SetScale(2);
    s->SetTransform(t);
}

OldD6::OldD6(int speed, const Vector2& position, int init) : Die(speed) {
    mInitFace = init;
    
    Sprite* s = new Sprite(this, bn::sprite_items::d6_old.create_sprite(position));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d6_old.tiles_item(), init, init, init, init, init, init));
    SetPosition(position);
    mAction->update();
    
    Transform t;
    t.SetScale(2);
    s->SetTransform(t);
}

OldD6::OldD6(int speed, const bn::fixed_point& position) : Die(speed) {
    Sprite* s = new Sprite(this, bn::sprite_items::d6_old.create_sprite(position));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d6_old.tiles_item(), 0, 0, 0, 0, 0, 0));
    SetPosition(position);
    mAction->update();
    
    Transform t;
    t.SetScale(2);
    s->SetTransform(t);
}

OldD6::OldD6(int speed, const bn::fixed_point& position, int init) : Die(speed) {
    mInitFace = init;
    
    Sprite* s = new Sprite(this, bn::sprite_items::d6_old.create_sprite(position));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d6_old.tiles_item(), init, init, init, init, init, init));
    SetPosition(position);
    mAction->update();
    
    Transform t;
    t.SetScale(2);
    s->SetTransform(t);
}

OldD6::~OldD6() {
    delete mAction;
}

void OldD6::Roll() {
    *mAction = bn::create_sprite_animate_action_forever(
        reinterpret_cast<Sprite*>(mComponents[0])->GetPtr(), mSpeed, bn::sprite_items::d6_old.tiles_item(), 0, 1, 2, 3, 4, 5);
    currentFrame = 0;
    mAction->update();
    mRolling = true;
}

RollResult OldD6::Stop() {
    RollResult retval(0, 0);
    
    if (mRolling) {
        Sprite* s = reinterpret_cast<Sprite*>(mComponents[0]);
        
        int cVal = Random::GetInt(6);
        *mAction = bn::create_sprite_animate_action_forever(
                                                            s->GetPtr(), 0, bn::sprite_items::d6_old.tiles_item(), cVal, cVal, cVal, cVal, cVal, cVal);
        mAction->update();
        
        if (cVal < 3) {
            bn::sound_items::good.play(1);
            
        } else if (cVal < 5) {
            bn::sound_items::great.play(1);
            
        } else {
            bn::sound_items::excelent.play(1);
            
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

void OldD6::SetDigit(int i) {
    if (i < 1 || i > 7) return;
    int cval = i - 1;
    Sprite* s = reinterpret_cast<Sprite*>(mComponents[0]);
    *mAction = bn::create_sprite_animate_action_forever(
        s->GetPtr(), 0, bn::sprite_items::d6_old.tiles_item(), cval, cval, cval, cval, cval, cval);
    mAction->update();
}

void OldD6::Reset() {
    *mAction = bn::create_sprite_animate_action_forever(reinterpret_cast<Sprite*>(mComponents[0])->GetPtr(), 0, bn::sprite_items::d6_old.tiles_item(), mInitFace, mInitFace, mInitFace, mInitFace, mInitFace, mInitFace);
    mAction->update();
    currentFrame = mInitFace * mSpeed;
    mRolling = false;
}

void OldD6::Update() {
    if (mRolling) {
        currentFrame++;
        if (currentFrame >= mSpeed * 4) {
            currentFrame = 0;
        }
    }
}

void OldD6::Draw() {
    GameObject::Draw();
    mAction->update();
}

#endif
