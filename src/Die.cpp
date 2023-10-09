#ifndef DIE_CPP
#define DIE_CPP

#include "Die.h"
#include "bn_span.h"
#include "bn_color.h"

//bn::random Die::gRand = bn::random();

// Die base class
Die::Die(int speed) : mSpeed(speed) {}
Die::~Die() {}

void Die::GenerateDistribution(int dieCount, bn::vector<Vector2, MAX_ROLLABLE_DICE>& locationVector, uint spacing) {
    
    bn::vector<Vector2, MAX_ROLLABLE_DICE+1> locations;
    
	uint halfSpacing;
	halfSpacing = spacing/2;
	locations.clear();
	
	if (dieCount < 6) {
		// If even number of dice
		if (dieCount % 2 == 0) {
			Vector2 start = Vector2(0, 0);
			start += Vector2(-16 - halfSpacing, 0);
			start += Vector2((-32 - spacing) * ((dieCount-2)/2), 0);
			locations.push_back(start);
			
			// If odd number of dice
		} else {
			Vector2 start = Vector2(0, 0);
			start += Vector2((-32 - spacing) * ((dieCount-1)/2), 0);
			locations.push_back(start);
		}
		
		for (int i = 0; i < dieCount-1; i++) {
			locations.push_back(locations[i] + Vector2(32 + spacing, 0));
		}
		
		// Two Lines
	} else if (dieCount < 11) {
		uint halfCount = dieCount/2;
		
		// Top line
		Vector2 start = Vector2(0, -16 - halfSpacing);
		
		// If even number of dice on top row
		if ((dieCount - halfCount) % 2 == 0) {
			start += Vector2(-16 - halfSpacing, 0);
			start += Vector2((-32 - spacing) * ((halfCount-1)/2), 0);
			locations.push_back(start);
			
			// If odd number of dice on top row
		} else {
			start += Vector2((-32 - spacing) * (halfCount/2), 0);
			locations.push_back(start);
		}
		
		for (uint i = 0; i < halfCount-1; i++) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
		if (dieCount % 2 == 1) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
		// Bottom line
		start = Vector2(0, 16 + halfSpacing);
		
		// If even number of dice
		if (halfCount % 2 == 0) {
			start += Vector2(-16 - halfSpacing, 0);
			start += Vector2((-32 - spacing) * ((halfCount-2)/2), 0);
			locations.push_back(start);
			
			// If odd number of dice
		} else {
			start += Vector2((-32 - spacing) * ((halfCount-1)/2), 0);
			locations.push_back(start);
		}
		
		for (uint i = 0; i < halfCount-1; i++) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
		// Up to 15 dice
	} else if (dieCount == 11) {
		locations.push_back(Vector2(-32 - spacing, -32 - spacing));
		
		for (uint i = 0; i < 2; i++) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
		locations.push_back(Vector2(-64 -(spacing*2), 0));
		
		for (uint i = 0; i < 4; i++) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
		locations.push_back(Vector2(-32 - spacing, 32 + spacing));
		
		for (uint i = 0; i < 2; i++) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
	} else if (dieCount == 12) {
		Vector2 start = Vector2(-16 - halfSpacing, -32 - spacing);
		start += Vector2(-32 - spacing, 0);
		locations.push_back(start);
		
		for (int r = 0; r < 3; r++) {
			for (uint i = 0; i < 3; i++) {
				locations.push_back(locations.back() + Vector2(32 + spacing, 0));
			}
			start += Vector2(0, 32 + spacing);
			locations.push_back(start);
		}
		locations.pop_back();
		
	} else if (dieCount == 13) {
		Vector2 start = Vector2(-16 - halfSpacing, -32 - spacing);
		start += Vector2(-32 - spacing, 0);
		locations.push_back(start);
		
		for (uint i = 0; i < 3; i++) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
		locations.push_back(Vector2(-64 -(spacing*2), 0));
		
		for (uint i = 0; i < 4; i++) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
		locations.push_back(start + Vector2(0, 64 + (spacing*2)));
		
		for (uint i = 0; i < 3; i++) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
	} else if (dieCount == 14) {
		Vector2 start = Vector2(-64 -(spacing*2), -32 - spacing);
		locations.push_back(start);
		
		for (uint i = 0; i < 4; i++) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
		Vector2 four = Vector2(-16 - halfSpacing, 0);
		four += Vector2(-32 - spacing, 0);
		locations.push_back(four);
		
		for (uint i = 0; i < 3; i++) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
		locations.push_back(start + Vector2(0, 64 + (spacing*2)));
		
		for (uint i = 0; i < 4; i++) {
			locations.push_back(locations.back() + Vector2(32 + spacing, 0));
		}
		
	} else {
		Vector2 start = Vector2(-64 -(spacing*2), -32 - spacing);
		locations.push_back(start);
		
		for (int r = 0; r < 3; r++) {
			for (uint i = 0; i < 4; i++) {
				locations.push_back(locations.back() + Vector2(32 + spacing, 0));
			}
			start += Vector2(0, 32 + spacing);
			locations.push_back(start);
		}
		locations.pop_back();
	}
    
    locationVector.clear();
    for (int i = 0; i < locations.size(); i++) {
        locationVector.push_back(locations[i]);
    }
}

#endif
