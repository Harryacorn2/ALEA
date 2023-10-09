#ifndef SCENE_MANAGER_CPP
#define SCENE_MANAGER_CPP

#include "SceneManager.h"
#include "bn_sprite_text_generator.h"
#include "common/common_info.h"
#include "common/common_variable_8x8_sprite_font.h"
#include "bn_sprite_items_d4.h"
#include "bn_sprite_items_d6.h"
#include "bn_sprite_items_d8.h"
#include "bn_sprite_items_digits.h"

#include "TextLine.h"
#include "Animator.h"

bool SceneManager::mUnloadFlag = false;
bn::regular_bg_ptr* SceneManager::mGlobalBackground = NULL;

void SceneManager::Quit() {
	mUnloadFlag = true;
}

void SceneManager::Unload() {
	GameObject::mAll.clear();
	mUnloadFlag = false;
}

void SceneManager::FifteenDice() {
	int arraySize = 15;
	int horizontalInteriorSize = 140;
	int maxDicePerRow = 5;
	int spacing = horizontalInteriorSize/(arraySize-1);
	if (arraySize > maxDicePerRow) spacing = horizontalInteriorSize/(maxDicePerRow-1);
	bn::vector<Die*, MAX_SPRITES> allDice;
	
	bn::fixed_point position(bn::fixed(-horizontalInteriorSize/2), bn::fixed(0));
	if (arraySize > maxDicePerRow) {
		for (int i = 0; i < arraySize / (maxDicePerRow + 1); i++) {
			position -= bn::fixed_point(bn::fixed(0), bn::fixed(spacing / 2));
		}
	}
	
	for (int i = 0; i < arraySize; i++) {
		allDice.push_back(new D6(2, position, i%5));
		allDice[i]->SetScale(bn::fixed(2));
		position += bn::fixed_point(bn::fixed(spacing), bn::fixed(0));
		allDice[i]->Update();
		
		if ((i+1) % maxDicePerRow == 0 && i != 1) {
			position += bn::fixed_point(bn::fixed(-horizontalInteriorSize - spacing), bn::fixed(spacing));
		}
	}
	
	int toggle = arraySize;
	
	while(!SceneManager::mUnloadFlag) {
		if (bn::keypad::start_pressed()) {
			for(int i = 0; i < arraySize; i++) {
				allDice[i]->Roll();
			}
			toggle = 0;
			
			
			
		} else if (bn::keypad::a_pressed() || bn::keypad::b_pressed()) {
			if (toggle < arraySize) {
				allDice[toggle]->Stop();
				toggle++;
			}
			
		} else if (bn::keypad::select_pressed()) {
			SceneManager::Quit();
			//			for(int i = 0; i < arraySize; i++) {
			//				allDice[i]->Reset();
			//			}
			//			toggle = arraySize;
		}
		
		GameObject::UpdateAll();
		GameObject::DrawAll();
		bn::core::update();
	}
	
	for (auto die : allDice) {
		delete die;
	}
	SceneManager::Unload();
}

void SceneManager::RotatingDice() {
	auto blank = GameObject();
	auto blank2 = GameObject();
	
	blank.SetPosition(-32, 0);
	blank2.SetPosition(32, 0);
	
	auto die1 = D6(10);
	auto die2 = D6(10);
	auto die3 = D6(10);
	auto die4 = D6(10);
	auto die5 = D6(10);
	auto die6 = D6(10);
	auto die7 = D6(10);
	
	die1.SetPosition(32, 0);
	die2.SetPosition(-32, 0);
	die3.SetPosition(0, 32);
	die4.SetPosition(0, -32);
	
	die5.SetPosition(32, 0);
	die6.SetPosition(0, 32);
	die7.SetPosition(0, -32);
	
	die1.SetParent(&blank);
	die2.SetParent(&blank);
	die3.SetParent(&blank);
	die4.SetParent(&blank);
	
	die5.SetParent(&blank2);
	die6.SetParent(&blank2);
	die7.SetParent(&blank2);
	
	die1.Update();
	die1.Roll();
	die2.Update();
	die2.Roll();
	die3.Update();
	die3.Roll();
	die4.Update();
	die4.Roll();
	die5.Update();
	die5.Roll();
	die6.Update();
	die6.Roll();
	die7.Update();
	die7.Roll();
	
	while(!SceneManager::mUnloadFlag) {
		blank.SetRotation(blank.GetRotation() + 5);
		blank2.SetRotation(blank2.GetRotation() + 5);
		
		if (bn::keypad::up_held()) {
			//			blank.SetPosition(blank.GetPosition() + bn::fixed_point(bn::fixed(1), bn::fixed(0)));
		}
		
		if (bn::keypad::down_held()) {
			//			blank.SetPosition(blank.GetPosition() + bn::fixed_point(bn::fixed(-1), bn::fixed(0)));
		}
		
		if (bn::keypad::left_held()) {
			//			blank.SetRotation(blank.GetRotation() - 5);
		}
		
		if (bn::keypad::right_held()) {
			//			blank.SetRotation(blank.GetRotation() + 5);
		}
		
		if (bn::keypad::select_pressed()) {
			SceneManager::Quit();
		}
		
		GameObject::UpdateAll();
		GameObject::DrawAll();
		bn::core::update();
	}
	
	SceneManager::Unload();
}

void SceneManager::AnimationDemo() {
	// Setup Here
	auto die = D6(10);
	Animator* anim = die.AddAnimator();
	
	anim->AddAnimation(new Lerp(Vector2(64, -64), 20, 30));
	anim->AddAnimation(new Lerp(Vector2(64, 64), 20, 0));
	anim->AddAnimation(new Lerp(Vector2(-64, 64), 20, 0));
	anim->AddAnimation(new Lerp(Vector2(-64, -64), 20, 0));
	anim->AddAnimation(new Lerp(Vector2(64, -64), 20, 0));
	anim->AddAnimation(new Lerp(Vector2(0, 0), 20, 0));
	die.Roll();
	die.Update();
	
	while(!SceneManager::mUnloadFlag) {
		
		// Main gameloop here
		
		if (bn::keypad::select_pressed()) {
			SceneManager::Quit();
		}
		
		GameObject::UpdateAll();
		GameObject::DrawAll();
		bn::core::update();
	}
	
	SceneManager::Unload();
}

void SceneManager::TextDemo() {
	// Setup Here
	TextLine text("Hello");
	text.SetPosition(10, 0);
	D6 die = D6();
	
	text.SetParent(&die);
//	bn::sprite_text_generator text_generator(common::variable_8x8_sprite_font);
//	bn::vector<bn::sprite_ptr, 16> text_sprites;
//	text_generator.generate(0, 0, "Hello I'm aviel", text_sprites);
	
	
	
	while(!SceneManager::mUnloadFlag) {
		
		// Main gameloop here
		
		if (bn::keypad::up_held()) {
			die.SetRotation(die.GetRotation() + bn::fixed(5));
//			text.SetPosition(text.GetPosition() + Vector2(0, -1));
		}
		
		if (bn::keypad::down_held()) {
			die.SetRotation(die.GetRotation() - bn::fixed(5));
//			text.SetPosition(text.GetPosition() + Vector2(0, 1));
		}
		
		if (bn::keypad::left_held()) {
			die.SetPosition(die.GetPosition() + Vector2(-1, 0));
		}
		
		if (bn::keypad::right_held()) {
			die.SetPosition(die.GetPosition() + Vector2(1, 0));
		}
		
		if (bn::keypad::a_pressed()) {
			text.SetText("My Name Is Aviel!");
		}
		
		if (bn::keypad::b_pressed()) {
			text.SetText("My Name Is Edgar!");
		}
		
		if (bn::keypad::select_pressed()) {
			SceneManager::Quit();
		}
		
		GameObject::UpdateAll();
		GameObject::DrawAll();
		bn::core::update();
	}
	
	SceneManager::Unload();
}

#endif
