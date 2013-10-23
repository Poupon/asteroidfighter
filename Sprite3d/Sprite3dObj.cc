#include <Sprite3dObj.h>
#include <GL/glut.h>


//**************************************
Sprite3dObj::Sprite3dObj(  O3dObj *pObj, float pLifeTime  )
:Sprite3d( (pObj == NULL ? 0 : pObj->getRadius()), pLifeTime),
 cObj( pObj ),
 cDeepDestroy(GL_FALSE)
{

}
//-----------------------------------
Sprite3dObj::~Sprite3dObj()
{
	if( cDeepDestroy )
	{
		cObj->deleteAll();
		delete cObj;
	}
}
//-----------------------------------
GLboolean Sprite3dObj::animate()
{
	if( cObj != NULL )
		cObj->animate();

	return Sprite3d::animate();
}
//-----------------------------------
void Sprite3dObj::draw(  O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
	if( cObj == NULL )
		return;

	// Pas de glPushMatrix/glPopMatrix car l objet et seul dans le
	// Sprite et le Sprite fait glPushMatrix/glPopMatrix !

	cObj->pushTransf();

	if( cObj->getObjProps() )
		{
			cObj->getObjProps()->open();
			cObj->draw( pVProps, cObj->getObjProps() );
	//		glutWireSphere( cRadius, 8,  8);

			cObj->getObjProps()->close();
		}
	else 
		{
			cObj->draw( pVProps, pObjProps );
	//		glutWireSphere( cRadius, 8,  8);
		}
}

//**************************************
