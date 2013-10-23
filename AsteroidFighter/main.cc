#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>


#include <GL/glut.h>

#include <O3d/O3dObjProps.h>
#include <O3d/O3dKamera.h>
#include <O3d/O3dObjText.h>


#include <Sprite3d/World.h>
#include <Sprite3d/ObjOdron.h>
#include <Sprite3d/ObjPart.h>
#include <Sprite3d/Sprite3d.h>
#include <Sprite3d/Utils3d.h>
#include <Sprite3d/Collision.h>
#include <Sprite3d/ObjText2d.h>
#include <Sprite3d/ObjText.h>
#include <Sprite3d/SceneManager.h>
#include <Sprite3d/SoundControler.h>

#include <MainMenu.h>
#include <Help.h>

#include <Space/WorldGame.h>

#include <plib/ul.h>

#ifdef  PUI_WIN
#include <plib/pu.h>
#endif

#include <plib/fnt.h>

int sStartNiveau = 0;

extern PSoundId sOceanSound;


//****************************************************
class GameWorldControler: public WorldControler{

	int          cSize;
	Double3      cMax;
	O3dObjProps* cGen;

public:
	GameWorldControler( int lTest, int pSize, int pWidth, int pHeight)
		:WorldControler( pWidth, pHeight ),
		 cSize( pSize )		,
		 cMax( 300, 200, 100 ),
		 cGen(NULL)
	{
		Float4 mat1( 0.5, 0.5, 0.5, 1.0 );
		Float4 mat2( 0.0, 0.0, 0.0, 1.0 );

		O3dObjProps* lProps = new O3dObjProps();
		Float4 pr6 (0.3, 0.5, 0.9, 0.2);
		lProps->ObjPropsFloat4::set( MATERIAL, pr6);
		cGen = new O3dObjProps;

		cGen->ObjPropsFloat4::set( MATERIAL, mat1 );
		cGen->ObjPropsFloat4::set( EMISSION, mat2 );

		WorldGame::InitSprite();
		WorldControler::InitCallback();


		World *lWorld = new WorldGame( pSize, WorldControler::WC, new O3dKamera(), cMax,  cGen );

		WorldControler::WC->setGame( lWorld );

		World  *lWorldHelp = new Help( pSize,  WorldControler::WC,new O3dKamera(), cMax,  cGen );
		lWorldHelp->initStart(sStartNiveau);
		WorldControler::WC->setHelpWorld( lWorldHelp );

		World  *lWorldMainMenu = new MainMenu( pSize,  WorldControler::WC,new O3dKamera(), cMax,  cGen );
		lWorldMainMenu->initStart( sStartNiveau );
		WorldControler::WC->setMainWorld( lWorldMainMenu );
	}



protected:
	void selectNewGame( unsigned char pKey, int pX, int pY )
	{
		World *lWorld = WorldControler::GetGameWorld();
    //    if( lWorld ) {
	//	    delete lWorld;
    //       }

		lWorld = new WorldGame( cSize, WorldControler::WC, new O3dKamera(), cMax,  cGen );
		WorldControler::WC->setGame( lWorld );
	}

	//------------------------------------------------

};
//****************************************************





void InitWorld( int pSize, int lTest)
{


/*
  Menu3d* lMenu = new Menu3d();
  lMenu->addItem( "Go" );
  lMenu->addItem( "Help" );
  lMenu->pop();
  lMenu->affectToMouseButton(GLUT_LEFT_BUTTON);
*/
 /*
  ObjText* lOText = new ObjText( "Coucou" );
  Sprite3dObj* lSText = new Sprite3dObj( lOText );
  lSText->getTransf().TransfDouble3::get(POS)[ 0 ] = -120;
   Double3 lSpin3( randf( 50 ), randf( 50 ), randf( 50 ));

   lSText->SpriteDouble3::set( SPRITE_SPIN,  lSpin3 );
   lSText->getTransf().TransfDouble3::set( SCALE, Double3(0.1, 0.1, 0.1));

   lWorld->add( lSText );
  */


 // Sprite3d* lSp = TheShipsMaker->makeSpriteShip3();
 // lSp->SpriteDouble3::set( SPRITE_SPIN,  Double3( 50, 50, 50));
 // lWorld->add( lSp );
}

//------------------------------------------------
void
printHelp()
{
	std::cout << "StarFighter 0.3b" << std::endl;
	std::cout << "-F<number> frame/second ex: -F25" << std::endl;
	std::cout << "-S<number> size         ex: -S10" << std::endl;
}
//****************************************************
int main(int argc, char **argv)
{


	std::cout << " sizeof(int)=" << sizeof(int)
						<< " sizeof(long)=" << sizeof(long)
						<< " sizeof(double)=" << sizeof(double)
						<< " sizeof(float)=" << sizeof(float)
						<< " sizeof(long long)=" << sizeof(long long)
						<< " sizeof(long double)=" << sizeof(long double)
						<< " sizeof(void*)=" << sizeof(void*)
						<< std::endl;

	//	int lRate = 60;
	int lRate =60;
	int lTest = 0;
	int lSize = 10;
	char *lData=NULL;

	for( int i =1; i< argc; i++)
	{
		char *pStr = argv[i];
		if( *pStr == '-' )
			switch( *(++pStr))
			{
				case 'G' :
					WorldControler::sDebug =1;
					break;

				case 'F' :
					{
						lRate = atoi( ++pStr );
						if( lRate > 1 && lRate < 101 )
							WorldControler::SetRate( lRate );
						break;
					}
				case 'X':
					{
						lSize = atoi( ++pStr);
						break;
					}

			case 'D': 
				lData=++pStr;
				break;
			case 'T':
				lTest = atoi(++pStr);
				break;

			case 'M':
				SoundControler::sMute = GL_TRUE;
				break;

			case 's':
				SoundControler::sNoSound = GL_TRUE;
				break;

			case 'S':
				SoundControler::sNoSound = GL_FALSE;
				break;

			case 'N':
						sStartNiveau = atoi( ++pStr);
					break;

			case 'H':
			case 'h':
			default:
				printHelp();
				break;
			}
	}
	/*
slScheduler sched ( 8000 ) ;
 sched . setSafetyMargin ( 0.128f ) ;
 slSample *s2 = new slSample ( "Data/sound/zzap.wav" , & sched ) ;
   s2 -> adjustVolume ( 5.0f  ) ;
  sched . playSample ( s2 ) ;
  while ( SL_TRUE )
  {
          Sleep ( 1000 / 30 ) ;
         sched . update () ;
  }
*/


	SoundControler lSoundControler;

	

	Utils3d::Init( "AsteroidFighter 1.0", argc, argv, 80*lSize, 60*lSize);

	GameWorldControler lWControl( lTest, lSize, 80*lSize, 60*lSize );
	WorldControler::SetRate( lRate );


	fntInit(); // PLIB pour les fonts !!!

		//	InitWorld(lSize, lTest);

	lWControl.mainWorld();


	if( lData )
		{
			std::string lDataSound( lData );
			lDataSound += "/sound";
			WorldGame::InitSound(lDataSound.c_str()); // Pour les sons notamment
		}
	else 
		{
			WorldGame::InitSound("sound"); // Pour les sons notamment
		}

    ulSleep ( 1 ) ;
		/*
		slSample* lSound ;
SoundLibrary sLib(200, "Data/Douteux");
//sLib.loadSample("alternative_001.wav");
sLib.loadSample("explo1.wav");
sLib.loadSample("explo2.wav");
//sLib.loadSample("WHOOSH.WAV.wav");

ulSleep(3);
for(int i=0; i<50; i++)
{
lSound = sLib.getSample(i);
if( lSound == NULL)
    break;
SoundControler::sTheSoundControler->playSample( lSound);
for( int t=0; t<20; t++)
{
  SoundControler::sTheSoundControler->process();
    ulMilliSecondSleep(100);
}
ulSleep(3);
}
*/


//slSample* lSoundExplosion = SoundControler::sTheSoundControler->loadSample( "Data/sound/Warp.wav" );
//SoundControler::sTheSoundControler->playSample( lSoundExplosion );
    ulSleep ( 5 ) ;
	Utils3d::Loop();

	return 0;
}
//****************************************************





