#ifndef _O3dObjPLibFont_h_
#define _O3dObjPLibFont_h_

#include <O3d/O3dObjPoint.h>

#include <string>
#include <vector>

#include "plib/fnt.h" 

//****************************************
class O3dObjPLibFont : public O3dObj 
{
  fntTexFont& cFont;
	float       cSize;
	std::string cStr;

public:	
	O3dObjPLibFont( fntTexFont& pFont, float pSize, const char *pStr ) 
		: cFont(pFont), cSize(pSize), cStr(pStr){;}

	virtual void drawObj(  O3dViewProps & pVProps, O3dObjProps *pObjProps );
	virtual const char *getObjTypeStr()		{ return "Text";		}
	void setStr( const char* pStr )  { cStr = pStr; }
	fntTexFont& getFont() { return cFont; } 
	float      getSize() { return cSize; }

};
//****************************************


#endif
