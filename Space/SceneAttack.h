#ifndef _SceneAttack_h
#define _SceneAttack_h


#include <Sprite3d/AutoPtr.h>


#include <Sprite3d/Sprite3dObj.h>

#include <Space/Scene.h>


//**************************************
class SceneAttack : public Scene
{
	
	AutoPtr<O3dObjProps> caPropsGen;
	AutoPtr<T3dTexture>  caGenTexture;

public:
	SceneAttack( const char* pName, int pHardness, Double3 & lPos, float  pInterval, float pH, float pV);
	virtual~SceneAttack();

	virtual GLboolean animate();
};
//**************************************

#endif

