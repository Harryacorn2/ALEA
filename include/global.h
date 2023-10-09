#ifndef GLOBAL_H
#define GLOBAL_H

#include "bn_core.h"
#include "bn_vector.h"

#define MAX_SPRITES 128
#define MAX_ROLLABLE_DICE 15

#define uint unsigned int
//#define short short int

typedef bn::vector<uint, MAX_ROLLABLE_DICE> RollVector;

#endif
