#ifndef _SceneGrotte_h
#define _SceneGrotte_h


#include <Sprite3d/AutoPtr.h>


#include <Space/AsteroidesMaker.h>

#include <Space/Scene.h>

//**************************************
class SceneGrotte : public Scene
{
	float cIntervalParoi;
	int   cSizeParoi;

	GLboolean cFirstTime;

	EnumAsteroides cTypeAsteroide;
	
	AutoPtr<O3dObjProps> caPropsGen;
	AutoPtr<T3dTexture>  caGenTexture;

	void makeFloor( int pH );
	void makeArtefact();
	void makeWall(int pMin, int pMax, GLboolean pIndestructible, float pSpeed=0.0f, float pDeltaX=0.0f, float pAleaX=0.0f );
	void makeAsteroide(Double3& pPos, int pSz, GLboolean pIndestructible );

public:
	SceneGrotte( const char* pName, EnumAsteroides pTypeAsteroide, int pHardness, Double3 & lPos, float  pInterval, float  pIntervalParoi, int pSizeParoi, float pH, float pV);
	virtual~SceneGrotte();

	virtual GLboolean animate();
	virtual GLboolean leaveWorld();
	
	void      enterWorld(); 

	static SceneGrotte *TheSceneGrotte;
};
//**************************************

#endif

