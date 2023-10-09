#ifndef SELECTD6_CPP
#define SELECTD6_CPP

#include "SceneManager.h"
#include "TextLine.h"
#include "Animator.h"
#include "Die.h"

void SceneManager::SelectD6() {
    // Setup Here
    
    TextLine title("ALEA", yobani_fixed_16x16_sprite_font);
    title.AlignCenter();
    title.SetPosition(0, -34);
    
    TextLine credits1("by Aviel Dardashti");
    TextLine credits2("and Edgar Casarin");
    
    credits1.AlignCenter();
    credits1.SetOneSpritePerChar(true);
    credits1.SetPosition(0, 30);
    
    credits2.AlignCenter();
    credits2.SetOneSpritePerChar(true);
    credits2.SetPosition(0, 40);
    
    TextLine score("00000", yobani_variable_8x8_sprite_font);
    
    score.SetPosition(0, -65);
    score.AlignCenter();
    
    int runningCount = 1;
    GameObject* obj = new GameObject();
    GameObject& parent = *obj;
    Animator* parentAnim = obj->AddAnimator();
    
    auto UpdateMenu = [&]() {
        parent.RemoveAllChildren();
        
        if (runningCount < 7) {
            GameObject* child = new OldD6(10, Vector2(0, 0), runningCount - 1);
            child->SetScale(1);
            parent.AddChild(child);
            
        } else if (runningCount < 13) {
            GameObject* child1 = new OldD6(10, Vector2(-18, 0), 5);
            GameObject* child2 = new OldD6(10, Vector2(18, 0), (runningCount - 1) % 6);
            child1->SetScale(1);
            child2->SetScale(1);
            
            parent.AddChild(child1);
            parent.AddChild(child2);
            
        } else{
            GameObject* child1 = new OldD6(10, Vector2(-35, 0), 5);
            GameObject* child2 = new OldD6(10, Vector2(0, 0), 5);
            GameObject* child3 = new OldD6(10, Vector2(35, 0), (runningCount - 1) % 6);
            
            child1->SetScale(1);
            child2->SetScale(1);
            child3->SetScale(1);
            
            parent.AddChild(child1);
            parent.AddChild(child2);
            parent.AddChild(child3);
        }
    };
    
    UpdateMenu();
    
    bool selectionComplete = false;
    
    // Menu selection
    while((!SceneManager::mUnloadFlag) && !selectionComplete) {
        if (bn::keypad::up_pressed()) {
            if (runningCount < 15) {
                runningCount++;
                UpdateMenu();
            } else {
                parentAnim->AddAnimation(new HoriShake(2, 10));
            }
        }
        
        if (bn::keypad::down_pressed()) {
            if (runningCount > 1) {
                runningCount--;
                UpdateMenu();
            } else {
                parentAnim->AddAnimation(new HoriShake(2, 10));
            }
        }
        
        if (bn::keypad::right_pressed()) {
            if (runningCount < 15) {
                if (runningCount < 6) {
                    runningCount = 6;
                    
                } else if (runningCount < 12) {
                    runningCount = 12;
                    
                } else {
                    runningCount = 15;
                }
                
                UpdateMenu();
            } else {
                parentAnim->AddAnimation(new HoriShake(2, 10));
            }
        }
        
        if (bn::keypad::left_pressed()) {
            if (runningCount > 1) {
                if (runningCount <= 6) {
                    runningCount = 1;
                    
                } else if (runningCount <= 12) {
                    runningCount = 6;
                    
                } else {
                    runningCount = 12;
                }
                
                UpdateMenu();
            } else {
                parentAnim->AddAnimation(new HoriShake(2, 10));
            }
        }
        
        
        if (bn::keypad::l_held() && bn::keypad::r_held() && bn::keypad::start_pressed()) {
            SceneManager::Quit();
            
        } else if (bn::keypad::start_pressed()) {
            selectionComplete = true;
        }
        
        
        GameObject::UpdateAll();
        GameObject::DrawAll();
        bn::core::update();
    }
    
    
    // Die Rolling
    title.AddAnimator()->AddAnimation(new EaseIn(Vector2(0, -100), 30, 0));
    credits1.AddAnimator()->AddAnimation(new EaseIn(Vector2(0, 100), 30, 0));
    credits2.AddAnimator()->AddAnimation(new EaseIn(Vector2(0, 110), 30, 0));
    bool rollingComplete = false;
    
    for (int i = 0; i < 30; i++) {
        GameObject::UpdateAll();
        GameObject::DrawAll();
        bn::core::update();
    }
    
    delete obj;
    
    bn::vector<Vector2, MAX_ROLLABLE_DICE> locations;
    bn::vector<Die*, MAX_ROLLABLE_DICE> dice;
        
    Die::GenerateDistribution(runningCount, locations);
    
    for (auto loc : locations) {
        dice.push_back(new OldD6(2, loc, 3));
        dice.back()->SetScale(1);
        dice.back()->Roll();
    }
    
    int toggle = 0;
    int totalRolledValue = 0;
    
    while ((!SceneManager::mUnloadFlag) && !rollingComplete) {
        if (bn::keypad::a_pressed() || bn::keypad::b_pressed()) {
            if (toggle < runningCount) {
                totalRolledValue += dice[toggle]->Stop().value;
                score.SetText(bn::to_string<5>(totalRolledValue));
                toggle++;
            }
        }
        
        if (bn::keypad::l_held() && bn::keypad::r_held() && bn::keypad::start_pressed()) {
            SceneManager::Quit();
        }
        
        if (bn::keypad::start_pressed()) {
            bool runningAuto = true;
            int waiting = 0;
            
            while (runningAuto && (!SceneManager::mUnloadFlag)) {
                int rolledValue = 0;
                
                if (waiting <= 0) {
                    if (toggle < runningCount) {
                        rolledValue = dice[toggle]->Stop().value;
                        totalRolledValue += rolledValue;
                        score.SetText(bn::to_string<5>(totalRolledValue));
                        toggle++;
                        
                        if (rolledValue < 3) {
                            waiting = 15;
                        } else if (rolledValue < 5) {
                            waiting = 25;
                        } else {
                            waiting = 35;
                        }
                    } else {
                        runningAuto = false;
                    }
                    
                } else {
                    waiting--;
                }
                
                if (bn::keypad::l_held() && bn::keypad::r_held() && bn::keypad::start_pressed()) {
                    SceneManager::Quit();
                }
                
                GameObject::UpdateAll();
                GameObject::DrawAll();
                bn::core::update();
            }
        }
        
        GameObject::UpdateAll();
        GameObject::DrawAll();
        bn::core::update();
    }
    
    for (auto i : dice) {
        delete i;
    }
    SceneManager::Unload();
}

#endif
