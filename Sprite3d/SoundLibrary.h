#ifndef h_SoundLibrary_h
#define h_SoundLibrary_h

#include <T3d/T3dBox.h>

#include <Sprite3d/SoundControler.h>

//*************************************************

typedef long PSoundId;
#define PBadSoundId -1

class SoundLibrary{

	slSample* *cVectSound;
	long   cNbSound;
	long   cMaxSound;
	
	const char* cBasePath;
	
public:
	SoundLibrary( long pMaxSound, const char* pBasePath=NULL  );
	//	virtual SoundLibrary::~SoundLibrary();
	
	PSoundId loadSample ( const char* pName );
	slSample* getSample( PSoundId pSoundId);

	
};
//*************************************************

#endif
