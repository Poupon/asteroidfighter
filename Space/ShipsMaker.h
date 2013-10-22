#ifndef H__SHIPSMAKER__H
#define H__SHIPSMAKER__H

#include <O3d/O3dObjProps.h>
#include <O3d/O3dObj.h>
#include <O3d/O3dObjPrim.h>
#include <Sprite3d/Sprite3dPilot.h>
#include <Sprite3d/ObjPart.h>
#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Action.h>

#include <Space/ActionsShip.h>
#include <U3d/WeaponsMaker.h>


	enum ShipType{
		SHIP1,
		SHIP2,
		SHIP3,
		INTERCEPTOR,
		TORPILLEUR,
		CROISEUR,
		MEGA_CROISEUR,
		CUIRASSE,
		BASE_TORE,
		MAX_SHIP_TYPE
	};

class Tourelle;

//**********************************************
class ShipsMaker :public ActionsShip{

protected:
	Float4 cColorBody;
	Float4 cColorGrid;
	Float4 cColorModul;
	Float4 cColorSoute;
	Float4 cColorFan;
	Float4 cColorFire;
	Float4 cColorDome;

	O3dObjProps cPropsBlindage;
	O3dObjProps cPropsBody;
	O3dObjProps cPropsGrid;
	O3dObjProps cPropsModul;
	O3dObjProps cPropsSoute;
	O3dObjProps cPropsFan;
	O3dObjProps cPropsFire;
	O3dObjProps cPropsDome;

	O3dObjProps cPropsEcail;
	O3dObjProps cPropsSpin;
	O3dObjProps cPropsMaille;
	O3dObjProps cPropsBleue;
	O3dObjProps cPropsFlamme;
	O3dObjProps cPropsDalle;
	O3dObjProps cPropsEmail;


	AutoPtr<T3dTexture> caTexBlindage;
	AutoPtr<T3dTexture> caTexEcail;
	AutoPtr<T3dTexture> caTexMod;
	AutoPtr<T3dTexture> caTexBody;
	AutoPtr<T3dTexture> caTexSpin;
	AutoPtr<T3dTexture> caTexMaille;
	AutoPtr<T3dTexture> caTexBleue;
	AutoPtr<T3dTexture> caTexFlamme;
	AutoPtr<T3dTexture> caTexDalle;
	AutoPtr<T3dTexture> caTexEmail;

public:
	ShipsMaker();
	Sprite3d* makeShip( ShipType pShipType, int pMaxLife, 
											float  pSpin, 
											float pMaxSpeed, float pMaxDeltaV, float pReactivity, 
											int pNiveau,
											ShipAction pShipAction=SHIP_ACTION_NOMINAL );

public:


	O3dObj* makeReactor( float pSz );
	Tourelle* makeModul( float pSz );
	O3dObj* makeGrid( float pH, float pL );
	O3dObj* makeSoute( float pH, float pL );
	O3dObj* makeFan( float pH, float pL, int pFacette );


	ObjVect* makeShip1( float pSz, Sprite3dObj* pSp, EnumWeapons pWeapon, int pNiveau );
	ObjVect* makeShip2( float pSz, Sprite3dObj* pSp, int pNiveau  );
	ObjVect* makeShip3( float pSz, Sprite3dObj* pSp, int pNiveau  );
	ObjVect* makeInterceptor( float pSz, Sprite3dObj* pSp,  int pNiveau  );
	ObjVect* makeTorpilleur( float pSz, Sprite3dObj* pSp, int pNiveau );
	ObjVect* makeCroiseur( float pSz, Sprite3dObj* pSp,   int pNiveau );
	ObjVect* makeMegaCroiseur( float pSz, Sprite3dObj* pSp,   int pNiveau );
	ObjVect* makeCuirasse( float pSz, Sprite3dObj* pSp, int pNiveau  );
	ObjVect* makeBaseTore( float pSz, Sprite3dObj* pSp, int pNiveau  );

};

extern ShipsMaker * TheShipsMaker;

//**********************************************


#define MAKE_INTERCEPTOR(pHardness)  TheShipsMaker->makeShip( INTERCEPTOR, 2, 10, 70, 20, 0.4, pHardness )
#define MAKE_TORPILLEUR(pHardness)   TheShipsMaker->makeShip( INTERCEPTOR, 2, 10, 70, 20, 0.4, pHardness )

#define MAKE_SHIP1(pHardness) TheShipsMaker->makeShip( SHIP1, 5,  15, 30, 5, 0.2, pHardness  )
#define MAKE_SHIP2(pHardness) TheShipsMaker->makeShip( SHIP2, 10, 12, 30, 5, 0.2, pHardness)
#define MAKE_SHIP3(pHardness) TheShipsMaker->makeShip( SHIP3, 15, 10, 20, 4, 0.18, pHardness)

#define MAKE_TORPILLEUR1   TheShipsMaker->makeShip( TORPILLEUR, 10, 10, 70, 20, 0.4, 0  )
#define MAKE_TORPILLEUR2   TheShipsMaker->makeShip( TORPILLEUR, 15, 10, 70, 20, 0.4, 1  )
#define MAKE_TORPILLEUR3   TheShipsMaker->makeShip( TORPILLEUR, 20, 10, 70, 20, 0.4, 2  )

#define MAKE_CROISEUR1 TheShipsMaker->makeShip( CROISEUR, 30, 100, 30+randf(4), 15+randf(3), 0.3 +randf(0.1), 0, SHIP_ACTION_ATTACK  )
#define MAKE_CROISEUR2 TheShipsMaker->makeShip( CROISEUR, 40, 100, 35+randf(4), 17+randf(3), 0.32+randf(0.1), 1, SHIP_ACTION_ATTACK  )
#define MAKE_CROISEUR3 TheShipsMaker->makeShip( CROISEUR, 50, 100, 40+randf(4), 20+randf(3), 0.34+randf(0.1), 2, SHIP_ACTION_ATTACK  )

#define MAKE_CUIRASSE1  TheShipsMaker->makeShip( CUIRASSE,  100, 10,  20+randf(2), 10+randf(2), 0.3+randf(0.1), 0, SHIP_ACTION_ATTACK  )
#define MAKE_CUIRASSE2  TheShipsMaker->makeShip( CUIRASSE,  150, 10,  25+randf(2), 12+randf(2), 0.3+randf(0.1), 1, SHIP_ACTION_ATTACK  )
#define MAKE_CUIRASSE3  TheShipsMaker->makeShip( CUIRASSE,  200, 10,  30+randf(2), 15+randf(3), 0.3+randf(0.1), 2, SHIP_ACTION_ATTACK  )


#define MAKE_BASE1 TheShipsMaker->makeShip( BASE_TORE, 400,  10, 10, 2, 0.1, 0 )
#define MAKE_BASE2 TheShipsMaker->makeShip( BASE_TORE, 650, 10, 10, 2, 0.1, 1 )
#define MAKE_BASE3 TheShipsMaker->makeShip( BASE_TORE, 800, 10, 10, 2, 0.1, 2 )

#define MAKE_MEGA_CROISEUR1 TheShipsMaker->makeShip( MEGA_CROISEUR, 900, 15, 20+randf(2), 12+randf(2), 0.2+randf(0.1), 0, SHIP_ACTION_ATTACK )
#define MAKE_MEGA_CROISEUR2 TheShipsMaker->makeShip( MEGA_CROISEUR, 1200, 15, 20+randf(2), 12+randf(2), 0.2+randf(0.1), 1, SHIP_ACTION_ATTACK )
#define MAKE_MEGA_CROISEUR3 TheShipsMaker->makeShip( MEGA_CROISEUR, 1800, 15, 20+randf(2), 12+randf(2), 0.2+randf(0.1), 2, SHIP_ACTION_ATTACK )

#define MAKE_INTERCEPTOR_ATTACK(pHardness)  TheShipsMaker->makeShip(INTERCEPTOR,  2, 10, 40+randf(6), 16+randf(4), 0.4+randf(0.1), pHardness, SHIP_ACTION_TOURNOI )
#define MAKE_TORPILLEUR_ATTACK(pHardness)   TheShipsMaker->makeShip( TORPILLEUR, 10, 15, 35+randf(6), 18+randf(4), 0.3+randf(0.1), pHardness, SHIP_ACTION_KAMIKAZE )
#endif
