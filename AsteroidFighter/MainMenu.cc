#include <stdlib.h>
#include <time.h>

#include <T3d/T3dLoadImg.h>
#include <T3d/T3dColor.h>

#include <O3d/O3dObjPrim.h>
#include <O3d/O3dObjText.h>

#include <O3d/O3dObjPLibFont.h>

#include <Sprite3d/ObjOdron.h>
#include <Sprite3d/World.h>
#include <Sprite3d/ObjText2d.h>
#include <Sprite3d/ObjText.h>
#include <Sprite3d/Random.h>
#include <Sprite3d/SoundControler.h>

#include <U3d/WeaponsMaker.h>


#include <MainMenu.h>

#include <Space/Pilot.h>
#include <Space/SceneAsteroide.h>
#include <Space/ShipsMaker.h>
#include <Space/Def.h>
#include <U3d/Sky.h>

#include <iostream>

#include <U3d/Banniere.h>


#ifdef  PUI_WIN
#include <plib/pu.h>
#endif

MainMenu* MainMenu::TheMainMenu = NULL;

//**************************************
MainMenu::MainMenu( int pSize, WorldControler* pControl, O3dKamera* pKamera, Double3& pMax,
						O3dObjProps *pProps)
:World(pControl, pKamera, pMax, pProps)	,
 cColorTextNormal( 1.0, 1.0, 0.0, 1.0 ),
 cSize( pSize ),
 cMuteSoundButton( NULL )
{
    TheMainMenu = this;
}
//-----------------------------
void
MainMenu::mouseMove( int pX, int pY )
{
	//	std::cout << "MainMenu::mouseMove" << std::endl;
}
//-----------------------------
void
MainMenu::mouseButton( int pButton, int pState, int pX, int pY)
{
	/*
	Double3 lPos;
	Double3 lResult;
	WorldControler::GetCurrentWorld()->getKamera()->getProject( WorldControler::GetCurrentWorld()->getPilot()->getTransf().get( POS),  lPos );
	lPos[0] = pX;
	lPos[1] = pY;

	WorldControler::GetCurrentWorld()->getKamera()->getUnProject( lPos, lResult );

	std::cout << "MainMenu::mouseButton:" << pX << " " << pY << " -> "
						<<  lResult[0] << "," << lResult[1] << "," << lResult[2] << std::endl;

	Sprite3d* lSprite =  isSpriteIntersect( lResult, 5, InteractObstacle );
	if( lSprite != NULL ) {
		std::cout << ">>>>Sprite:" << lSprite << std::endl;
	 std::cout << lSprite->fireUserAction( (void*)1, (void*)2 )<< std::endl;
	}
	*/
}
//-----------------------------
long
MainMenu::userAction( Sprite3d &pMySprite, void*pParam0, void*pParam1, void*pParam2 )
{
	//	std::cout << "UserAction -> " << (char*) pParam0 << ":"<< (long) pParam1 << ":" <<  (long) pParam2 << std::endl;
	return 666;
}
//-----------------------------
void
MainMenu::AfficheLine( int pX, int pY, const char* pStr ){

	static fntTexFont  *sFont = NULL;

	if( sFont == NULL )
		 sFont = new fntTexFont( "font/Helvetica.txf" );

	O3dObjPLibFont* lObjText = new O3dObjPLibFont( *sFont, 5, pStr );

	//	O3dObjText2d* lObjText = new O3dObjText2d( WorldControler::sCurrentFont, 16, 3, pStr );
	Sprite3dObj* lText = new  Sprite3dObj( lObjText );

	Double3 lPos( pX, pY, 0.0 );
	lText->getTransf().TransfDouble3::set( POS, lPos );

	cPropsTextNormal.ObjPropsFloat4::set( MATERIAL, cColorTextNormal );
	lText->setObjProps( &cPropsTextNormal );
	add( lText );
}
//-----------------------------
GLboolean
MainMenu::initStart(int pNiveau, const char* pFile)
{

	//  Sprite3dObj* lCentre = new Sprite3dObj( new ObjOdron( 60, 0));
	//  add( lCentre );

	//  Double3 spin( 5.0, 8.0, 10.0 );
	//  lCentre->SpriteDouble3::set( SPRITE_SPIN, spin );



  //===== Initialisation des props du generateur =====
	//  Float4 mat1(   0.8, 0.4, 0.5, 1.0 );
// caPropsGen = new O3dObjProps;
//  /caPropsGen->ObjPropsFloat4::set( MATERIAL, mat1 );
//  lCentre->setObjProps( caPropsGen );

  //=============================================



  //======= Positionnement spacial du Generateur ====
 // lCentre->getTransf().TransfDouble3::set( POS, lPos );


	int pX = -110;
	int pY =  90;
	int lStep = -8;

	AfficheLine( pX, pY, "****** Quick help* ******" );
	pY += lStep;	AfficheLine( pX, pY, "Quit Game           -> Q / Esc" );
	pY += lStep;	AfficheLine( pX, pY, "New game            -> N" );
	pY += lStep;	AfficheLine( pX, pY, "Main Menu           -> M" );
	pY += lStep;	AfficheLine( pX, pY, "Help                -> H" );
	pY += lStep;	AfficheLine( pX, pY, "Pause               -> P" );
	pY += lStep;	AfficheLine( pX, pY, "Resume              -> R" );
	pY += lStep;	AfficheLine( pX, pY, "Full screen/Window  -> F" );

	pY += lStep;

	pY += lStep;	AfficheLine( pX, pY, "Use spacebar to partial recharge Field (use energy)" );
	pY += lStep;	AfficheLine( pX, pY, "Use middle mouse button or 'A'to warp to cursor position(use energy)");
	pY += lStep;	AfficheLine( pX, pY, "Use left  mouse button or '1' to fire with energy weapon" );
	pY += lStep;	AfficheLine( pX, pY, "Use right mouse button or '2' to fire with rocket weapon" );
	pY += lStep;	AfficheLine( pX, pY, "Use CTRL  with mouse button for side fire" );
	pY += lStep;	AfficheLine( pX, pY, "Use SHIFT with mouse button for top fire" );
	pY += lStep;	AfficheLine( pX, pY, "Use ALT   with mouse button for top, side and front fire" );
	/*
	{
  O3dObjText2d* lObjText = new O3dObjText2d( WorldControler::sCurrentFont, 16, 3, "<Command>" );

  lObjText->push_back( new std::string( "****** Quick help* ******") );
  lObjText->push_back( new std::string( "Quit Game           -> Q / Esc") );
  lObjText->push_back( new std::string( "New game            -> N") );
  lObjText->push_back( new std::string( "Help                -> H") );
  lObjText->push_back( new std::string( "Pause               -> P") );
  lObjText->push_back( new std::string( "Resume              -> R") );
  lObjText->push_back( new std::string( "Full screen/Window  -> F") );
 Sprite3dObj* lText = new  Sprite3dObj( lObjText );

 Double3 lPos( -60.0, 0.0, 0.0 );
 lText->getTransf().TransfDouble3::set( POS, lPos );

 cPropsTextNormal.ObjPropsFloat4::set( MATERIAL, cColorTextNormal );
 lText->setObjProps( &cPropsTextNormal );
  add( lText );
	}



	{
		O3dObjText2d* lObjText = new O3dObjText2d( WorldControler::sCurrentFont, 16, 3, "" );
		lObjText->push_back( new std::string( "Use spacebar to recharge Field") );
		lObjText->push_back( new std::string( "Use middle mouse  button or 'A' to warp to cursor position") );
		lObjText->push_back( new std::string( "Use left  mouse button or '1' to fire with energy weapon") );
		lObjText->push_back( new std::string( "Use right mouse button or '2' to fire with rocket weapon") );
		lObjText->push_back( new std::string( "Use CTRL  with mouse button for side fire") );
		lObjText->push_back( new std::string( "Use SHIFT with mouse button for side and front fire") );



		Sprite3dObj* lText = new  Sprite3dObj( lObjText );

		Double3 lPos( -60.0, -20.0, 0.0 );
		lText->getTransf().TransfDouble3::set( POS, lPos );

		cPropsTextNormal.ObjPropsFloat4::set( MATERIAL, cColorTextNormal );
		lText->setObjProps( &cPropsTextNormal );
		add( lText );
	}
	*/


 // Pilot *lPilot = new Pilot();
 // lPilot->getTransf().TransfDouble3::get(POS)[ 0 ] = -120;

 // lPilot->getTransf().TransfDouble3::get(SCALE) *=3;

// add( lPilot );
 // setPilot( lPilot );

  add( new Sky( 10*cSize, cSize*100 ) );

	Sprite3d* lSp;

	Double3 lTransfNull( 0, 0, 0 );

	srand( ::time(NULL) );

	for( int i= 0; i< 20; i++ )
	{
		lSp=TheAsteroidesMaker->makeSpriteAsteroide( ASTEROIDE_PIERRE/*ASTEROIDE_CRISTAL*/, randp(9)+6, randp(2)+2 );
		//	Sprite3d* lAster=MAKE_INTERCEPTOR2;
		Double3 lSpinAster(  randf(20), randf(20), randf(20));
		lSp->MkSetSPIN( lSpinAster );
		lSp->MkGetPOS()[0] = randf(150 );
		lSp->MkGetPOS()[1] = randf(150 );
		lSp->MkGetPOS()[2] = randf( 20 )-100;
		lSp->setAction( SPRITE_USER_ACTION, this, const_cast<char*>("Asteroide") );

		add( lSp );
	}


	{
		lSp = TheShipsMaker->makeShip( BASE_TORE, 10, 20, 0, 0, 0, 1 );
		lSp->MkSetSPEED( lTransfNull );
		Double3 lSpinAster( 10, 8, 9 );
		lSp->MkSetSPIN( lSpinAster );
		Double3 lGrow( 1.6, 1.6, 1.6 );
		lSp->MkSetSCALE( lGrow );
		lSp->MkGetPOS()[0] = -100;
		lSp->MkGetPOS()[1] = 60;
		lSp->MkGetPOS()[2] = -40;
		lSp->setMask( InteractObstacle, InteractObstacle);
		lSp->setAction( SPRITE_USER_ACTION, this, const_cast<char*>("Tore") );

		add( lSp );
	}

	/*
	{
		T3dTransf lT3dTransf;
		lSp = WeaponsMaker::MakeSprite( &lT3dTransf, WEAPON_ROCKET,  0, 0 );

		lSp->MkSetSPEED( lTransfNull );

		Double3 lGrow( 5, 5, 5 );
		lSp->MkSetSCALE( lGrow );

		Double3 lSpinAster( 0, 0, 0);
		lSp->MkSetSPIN( lSpinAster );
		lSp->MkGetPOS()[0] =  100;
		lSp->MkGetPOS()[1] = -100;
		lSp->MkGetPOS()[2] = -100;


		add( lSp );
	}
	*/




	//  Pilot *lPilot = new Pilot();
	//  lPilot->getTransf().TransfDouble3::get(POS)[ 0 ] = -100;
	//  Double3 lGrow( 4, 4, 4 );
	//  lPilot->MkSetSCALE( lGrow );
	//	lPilot->setAction( SPRITE_USER_ACTION, this, const_cast<char*>("Pilot") );
	//	lPilot->SpriteFloat::set( SPRITE_LIFE_POINT, 0 ); // Pour neutraliser les deplacement

	//  add( lPilot );
	//  setPilot( lPilot );



  return GL_TRUE;
}
//------------------------------------------------

void
MainMenu::MyReadFileCb( puObject * pObject)
{	
	char *lStr;
	pObject->getValue( &lStr );

	//	std::cout << "MainMenu::MyFileReadCb " << pObject << ":" << lStr 						<< std::endl;
	
	std::string lStrFileSav( lStr ); 

	puDeleteObject( TheMainMenu->cReadSavBox );
	TheMainMenu->cReadSavBox = NULL;

	if( lStrFileSav.empty() == false ){
		TheMainMenu->getMyControler()->start( 0, lStrFileSav.c_str() );
	}
}
//------------------------------------------------
void
MainMenu::MyButtonCb( puObject * pObject)
{
	//  std::cout <<  "MyButtonCb :" << pObject->getValue() << std::endl;

	
	if( pObject == TheMainMenu->cReadAutoBox ){
		
		TheMainMenu->cReadSavBox = new puaFileSelector( 10, 50, 1000, 500, 2, "Sav", "Read saved game" );
		
		TheMainMenu->cReadSavBox->setCallback( MyReadFileCb ) ;
	
		//		glutPostRedisplay();
		return;
	}

	if( pObject == TheMainMenu->cGentileBox )
        WorldControler::sDifficultyLevel = 0;

	if( pObject == TheMainMenu->cEasyBox )
        WorldControler::sDifficultyLevel = 1;

	if( pObject == TheMainMenu->cMediumBox )
        WorldControler::sDifficultyLevel = 2;

	if( pObject == TheMainMenu->cHardBox)
        WorldControler::sDifficultyLevel = 3;

	if( pObject == TheMainMenu->cExtremeBox )
        WorldControler::sDifficultyLevel = 4;

	//	  std::cout <<  "sDifficultyLevel :" << WorldControler::sDifficultyLevel
	//							<< std::endl;

		////		TheMainMenu->getMyControler()->setCurrent( WorldControler::GetGameWorld() );

		//	if( WorldControler::GetCurrentWorld() == WorldControler::GetGameWorld() )
		TheMainMenu->getMyControler()->start();

}
//------------------------------------------------
void
MyMuteSoundButtonCb(  puObject * pObject)
{
	//  std::cout <<  "MyButtonCb :" << pObject->getValue() << std::endl;

	if( pObject->getValue() == 0 )
		SoundControler::sMute = GL_TRUE;
	else
		SoundControler::sMute = GL_FALSE;
}
//------------------------------------------------
 void
MainMenu::reshapeWorld(int pWidth, int pHeight)
{
	leaveWorld();
	enterWorld();
}
//------------------------------------------------

void
MainMenu::enterWorld()
{
	static fntTexFont  *sFont = NULL;
	static puFont      *sPuFont = NULL;

	if( sFont == NULL )
		{
			sFont = new fntTexFont( "font/Helvetica.txf" );
			sPuFont = new puFont( sFont, 20 );
			puSetDefaultFonts( *sPuFont, *sPuFont ) ;
		}


	int lScreenWidth, lScreenHeight;

	puGetWindowSizeGLUT ( &lScreenWidth, &lScreenHeight );

	//	std::cout << "enterWorld" << std::endl;
	//		puOneShot *b = new puOneShot ( 50, 50, 200, 80 ) ;

	static 	const char* TVal[6] = { "Gentile",  "Easy", "Medium", "Hard", "Extreme", NULL };

	//  puOneShot *b = new puOneShot ( 0, 50, 200, 80 ) ;

	int lStepX = 10;
	int lStepY = 10;

	int lTextL = 300;

	int lTextH = 300;
	int lX = lScreenWidth - (lTextL+lStepX );
	int lY = -10;


	/*
	cQuickHelp = new puaLargeInput( lX,  lY-lTextH, lTextL , lTextH ,2, 8, TRUE );
	cQuickHelp->rejectInput();
	cQuickHelp->setText(	"****** Quick help* ******\n"
												"\n"
												"Quit Game           -> Q / Esc\n"
												"New game            -> N\n"
												"Main Menu           -> M\n"
												"Help                -> H\n"
												"Pause               -> P\n"
												"Resume              -> R\n"
												"Full screen/Window  -> F\n"
												"\n"
												"Use spacebar to recharge Field\n"
												"Use middle mouse  button or 'A' to warp to cursor position\n"
												"Use left  mouse button or '1' to fire with energy weapon\n"
												"Use right mouse button or '2' to fire with rocket weapon\n"
												"Use CTRL  with mouse button for side fire\n"
												"Use SHIFT with mouse button for side and front fire");


	//	cDifficultyBox = new puButtonBox ( x0+l, y0+h, x0+l*2, y0+h*2,
	//																		 const_cast<char**>(TVal), 1 ) ;
	int lWidth, lHeight;
	cQuickHelp->getSize( &lWidth, &lHeight );

	lY -= lStepY*6 +  ;
	*/

 	lY -= lStepY*5 +lTextH;
	//	lX +=500;

	lX = lStepX;
	lY = lStepY;

	cExtremeBox= new puOneShot( lX, lY, "Start Extreme" );
	cExtremeBox->setCallback( MyButtonCb ) ;
	int lWidth, lHeight;
	cExtremeBox->getSize( &lWidth, &lHeight );

	lY += lStepY+lHeight;

	cHardBox= new puOneShot( lX, lY, "Start   Hard  " );
	cHardBox->setCallback( MyButtonCb ) ;
	lY += lStepY+lHeight;

	cMediumBox= new puOneShot( lX, lY, "Start  Medium " );
	cMediumBox->setCallback( MyButtonCb ) ;
	lY += lStepY+lHeight;

	cEasyBox= new puOneShot( lX, lY, "Start   Easy  " );
	cEasyBox->setCallback( MyButtonCb ) ;
	lY += lStepY+lHeight;

	cGentileBox = new puOneShot( lX, lY, "Start Gentile" );
	cGentileBox->setCallback( MyButtonCb ) ;
	cGentileBox->getSize( &lWidth, &lHeight );

	lY += lStepY+lHeight;
	lY += lStepY+lHeight;

  cReadAutoBox= new puOneShot( lX, lY, "Read Save game" );
	cReadAutoBox->setCallback( MyButtonCb ) ;
	cReadAutoBox->getSize( &lWidth, &lHeight );



	//	if( SoundControler::sNoSound == GL_FALSE )
	/*
		{
						puText* cTextSound = new puText( lX+ lWidth+lStepX*2 , lY);
						cTextSound->setLabel("Soundewrwerjewrwejrkewj  w;rlwerwerkwekr  " );
						int lWidth2;
						cTextSound->getSize( &lWidth2, &lHeight );
			cMuteSoundButton = new puButton( lX+lWidth+lStepX*2, lY, lX+ lWidth+lStepX*2+50, lY+32, PUBUTTON_XCHECK );
			//			cMuteSoundButton->setButtonType( PUBUTTON_XCHECK );
			cMuteSoundButton->setLabel( "Soundewre  werweewrwr weer" );
			cMuteSoundButton->setCallback( MyMuteSoundButtonCb ) ;
			if(	SoundControler::sMute == GL_FALSE )
				cMuteSoundButton->setValue( 1 );
			else
				cMuteSoundButton->setValue( 0 );
		}
		*/



	lY += lStepY+lHeight;





	/*
	cDifficultyBox = new puButtonBox ( lX, lY-60,  lX+200, lY+400, const_cast<char**>(TVal), 1 ) ;

	cDifficultyBox->setCallback( MyButtonCb2 ) ;
 	cDifficultyBox->setLegend( "Difficulty level") ;
	cDifficultyBox->setValue( WorldControler::sDifficultyLevel );
	*/

	WorldControler::PuiInUse = GL_TRUE;
}

//------------------------------------------------

void
MainMenu::leaveWorld()
{
	//	if( cQuickHelp )
	//		puDeleteObject ( cQuickHelp );
	//	cQuickHelp = NULL;

	if(cReadAutoBox )
		puDeleteObject(  cReadAutoBox);
		cReadAutoBox= NULL;



	if(cGentileBox )
		puDeleteObject( cGentileBox );
	cGentileBox	= NULL;

	if(cEasyBox )
		puDeleteObject( cEasyBox );
	cEasyBox	= NULL;

	if(cMediumBox )
		puDeleteObject( cMediumBox );
	cMediumBox	= NULL;

	if( cHardBox)
		puDeleteObject( cHardBox );
	cHardBox	= NULL;

	if(cExtremeBox )
		puDeleteObject( cExtremeBox );
	cExtremeBox	= NULL;

	if( cMuteSoundButton )
		puDeleteObject( cMuteSoundButton );
	cMuteSoundButton = NULL;

	if( cReadAutoBox )
		puDeleteObject( cReadAutoBox );
	cReadAutoBox = NULL;

	WorldControler::PuiInUse = GL_FALSE;
}
//**************************************

