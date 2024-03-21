#include "global.h"
#include "SceneManager.h"

int main()
{ 
    
    bn::core::init();
    SceneManager::Init();
    
    while (true) {
//        SceneManager::AnimationDemo();
//        SceneManager::RotatingDice();
//        SceneManager::FifteenDice();
//        SceneManager::TextDemo();
//        SceneManager::ShapeTest();
//        SceneManager::TextObjectTest();
//        SceneManager::SRAMTest();
        SceneManager::EllipseTest();
        
//        SceneManager::SelectD6();
        SceneManager::SelectAny();
    }
}
