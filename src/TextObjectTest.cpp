#include "SceneManager.h"
#include "TextLine.h"
#include "Log.h"

void SceneManager::TextObjectTest() {
    TextLine textLine("Hello", yobani_variable_8x8_sprite_font);
    textLine.AlignCenter();
    textLine.SetOneSpritePerChar(true);
    
    while (true) {
        if (bn::keypad::up_held()) {
            textLine.SetPosition(textLine.GetPosition() + Vector2(0, -1));
        }
        
        if (bn::keypad::down_held()) {
            textLine.SetPosition(textLine.GetPosition() + Vector2(0, 1));
        }
        
        if (bn::keypad::left_held()) {
            textLine.SetPosition(textLine.GetPosition() + Vector2(-1, 0));
        }
        
        if (bn::keypad::right_held()) {
            textLine.SetPosition(textLine.GetPosition() + Vector2(1, 0));
        }
        
        if (bn::keypad::r_held()) {
            textLine.SetRotation(textLine.GetRotation() + 1);
        }
        
        if (bn::keypad::l_held()) {
            textLine.SetRotation(textLine.GetRotation() - 1);
        }
        
        if (bn::keypad::a_held()) {
            textLine.SetScale(textLine.GetScale() + 0.01);;
        }
        
        if (bn::keypad::b_held()) {
            textLine.SetScale(textLine.GetScale() - 0.01);
        }
        
        GameObject::UpdateAll();
        GameObject::DrawAll();
        bn::core::update();
    }
}
