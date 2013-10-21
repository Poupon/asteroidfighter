#ifndef h_Collision_h
#define h_Collision_h

#include <vector>

#include <Sprite3d/World.h>

class Sprite3d;

typedef std::vector < Sprite3d *> VSprite3d; // redefinition


//**************************************
class Collision
{	
	VSprite3d** cTab;
	float      cMul;
	int        cDim;
	int        cNbDiv;

	int        cPosIter;
	float      cMin;

public:
	Collision( int pDim, GLdouble pMin, GLdouble pMax, int pNbDiv );
	virtual ~Collision();

protected:
	void set( Sprite3d *pSprite);
	void set( VSprite3d& vSprite  );
	void add( int pPos, Sprite3d *pSprite ); 
	VSprite3d* next();

public:

	static void      SpatialDetection(  VSprite3d& pVSprite, int *pDim, GLdouble *pMin, GLdouble *pMax, int *pNbDiv, int pNbDim );
	static void      SimpleDetection(VSprite3d& pVSprite);
	static GLboolean DetectCollision( Sprite3d &A, Sprite3d &B );
};
//**************************************


#endif
