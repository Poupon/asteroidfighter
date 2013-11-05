#ifndef h_Def_h
#define h_Def_h


static const unsigned int InteractAllied       =0x03+0x4;
static const unsigned int InteractAlliedWeapon =0x30;

static const unsigned int InteractEnemy        =0x30;
static const unsigned int InteractEnemyWeapon  =0x03;

static const unsigned int InteractObstacle     =0x33;

static const unsigned int InteractBonus    =0x4;

enum {
	NO_TYPE=0,
	CONTAINER,
	FRIEND_SHIP,
	ALIEN_SHIP,
	ASTEROIDE
};

enum{ FRIEND, ALIEN };



#endif
