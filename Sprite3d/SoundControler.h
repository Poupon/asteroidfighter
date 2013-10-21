#ifndef h_SoundControler_h
#define h_SoundControler_h

#include <T3d/T3dBox.h>

#define SL_SOUND 1

#ifdef SL_SOUND
#include <plib/sl.h>
#else
typedef void* slSample;
#endif


//*************************************************

class SoundControler{

#ifdef SL_SOUND
	slScheduler *cSlSheduller;
#endif

public:
	SoundControler( int pRate=8000, int pSafetyMargin=0.128f );
	
	int playSample ( slSample *pSample, int pPriority = 1, slPreemptMode pMode = SL_SAMPLE_ABORT ) ;
	int playMusic (const char *pName, int pPriority = 1, slPreemptMode pMode = SL_SAMPLE_ABORT ) ;


	slSample* loadSample( const char* pName );

	void process();

	static GLboolean sMute;
	static GLboolean sNoSound;
	static SoundControler* sTheSoundControler;
};
//*************************************************


#define PLAYSAMPLE(A)  SoundControler::sTheSoundControler->playSample(A)
#define PLAYMUSIC(A)  SoundControler::sTheSoundControler->playMusic(A)

#endif
