#ifndef SELECTANY_CPP
#define SELECTANY_CPP

#include "SceneManager.h"
#include "TextLine.h"
#include "Crane.h"
#include "Die.h"
#include "DieRoll.h"
#include "Log.h"
#include "Random.h"

#include "bn_string.h"

void Halt(int i) {
    while (i > 0) {
        GameObject::UpdateAll();
        GameObject::DrawAll();
        bn::core::update();
        i--;
    }
}

void SceneManager::SelectAny() {
    // MARK: - Title Phase
    
    TextLine score("ALEA", yobani_variable_8x8_sprite_font);
    
    score.SetPosition(0, -65);
    score.AlignCenter();
    score.SetZOrder(10000);
    
    // TODO: Reset after roll
     
    while (true) {
        
        // MARK: - Die Selection Phase
        RollVector rollVector;
        
        {
            Crane crane;
            bool selectionMade = false;
            
            while (!selectionMade) {
                if (bn::keypad::right_pressed()) {
                    crane.RotateRight();
                }
                
                if (bn::keypad::left_pressed()) {
                    crane.RotateLeft();
                }
                
                if (bn::keypad::up_pressed()) {
                    crane.IncrementSelected();
                }
                
                if (bn::keypad::down_pressed()) {
                    crane.DecrementSelected();
                }
                
                if (bn::keypad::start_pressed()) {
                    rollVector = crane.Seperate();
                    if (rollVector.size() > 0) {
                        selectionMade = true;
                    }
                }
                
                // Reroll seed every frame during selection
                Random::GetLong();
                GameObject::UpdateAll();
                GameObject::DrawAll();
                bn::core::update();
            }
            
            int waitFor = 60;
            
            while (waitFor > 0) {
                waitFor--;
                
                if (bn::keypad::start_pressed()) {
                    crane.Skip();
                    waitFor = 0;
                }
                
                GameObject::UpdateAll();
                GameObject::DrawAll();
                bn::core::update();
            }
        }
        
        // MARK: - Rolling Phase
        DieRoll dieRoll(rollVector);
        
        // Roll dice
        int frameCounter = 10;
        int dieCounter = 0;
        while (dieCounter < dieRoll.GetDieCount()) {
            if (frameCounter > 0) {
                frameCounter--;
            } else {
                dieRoll.RollOne();
                frameCounter = 10;
                dieCounter++;
            }
            
            if (bn::keypad::start_pressed()) {
                dieRoll.RollAll();
                dieCounter = dieRoll.GetDieCount();
            }
            
            GameObject::UpdateAll();
            GameObject::DrawAll();
            bn::core::update();
        }
        
        score.SetText("000000");
        
        bool FinishedManuallyStopping = false;
        bool FinishedStopping = false;
        
        // MARK: - Stopping Phase
        
        // Stopping Manually
        while (!FinishedManuallyStopping) {
            
            if (bn::keypad::a_pressed() || bn::keypad::b_pressed()) {
                RollResult result = dieRoll.StopOne();
                score.SetText(bn::to_string<6>(dieRoll.GetRolledValue()));
                
                if (result.type == 0) {
                    bn::sound_items::good.play(1);
                } else if (result.type == 1) {
                    bn::sound_items::great.play(1);
                } else {
                    bn::sound_items::excelent.play(1);
                }
                
                if (dieRoll.IsFinishedStopping()) {
                    FinishedManuallyStopping = true;
                    FinishedStopping = true;
                }
            }
            
            if (bn::keypad::start_pressed()) {
                FinishedManuallyStopping = true;
            }
            
            GameObject::UpdateAll();
            GameObject::DrawAll();
            bn::core::update();
        }
        
        // Optional Automatic Rolling
        frameCounter = 0;
        while (!FinishedStopping) {
            if (frameCounter > 0) {
                frameCounter--;
                
            } else {
                RollResult result = dieRoll.StopOne();
                score.SetText(bn::to_string<6>(dieRoll.GetRolledValue()));
                
                if (result.type == 0) {
                    bn::sound_items::good.play(1);
                    frameCounter = 15;
                    
                } else if (result.type == 1) {
                    bn::sound_items::great.play(1);
                    frameCounter = 25;
                    
                } else {
                    bn::sound_items::excelent.play(1);
                    frameCounter = 35;
                }
            }
            
            if (bn::keypad::start_pressed()) {
                dieRoll.StopAll();
                int total = dieRoll.GetRolledValue();
                score.SetText(bn::to_string<6>(total));
                
                if (total >= dieRoll.GetGoodRoll()) {
                    bn::sound_items::excelent.play(1);
                    
                } else if (total > dieRoll.GetAverageRoll()) {
                    bn::sound_items::great.play(1);
                    
                } else {
                    bn::sound_items::good.play(1);
                }
                
                FinishedStopping = true;
            }
            
            if (dieRoll.IsFinishedStopping()) {
                FinishedStopping = true;
            }
            
            GameObject::UpdateAll();
            GameObject::DrawAll();
            bn::core::update();
        }
        
        bool FinishedViewing = false;
        while (!FinishedViewing) {
            
            if (bn::keypad::start_pressed()) {
                FinishedViewing = true;
            }
            
            GameObject::UpdateAll();
            GameObject::DrawAll();
            bn::core::update();
        }
    }
}

#endif
