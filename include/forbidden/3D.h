#include "bn_core.h"
#include "bn_point.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_sprite_item.h"
#include "bn_sprite_affine_mat_ptr.h"
#include "bn_affine_mat_attributes.h"

#include "engineMath.h"

class Triangle {
public:
	Triangle(const bn::sprite_item& sprite_item, const Vector3& p0, const Vector3& p1, const Vector3& p2) :
	mSprite(sprite_item.create_sprite(0, 0)),
	mSpriteAffineMat(bn::sprite_affine_mat_ptr::create()),
	mP0(p0),
	mP1(p1),
	mP2(p2),
	mHalfSize(sprite_item.shape_size().width() / 2)
	{
		mSprite.set_affine_mat(mSpriteAffineMat);
		Draw();
	}
	
	void Draw() {
		int x0 = mP0.x;
		int y0 = mP0.y;
		int x1 = mP1.x;
		int y1 = mP1.y;
		int x2 = mP2.x;
		int y2 = mP2.y;
		int affine_divisor = x0*y1 - x0*y2 - x1*y0 + x1*y2 + x2*y0 - x2*y1;
		
		if(!affine_divisor)
		{
			mSprite.set_visible(false);
			return;
		}
		
		int pa = (-512*mHalfSize*y1 + 512*mHalfSize*y2 + 256*y1 - 256*y2) / affine_divisor;
		int pb = (256*(2*mHalfSize*x1 - 2*mHalfSize*x2 - x1 + x2)) / affine_divisor;
		int pc = (-512*mHalfSize*y0 + 512*mHalfSize*y1 + 256*y0 - 256*y1) / affine_divisor;
		int pd = (256*(2*mHalfSize*x0 - 2*mHalfSize*x1 - x0 + x1)) / affine_divisor;
		bn::affine_mat_attributes attributes;
		attributes.unsafe_set_register_values(pa, pb, pc, pd);
		mSpriteAffineMat.set_attributes(attributes);
		
//		mSpriteAffineMat.set_attributes(attributes);
		mSprite.set_position(bn::fixed_point(mP0.x, mP0.y));
	}
	
private:
	bn::sprite_ptr mSprite;
	bn::sprite_affine_mat_ptr mSpriteAffineMat;
	Vector3 mP0;
	Vector3 mP1;
	Vector3 mP2;
	int mHalfSize;
};