#include <Sprite3d/World.h>

#include <Sprite3d/SceneManager.h>
#include <U3d/Sky.h>

#include <Sprite3d/Random.h>

#include <SceneAsteroide.h>
#include <SceneBase.h>
#include <SceneAttack.h>
#include <SceneGrotte.h>
#include <SceneLife.h>
#include <Pilot.h>
#include <Def.h>
#include <WorldGame.h>
#include <ShipsMaker.h>
#include <MinesMaker.h>
#include <U3d/BonusMaker.h>
#include <U3d/WeaponsMaker.h>
#include <U3d/SpriteExplosion.h>
#include <U3d/ObjPrimPart.h>
#include <U3d/Banniere.h>

#include <WorldGame.h>
#include <ActionsShip.h>



float WorldGame::GlobalScroll = -20;
WorldGame *WorldGame::TheWorldGame = NULL;
float WorldGame::XSizeWorld = 150;
float WorldGame::YSizeWorld = 120;

//************************************************************
WorldGame::WorldGame( int pSize, WorldControler* pControl, O3dKamera* pKamera, Double3& pMax,
						O3dObjProps *pProps)
	:World(pControl, pKamera, pMax, pProps),
	cSize(pSize),
	 cSceneManager(NULL),
	 cLevel(0)
{
	TheWorldGame = this;
	cInfoLevel[0]='\0';
}
//---------------------------------------------------
WorldGame::~WorldGame()
{
	delete cSceneManager;
	TheWorldGame = NULL;
}
//---------------------------------------------------
const char*
WorldGame::getInfoLeveL(){
	sprintf( cInfoLevel, cSceneManager->getInfoScene() );
	return cInfoLevel;
}
//---------------------------------------------------
GLboolean
WorldGame::initStart( int pNiveau )
{
  Double3 lGenPos( 160.0, 0.0, 0.0 );
	Float4 lBanColor( 0.6, 0.6, 0.9, 0.4 ) ;


	// We must allocate all in the heap because on restart, we must
	// forget all.

	cSceneManager = new SceneManager();
	std::cout << "WorldGame::initStart" << std::endl;
	// Mettre une scene d'intro !!!

	int lDureGen = 20; //40;

	if( pNiveau == 0 )
		{
			if(  WorldControler::sDifficultyLevel >2 )
				{
					pNiveau = WorldControler::sDifficultyLevel*2;
					WorldGame::GlobalScroll -= pNiveau;
				}
		}	//			std::cout << "pNiveau:" << pNiveau << std::endl;
	for( cLevel=pNiveau; cLevel< pNiveau+8+WorldControler::sDifficultyLevel*2; cLevel++ )		// acceleration a chaque niveau !!!
		{
			//			std::cout << "pLevel:" << cLevel << std::endl;
			// Message NEXT LEVEL
			if( cLevel!= pNiveau )
				{
					cSceneManager->addSceneTempo(3);
					cSceneManager->addScene( makeBanniere( "textures/NextLevel.gif", lBanColor, 3), 4);
					cSceneManager->addSceneTempo(3);
					WorldGame::GlobalScroll -= 1;
				}


			if( cLevel > 6 )
				cSceneManager->addScene( new SceneLife( lGenPos, YSizeWorld, 20.0f ),  0.5 );

			int duree = lDureGen+cLevel*3;





			cSceneManager->addScene( new SceneAsteroide( "Asteroide Water", ASTEROIDE_WATER, cLevel, lGenPos, 0.3f, YSizeWorld, 20.0f ),  duree );
			cSceneManager->addSceneTempo(5);
			cSceneManager->addScene( new SceneAttack( "Attack 1", cLevel, lGenPos, 1, YSizeWorld, 30.0f ), duree);
			cSceneManager->addSceneTempo(5);

			if( cLevel == 0 )
				continue;

			cSceneManager->addScene(new SceneGrotte( "Into Asteroide Water", ASTEROIDE_WATER, cLevel, lGenPos, 1, 0.4, 15, YSizeWorld, 50.0f ),duree );
			cSceneManager->addSceneTempo(5);

			if( cLevel == 1 )
				continue;

			cSceneManager->addScene( new SceneAttack( "Attack 2",cLevel, lGenPos, 1, YSizeWorld, 30.0 ), duree);
			cSceneManager->addSceneTempo(5);
			cSceneManager->addScene( new SceneAsteroide( "Asteroide Water",ASTEROIDE_ICE, cLevel, lGenPos, 0.3, YSizeWorld, 20.0 ), duree);
			cSceneManager->addSceneTempo(5);
			if( cLevel == 2 )
				continue;

			cSceneManager->addScene(new SceneGrotte( "Into Asteroide Ice", ASTEROIDE_ICE,  cLevel, lGenPos, 1.2, 0.7, 13, YSizeWorld, 50.0 ), duree);
			cSceneManager->addSceneTempo(5);

			if( cLevel == 3 )
				continue;


			cSceneManager->addScene( new SceneAsteroide( "Asteroide Snow", ASTEROIDE_SNOW, cLevel, lGenPos, 0.3f, YSizeWorld, 20.0f ), duree);
			cSceneManager->addSceneTempo(5);
			cSceneManager->addScene(new SceneGrotte( "Into Asteroide Snow", ASTEROIDE_SNOW, cLevel , lGenPos, 1.5, 0.6, 15, YSizeWorld, 50.0 ), duree);
			cSceneManager->addSceneTempo(5);

			if( cLevel == 4 )
				continue;


			cSceneManager->addScene( new SceneAttack( "Attack 3", cLevel, lGenPos, 1, YSizeWorld, 30.0 ), duree);
			cSceneManager->addScene( new SceneAsteroide( "Asteroide Mars", ASTEROIDE_MARS, cLevel, lGenPos, 0.3, (int)YSizeWorld, 20.0 ), duree );
			cSceneManager->addSceneTempo(5);
			cSceneManager->addScene(new SceneGrotte( "Into Asteroide Mars", ASTEROIDE_MARS, cLevel , lGenPos, 0.9, 0.5, 14, YSizeWorld, 50.0 ), duree);
			cSceneManager->addSceneTempo(5);

			if( cLevel == 5 )
				continue;


		 	cSceneManager->addScene( new SceneAttack( "Attack 4", cLevel, lGenPos, 1, YSizeWorld, 30.0 ), duree);
			cSceneManager->addScene( new SceneAsteroide( "Asteroide Cristal", ASTEROIDE_CRISTAL, cLevel, lGenPos, 0.3, YSizeWorld, 20.0 ), duree );
			cSceneManager->addSceneTempo(5);
			cSceneManager->addScene(new SceneGrotte( "Into Asteroide Cristal", ASTEROIDE_CRISTAL,  cLevel, lGenPos, 1.1, 0.6, 14, YSizeWorld, 50.0 ), duree);
			cSceneManager->addSceneTempo(5);
			if( cLevel == 6 )
				continue;

			cSceneManager->addScene( new SceneAttack( "Attack 5", cLevel, lGenPos, 1, YSizeWorld, 30.0), duree);
			cSceneManager->addScene( new SceneBase( "Attack Base", cLevel, lGenPos, 1, YSizeWorld, 20.0, (int)BASE_TORE ), duree);

			if( cLevel == 7 )
				continue;

			cSceneManager->addSceneTempo(10);
			cSceneManager->addScene( new SceneBase( "Attack Base", cLevel, lGenPos, 1, YSizeWorld, 20.0, (int)MEGA_CROISEUR ), duree);

			// Mettre un vrai boss de niveau
			// Mettre une scene de fin de niveau !!!
			// Possiblite d'achat de materiel !!!
			/*
			{
				Sprite3d* sp = TheBonusMaker->makeSpriteBonus( CONTAINER_UPGRAD, CONTAINER_LIFE, InteractBonus, InteractBonus, 1 );

				Double3 lPos;
				lPos[0] =  randf(100);
				lPos[1] = -100;
				lPos[ 2 ] = 0;

				sp->getTransf().TransfDouble3::set( POS, lPos );


				Double3 lD3( randf( 150 ), randf( 150 ), randf( 150 ));
				sp->SpriteDouble3::set( SPRITE_SPIN, lD3);

				cSceneManager->addScene(sp);
			}
			*/
		}

	// Mettre une scene de reusite

  cSceneManager->go(this);


  Pilot *lPilot = new Pilot();
  lPilot->getTransf().TransfDouble3::get(POS)[ 0 ] = -YSizeWorld;

  add( lPilot );
  setPilot( lPilot );


  add( new Sky( 10*cSize, cSize*100 ) );
  return GL_TRUE;
}
//---------------------------------------------------
void
WorldGame::freeRessources()
{
	empty();

	delete cSceneManager;
	cSceneManager = NULL;
}
//---------------------------------------------------
void
WorldGame::gameOver()
{
	std::cout << "WorldGame::gameOver" << std::endl;
	World::gameOver();

	Float4 lBanColor( 0.9, 0.9, 1.0, 0.5 ) ;

	Sprite3d* lSpBan = new Banniere( "textures/game_over.gif", lBanColor );

	Double3 lPosBan( 0, 0, 20 );
	Double3 lSpeed( 0, 0, 20 );
	Double3 lScale( 40, 40, 40 );
	Double3 lSpin(25, 15, 15);

	lSpBan->MkSetPOS(   lPosBan  );
	lSpBan->MkSetSPEED( lSpeed  );
	lSpBan->MkSetSCALE( lScale  );
	lSpBan->MkSetSPIN(  lSpin );


	WorldControler::Add( lSpBan );



	((WorldGame*)WorldControler::GetGameWorld())->getSceneManager()->addSceneTempo( 25, SceneManager::GameWinner  );

	// Faire qq chose !
}

//------------------------------
// Pour laisser du temps entre deux scenes

Sprite3d*
WorldGame::makeBanniere( const char* pName, Float4 pColor, float pLiveTime )
{
	Sprite3d* lSpBan = new Banniere( pName, pColor );

	Double3 lPosBan( 0, 0, -100 );
	Double3 lSpeed( 0, 0, 80 );
	Double3 lScale( 20, 20, 20 );
	Double3 lSpin(0, 0, 20);

	lSpBan->MkSetPOS(   lPosBan  );
	lSpBan->MkSetSPEED( lSpeed  );
	lSpBan->MkSetSCALE( lScale  );
	lSpBan->MkSetSPIN(  lSpin );
	lSpBan->SpriteFloat::set( SPRITE_LIFETIME, pLiveTime  );

	return lSpBan;
}
//---------------------------------------------------
int
WorldGame::userEvent( void *pUserData)
{
	std::cout << "WorldGame::gameWinner" << std::endl;
	World::gameWinner();

	// Mettre autre Sprite
	//	Sprite3dObj* lSpriteEx = new Sprite3dObj( new ObjDebris( 500, 20 ) );
	//	lSpriteEx->setTransf( cPilot->getTransf() );
	//	lSpriteEx->SpriteFloat::set( SPRITE_LIFETIME, 7 );

	// 	WorldControler::Add( lSpriteEx );

	Float4 lBanColor( 0.9, 0.9, 1.0, 0.5 ) ;

	Sprite3d* lSpBan = new Banniere( "textures/you_win.gif", lBanColor );

	Double3 lPosBan( 0, 0, 20 );
	Double3 lSpeed( 0, 0, 20 );
	Double3 lScale( 40, 40, 40 );
	Double3 lSpin(25, 15, 15);

	lSpBan->MkSetPOS(   lPosBan  );
	lSpBan->MkSetSPEED( lSpeed  );
	lSpBan->MkSetSCALE( lScale  );
	lSpBan->MkSetSPIN(  lSpin );


	WorldControler::Add( lSpBan );



	((WorldGame*)WorldControler::GetGameWorld())->getSceneManager()->addSceneTempo( 25, SceneManager::GameWinner  );

 return 1;
}
//---------------------------------------------------
void
WorldGame::InitSprite()
{
	new ShipsMaker;
	new MinesMaker;
	new WeaponsMaker;
	new BonusMaker;
	new AsteroidesMaker;

	SpriteExplosion::Init();
}
//---------------------------------------------------

PSoundId sOceanSound=PBadSoundId;


void
WorldGame::InitSound( const char* pPathSound)
{
	TheWorldGame->setMySoundLibrary( new SoundLibrary(256, pPathSound ));

		sOceanSound = TheWorldGame->getMySoundLibrary()->loadSample( "ocean.wav" );

	Pilot::InitSound(TheWorldGame);
	ActionsShip::InitSound(TheWorldGame);
	WeaponsMaker::InitSound(TheWorldGame);
}
//---------------------------------------------------

