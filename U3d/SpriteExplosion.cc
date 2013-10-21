#include <GL/glut.h>

#include <Sprite3d/World.h>

#include <SpriteExplosion.h>
#include <iostream>

AutoPtr<O3dObjProps> SpriteExplosion::caExplosionProps;
AutoPtr<O3dObjProps> SpriteExplosion::caExplosionPlasmaProps;

//***************************

void
SpriteExplosion::Init()
{
	Float4 pr(0.6, 0.2, 0.0, 0.2);
	caExplosionProps =  new O3dObjProps();
	caExplosionProps->ObjPropsFloat4::set( MATERIAL, pr );
	caExplosionProps->ObjPropsFloat4::set( EMISSION, pr );

	Float4 pr2(0.1, 0.7, 1.0, 0.1);
	caExplosionPlasmaProps =  new O3dObjProps();
	caExplosionPlasmaProps->ObjPropsFloat4::set( MATERIAL, pr2 );
	caExplosionPlasmaProps->ObjPropsFloat4::set( EMISSION, pr2 );
}
//----------------------
SpriteExplosion::SpriteExplosion( float pRadius, float pLifeTime, float pDestroy )
:Sprite3d(  pRadius, pLifeTime  )
{
	cRadius = pRadius;
	SpriteFloat::set( SPRITE_DESTROY_POINT, pDestroy);
}
//----------------------
void SpriteExplosion::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{

	float lAvance = (WorldControler::GetTime()-SpriteFloat::get(SPRITE_BIRTHTIME))/SpriteFloat::get(SPRITE_LIFETIME);

	int val;
	if( lAvance < 0.5 )
		val = static_cast<int>((cRadius*2*lAvance )+1.0);
	else
		val = static_cast<int>((cRadius *2 *(1.0-lAvance)) + 1.0);

	glutSolidSphere( val + 1.0, 6 + val, 6 + val );
}
//***************************
