#ifndef _SceneArtifice_h
#define _SceneArtifice_h


#include <Sprite3d/AutoPtr.h>


#include <Sprite3d/Sprite3dObj.h>
#include <Sprite3d/Action.h>


//**************************************
class SceneArtifice : public Sprite3dObj, public Action
{
	float cInterval;
	int   cH;
	float cV;
	
	AutoPtr<O3dObjProps> caPropsGen;
	AutoPtr<T3dTexture>  caGenTexture;
	int cHardness;
public:
	SceneArtifice( int pHardness, Double3 & lPos, float  pInterval, float pH, float pV);
	virtual~SceneArtifice();

	virtual GLboolean animate();
	virtual GLboolean leaveWorld();
    virtual GLboolean kill( Sprite3d &pMySprite, void*pParam );
};
//**************************************

#endif
