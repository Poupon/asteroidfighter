#include <GL/glut.h>

#include <O3d/O3dKamera.h>
#include <T3d/T3dPrimitiv.h>
#include <T3d/T3dColor.h>
#include <T3d/T3dFont.h>
#include <T3d/T3dFontRaster.h>


#include <iostream>

#include <World.h>
#include <WorldControler.h>
#include <ObjOdron.h>
#include <Sprite3d.h>
#include <Collision.h>
#include <Sprite3dPilot.h>


//--------------------------------
inline void
RemoveSprite(  Sprite3d *pSp,  VSprite3d& vect )
{
	for( VSprite3d::iterator iter = vect.begin(); iter != vect.end(); iter++ )
		if( *iter == pSp )
			vect.erase( iter );
}

//**************************************

World::World( WorldControler *pControl, O3dKamera* pKamera, Double3& pMax, O3dObjProps*pProps )
:cPilot( NULL ),
 cProps( pProps ),
 cMyControler(pControl),
 cKamera(pKamera),
 cOverlayOpen( GL_FALSE ),
 cBox( pMax, pMax )
{
	for( int i = 0; i < 3; i++ )
	{
		cBox.getMin()[i] = -cBox.getMax()[i] ;
	}

}
//--------------------------------
World::~World()
{
	empty();
}
//--------------------------------
void
World::add( Sprite3d *pSprite ){
	cNewSprite.push_back( pSprite );
}
//--------------------------------
void
World::empty()
{
	killAllSprite(); // y compris cPilot
	cPilot = NULL;
}
//--------------------------------
void
World::gameOver()
{
	//	cPilot = NULL;
}
//--------------------------------
void
World::gameWinner()
{
	//	cPilot = NULL;
}
//--------------------------------
GLboolean
World::initOverlay()
{
	int transparent, red, white;

	//	glutInitDisplayMode(GLUT_SINGLE | GLUT_INDEX);
	int overlaySupport = glutLayerGet(GLUT_OVERLAY_POSSIBLE);

	if (overlaySupport)
		{

			glutEstablishOverlay();
			glutHideOverlay();
			transparent = glutLayerGet(GLUT_TRANSPARENT_INDEX);
			glClearIndex(transparent);
			red = (transparent + 1) % glutGet(GLUT_WINDOW_COLORMAP_SIZE);
			white = (transparent + 2) % glutGet(GLUT_WINDOW_COLORMAP_SIZE);
			glutSetColor(red, 1.0, 0.0, 0.0);  /* Red. */
			glutSetColor(white, 1.0, 1.0, 1.0);  /* White. */
			////////		glutOverlayDisplayFunc(redrawOverlay);
			////////			glutReshapeFunc(reshape);
			cOverlayOpen = GL_TRUE;

		}
	else
		{
			std::cout << "Overlay failed" << std::endl;
		}

	return cOverlayOpen;
}
//--------------------------------
//----------- DRAW --------------
//--------------------------------
void World::drawWorld()
{
  if( cPilot )
		cPilot->drawControl();

  cKamera->exec();
//	  T3dPrimitiv::DrawRepere( 120, 1 );
	//	T3dPrimitiv::DrawGrid( 100, 10 );

 // cLiveObj.drawObj( getProps() );
  drawLiveSprite();

}
//--------------------------------
void World::drawLiveSprite()
{
	O3dViewProps lViewProps( *getKamera() );
	lViewProps.setDefaultFont( T3dFont::DefaultFont );
	// IMPLEMENTER UNE POLICE !!!!!!
	lViewProps.ViewPropsBool::set( DRAW_ID, GL_FALSE);
	for( std::vector <Sprite3d*>::iterator iter = cLiveSprite.begin(); iter != cLiveSprite.end(); ++iter )
	{
		(*iter)->makeDraw( lViewProps, cProps );
	}
}
//-------------------------------------------------
void World::reshapeWorld(int pWidth, int pHeight)
{

}
//-------------------------------------------------
// Determine si un des sprites intersecte avec une zone

Sprite3d*
World::isSpriteIntersect( Double3 pPos, float pRadius, unsigned int pMmask_Att)
{
	for( std::vector <Sprite3d*>::iterator iter = cLiveSprite.begin(); iter != cLiveSprite.end(); ++iter )
	{
		unsigned int mask_Def = (*iter)->getDefMask();
		if( (mask_Def & pMmask_Att) )
		{

			if( (*iter)->intersect( pPos, pRadius ) == GL_TRUE )
				return (*iter);
		}
		else {
		}

	}
	return NULL;
}
//-------------------------------------------------
// Determine si un des sprites intersecte avec une zone

Sprite3d*
World::isSpriteIntersectXY( Double3 pPos, float pRadius, unsigned int pMmask_Att)
{
	for( std::vector <Sprite3d*>::iterator iter = cLiveSprite.begin(); iter != cLiveSprite.end(); ++iter )
	{
		unsigned int mask_Def = (*iter)->getDefMask();
		if( (mask_Def & pMmask_Att) )
		{

			if( (*iter)->intersectXY( pPos, pRadius ) == GL_TRUE )
				return (*iter);
		}
		else {
		}

	}
	return NULL;
}

//--------------------------------
//----------- ANIMATE ------------
//--------------------------------
extern int lNbCalcul;

void World::animateLiveSprite()
{
	//	std::cout << "World::animateLiveSprite " << cNewSprite.size() << std::endl;


		// Ajout des nouveau Sprite
	for( std::vector <Sprite3d*>::iterator iter1 = cNewSprite.begin(); iter1 != cNewSprite.end(); ++iter1 )
	{
		Sprite3d* lSprite = *iter1;
		//		std::cout << "World::animateLiveSprite " << lSprite << std::endl;
		cLiveSprite.push_back( lSprite );
	}

	cNewSprite.clear();

		// Boucle d animation
	for( std::vector <Sprite3d*>::iterator iter2 = cLiveSprite.begin(); iter2 != cLiveSprite.end(); ++iter2 )
		{
			(*iter2)->animate();
		}

	lNbCalcul = 0;

	// Detection et resolution des collisions
    Collision::SimpleDetection( cLiveSprite );

//	int   lDim[2]={ 0, 1 };
//	int   lNbDiv[2]={ 10, 10 };
//	cout << "***********************************" <<endl;
//	Collision::SpatialDetection( cLiveSprite, &lDim[0], cBox.getMin(), cBox.getMax(), &lNbDiv[0], 2 );
//	cout << "Collision " << cLiveSprite.size() << "/" << lNbCalcul <<endl;


		// Elimination logique des Sprite sortie du monde
	for( std::vector <Sprite3d*>::iterator iter3 = cLiveSprite.begin(); iter3 != cLiveSprite.end(); ++iter3 )
	{
		if( cBox.isInto( (*iter3)->getTransf().TransfDouble3::get(POS)) == GL_FALSE
			&& (*iter3)->leaveWorld() == GL_TRUE)
			{
				cDeadSprite.push_back( (*iter3) ); // On stocke le pointer sur le tableau
			}
	}


		// Elimination physique des Sprite morts // Inverser boucle si strl::vector

	// TODO a optimiser !!!
	for( std::vector<Sprite3d*>::iterator iter4 = cDeadSprite.begin(); iter4 != cDeadSprite.end(); iter4++ )
		{
			for( VSprite3d::iterator iter5 = cLiveSprite.begin(); iter5 != cLiveSprite.end(); iter5++ )
			{
				if( *iter4 == *iter5 )
				{
					delete( *iter5 );
					*iter5 = NULL;
					cLiveSprite.erase( iter5 );
					break;
				}
			}
		}

	cDeadSprite.clear();
}
//--------------------------------
void
World::removeSprite(  Sprite3d *pSp )
{
	RemoveSprite( pSp, cLiveSprite );
	RemoveSprite( pSp, cDeadSprite );
	RemoveSprite( pSp, cNewSprite );
}
//--------------------------------
void
World::deleteSprite( Sprite3d* pSprite)
{
	if(pSprite ->getDeleteControler() == NULL)
		delete pSprite;
	else
		pSprite->getDeleteControler()->execDelete( pSprite  );
}
//--------------------------------
void World::killAllSprite()
{
#ifndef PC_WINDOWS
	for( std::vector < Sprite3d *> ::iterator iter = cNewSprite.begin(); iter != cNewSprite.end(); ++iter )
		deleteSprite( *iter );

	for( std::vector < Sprite3d *> ::iterator iter2 = cLiveSprite.begin(); iter2 != cLiveSprite.end(); ++iter2 )
		deleteSprite( *iter2 );

	for( std::vector < Sprite3d *> ::iterator iter3 = cDeadSprite.begin(); iter3 != cDeadSprite.end(); ++iter3 )
		deleteSprite( *iter3 );
#endif
	cNewSprite.clear();
	cLiveSprite.clear();
	cDeadSprite.clear();

}
//--------------------------------
void World::animateWorld()
{
	animateLiveSprite();
}
//--------------------------------
//---------- EVENT ---------------
//--------------------------------

void World::mouseMove( int pX, int pY )
{
	if( cPilot )
		cPilot->mouseMove( pX, pY );
}
//--------------------------------
void World::key( unsigned char pKey, int pX, int pY )
{
	if( cPilot )
		cPilot->key( pKey, pX, pY );
}
//--------------------------------
void World::mouseButton( int pButton, int pState, int pX, int pY)
{
	if( cPilot )
		cPilot->mouseButton( pButton, pState, pX, pY );
}
//--------------------------------
void
World::setPilot( int pX, int pY )
{
	if( cPilot )
		cPilot->mouseMove( pX, pY );
}

//--------------------------------
void
World::setPilotKey(unsigned char pKey, int pX, int pY  )
{
	if( cPilot )
		cPilot->key( pKey, pX, pY );
}
//--------------------------------
void
World::setPilotSpecialKey(unsigned char pKey, int pX, int pY  )
{
	if( cPilot )
		cPilot->key( pKey, pX, pY );
}
//--------------------------------
void
World::setPilotKeyUp(unsigned char pKey, int pX, int pY  )
{
	if( cPilot )
		cPilot->key( pKey, pX, pY );
}
//------------------------------------------------

GLboolean
World::GetDistPilot( Sprite3d *pSprite,  Double3 & pDist )
{
	Sprite3d* lPilot = WorldControler::GetCurrentWorld()->getPilot();
	if( lPilot == NULL )
		return GL_FALSE;

	O3dObj::GetObjectDistance( lPilot, pSprite, pDist );
	return GL_TRUE;
}
//------------------------
GLboolean
World::GetPositionWithoutCollision( int pInteract, Double3& pPos, int pSize, int pLimitX, int pLimitY, int pLimitZ, int pNbTry, float pMarge ){

	int i;
  for( i = 0; i < pNbTry; i++ ) {
		if( pLimitX != 0 )
			pPos[ 0 ] = (rand()%(pLimitX << 1))-pLimitX;

		if( pLimitY != 0 )
			pPos[ 1 ] = (rand()%(pLimitY << 1))-pLimitY;

		if( pLimitZ != 0 )
			pPos[ 2 ] = (rand()%(pLimitZ << 1))-pLimitZ;

		if( WorldControler::GetCurrentWorld()->isSpriteIntersect( pPos, pSize*pMarge, pInteract ) == NULL ){
			return GL_TRUE;
		}
	}

	return GL_FALSE;
}

//--------------------------------

//**************************************

