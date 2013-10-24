#include <SceneManager.h>
#include <Sprite3d/WorldControler.h>

#include <Sprite3d/Scene.h>


// **************************************
SceneManager::SceneManager()
	:cCurScene(0),
	 cWorld(NULL)
{
	cStrInfo[0] = '\0';
}

//------------------------------
SceneManager::~SceneManager()
{
	/* Bug ! (les scene sont peut deja detruite ? 
	std::cout << "~SceneManager " << cSceneVect.size() << std::endl;
		for( unsigned int i=0; i<  cSceneVect.size(); i++ )
		{
			std::cout << "~SceneManager " << i << " " << cSceneVect[i]->getStrName() << std::endl;
			if( cSceneVect[i] != NULL ){
				delete cSceneVect[i];
				cSceneVect[i] = NULL;
			}
			}
		std::cout << "~SceneManager end" << std::endl;
	*/
	cSceneVect.clear();
}
//------------------------------
const char*
SceneManager::getInfoScene(){
	return cStrInfo;
}
//------------------------------
void SceneManager::addScene( Sprite3d *pSprite, float pLiveTime )
{
	pSprite->setDeleteControler(this);
	pSprite->setAction( SPRITE_ACTION_KILL,        this );
	pSprite->setAction( SPRITE_ACTION_LEAVE_WORLD, this );


	if( pLiveTime != -1 )
		pSprite->SpriteFloat::set( SPRITE_LIFETIME, pLiveTime  );


	cSceneVect.push_back( pSprite );
}
//------------------------------
// Pour laisser du temps entre deux scenes

void SceneManager::addSceneTempo( float pLiveTime, GameFinish cGameFinish )
{
	Sprite3d* lSprite = new Sprite3d(0.00001, pLiveTime);
	lSprite->setDeleteControler(this);
	lSprite->setAction( SPRITE_ACTION_KILL, this );

	lSprite->MkSetUSER5( static_cast<float>(cGameFinish ));

	cSceneVect.push_back( lSprite );
}
//------------------------------
// Pour laisser du temps entre deux scenes

void SceneManager::setCurrentSceneTempo( float pLiveTime, GameFinish cGameFinish )
{
	if( cCurScene == cSceneVect.size() )
		{
			return;
		}

	cSceneVect[cCurScene]->SpriteFloat::set( SPRITE_LIFETIME, pLiveTime );
	cSceneVect[cCurScene]->MkSetUSER5( static_cast<float>(cGameFinish ));
}
//------------------------------
// Lance la premiere scene du scenario, c'est la fin
// de la scene (kill -> endScene ) qui provoque
// l'execution de la scene suivante
// la fin de la derniere scene provoque la fin du scenario
// et donc la victoire

void
SceneManager::go(World* pWorld)
{
	sprintf( cStrInfo, "%d/%ld | %s", cCurScene, cSceneVect.size(), cSceneVect[cCurScene]->getStrInfo() );
  cSceneVect[cCurScene]->resetLife();  // remet a jour l heure de creation
  pWorld->add(cSceneVect[cCurScene]);
}
//------------------------------
void
SceneManager::resetCurrentSceneFromBegin( Sprite3dPilot* pPilot )
{
	cWorld = WorldControler::GetCurrentWorld();

	if( cWorld )
		{
			cWorld->removeSprite( (Sprite3d*) pPilot );
			cWorld->removeSprite( cSceneVect[cCurScene] );

			cWorld->killAllSprite();

			cSceneVect[cCurScene]->resetLife();  // remet a jour l heure de creation

			cWorld->add( (Sprite3d*) pPilot );
			cWorld->add( cSceneVect[cCurScene]   );
		}
}
//------------------------------
int
SceneManager::endScene()
{
	std::cout << "SceneManager::endScene" << std::endl;
 // le Sprite est elimine par World qui appele execDelete

	cSceneVect[cCurScene]->leaveWorld();
	cCurScene++;

	if( cCurScene == cSceneVect.size() )
		{
			sprintf( cStrInfo, "Finish");
			WorldControler::WC->userEvent(NULL);
			return  0;
		}

	sprintf( cStrInfo, "%d/%ld | %s", cCurScene, cSceneVect.size(), cSceneVect[cCurScene]->getStrInfo());
	cSceneVect[cCurScene]->resetLife();

	if( WorldControler::GetCurrentWorld())
		WorldControler::Add(cSceneVect[cCurScene]);


	return 0;
}
//------------------------------
GLboolean
SceneManager::leaveWorld( Sprite3d &pMySprite, void*pParam )
{
	return GL_FALSE;  // Pour empecher la detruction, passage par kill oubligee
}
//------------------------------
GLboolean SceneManager::kill( Sprite3d &pMySprite, void *pParam )
{
	std::cout << "SceneManager::kill" << std::endl;

	endScene();

	switch( static_cast<int>(pMySprite.MkGetUSER5())  )
		{
		case GameOver:
			sprintf( cStrInfo, "Game Over" );
			WorldControler::GameOver();
			return GL_TRUE;

		case GameWinner:
			sprintf( cStrInfo, "Win " );
			WorldControler::GameWinner();
			return GL_TRUE;
		}
	return GL_TRUE;
}

//------------------------------------------------
void
SceneManager::execDelete( Sprite3d* pToDel )
{
	std::cout << "SceneManager::execDelete" << std::endl;
	for( unsigned int i=0; i<  cSceneVect.size(); i++ )
		{
			if( cSceneVect[i] == pToDel )
				{
					delete cSceneVect[i];
					cSceneVect[i] = NULL;
				}
		}
}




