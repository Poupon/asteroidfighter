
#ifndef h_World_h
#define h_World_h


#include <T3d/T3dBox.h>
#include <O3d/O3dObjProps.h>
#include <O3d/O3dKamera.h>

#include <Sprite3d/ObjVect.h>
#include <T3d/T3dFont.h>


#include <Sprite3d/SoundLibrary.h>

class Sprite3d;

class O3dKamera;
class Sprite3dPilot;

class WorldControler;

//**************************************

class World
{
protected:
	WorldControler *cMyControler;
	ObjVect cLiveObj;
	std::vector <Sprite3d*> cServiceSprite;

	std::vector <Sprite3d*> cNewSprite;
	std::vector <Sprite3d*> cLiveSprite;
	std::vector <Sprite3d*> cDeadSprite;

	O3dKamera*   cKamera;
	Sprite3dPilot *cPilot;
	O3dObjProps *cProps;

	T3dBox cBox; // The size of this world !

	GLboolean cOverlayOpen;

	SoundLibrary* cMySoundLibrary;

public:

	World( WorldControler* pControl, O3dKamera* pKamera, Double3& pMax, O3dObjProps *pProps=NULL);
	virtual~World();

	void setProps( O3dObjProps *pProps ) {cProps = pProps; }
	O3dObjProps *getProps() {return cProps; }


	void killSprite( Sprite3d *pSp )
	{
		cDeadSprite.push_back( pSp );
		//cLiveSprite.erase( pSp );
	}

	void removeSprite(  Sprite3d *pSp );
	void deleteSprite( Sprite3d* pSprite);

	void killAllSprite();

	virtual void add( O3dObj *pObj ){ cLiveObj.push_back( pObj ); }
	virtual void add( Sprite3d *pSprite );
	
	
	WorldControler * getMyControler() { return cMyControler;}
	void setMyControler(WorldControler *pControl) { cMyControler=pControl;}

	SoundLibrary* setMySoundLibrary( SoundLibrary* pMySoundLibrary )
	{
		SoundLibrary* lTmpSoundLibrary = cMySoundLibrary;
		cMySoundLibrary = pMySoundLibrary;
		return lTmpSoundLibrary;
	}
	SoundLibrary* getMySoundLibrary() { return cMySoundLibrary; }

	T3dBox & getBox()	{ return cBox; 	}
	
	virtual void setPilot( Sprite3dPilot *pPilot )	{		cPilot = pPilot;	}
	virtual Sprite3dPilot *getPilot() { return cPilot; }
	virtual void setKamera( O3dKamera *pKamera )   	{ cKamera= pKamera;	}
	virtual O3dKamera* getKamera() {return cKamera; }

	Sprite3d *isSpriteIntersect( Double3 pPos, float pRadius, unsigned int pMmask_Att );
	Sprite3d *isSpriteIntersectXY( Double3 pPos, float pRadius, unsigned int pMmask_Att );


	GLboolean initOverlay();
	GLboolean asOverlay() { return cOverlayOpen; }



	virtual const char* getInfoLeveL() { return "";}

	// Draw

	virtual void drawWorld();


	// Animate
	virtual void animateWorld();
	virtual void animateLiveSprite();
	virtual void drawLiveSprite();


	// Event
	virtual void mouseMove( int pX, int pY );
	virtual void mouseButton( int pButton, int pState, int pX, int pY );
	virtual void key( unsigned char pKey, int pX, int pY );
	virtual void setPilot( int pX, int pY );
	virtual void setPilotKey(unsigned char pKey, int pX, int pY  );
	virtual void setPilotKeyUp(unsigned char pKey, int pX, int pY  );
	virtual void setPilotSpecialKey(unsigned char pKey, int pX, int pY  );


	virtual GLboolean initStart(int pNiveau=0)=0;
	virtual void freeRessources() {;}
	virtual void empty();
	virtual void gameOver();
	virtual void gameWinner();

	virtual int userEvent( void* pUserData ) { return 0; }

	virtual void enterWorld(){;}
	virtual void leaveWorld(){;}
	virtual void reshapeWorld(int pWidth, int pHeight){;}
	

	static GLboolean GetDistPilot( Sprite3d *pSprite,  Double3 & pDist );
	static GLboolean GetPositionWithoutCollision( int pInteract,Double3& pPos, int pSize, int pLimitX, int pLimitY=0, int pLimitZ=0, int pNbTry=10, float pMarge=1.5 );


protected:
};
//**************************************



#endif
