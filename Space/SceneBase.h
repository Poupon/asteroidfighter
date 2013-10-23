#ifndef _SceneBase_h
#define _SceneBase_h


#include <Sprite3d/AutoPtr.h>


#include <Sprite3d/Sprite3dObj.h>

#include <Space/Scene.h>


//**************************************
class SceneBase : public Scene
{	
	AutoPtr<O3dObjProps> caPropsGen;
	AutoPtr<T3dTexture>  caGenTexture;
    int cShipType;
public:
	SceneBase( const char* pName, int pHardness, Double3 & lPos, float  pInterval, float pH, float pV,
               int pShipType);
	virtual~SceneBase();

	virtual GLboolean animate();
	virtual GLboolean leaveWorld();
};
//**************************************

#endif
