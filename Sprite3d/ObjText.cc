#include <Objtext.h>

#include <GL/glut.h>
#include <ostream>

//***********************************
ObjText::ObjText( const char *pStr )
{
  cStr = pStr;
}
//---------------------------------
void
ObjText::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{
  std::cout << "ObjText" << std::endl;
  int l = strlen( cStr );
  float x = 0;
  for( int i =0; i < l; i++ )
    {
     glutStrokeCharacter( GLUT_STROKE_ROMAN, cStr[i] );
     glTranslatef( x, 0., 0. );
     x+=glutStrokeWidth( GLUT_STROKE_ROMAN, cStr[i] );


	  //  glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, cStr[i] );
	//	glRasterPos2f( x, 0 );
	  //	x+=glutBitmapWidth( GLUT_BITMAP_HELVETICA_18, cStr[i] );
    }
}
