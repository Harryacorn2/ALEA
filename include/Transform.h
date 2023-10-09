#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "engineMath.h"

class Transform {
public:
	Transform();
    Transform(Vector2 translation);
	
	bn::fixed GetScale() const;
	bn::fixed GetRotation() const;
	Vector2 GetTranslation() const;
	
	void SetScale(bn::fixed scale);
	void SetRotation(bn::fixed rotation);
	void SetTranslation(Vector2 translation);
	
	Matrix3 GetMatrix();
	
private:
	Matrix3 mBufferedMatrix;
	bn::fixed mRotation = 0;
	bn::fixed mScale = 1;
	Vector2 mTranslation;
	
	bool mMatrixIsCurrent = false;
};

#endif
