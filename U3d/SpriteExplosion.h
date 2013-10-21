#ifndef h_SpriteExplosion_h
#define h_SpriteExplosion_h

#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Sprite3d.h>

//***************************

class SpriteExplosion : public Sprite3d
{
public:
	SpriteExplosion( float pRadius, float pLifeTime, float pDestroy=0.0 );
	virtual void drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps);	

	static AutoPtr<O3dObjProps> caExplosionProps;
	static AutoPtr<O3dObjProps> caExplosionPlasmaProps;



	static void Init();
};
//***************************


#endif
