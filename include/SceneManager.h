#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "global.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_bg.h"
#include "bn_random.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "Die.h"

class SceneManager {
public:
	static void Init() {
		mGlobalBackground = new bn::regular_bg_ptr(bn::regular_bg_items::bg.create_bg(0, 0));
	}
	
	static void FifteenDice();
	static void RotatingDice();
	static void AnimationDemo();
	static void TextDemo();
	static void ShapeTest();
    static void TextObjectTest();
    static void SRAMTest();
    
    static void SelectD6();
    static void SelectAny();
	
	static void Quit();
	static void Unload();
	
	static bool mUnloadFlag;
	
    static bn::random mRand;
    
private:
	static bn::regular_bg_ptr* mGlobalBackground;
};

#endif
