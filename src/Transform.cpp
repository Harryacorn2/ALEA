#ifndef TRANSFORM_CPP
#define TRANSFORM_CPP

#include "Transform.h"

Transform::Transform() : mBufferedMatrix(Matrix3::Identity), mTranslation(Vector2(0, 0)) {}

Transform::Transform(Vector2 translation) : mBufferedMatrix(Matrix3::CreateTranslation(translation)), mTranslation(translation) {}

bn::fixed Transform::GetScale() const { return mScale; }
bn::fixed Transform::GetRotation() const { return mRotation; }
Vector2 Transform::GetTranslation() const { return mTranslation; }

void Transform::SetScale(bn::fixed scale) {
	mScale = scale;
	mMatrixIsCurrent = false;
}

void Transform::SetRotation(bn::fixed rotation) {
	mRotation = In360(rotation);
	mMatrixIsCurrent = false;
}

void Transform::SetTranslation(Vector2 translation) {
	mTranslation = translation;
	mMatrixIsCurrent = false;
}

Matrix3 Transform::GetMatrix() {
	if (mMatrixIsCurrent) return mBufferedMatrix;
	
	auto retVal = Matrix3::CreateScale(mScale);
	retVal *= Matrix3::CreateRotation(mRotation);
	retVal *= Matrix3::CreateTranslation(mTranslation);
	
	mBufferedMatrix = retVal;
	
	return mBufferedMatrix;
}

#endif
