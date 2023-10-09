#include "3D.h"
#include "bn_vector.h"
#include "engineMath.h"

class RenderObj {
public:
	RenderObj();
	virtual ~RenderObj();
	virtual void Draw();
	
	Matrix4 mModelToWorld;
	
protected:
	bn::vector<Triangle> mPolygons;
};

class RenderCube : public RenderObj {
public:
	RenderCube();
	~RenderCube();
};