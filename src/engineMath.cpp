#include "engineMath.h"

bn::fixed In360(bn::fixed rotation) {
	if (rotation > 360) {
		return rotation - ((rotation/bn::fixed(360)).integer() * bn::fixed(360));
		
	} else if (rotation < 0) {
		bn::fixed x = (((bn::abs(rotation)/bn::fixed(360)).integer() + 1) * bn::fixed(360));
		return (rotation + x);
	}
	
	return rotation;
}

static bn::fixed m3Ident[3][3] =
{
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
};

const Matrix3 Matrix3::Identity(m3Ident);

bn::fixed LerpFixed(bn::fixed a, bn::fixed b, bn::fixed t) {
    return a + ((b - a) * t);
}
