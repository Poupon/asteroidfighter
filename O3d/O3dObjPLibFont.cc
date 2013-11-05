#include <O3dObjPLibFont.h>
#include <O3dObjProps.h>

#include <iostream>
#include <T3d/T3dColor.h>
#include <stdlib.h>


//****************************************
void 
O3dObjPLibFont::drawObj( O3dViewProps & pVProps, O3dObjProps *pObjProps )
{
	static fntRenderer sTexout ;

	 sTexout.setFont( &cFont );
	 sTexout.setPointSize( cSize);
	 sTexout.begin () ;
	 sTexout.start3f ( 0.0f, 0.0f, 0.0f ) ;
		     sTexout.puts ( cStr.data() ) ;
   sTexout.end () ;
	 glDisable      ( GL_TEXTURE_2D ) ; 
}



//****************************************
