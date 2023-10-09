#include "SceneManager.h"
#include "TextLine.h"
#include "bn_sram.h"

struct SRAMData {
    int formatTag;
    short previousRolls[64];
};

void SceneManager::SRAMTest() {
    TextLine score("Checking data", yobani_variable_8x8_sprite_font);
    score.AlignCenter();
    
    GameObject::UpdateAll();
    GameObject::DrawAll();
    bn::core::update();
    
    SRAMData data;
    bn::sram::read(data);
    
    GameObject::UpdateAll();
    GameObject::DrawAll();
    bn::core::update();
    
    if (data.formatTag == 12345678) {
        score.SetText("Data is formatted");
        
    } else {
        score.SetText(bn::to_string<64>(bn::sram::size()));
        data.formatTag = 12345678;
        bn::sram::clear(bn::sram::size());
        bn::sram::write(data);
    }
    
    while (true) {
        
        
        
        GameObject::UpdateAll();
        GameObject::DrawAll();
        bn::core::update();
    }
}
