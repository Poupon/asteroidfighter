

//*************************************************

class Collision2{

protected:

	Double3 cMul;
	int cDim;
	int cNbDiv;
	
	VSprite3d**cTab;
};
//*************************************************
//--------------------------------
void
Collision2::Collision2( int pDim, float pMax, int pNbDiv )
	:cDim(pDim),
	 cNbDiv(pNbDiv),
	 cTab(NULL)
{
	cMul = pNbDiv/pMax;

	cTab = new VSprite3d*[pNbDiv];

	for( int i=0; i<pNbDiv; i++)
		cTab[i] = NULL;
}
//--------------------------------
Collision2::~Collision2()
{
	for( int i=0; i<pNbDiv; i++)
		delete cTab[i];

	delete []cTab;
}
//--------------------------------
void
Collision2::add( Sprite3d *pSprite )
{
	if( cTab[i] == NULL)
		cTab[i] = new VSprite3d;

	cTab[i]->push_back( pSprite );
}
//--------------------------------
Collision2::set( VSprite3d& vSprite, int pDim )
{

	for( std::vector <Sprite3d*>::iterator iter1 = vSprite.begin(); iter1 != vSprite.end(); ++iter1 )
		{
			if( (*iter)->getInteract() != InteractNull )				
				set( (*iter));
		}
}
//--------------------------------
void 
Collision2::set( Sprite3d *pSprite)
{
	float lPos = pSprite->getTransf().TransfDouble3::get( POS)[cDim];
	int lPosMin = (lPos-pSprite->getRadius())*cMul;
	int lPosMax = (lPos+pSprite->getRadius())*cMul;

	if( lPosMin < 0 )      lPosMin = 0;
	if( lPosMax > cNbDiv ) lPosMax = cNbDiv-1;

	for( int i=lPosMin; i< lPosMax; i++)
		add( i, pSprite );	
}
//--------------------------------


void
Exploit(  VSprite3d& vSprite, listCol, *pDim, *pMax, *pNbDiv, nbDim )
{
	if( nbDim <= 0 )
		ScanCell(lVSprite, listCol );
	
	Collision2 pCol( pDim[0], pMax[0], pNbDiv[0] );

	pCol.set( vSprite );
	
	while( pCol.ok() )
		{			
			VSprite3d* lVSprite = pCol.get(i); // ne renvoit que si au moins 2
			if( lVSprite.size() < 3 )
				{
					Detection( A, B, listCol );
					continue;
				}

			if( nbDim > 0 )
				Exploit( lVSprite, listCol, pMax+1, pMax+1, &pNbDiv+1, nbDim-1 );				
		}
}


pDim = {0, 1, 2 };
Float3 Dim={100, 200, 300};
Int3   Div={10, 10, 10);

Exploit( listspprite, listcol,  3 );
