#include <SoundControler.h>
#include <SoundLibrary.h>




//*************************************************

SoundLibrary::SoundLibrary( long pMaxSound, const char* pBasePath)
	:cMaxSound(pMaxSound),
	 cBasePath( pBasePath ),
	 cNbSound(0)
{
	cVectSound = new slSample*[cMaxSound];
}

//------------------------------------------------
/*
SoundLibrary::~SoundLibrary(  )
{
	delete cVectSound;
	cVectSound = NULL;
	cMaxSound = 0;
}
*/
//------------------------------------------------	

PSoundId 
SoundLibrary::loadSample ( const char* pName )
{
	if( cNbSound >= cMaxSound )
		return PBadSoundId;

	slSample* lSample =	NULL;

	if( cBasePath== NULL )
		{
			std::cout << "SoundLibrary::loadSample :" << pName ;

			lSample =	SoundControler::sTheSoundControler->loadSample( pName );
		}
	else
		{

			std::string lPath( cBasePath );
			lPath += '/';
			lPath += pName;
			lSample =	SoundControler::sTheSoundControler->loadSample( lPath.c_str() );

			std::cout << "SoundLibrary::loadSample :" << lPath ;
		}

	if(  lSample == NULL )
		{
			std::cout << " *** FAIL *** " << std::endl;
			return PBadSoundId;
		}

	std::cout << " id: " << cNbSound << std::endl;

	cVectSound[cNbSound++] = lSample;

	return cNbSound-1;	
}

//------------------------------------------------

slSample* 
SoundLibrary::getSample( PSoundId pSoundId)
{
	std::cout << "SoundLibrary::getSample " << pSoundId << std::endl;

	if( pSoundId == PBadSoundId || pSoundId >= cNbSound )
		return NULL;
	
	return cVectSound[pSoundId];
}

//*************************************************
