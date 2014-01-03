#include <O3dSelectMode.h>
#include <O3d/O3dViewProps.h>
#include <O3d/O3dKamera.h>

#include <iostream>

/*---------------------------------------------------------------------*/
/*    O3dSelectMode::O3dSelect ...                                    */
/*---------------------------------------------------------------------*/

O3dSelectMode::O3dSelectMode()
:cNbSelect( 0 ),
 cFind(SELECT_NONE ),
 cViewProps( NULL ),
 cKamera( NULL ),
 cNbObj( 0 ),
 cNbComponent( 0 )
{
}
/*---------------------------------------------------------------------*/
/*    O3dSelectMode::raz ...                                           */
/*---------------------------------------------------------------------*/
void
O3dSelectMode::raz()
{
	cNbSelect = 0 ;
 	cFind = SELECT_NONE ;
 	cNbObj = 0 ;
	cNbComponent = 0 ;
}
/*---------------------------------------------------------------------*/
/*    O3dSelectMode::open ...                                          */
/*---------------------------------------------------------------------*/

void
O3dSelectMode::begin( O3dViewProps* pViewProps, O3dKamera* pKamera, int pX, int pY, float pWidht, float pHeight)
{
	cViewProps = pViewProps;
	cKamera = pKamera;

	raz();

	cViewProps->ViewPropsBool::set( MODE_SELECT, GL_TRUE );

	glSelectBuffer( cSzBuf, cSelectBuf );
	glRenderMode( GL_SELECT );

	glInitNames();
	// glPushName( (GLuint)-1 );
	cKamera->setPick( pX, pY, pWidht, pHeight);
}
/*---------------------------------------------------------------------*/
/*    O3dSelectMode::finish ...                                        */
/*---------------------------------------------------------------------*/

void
O3dSelectMode::finish()
{	
	glFlush();
	cNbSelect = glRenderMode( GL_RENDER );
	cViewProps->ViewPropsBool::set( MODE_SELECT, GL_FALSE );

	print();

	GLuint *ptr = &cSelectBuf[ 0 ];
	std::cout << "nb:" << cNbSelect<< std::endl ;
	for( int i= 0; i < cNbSelect; i++ )
	{
		GLuint lNames = *ptr;
		ptr++;

		 *ptr++; // z1
		 *ptr++; //z2

		std::cout << "Names:" << lNames <<std::endl;
		// On ne prend que le dernier objets
		if( i == (cNbSelect - 1) )
		{
			std::cout << "select:" << *ptr << std::endl;
			GLuint mem =SELECT_NONE;

			for( unsigned int j = 0; j < lNames; j++ )
			{
				std::cout << "j:" << j << "=" << *ptr << std::endl;
				if( mem == SELECT_ELEMENT )
				{
					std::cout << "Element:" << *ptr<< std::endl;
					cObjId[ cNbObj++ ] = *ptr;
					mem = *ptr;
				}
				else
				if( mem == SELECT_COMPONENT )
				{
					std::cout << "Component:" << *ptr <<std::endl;
					cComponent[ cNbComponent++ ] = *ptr;
				}
				else
					mem = *ptr;

				ptr++;
			}
		}
		else
		{
			for( unsigned int j = 0; j < lNames; j++ )
				{
					ptr++;
				}
		}
	}	
}
/*---------------------------------------------------------------------*/
/*	   O3dSelectMode::getSelectObject ...                              */
/*---------------------------------------------------------------------*/

long
O3dSelectMode::getSelectObject()
{
	if( cNbObj == 0 )
		return SELECT_NONE;
	return cObjId[ cNbObj-1];
}

/*---------------------------------------------------------------------*/
/*    O3dSelectMode::print ...                                        */
/*---------------------------------------------------------------------*/

void
O3dSelectMode::print()
{
	std::cout << "=======================================" <<std::endl;
	std::cout << cNbSelect << " Objects founds " << std::endl;
	GLuint *ptr = &cSelectBuf[ 0 ];

	for( int i= 0; i < cNbSelect; i++ )
	{
		GLuint lNames = *ptr;
		std::cout << "number of names for hit is " << lNames << std::endl;
		ptr++;
		std::cout << " z1=" << *ptr++;
		std::cout << " z2=" << *ptr++;
		std::cout << std::endl;

		for( unsigned int j = 0; j < lNames; j++ )
		{
			std::cout << " " << *ptr;
			ptr++;
		}
		std::cout << std::endl;
		std::cout << "-------------" << std::endl;
	}
	std::cout << "=======================================" << std::endl;
}



/*---------------------------------------------------------------------*/
/*    O3dSelectMode::print2 ...                                       */
/*---------------------------------------------------------------------*/

void
O3dSelectMode::print2()
{
	std::cout << "=======================================" << std::endl;

	std::cout << "SelecteD objects:";

	for( int i = 0; i < cNbObj; i++ )
		std::cout << cObjId[ i ] << ", ";

	std::cout << std::endl;

	std::cout << "Selected component:" ;
	for( int j = 0; j < cNbComponent; j++ )
		std::cout << cComponent[ j ] << ", ";

	std::cout << std::endl;

	std::cout << "Found:" << getSelectObject() <<std::endl;
	std::cout << "=======================================" << std::endl;
}


