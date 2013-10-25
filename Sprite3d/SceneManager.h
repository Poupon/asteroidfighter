#ifndef h_SceneManager_h
#define h_SceneManager_h

#include <Sprite3d/Sprite3d.h>
#include <Sprite3d/Action.h>


// **************************************

class SceneManager : public Action, public Sprite3dDeleteControler
{
public:
	enum GameFinish{ GameContinue=0, GameOver=1, GameWinner=2 };

protected:
	std::vector<Sprite3d*> cSceneVect;
	unsigned int cCurScene;
	char cStrInfo[512];

	World* cWorld;

public:
	SceneManager();
	virtual~SceneManager();

     void write( std::ostream & pOs);
     bool read( std::istream & pIs );
    void saveStateToFile( const char* pName );

	void go(World*pWorld);
	void addScene( Sprite3d* pSprite, float pLiveTime=-1 );
	void addSceneTempo( float pLiveTime, GameFinish cGameFinish=GameContinue );
	void setCurrentSceneTempo( float pLiveTime, GameFinish cGameFinish=GameContinue );
	int endScene();
	void resetCurrentSceneFromBegin( Sprite3dPilot* pPilot );

	virtual GLboolean leaveWorld( Sprite3d &pMySprite, void*pParam );
	virtual GLboolean kill( Sprite3d &pMySprite, void*pParam );
	void execDelete( Sprite3d* pToDel );

	int getCurrentSceneIndex() { return cCurScene; }
	Sprite3d* getCurrentScene() {return cSceneVect[cCurScene]; }
	int getNbScene() { return cSceneVect.size(); }

	const char* getInfoScene();
};
// **************************************

#endif
