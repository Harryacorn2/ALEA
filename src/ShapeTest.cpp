#ifndef SHAPETEST__CPP
#define SHAPETEST__CPP

#include "SceneManager.h"
#include "bn_sprite_items_d4.h"
#include "bn_sprite_items_d6.h"
#include "bn_sprite_items_d8.h"
#include "bn_sprite_items_d10.h"
#include "bn_sprite_items_d12.h"
#include "bn_sprite_items_d20.h"
#include "TextLine.h"
#include "Animator.h"

void SceneManager::ShapeTest() {
    TextLine title("ALEA", yobani_fixed_16x16_sprite_font);
    title.AlignCenter();
    title.SetPosition(0, -34);
    
    TextLine credits1("by Aviel Dardashti");
    TextLine credits2("and Edgar Casarin");
    
    credits1.AlignCenter();
    credits1.SetPosition(0, 30);
    
    credits2.AlignCenter();
    credits2.SetPosition(0, 40);
    
//    GameObject d4(1, 0, Vector2(-90, 0), bn::sprite_items::d4.create_sprite(0, 0, 4));
//    GameObject d6(1, 0, Vector2(-54, 0), bn::sprite_items::d6.create_sprite(0, 0, 6));
//    GameObject d8(1, 0, Vector2(-18, 0), bn::sprite_items::d8.create_sprite(0, 0, 8));
    Die* dice[6];
    dice[0] = new D4(0, Vector2(-90, 0), 4);
    dice[1] = new D6(0, Vector2(-54, 0), 6);
    dice[2] = new D8(0, Vector2(-18, 0), 8);
    dice[3] = new D10(0, Vector2(18, 0), 10);
    dice[4] = new D12(0, Vector2(54, 0), 12);
    dice[5] = new D20(0, Vector2(90, 0), 20);
    
    int num = 1;
    
    while(true) {
        
        if (bn::keypad::up_pressed()) {
            num++;
            for (int i = 0; i < 6; i++) {
                dice[i]->SetDigit(num);
            }
        }
        
        if (bn::keypad::down_pressed()) {
            num--;
            for (int i = 0; i < 6; i++) {
                dice[i]->SetDigit(num);
            }
        }
        
        GameObject::UpdateAll();
        GameObject::DrawAll();
        bn::core::update();
    }
}

#endif
