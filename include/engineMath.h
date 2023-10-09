#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

#include "bn_core.h"
#include "bn_math.h"
#include "bn_fixed_point.h"
#include "bn_fixed.h"
#include "bn_cstring.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_affine_mat_ptr.h"
#include "bn_affine_mat_attributes.h"

bn::fixed In360(bn::fixed rotation);

class Vector2 {
public:
    
    Vector2(bn::fixed X, bn::fixed Y) : x(X), y(Y) {};
    Vector2(bn::fixed_point xy) : x(xy.x()), y(xy.y()) {};
    
	bn::fixed x;
	bn::fixed y;
	
	static bn::fixed Dot(const Vector2& lhs, const Vector2& rhs) {
		return ((lhs.x * rhs.x) + (lhs.y * rhs.y));
	}
	
	bn::fixed Length() {
		return bn::sqrt(Dot(*this, *this));
	}
	
	Vector2 Lerp(Vector2 end, bn::fixed t) {
		return (*this * (1 - t)) + (end * t);
	}
	
	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
		return Vector2(lhs.x+rhs.x, lhs.y+rhs.y);
	}
	
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
		return Vector2(lhs.x-rhs.x, lhs.y-rhs.y);
	}
	
	friend Vector2 operator*(const Vector2& lhs, const bn::fixed& rhs) {
		return Vector2(lhs.x*rhs, lhs.y*rhs);
	}
	
	friend Vector2 operator/(const Vector2& lhs, const bn::fixed& rhs) {
		return Vector2(lhs.x/rhs, lhs.y/rhs);
	}
	
	void operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
	}
	
	void operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
	}
	
	void operator*=(const bn::fixed& other) {
		x *= other;
		y *= other;
	}
	
	void operator/=(const bn::fixed& other) {
		x /= other;
		y /= other;
	}
	
	bool operator==(const Vector2& other) const {
		return (x == other.x && y == other.y);
	}
	
	operator bn::fixed_point() const {
		return bn::fixed_point(bn::fixed(x), bn::fixed(x));
	}
};

class Matrix3 {
public:
	bn::fixed mat[3][3];
	
	Matrix3()
	{
		*this = Matrix3::Identity;
	}
	
	explicit Matrix3(const bn::fixed inMat[3][3])
	{
		bn::memcpy(mat, inMat, 9 * sizeof(bn::fixed));
	}
	
	// Matrix multiplication
	friend Matrix3 operator*(const Matrix3& left, const Matrix3& right)
	{
		Matrix3 retVal;
		// row 0
		retVal.mat[0][0] =
		left.mat[0][0] * right.mat[0][0] +
		left.mat[0][1] * right.mat[1][0] +
		left.mat[0][2] * right.mat[2][0];
		
		retVal.mat[0][1] =
		left.mat[0][0] * right.mat[0][1] +
		left.mat[0][1] * right.mat[1][1] +
		left.mat[0][2] * right.mat[2][1];
		
		retVal.mat[0][2] =
		left.mat[0][0] * right.mat[0][2] +
		left.mat[0][1] * right.mat[1][2] +
		left.mat[0][2] * right.mat[2][2];
		
		// row 1
		retVal.mat[1][0] =
		left.mat[1][0] * right.mat[0][0] +
		left.mat[1][1] * right.mat[1][0] +
		left.mat[1][2] * right.mat[2][0];
		
		retVal.mat[1][1] =
		left.mat[1][0] * right.mat[0][1] +
		left.mat[1][1] * right.mat[1][1] +
		left.mat[1][2] * right.mat[2][1];
		
		retVal.mat[1][2] =
		left.mat[1][0] * right.mat[0][2] +
		left.mat[1][1] * right.mat[1][2] +
		left.mat[1][2] * right.mat[2][2];
		
		// row 2
		retVal.mat[2][0] =
		left.mat[2][0] * right.mat[0][0] +
		left.mat[2][1] * right.mat[1][0] +
		left.mat[2][2] * right.mat[2][0];
		
		retVal.mat[2][1] =
		left.mat[2][0] * right.mat[0][1] +
		left.mat[2][1] * right.mat[1][1] +
		left.mat[2][2] * right.mat[2][1];
		
		retVal.mat[2][2] =
		left.mat[2][0] * right.mat[0][2] +
		left.mat[2][1] * right.mat[1][2] +
		left.mat[2][2] * right.mat[2][2];
		
		return retVal;
	}
	
	Matrix3& operator*=(const Matrix3& right)
	{
		*this = *this * right;
		return *this;
	}
	
	void Transpose()
	{
		bn::fixed temp[3][3];
		
		temp[0][0] = mat[0][0];
		temp[0][1] = mat[1][0];
		temp[0][2] = mat[2][0];
		
		temp[1][0] = mat[0][1];
		temp[1][1] = mat[1][1];
		temp[1][2] = mat[2][1];
		
		temp[2][0] = mat[0][2];
		temp[2][1] = mat[1][2];
		temp[2][2] = mat[2][2];
		
		memcpy(mat, temp, 9 * sizeof(bn::fixed));
	}
	
	// TODO: Optimize this
	// Untested change
	void ApplyToSprite(bn::sprite_ptr sprite, bool lockRotation = false) {
		Vector2 norman(mat[0][0], mat[1][0]);
		auto scale = norman.Length();
		if (scale > 0.95 && scale < 1.05) {
			scale = 1;
		}
		bn::fixed degrees = bn::degrees_atan2(mat[0][1].data(), mat[0][0].data());
		degrees = ((degrees/10)*10).integer();
		
		if (!lockRotation) sprite.set_rotation_angle(In360(-degrees));
		sprite.set_scale(scale);
		sprite.set_position(mat[2][0], mat[2][1]);
	}
	
	// Transpose the provided matrix
	friend Matrix3 Transpose(const Matrix3& inMat)
	{
		Matrix3 retVal = inMat;
		retVal.Transpose();
		return retVal;
	}
	
	// Create a scale matrix with x and y scales
	static Matrix3 CreateScale(bn::fixed xScale, bn::fixed yScale)
	{
		bn::fixed temp[3][3] =
		{
			{ xScale, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}
	
	static Matrix3 CreateScale(const Vector2& scaleVector)
	{
		return CreateScale(scaleVector.x, scaleVector.y);
	}
	
	// Create a scale matrix with a uniform factor
	static Matrix3 CreateScale(bn::fixed scale)
	{
		return CreateScale(scale, scale);
	}
	
	// Create a rotation matrix about the Z axis
	// theta is in radians
	static Matrix3 CreateRotation(bn::fixed theta)
	{
		theta = In360(theta);
		bn::fixed temp[3][3] =
		{
			{ bn::degrees_lut_cos(theta.integer()), bn::degrees_lut_sin(theta.integer()), 0.0f },
			{ -bn::degrees_lut_sin(theta.integer()), bn::degrees_lut_cos(theta.integer()), 0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}
	
	// Create a translation matrix (on the xy-plane)
	static Matrix3 CreateTranslation(const Vector2& trans)
	{
		bn::fixed temp[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ trans.x, trans.y, 1.0f },
		};
		return Matrix3(temp);
	}
	
	static Matrix3 CreateTranslation(const bn::fixed_point& trans)
	{
		bn::fixed temp[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ trans.x(), trans.y(), 1.0f },
		};
		return Matrix3(temp);
	}
	
	static const Matrix3 Identity;
	
	static bool UnitTest();
};

#endif
