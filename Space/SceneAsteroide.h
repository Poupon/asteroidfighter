#ifndef _SceneAsteroide_h
#define _SceneAsteroide_h


#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Sprite3dObj.h>

#include <Space/AsteroidesMaker.h>

#include <Space/Scene.h>

//**************************************
class SceneAsteroide : public Scene
{
	EnumAsteroides cTypeAsteroide;
	
	AutoPtr<O3dObjProps> caPropsGen;
	AutoPtr<T3dTexture>  caGenTexture;

public:
	SceneAsteroide(const char* pName,  EnumAsteroides pTypeAsteroide, int pHardness, Double3 & lPos, float  pInterval, float pH, float pV);
	virtual~SceneAsteroide();

	virtual GLboolean animate();
	virtual GLboolean leaveWorld();

	static SceneAsteroide *TheSceneAsteroide;
};
//**************************************

#endif

