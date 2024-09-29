#include "SceneManager.h"
#include "TextLine.h"
#include "Animator.h"
#include "Animation.h"
#include "Crane.h"

#include "Profiler.h"

void SceneManager::EllipseTest() {
    TextLine title("ALEA", yobani_fixed_16x16_sprite_font);
    title.AlignCenter();
    title.SetScale(2);
    title.SetZOrder(0);
    
    title.GetAnimator()->AddAnimation(new Bob(Vector2(0, 4), 199));
    
    bn::fixed diePositions[6] = {0.25, 0.41666, 0.58333, .75, 0.91666, 0.08333}; // starts with d20 at the bottom and goes clockwise
    
    Die* dieArray[6];
    dieArray[5] = new D4(0, Vector2(0, 0), 4);
    dieArray[4] = new D6(0, Vector2(0, 0), 6);
    dieArray[3] = new D8(0, Vector2(0, 0), 8);
    dieArray[2] = new D10(0, Vector2(0, 0), 10);
    dieArray[1] = new D12(0, Vector2(0, 0), 12);
    dieArray[0] = new D20(0, Vector2(0, 0), 20);
    
    Ellipse dicePath(160, 40);
    dicePath.mPosition = Vector2(0, 0);
    
    bn::fixed maxScale = 1;
    bn::fixed minScale = 0.3;
    bn::fixed rotationSpeed = 0.003; // Higher # is faster
    
    // No button pressed idle
    for (int i = 0; i < 6; i++) {
        dieArray[i]->SetPosition(dicePath.GetPointOnEllipse(diePositions[i]));
    }
    
    auto RotateDice = [&]() {
        for (int i = 0; i < 6; i++) {
            diePositions[i] += rotationSpeed;
            if (diePositions[i] > 1) diePositions[i] = 0;
            
            Vector2 pos = dicePath.GetPointOnEllipse(diePositions[i]);
            
            dieArray[i]->SetPosition(pos);
            bn::fixed v = ((pos.y) + (dicePath.mHeight/2)) / dicePath.mHeight; // Represents vertical element 0-1
            bn::fixed scaleDifference = maxScale - minScale;
            bn::fixed scale = (scaleDifference * v) + minScale;
            
            dieArray[i]->SetScale(scale);
            dieArray[i]->GetSprite()->SetZOrder(-(pos.y).floor_integer());
        }
    };
    
    auto ShrinkRing = [&]() {
        rotationSpeed += 0.0003;
        dicePath.mWidth -= 1;
        minScale += 0.003;
        if (minScale > .52) minScale = .52;
//        dicePath.mHeight -= 0.5;
    };
    
    bool notStarted = true;
    
    while (notStarted) {
        PROFILE_CONTROL();
        PROFILE_SCOPE(Frame);
        
        Profiler::StartEvent("Rotate Dice");
        RotateDice();
        Profiler::EndEvent();
        
        GameObject::UpdateAll();
        GameObject::DrawAll();
        
        PROFILE_SCOPE(Butano);
        bn::core::update();
        
        if (bn::keypad::start_pressed()) {
            notStarted = false;
        }
    }
    
    title.GetAnimator()->ClearAllAnimations();
    title.GetAnimator()->AddAnimation(new EaseOut(Vector2(0, 10), 10));
    title.GetAnimator()->AddAnimation(new EaseIn(Vector2(0, -100), 50));
    
    for (int i = 60; i > 0; i--) {
        ShrinkRing();
        RotateDice();
        
        GameObject::UpdateAll();
        GameObject::DrawAll();
        bn::core::update();
    }
    
    // Align
    bool aligning = true;
    
    while(aligning) {
        if (diePositions[0] <= .25 && diePositions[0] + rotationSpeed >= .25) {
            diePositions[0] = 0.25;
            diePositions[1] = 0.41666;
            diePositions[2] = 0.58333;
            diePositions[3] = .75;
            diePositions[4] = 0.91666;
            diePositions[5] = 0.08333;
            rotationSpeed = 0;
            
            aligning = false;
        }
        
        ShrinkRing();
        RotateDice();
        
        GameObject::UpdateAll();
        GameObject::DrawAll();
        bn::core::update();
    }
    
    int frames = 15;
    
    dieArray[0]->GetAnimator()->AddAnimation(new EaseOutAndScale(Vector2(0, Crane::mFrontHeight), 1, frames));
    dieArray[1]->GetAnimator()->AddAnimation(new EaseOutAndScale(Vector2(-Crane::mCloseWidth, Crane::mCloseHeight), 0.78125, frames));
    dieArray[2]->GetAnimator()->AddAnimation(new EaseOutAndScale(Vector2(-Crane::mFarWidth, Crane::mFarHeight), 0.59375, frames));
    dieArray[3]->GetAnimator()->AddAnimation(new EaseOutAndScale(Vector2(0, Crane::mBackHeight), .52, frames));
    dieArray[4]->GetAnimator()->AddAnimation(new EaseOutAndScale(Vector2(Crane::mFarWidth, Crane::mFarHeight), 0.59375, frames));
    dieArray[5]->GetAnimator()->AddAnimation(new EaseOutAndScale(Vector2(Crane::mCloseWidth, Crane::mCloseHeight), 0.78125, frames));
    
    while(frames > 0 || !title.GetAnimator()->GetAnimations().empty()) {
        frames--;
        GameObject::UpdateAll();
        GameObject::DrawAll();
        bn::core::update();
    }
    
    for (int i = 0; i < 6; i++) {
        delete dieArray[i];
    }
}
