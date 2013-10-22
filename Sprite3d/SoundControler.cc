#include <SoundControler.h>



GLboolean SoundControler::sNoSound = GL_FALSE;
GLboolean SoundControler::sMute    = GL_FALSE;

SoundControler* SoundControler::sTheSoundControler = NULL;

//*************************************************

SoundControler::SoundControler( int pRate, int pSafetyMargin)
	:cSlSheduller(NULL)
{
#ifdef SL_SOUND
	if( !sNoSound )
		{
			cSlSheduller = new slScheduler( 8000);
			//	cSlSheduller->setSafetyMargin (pSafetyMargin);
			cSlSheduller->setSafetyMargin( 0.2);
		}
#endif

	sTheSoundControler = this;
}

//------------------------------------------------
void
SoundControler::process()
{
#ifdef SL_SOUND
	if( !sNoSound && cSlSheduller )
		{
			std::cout << "=== SoundControler::process ===" << std::endl;
			cSlSheduller->dumpUpdate () ;
		}
#endif
}

//------------------------------------------------
int
SoundControler::playSample ( slSample *pSample, int pPriority,slPreemptMode pMode)
{
	if( pSample == NULL )
		return -1;


#ifdef SL_SOUND
	if( !sNoSound && cSlSheduller )
		{
			std::cout << "SoundControler::playSimple:" << std::hex << pSample << std::endl;
		  return cSlSheduller->playSample( pSample, pPriority, pMode );
		}

	return -1;
#endif
}
//------------------------------------------------
int
SoundControler::loopSample ( slSample *pSample, int pPriority,slPreemptMode pMode)
{
	if( pSample == NULL )
		return -1;


#ifdef SL_SOUND
	if( !sNoSound && cSlSheduller )
		{
			std::cout << "SoundControler::playSimple:" << std::hex << pSample << std::endl;
		  return cSlSheduller->loopSample( pSample, pPriority, pMode );
		}

	return -1;
#endif
}
//------------------------------------------------
slSample*
SoundControler::loadSample( const char* pName )
{

#ifdef SL_SOUND
	if( !sNoSound && cSlSheduller != NULL)
		{
			std::cout << "SoundControler::loadSample :" << pName  << " " << cSlSheduller << "-->";
			return new slSample( pName );
		}
#endif
	return NULL;
}
//------------------------------------------------
int
SoundControler::playMusic ( const char *pName, int pPriority, slPreemptMode pMode)
{
#ifdef SL_SOUND
	if( !sNoSound && cSlSheduller )
		{
			std::cout << "SoundControler::playMusic :" << pName  << " " << cSlSheduller << "-->";
		  return cSlSheduller->playMusic( pName, pPriority, pMode );
		}
#endif

	return 0;
}
//*************************************************
