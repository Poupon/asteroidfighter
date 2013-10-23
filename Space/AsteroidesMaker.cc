#include <stdlib.h>

#include <Sprite3d/ObjPart.h>
#include <Sprite3d/Sprite3d.h>
#include <Sprite3d/Utils3d.h>
#include <Sprite3d/Collision.h>
#include <Sprite3d/ObjText2d.h>
#include <Sprite3d/Random.h>
#include <Sprite3d/ObjOdron.h>

#include <WorldGame.h>

#include <U3d/SpriteExplosion.h>

#include <T3d/T3dLoadImg.h>

#include <AsteroidesMaker.h>
#include <Space/Def.h>

AsteroidesMaker* TheAsteroidesMaker=NULL;

#define ASTEROIDE_TYPE   SPRITE_USER1


// **********************************************************
AsteroidesMaker::AsteroidesMaker()
:cColorGrey(  0.5, 0.5, 0.5, 1.0 ),
cColorSnow(  0.6, 0.6, 1.0, 1.0 ),
 cColorIce(  0.6, 0.6, 1.0, 0.5),
//cColorCristal1(  0.3, 0.4, 0.8, 0.05),
cColorCristal1(  0.8, 0.4, 0.2, 0.05),
  cColorCristal2(  0.8, 0.5, 0.8, 0.15)
{
  TheAsteroidesMaker = this;


  cPropsSnow.ObjPropsFloat4::set( MATERIAL, cColorSnow );
  cPropsIce.ObjPropsFloat4::set( MATERIAL, cColorIce );

  cPropsCristal1.ObjPropsFloat4::set( MATERIAL, cColorCristal1 );
  cPropsCristal2.ObjPropsFloat4::set( MATERIAL, cColorCristal2 );


 // cPropsLune.ObjPropsFloat4::set( MATERIAL, cColorGrey );
  T3dLoadImage imgLune( "textures/3.gif" );
  caTexLune = new T3dTexture( imgLune.width, imgLune.height, imgLune.makeRGBA() );
  cPropsLune.setTexture( caTexLune );

  T3dLoadImage imgMars( "textures/39.gif" );
  caTexMars = new T3dTexture( imgMars.width, imgMars.height, imgMars.makeRGBA() );
  cPropsMars.setTexture( caTexMars );

  T3dLoadImage imgWater( "textures/48.gif" );
  caTexWater = new T3dTexture( imgWater.width, imgWater.height, imgWater.makeRGBA() );
  cPropsWater.ObjPropsFloat4::set( MATERIAL, cColorIce );
  cPropsWater.setTexture( caTexWater );

}
//---------------------------------------
O3dObj*
AsteroidesMaker::makeAsteroide( float pSz, int pFacette )
{
	O3dObj * lObj =  new ObjOdron( pSz, pFacette );
	lObj->setRadius( pSz );
	return lObj;
}
//---------------------------------------
ObjVect*
AsteroidesMaker::makeAsteroideSnow(float pSz, int pFacette )
{
	ObjVect* lOvect = new ObjVect;
	O3dObj * lObj;

	lOvect->push_back( (lObj=new ObjOdron(  pSz, pFacette) ));

	for( int i=0; i< pSz*0.2; i++)
	{
	 lOvect->push_back( (lObj=new ObjOdron( randp( pSz-3)+3, (int) randp( pFacette-2)+2 )));
	 Double3 lD3( randf(pSz), randf(pSz),randf(pSz));
	 lObj->getTransf().TransfDouble3::set( POS, lD3 );
	}

	lOvect->setRadius( pSz );
	lOvect->setObjProps( &cPropsSnow);
	return lOvect;
}

//---------------------------------------
ObjVect*
AsteroidesMaker::makeAsteroideCristal(float pSz, int pFacette )
{
	ObjVect* lOvect = new ObjVect;
	O3dObj * lObj;



	for( int i =3; i < pSz+2; i +=2)
	{
      lOvect->push_back( (lObj=new ObjOdron(  -i, pFacette) ));
      lObj->setObjProps( &cPropsCristal1);
 	 Double3 lD3( randf(360), randf(360),randf(360));
	 lObj->getTransf().TransfDouble3::set( ANGLE, lD3 );
    }
 /*
	for( int i =3; i < 4; i++ )
	{
	  lOvect->push_back( (lObj=new ObjOdron(  pSz-i*5, pFacette) ));
 	 Double3 lD3( randf(360), randf(360),randf(360));
	 lObj->getTransf().TransfDouble3::set( ANGLE, lD3 );
    }
     */
//	for( int i=0; i< pSz*0.5; i++)
/*	{
		lOvect->push_back( (lObj=new ObjOdron( randp( pSz*0.3)+1, (int) randp( 3)+1 )));
		Double3 lD3( randf(pSz*0.6)+1, randf(pSz*0.6)+1,randf(pSz*0.6)+1);
	    lObj->getTransf().TransfDouble3::set( POS, lD3 );
	}
	*/
	lOvect->setRadius( pSz );
	lOvect->setObjProps( &cPropsCristal2);
	return lOvect;
}

//---------------------------------------
O3dObj*
AsteroidesMaker::makeAsteroideIce( float pSz, int pFacette )
{
	O3dObj * lObj = new ObjOdron(  pSz, pFacette);

	lObj->setRadius( pSz );
	lObj->setObjProps( &cPropsIce);
	return lObj;
}
//----------------------------------------------
Sprite3d*
AsteroidesMaker::makeSpriteAsteroide( EnumAsteroides pType, float pSz, int pFacette )
{
  Sprite3dObj *sp ;

  switch( pType )
  {
  case ASTEROIDE_PIERRE:
		sp = new Sprite3dObj( makeAsteroide( pSz, pFacette));
		sp->getObj()->setObjProps( &cPropsLune );
		break;
  case ASTEROIDE_MARS:
		sp = new Sprite3dObj( makeAsteroide( pSz, pFacette));
		sp->getObj()->setObjProps( &cPropsMars );
		break;
  case ASTEROIDE_WATER:
		sp = new Sprite3dObj( makeAsteroide( pSz, pFacette));
		sp->getObj()->setObjProps( &cPropsWater );
		break;
  case ASTEROIDE_SNOW:
		sp  = new Sprite3dObj( makeAsteroideSnow( pSz, pFacette));
		break;
	case ASTEROIDE_CRISTAL:
		sp  = new Sprite3dObj( makeAsteroideCristal( pSz, pFacette));
		break;
	case ASTEROIDE_ICE:
  default:
		sp  = new Sprite3dObj( makeAsteroideIce( pSz, pFacette));
  }
	sp->SpriteFloat::set( ASTEROIDE_TYPE, pType );

	// Comme chaque object est unique il doit etre detruit a la mort du sprite
  sp->setDeepDestroy(GL_TRUE);

  sp->setMask( InteractObstacle, InteractObstacle );
  sp->setAction( SPRITE_ACTION_COLLISION, this);
  sp->SpriteFloat::set( SPRITE_LIFE_POINT, pSz*2 );
  sp->SpriteFloat::set( SPRITE_MAX_LIFE_POINT, pSz*2 );
  sp->SpriteFloat::set( SPRITE_DESTROY_POINT, 1+pSz/4 );
  sp->SpriteLong::set ( SPRITE_TYPE, ASTEROIDE );

  return sp;
}
//------------------------------------------------
GLboolean
AsteroidesMaker::collision( Sprite3d &pMySprite, Sprite3d &pSprite, void *pParam )
{

	if( pSprite.getDefMask() == InteractObstacle )
	{
		return GL_TRUE;

		if(  pMySprite.getObjectId() != pSprite.cLastColId
		|| pSprite.getObjectId() != pMySprite.cLastColId)
		{
			Double3 speed1( pMySprite.SpriteDouble3::get( SPRITE_SPEED ));
			Double3 speed2( pSprite.SpriteDouble3::get( SPRITE_SPEED ) );

			pMySprite.getTransf().TransfDouble3::get( POS ) -= speed1;
			pSprite.getTransf().TransfDouble3::get( POS ) -= speed2;

			// On revient en vitesse par seconde !!!!!
			speed1 /= WorldControler::GetRatio();
			speed2 /= WorldControler::GetRatio();

		//	diff = pMySprite.getRadius()/pSprite.getRadius();
		//	if( diff >
/*
			if( speed1[ 0 ]*speed2[ 0 ]>0 )
			{
			}
			else
			{
				speed1[ 0 ] = -speed1[ 0 ];
				speed2[0]  = -speed2[0];
			}

			if( speed1[ 1 ]*speed2[ 1 ]>0 )
			{
			}
			else
			{
				speed1[ 1 ] = -speed1[ 1 ];
				speed2[1]  = -speed2[1];
			}
			*/
/*

			//cout << "speed1:" ; print(//cout, speed1) << endl;
			//cout << "speed2:" ; print(//cout, speed2) << endl;

			Double3 erg1( speed1 );
			Double3 erg2( speed2 );
			//cout << "Radius1:"<< pMySprite.getRadius() <<endl;
			//cout << "Radius2:"<<  pSprite.getRadius() <<endl;
 			erg1 *= pMySprite.getRadius();
 			erg2 *= pSprite.getRadius();

			//cout << "erg1:" ; print(//cout, erg1) << endl;
			//cout << "erg2:" ; print(//cout, erg2) << endl;

			Double3 don1( erg1 );
			Double3 don2( erg2 );
			don1 /= 2;
			don2 /= 2;

			//cout << "don1:" ; print(//cout, don1) << endl;
			//cout << "don2:" ; print(//cout, don2) << endl;

			erg1 -= don1;
			erg2 -= don2;
			erg1 += don2;
			erg2 += don1;
			//cout << "erg1:" ; print(//cout, erg1) << endl;
			//cout << "erg2:" ; print(//cout, erg2 )<< endl;

			erg1 /= pMySprite.getRadius();
			erg2 /= pSprite.getRadius();

			//cout << "erg1:" ; print(//cout, erg1) << endl;
			//cout << "erg2:" ; print(//cout, erg2) << endl;

			pMySprite.SpriteDouble3::set( SPRITE_SPEED, erg1 );
			pSprite.SpriteDouble3::set( SPRITE_SPEED, erg2 );
*/


			pSprite.cLastColId = pMySprite.getObjectId();
			pMySprite.cLastColId = pSprite.getObjectId();

			pMySprite.SpriteDouble3::set( SPRITE_SPEED, speed1 );
			pSprite.SpriteDouble3::set( SPRITE_SPEED, speed2 );
/*
			float diff = pMySprite.getRadius()/pSprite.getRadius();
			if( diff < 1.33 || diff > 0.75)
			{
				pMySprite.SpriteDouble3::set( SPRITE_SPEED, speed2 );
				pSprite.SpriteDouble3::set( SPRITE_SPEED, speed1 );
			}
			if( diff > 1.33  )
			{
				speed2.inverse();
				pSprite.SpriteDouble3::set( SPRITE_SPEED, speed2 );
			}
			else
			{
				speed1.inverse();
				pMySprite.SpriteDouble3::set( SPRITE_SPEED, speed1 );
			}
*/
		}
		return GL_TRUE;
	}

	pMySprite.SpriteFloat::set( SPRITE_LIFE_POINT,
								pMySprite.SpriteFloat::get( SPRITE_LIFE_POINT )-pSprite.SpriteFloat::get( SPRITE_DESTROY_POINT ));


	if( pMySprite.SpriteFloat::get( SPRITE_LIFE_POINT ) <= 0 )
	{
		int max = static_cast<long>(randp(pMySprite.getRadius()*0.5)+1.0);
		for( int j=0; j< max+1; j++)
		{
			SpriteExplosion *sp = new SpriteExplosion( 1.3+randp(pMySprite.getRadius()), 0.3+randp(0.3) );
			sp->setTransf( pMySprite.getTransf() );
			sp->setObjProps( SpriteExplosion::caExplosionProps );
  	        WorldControler::Add( sp );
		}

		int pSz = static_cast< int>(pMySprite.getRadius()*0.6);
		if( pSz > 30 )
		{
			std::cout << "***************** pSz=" << pSz << std::endl;
			pSz = 30;
		}
		for( int i = 0; i < pSz; i++ )
		{
			float sz = randp(pSz);

			if( sz < 1.0 )
				continue;


 			int w = rand()%2+1;

			long lType = (long)pMySprite.SpriteFloat::get( ASTEROIDE_TYPE );

			Sprite3d *sp = makeSpriteAsteroide( (EnumAsteroides)lType, sz, w );

			 sp->setTransf( pMySprite.getTransf() );

			 Double3 v3( randf(WorldGame::GlobalScroll)+WorldGame::GlobalScroll , randf(WorldGame::GlobalScroll), 0.0 );
			 sp->SpriteDouble3::set( SPRITE_SPEED, v3 );
			 sp->Sprite3d::animate();
			 sp->Sprite3d::animate();
			 sp->Sprite3d::animate();

			 WorldControler::Add( sp );
		}
	    WorldControler::KillSprite( &pMySprite );
	}
	else
	{
		pMySprite.SpriteDouble3::get( SPRITE_SPEED)[0] =  pMySprite.SpriteDouble3::get( SPRITE_SPEED )[0]*0.95;
	}
	return GL_TRUE;
}
//**************************
