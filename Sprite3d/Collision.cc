#include <Collision.h>
#include <algorithm>
#include <Sprite3d.h>
#include <iostream>

static const unsigned long coll_mask= 0x3F;
static const unsigned long coll_dec = 0x0A;

// Optimisation on pourrait peut etre allouer directement new VSprite3d[pNbDiv]
// cela pourrait

#define DBGOUT if( 0 ) std::cout

//**************************************
// 2013 pDim represente la dimension de decoupage ? x 0 y 1 z 2 ?

Collision::Collision(  int pDim, GLdouble pMin, GLdouble pMax, int pNbDiv )
	:cTab(NULL),
	 cDim(pDim),
	 cNbDiv(pNbDiv),
	 cPosIter(0),
	 cMin( pMin)
{
	cMul = pNbDiv/(pMax-pMin);

	DBGOUT << "Collision cMul:" << cMul << std::endl;

	cTab = new VSprite3d*[pNbDiv];

	for( int i=0; i<pNbDiv; i++)
		cTab[i] = NULL;
}
//--------------------------------
Collision::~Collision()
{
	for( int i=0; i< cNbDiv; i++)
		delete cTab[i];

	delete []cTab;
}
//--------------------------------
void
Collision::add( int pPos, Sprite3d *pSprite )
{
	DBGOUT << " pos:" << pPos ;
	if( cTab[pPos] == NULL)
		{
			DBGOUT << " alloc ";
			cTab[pPos] = new VSprite3d;
		}

	DBGOUT << std::endl;

	cTab[pPos]->push_back( pSprite );
}
//--------------------------------
void
Collision::set( VSprite3d& vSprite  )
{
	for( std::vector <Sprite3d*>::iterator iter = vSprite.begin(); iter != vSprite.end(); ++iter)
		{
			if( (*iter)->getInteract() != InteractNull )
				set( (*iter));
		}
}
//--------------------------------
void
Collision::set( Sprite3d *pSprite )
{
	// On va dispose le sprite dans une des cases du tableau en fonction
	// de sa position

	float lPos = pSprite->getTransf().TransfDouble3::get( POS )[cDim];

	int lPosMin = static_cast<int>(((lPos-cMin)-pSprite->getRadius())*cMul);
	int lPosMax = static_cast<int>(((lPos-cMin)-pSprite->getRadius())*cMul);

	//	DBGOUT << "Pos:" << lPos << " -> " << lPos-cMin << " -> " << (lPos-cMin)-pSprite->getRadius() << " -> " << lPosMin << std::endl;
	//	DBGOUT << "Pos:" << lPos << " -> " << lPos-cMin << " -> " << (lPos-cMin)+pSprite->getRadius() << " -> " << lPosMax << std::endl;

	// En dehors ?
	if( lPosMin > cNbDiv
			|| lPosMax < 0 )
		return ;


	if( lPosMin < 0 )       lPosMin = 0;
	if( lPosMax >= cNbDiv ) lPosMax = cNbDiv-1;

	for( int i=lPosMin; i<= lPosMax; i++)
		add( i, pSprite );
}
//--------------------------------
VSprite3d*
Collision::next()
{
	while( cPosIter < cNbDiv )
		{
			if( cTab[cPosIter]
					&& cTab[ cPosIter]->size() > 1 )
				return cTab[ cPosIter++];

			cPosIter++;
		}

	return NULL;
}

int lNbCalcul=0;

//--------------------------------
// Essaye de restreindre le nombre de test de collision
// en classant les sprites en fonction de leur position
// selon les diffentes dimensions spatiales
// efficace si beaucoup de Sprites, et s'ils sont disperse
// relativement equitablement dans l'espace

// A DEBUGGER !!!!!

// static 
void
Collision::SpatialDetection(  VSprite3d& pVSprite, int *pDim, GLdouble *pMin, GLdouble *pMax, int *pNbDiv, int pNbDim )
{
	if( pNbDim <= 0 )
		{
			// fin de la recursion
			SimpleDetection( pVSprite );
			return ;
		}

	DBGOUT << " ------- SpatialDetection Dim:" << *pDim << " min:" << *pMin << " max:" << *pMax
			 << " div:" << *pNbDiv << " reste:" << pNbDim << std::endl;

	Collision pCol(  *pDim, *pMin, *pMax, *pNbDiv );

	pCol.set( pVSprite );

	VSprite3d* pResult;
	while( (pResult = pCol.next()) != NULL )
		{
			DBGOUT << "Eval Result: " << pResult->size()  << " dim:" << pNbDim <<std::endl;
			if( pResult->size() == 2 || pNbDim == 1 )
				{
					SimpleDetection( *pResult );
					continue;
				}

			// Recursion avec la dimension spatiale suivante

			SpatialDetection( *pResult, pDim+1, pMin+1, pMax+1, pNbDiv+1, pNbDim-1 );
		}
}

//----------------------------------------
// Detecte et appelle la proc de collision
// Algo en factorielle N (peu efficace pour de nombreux sprites)

// static 

long 
Collision::SimpleDetection(VSprite3d& pVSprite)
{
	int lCpt=0;
	int lCpt2=0;

	for( VSprite3d::iterator iter = pVSprite.begin(); iter != pVSprite.end()-1; ++iter )
		{
			if( (*iter)== nullptr ) continue;

			if( (*iter)->getInteract() == InteractNull )
				continue;

			unsigned int maskA_Def = (*iter)->getDefMask();
			unsigned int maskA_Att = (*iter)->getAttMask();

			for( VSprite3d::iterator iter2 = iter + 1; iter2 != pVSprite.end(); ++iter2 )
				{
				if( (*iter2)== nullptr ) continue;

				if( (*iter2)->getInteract() == InteractNull )
						continue;

					lNbCalcul++;
					lCpt++;

					unsigned int maskB_Def =  (*iter2)->getDefMask();
					unsigned int maskB_Att = (*iter2)->getAttMask();

					if(  ((maskA_Def & maskB_Att ) || (maskA_Att & maskB_Def ))
							 && DetectCollision( *(*iter), *(*iter2) ) )
						{
							lCpt2++;

							if(  (maskA_Def & maskB_Att ) )
								(*iter)->collision( *(*iter2) );

							if( (maskB_Def & maskA_Att ) )
								(*iter2)->collision( *(*iter) );
						}
				}
		}

	DBGOUT << " SimpleDetection: " << pVSprite.size() << " " << lCpt << " -> " << lCpt2 << std::endl;
	return lCpt2;
}

//--------------------------------
// static 

GLboolean Collision::DetectCollision( Sprite3d &A, Sprite3d &B )
{
	Double3 lDist( A.getTransf().get( POS ));
	lDist -= B.getTransf().get( POS );


	float lRadius = A.getRadius() + B.getRadius();
	if( (lDist[ 0 ]*lDist[ 0 ] + lDist[ 1 ]*lDist[ 1 ] + lDist[ 2 ]*lDist[ 2 ]) < (lRadius *lRadius) )
		return GL_TRUE;

	return GL_FALSE;
}
//**************************************
/*
Exemple d appel

int   lDim[3]={ 2, 0, 1};          // d abord en z, x, puis y
float lMin[3]={ -2000, -1000, -500 }; // dimension du monde en z, x, y
float lMax[3]={ 2000, 1000, 500 }; // dimension du monde en z, x, y
int   lNbDiv[3]={ 50, 20, 10 };    // Nombre de division pour chaque dimension (a regler celon la taille des sprites )


SpatialDetection(  cSpriteVecteur, lDim, lMin, lMax, lNbDiv, 3 );

// On aurait pu aussi mettre 1 ou 2 dimension !

Attention un meme sprite peut etre appeler plusieurs fois pour une meme
collision avec SpatialDetection (si deux sprites sont sur la limite d une case)
(il faudrait faire une liste des collisions detecter, et faire un traitement sur les doublons)

il faudrait renvoyer une liste de couple de sprites, et faire 	std::unique( cMemCell.begin(), cMemCell.end());

*/
//**************************************
