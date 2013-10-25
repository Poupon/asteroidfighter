#include <stdlib.h>
#include <Def.h>

#include <T3d/T3dLoadImg.h>
#include <T3d/T3dColor.h>

#include <O3d/O3dObjPrim.h>

#include <Sprite3d/ObjOdron.h>
#include <Sprite3d/World.h>
#include <Sprite3d/Random.h>

#include <SceneGrotte.h>

#include <ShipsMaker.h>
#include <MinesMaker.h>
#include <AsteroidesMaker.h>
#include <WorldGame.h>

#include <U3d/BonusMaker.h>

#include <iostream>


SceneGrotte *SceneGrotte::TheSceneGrotte = NULL;

//**************************************
SceneGrotte::SceneGrotte( const char* pName, EnumAsteroides pTypeAsteroide, int pHardness, Double3& lPos,
								float pInterval, float pIntervalParoi, int pSizeParoi, float  pH, float pV )
:Scene( pName, pHardness, pInterval, pH, pV ),
 cIntervalParoi( pIntervalParoi ),
 cSizeParoi( pSizeParoi),
 cTypeAsteroide(pTypeAsteroide),
 cFirstTime(GL_TRUE)
{
  TheSceneGrotte = this;


  //===== Initialisation des props du generateur =====
  Float4 mat1(   0.8, 0.4, 0.5, 1.0 );

  caPropsGen = new O3dObjProps;
  caPropsGen->ObjPropsFloat4::set( MATERIAL, mat1 );


	caGenTexture = new T3dTexture( "textures/1.gif"  );
  caPropsGen->setTexture( caGenTexture );
  setObjProps( caPropsGen );

  //=============================================


  //======= Positionnement spacial du Generateur ====
  getTransf().TransfDouble3::set( POS, lPos );
  SpriteFloat::set( SPRITE_TIMER1, WorldControler::GetTime());
  SpriteFloat::set( SPRITE_TIMER2, WorldControler::GetTime());

  Double3 spin( 5.0, 8.0, 10.0 );
  SpriteDouble3::set( SPRITE_SPIN, spin );

  cInteract = GL_FALSE;

}
//------------------------
SceneGrotte::~SceneGrotte()
{
}

//------------------------
void
SceneGrotte::makeAsteroide(  Double3& pPos, int pSz, GLboolean pIndestructible ){
	Sprite3d *sp;

	int lFacette = rand()%2+1;

	//	std::cout << "X:" << pPos[0] << " Y:" << pPos[1] << std::endl;

 	Double3 lAngle(randf(360), randf(360), randf(360));
 	Double3 lScale( 1.0+randf(0.2), 1.0+randf(0.2), 1.0+randf(0.2));

	sp = TheAsteroidesMaker->makeSpriteAsteroide( cTypeAsteroide, pSz, lFacette );


	if( pIndestructible == GL_TRUE )
		{
			// Dans ce cas la grotte est indestructible !!
			sp->SpriteFloat::set( SPRITE_LIFE_POINT, 9999999 );
			sp->setAction( SPRITE_ACTION_COLLISION, NULL );
		}

	sp->getTransf().TransfDouble3::set( POS,   pPos );
	sp->getTransf().TransfDouble3::set( ANGLE, lAngle );
	sp->getTransf().TransfDouble3::set( SCALE, lScale );

	Double3 lD3 ( WorldGame::GlobalScroll, 0, 0);
	sp->SpriteDouble3::set( SPRITE_SPEED, lD3);
	WorldControler::Add( sp  );
}
//------------------------
void
SceneGrotte::makeFloor( int pH ){

	int lSz = (rand() % cSizeParoi) + cSizeParoi;

	Double3 lPos(  getTransf().TransfDouble3::get(POS)[0]+(lSz>>1), pH+(lSz>>1), 0 );
	makeAsteroide( lPos, (int)(lSz+randf(1)), GL_TRUE );
}
//------------------------
void
SceneGrotte::makeWall(int pMin, int pMax, GLboolean pIndestructible, float pSpeedX, float pDeltaX, float pAleaX ){

	float cX=0;

	for( int i=pMax;;){


		if( pMin < pMax ) {
			if( i <= pMin )
				break;
			i -=cSizeParoi>>1 ;
		}
		else {
			if( i >= pMin )
				break;
			i +=cSizeParoi>>1 ;
		}

		int lSz = (int) randf(cSizeParoi>>2) + cSizeParoi;
		Double3 lPos(  getTransf().TransfDouble3::get(POS)[0]+cX+(lSz>>2), i+(lSz>>2), randf(lSz>>2) );

		cX += pSpeedX + randf( pAleaX );
		pSpeedX += pDeltaX ;

		makeAsteroide( lPos, lSz, pIndestructible );
	}
}

//------------------------
void
SceneGrotte::makeArtefact() {

	int sz = 25;

	Double3 pos;
  pos[0] = getTransf().TransfDouble3::get(POS)[0];
	pos[ 1 ] = cH;
  pos[ 2 ] = 0;

	std::cout << "SceneGrotte::makeArtefact " << std::endl;

  SpriteFloat::set( SPRITE_TIMER1,  WorldControler::GetTime() );

	if( World::GetPositionWithoutCollision( InteractObstacle, pos, sz, 0, (int)cH ) == GL_FALSE){
		//	std::cout << "SceneGrotte::makeArtefact collision" << std::endl;
		return;
	}
	//	std::cout << "SceneGrotte::makeArtefact ok" << std::endl;


	Sprite3d	*sp = NULL;

	float p = randp( 100 );
	//	std::cout << "p:" << p << std::endl;
  if( p<= 8 )
		{
			Double3 lD3( randf( 75 ), randf( 75 ), randf( 75 ));
			sp = TheBonusMaker->makeSpriteBonus( CONTAINER,
																					 InteractBonus, InteractBonus, 1);

			sp->SpriteDouble3::set( SPRITE_SPIN, lD3);
		}
  else 	if( p <= 30 )
			sp = MAKE_MINE_1;
  else 	if( p <= 50 )
			sp = MAKE_MINE_LASER;
  else 	if( p <= 70 )
			sp = MAKE_MINE_ION;
	else if( p <= 80)
		{
			sp = MAKE_SHIP1(cHardness);
		}
  else	if( p <= 90 )
		{
			sp = MAKE_SHIP2(cHardness);
		}
	else	if( p <= 100 )
		{
			sp = MAKE_SHIP3(cHardness);
		}


	if( sp ) {
		Double3 lD3 ( WorldGame::GlobalScroll, 0, 0);
		sp->SpriteDouble3::set( SPRITE_SPEED, lD3);
		sp->getTransf().TransfDouble3::set( POS, pos );

		WorldControler::Add( sp  );
	}



}
//------------------------
GLboolean
SceneGrotte::animate() {

	Scene::animate();

	Sprite3d *sp;

	float lCurrentTime = WorldControler::GetTime();

	// generation des parois de la grotte

	if( ( lCurrentTime-SpriteFloat::get( SPRITE_TIMER2)) >= cIntervalParoi )
		{
			if( cFirstTime ){
				makeWall(  (((int)cH)>>2)+cSizeParoi,  (int)cH, GL_TRUE,  -8, 1, 2 );
				makeWall( (-((int)cH)>>2)-cSizeParoi, (int)-cH, GL_TRUE,  -8, 1, 2 );
				cFirstTime = GL_FALSE;

			SpriteFloat::set( SPRITE_TIMER3, lCurrentTime+3 + randp(2));
			}


		if( ( lCurrentTime-SpriteFloat::get( SPRITE_TIMER3)) >= 0 )
			{
				SpriteFloat::set( SPRITE_TIMER3, lCurrentTime+5 + randf(2));


				float lHauteur = randp( cH-cSizeParoi*4 )+cSizeParoi;

				float lDeriveX ;
				if(  lHauteur> ((int)cH)>>1 )
					lDeriveX= randf(0.4);
				else
					lDeriveX= randf(0.6);

				float lCorrectX;

				if( lDeriveX > 0.4 || lDeriveX < -0.4 )
					lCorrectX = randp( -lDeriveX/35 );
				else
					lCorrectX = randp( -lDeriveX/25 );


				if( randf(1)< 0 )
					makeWall( (int) -lHauteur,  (int)cH, GL_FALSE, lDeriveX, lCorrectX, randf(1) );
				else
					makeWall( (int)lHauteur,   (int)-cH, GL_FALSE, lDeriveX, lCorrectX, randf(1) );
			}

		makeFloor( (int)cH );
		makeFloor( (int)-cH );
		SpriteFloat::set( SPRITE_TIMER2,  WorldControler::GetTime() );
	}


  if( ( WorldControler::GetTime()-SpriteFloat::get( SPRITE_TIMER1)) < cInterval )
	  return GL_FALSE;


	makeArtefact();

  return GL_FALSE;
}
//------------------------
GLboolean SceneGrotte::leaveWorld()
{
		makeWall(  (((int)cH)>>2)+cSizeParoi,(int)  cH, 6, -1, 2 );
		makeWall( -(((int)cH)>>2)-cSizeParoi,(int) -cH, 6, -1, 2 );

	return GL_FALSE;
}
//**************************************

