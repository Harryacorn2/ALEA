#ifndef D4_CPP
#define D4_CPP

#include "Random.h"
#include "Die.h"
#include "bn_span.h"
#include "bn_color.h"
#include "ColorUtility.h"

#include "bn_sprite_items_d4.h"

#include <stdio.h>

// Six sided die class
D4::D4(int speed) : Die(speed) {
//    mSprite = bn::make_optional<bn::sprite_ptr>(bn::sprite_items::d4.create_sprite(0, 0));
    
    Sprite* s = new Sprite(this, bn::sprite_items::d4.create_sprite(0, 0));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d4.tiles_item(), 0, 0, 0, 0));
    mAction->update();
}

D4::D4(int speed, const Vector2& position) : Die(speed) {
//    mSprite = bn::sprite_items::d4.create_sprite(position);
    
    Sprite* s = new Sprite(this, bn::sprite_items::d4.create_sprite(position));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d4.tiles_item(), 0, 0, 0, 0));
    SetPosition(position);
    mAction->update();
}

D4::D4(int speed, const Vector2& position, int init) : Die(speed) {
    mInitFace = init;
    
//    mSprite = bn::sprite_items::d4.create_sprite(position);
    
    Sprite* s = new Sprite(this, bn::sprite_items::d4.create_sprite(position));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d4.tiles_item(), init, init, init, init));
    SetPosition(position);
    mAction->update();
}

D4::D4(int speed, const bn::fixed_point& position) : Die(speed) {
//    mSprite = bn::sprite_items::d4.create_sprite(position);
    
    Sprite* s = new Sprite(this, bn::sprite_items::d4.create_sprite(position));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d4.tiles_item(), 0, 0, 0, 0));
    SetPosition(position);
    mAction->update();
}

D4::D4(int speed, const bn::fixed_point& position, int init) : Die(speed) {
    mInitFace = init;
    
//    mSprite = bn::sprite_items::d4.create_sprite(position);
    Sprite* s = new Sprite(this, bn::sprite_items::d4.create_sprite(position));
    mComponents.push_back(s);
    
    mAction = new bn::sprite_animate_action(bn::create_sprite_animate_action_forever(s->GetPtr(), 0, bn::sprite_items::d4.tiles_item(), init, init, init, init));
    SetPosition(position);
    mAction->update();
}

D4::~D4() {
    delete mAction;
}

void D4::Roll() {
    *mAction = bn::create_sprite_animate_action_forever(
        reinterpret_cast<Sprite*>(mComponents[0])->GetPtr(), mSpeed, bn::sprite_items::d4.tiles_item(), 0, 3, 1, 2);
    currentFrame = 0;
    mAction->update();
    mRolling = true;
}

RollResult D4::Stop() {
    RollResult retval(0, 0);
    
    if (mRolling) {
        Sprite* s = reinterpret_cast<Sprite*>(mComponents[0]);
        
        int cVal = Random::GetInt(4);
        *mAction = bn::create_sprite_animate_action_forever(
            s->GetPtr(), 0, bn::sprite_items::d4.tiles_item(), cVal, cVal, cVal, cVal);
        mAction->update();
        
        if (cVal < 2) {
//            bn::sound_items::good.play(1);
            retval.type = 0;
            
        } else if (cVal < 3) {
//            bn::sound_items::great.play(1);
            retval.type = 1;
            
        } else {
//            bn::sound_items::excelent.play(1);
            retval.type = 2;
            
            // Set Palette to red
            bn::color raw[16];
            for (int i = 0; i < 16; i++) {
                raw[i] = Color::Black;
            }
            
            raw[2] = Color::Red;
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

void D4::Reset() {
    *mAction = bn::create_sprite_animate_action_forever(reinterpret_cast<Sprite*>(mComponents[0])->GetPtr(), 0, bn::sprite_items::d4.tiles_item(), mInitFace, mInitFace, mInitFace, mInitFace);
    mAction->update();
    currentFrame = mInitFace * mSpeed;
    mRolling = false;
}

void D4::SetDigit(int i) {
    if (i < 1 || i > 5) return;
    int cval = i - 1;
    Sprite* s = reinterpret_cast<Sprite*>(mComponents[0]);
    *mAction = bn::create_sprite_animate_action_forever(
        s->GetPtr(), 0, bn::sprite_items::d4.tiles_item(), cval, cval, cval, cval);
    mAction->update();
}

void D4::Update() {
    if (mRolling) {
        currentFrame++;
        if (currentFrame >= mSpeed * 6) {
            currentFrame = 0;
        }
    }
}

void D4::Draw() {
    GameObject::Draw();
    mAction->update();
}

#endif
