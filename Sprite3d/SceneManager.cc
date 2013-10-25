#include <SceneManager.h>
#include <Sprite3d/WorldControler.h>

#include <Sprite3d/Scene.h>
#include <Space/Pilot.h>

#include <fstream>
#include <sstream>


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
	// Bug ! (les scene sont peut deja detruite ?
	//std::cout << "~SceneManager " << cSceneVect.size() << std::endl;
	//	for( unsigned int i=0; i<  cSceneVect.size(); i++ )
		//{
		//	std::cout << "~SceneManager " << i << " " << cSceneVect[i]->getStrName() << std::endl;
		//	if( cSceneVect[i] != NULL ){
		//		delete cSceneVect[i];
		//		cSceneVect[i] = NULL;
	//		}
	//		}
	//	std::cout << "~SceneManager end" << std::endl;

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
//----------------------------------------------------------
static const char* sStrLevel = "(Level";
static const char* sStrScene = "Scene";
static const char* sStrTime  = "Time";
static const char* sStrDifficulty  = "Difficulty";


void
SceneManager::write( std::ostream & pOs){

    pOs << sStrLevel << ' '
        << sStrScene << ' ' << cCurScene  << ' '
        << sStrTime << ' ' << (long)WorldControler::sTime << ' '
        << sStrDifficulty << ' ' << WorldControler::sDifficultyLevel << ' '
        << ')';

}
//-------------
bool
SceneManager::read( std::istream & pIs ){

    std::string lTmpStr;

    long lCurScene = 0;
    long lTime =0;

    pIs >> lTmpStr;
    std::cout << "read " << lTmpStr << std::endl;

    if( lTmpStr.compare( sStrLevel ) != 0 )
        return false;

    pIs >> lTmpStr;
    if( lTmpStr.compare( sStrScene ) != 0 )
        return false;
    pIs >> lCurScene;

    pIs >> lTmpStr;
    if( lTmpStr.compare( sStrTime ) != 0 )
        return false;
    pIs >> lTime;

    cCurScene = lCurScene;
    WorldControler::sTime = lTime;

    return true;
}
//-------------
static const char* sDirSav = "Sav";
static const char* sAutoSavFile = "autosave";
static int sSavNum=0;

//-------------
void
SceneManager::restoreStateFromFile( const char* pName ){

    std::ostringstream lStrFile(sDirSav);

    lStrFile << sDirSav <<'/';
    lStrFile << pName;
 //   lStrFile << '_';
 //   lStrFile << ".sav" ;

std::cout << "*** restoreStateFromFile " << lStrFile.str() << std::endl;

    if( Pilot::ThePilot == NULL )
            return;

    std::ifstream lFis( lStrFile.str().c_str());
    if( lFis.bad())
        return;

    if( read( lFis )== false ){
        std::cout << "read scene fail" << std::endl;
            return ;
    }

    if( Pilot::ThePilot->read(lFos)== false ){
        std::cout << "read pilot fail" << std::endl;
            return ;
    }


    lFos.close();
}
//-------------
void
SceneManager::saveStateToFile( const char* pName ){

std::cout << "SceneManager::saveStateToFile " << pName << std::endl;

    std::ostringstream lStrFile(sDirSav);

    lStrFile << sDirSav <<'/';
    lStrFile << pName;
    lStrFile << '_';
    lStrFile << sSavNum++;
    lStrFile << ".sav" ;


std::cout << "\tsaveStateToFile " << lStrFile.str() << std::endl;

    if( Pilot::ThePilot == NULL )
            return;

    std::ofstream lFos( lStrFile.str().c_str());
    if( lFos.bad())
        return;

std::cout << "\tsaveStateToFile ok " << lStrFile.str() << std::endl;

    write( lFos );
    lFos << std::endl;

    Pilot::ThePilot->write(lFos);
    lFos << std::endl;

    lFos.close();
}
//-----------------------------------------------------------
// Lance la premiere scene du scenario, c'est la fin
// de la scene (kill -> endScene ) qui provoque
// l'execution de la scene suivante
// la fin de la derniere scene provoque la fin du scenario
// et donc la victoire

void
SceneManager::go(World* pWorld)
{
  sprintf( cStrInfo, "%d/%d | %s", cCurScene, cSceneVect.size(), cSceneVect[cCurScene]->getStrInfo() );
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

    saveStateToFile(sAutoSavFile);


	sprintf( cStrInfo, "%d/%d | %s", cCurScene, cSceneVect.size(), cSceneVect[cCurScene]->getStrInfo());
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




