#include <SoundControler.h>



#include <AL/al.h>
#include <AL/alc.h>

#include <sndfile.h>

#include <vector>

#include "World.h"
#include "WorldControler.h"


GLboolean SoundControler::sNoSound = GL_FALSE;
GLboolean SoundControler::sMute    = GL_FALSE;

SoundControler* SoundControler::sTheSoundControler = NULL;
ALCdevice*  sSoundDevice = NULL;
ALCcontext* sSoundContext = NULL;




//*************************************************

SoundControler::SoundControler(  int pMaxSource,  const char* pPath  )
{
	if( pPath != NULL )
		cPath = pPath;

	sTheSoundControler = this;


	sSoundDevice = alcOpenDevice(NULL);
	if (!sSoundDevice)
		{
			sNoSound = GL_TRUE;
			std::cerr<< "SoundControler::SoundControler alcOpenDevice failed"  << std::endl;
			return ;
		}


	// Création du contexte
	sSoundContext = alcCreateContext( sSoundDevice, NULL );
	if (!sSoundContext)
		{
				std::cerr << "SoundControler::SoundControler  alcCreateContext failed"  << std::endl;
				sNoSound = GL_TRUE;
			return ;
		}
 
	// Activation du contexte
	if (!alcMakeContextCurrent(sSoundContext))
		{
			std::cerr << "SoundControler::SoundControler  alcMakeContextCurrent failed"  << std::endl;
			sNoSound = GL_TRUE;
			return;
		}
 

	std::cout << "SoundControler::SoundControler OK " << pPath  << std::endl;


	// Reservation des sources
	for( int i=0; i< pMaxSource; ++i )
		{
			ALuint lSource;

			// IL FAUDRAIT UN CONTROL D'ERREUR
			alGenSources(1, &lSource);
			
			cSources.push_back( new SoundSource( i, lSource ) );

		}
}
//------------------------------------------------

SoundControler::~SoundControler(  )
{
	// ALCcontext* Context = alcGetCurrentContext();
  // ALCdevice*  Device  = alcGetContextsDevice(Context);


	// Destruction des buffers
	for( std::vector<PSoundId>::iterator p=cSamples.begin(); p!=cSamples.end(); ++p)
		{
		  ALuint lBuffer =  *p;

			alDeleteBuffers(1, &lBuffer);

			}

	// Destruction des sources
	for( std::vector<SoundSource*>::iterator p=cSources.begin(); p!=cSources.end(); ++p)
		{		  
			delete *p;
		}


	// Destruction du contexte
	if( sSoundContext!=NULL) 
		{
			// Désactivation du contexte
			alcMakeContextCurrent(NULL);
			alcDestroyContext(sSoundContext);
		}
 
	// Fermeture du device
	if( sSoundDevice != NULL )
    alcCloseDevice(sSoundDevice);


	sMute =  sNoSound = true;

}
//------------------------------------------------
PSoundId
SoundControler::LoadSample( const char* pSection, const char* pKey )
{
	const char* lName = World::ConfigGetKey( pSection, pKey );

	if( lName != NULL )
		{
			return sTheSoundControler->loadSample( lName );
		}

	std::cerr << "*** Error SoundControler::LoadSample no filename for " << pSection << ':' << pKey << std::endl;

	return PBadSoundId;
}
//------------------------------------------------
PSoundId
SoundControler::loadSample ( const char* pName )
{
	if( sMute || sNoSound )	return PBadSoundId;



	std::string lFilePath(  cPath );

	if( lFilePath.length() >0 )
		lFilePath += "/";

	lFilePath +=pName;

	std::cout << "SoundControler::loadSample " << lFilePath << std::endl;

	SF_INFO lFileInfos;
	SNDFILE* lFile = sf_open( lFilePath.c_str(), SFM_READ, &lFileInfos);
	if (! lFile) {

		std::cerr << "*** SoundControler::loadSample sf_open failed " << lFilePath << std::endl;
	
		return 0;
	}


	ALsizei lNbSamples  = static_cast<ALsizei>(lFileInfos.channels *lFileInfos.frames);
	ALsizei lSampleRate = static_cast<ALsizei>(lFileInfos.samplerate);

	// Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
	std::vector<ALshort> lSamples(lNbSamples);
	if (sf_read_short( lFile, &lSamples[0], lNbSamples) < lNbSamples) {
		std::cerr << "*** SoundControler::loadSample sf_read_short failed " << lFilePath << std::endl;
		return 0;
	}
	
	// Fermeture du fichier
	sf_close(lFile);
	
	
	ALenum lFormat;
	switch (lFileInfos.channels)
    {
		case 1 :  lFormat = AL_FORMAT_MONO16;   break;
		case 2 :  lFormat = AL_FORMAT_STEREO16; break;
        default : return 0;
    }


    // Création du tampon OpenAL
    ALuint lBuffer;
    alGenBuffers(1, &lBuffer);

    // Remplissage avec les échantillons lus
    alBufferData(lBuffer, lFormat, &lSamples[0], lNbSamples * sizeof(ALushort), lSampleRate);
 
    // Vérification des erreurs
    if (alGetError() != AL_NO_ERROR)   {
		 std::cerr << "*** SoundControler::loadSample alGetError " << lFilePath << std::endl;
		 return 0;
		}

		cSamples.push_back( lBuffer );

    return lBuffer;
}
//------------------------------------------------
// internal protected  function

SoundSource* 
SoundControler::internalPlaySample( PSoundId pBufferId, int pPriority, float pGain, float pPitch, bool pLoop){

	std::cout << "SoundControler::internalPlaySample" << pBufferId << " prio:" << pPriority ;
	//					<<  (sMute == GL_FALSE ? " ok ":" Mute ") 
	//					<<  ( sNoSound == GL_FALSE ? " sound ": " no_sound") << std::endl;


	if( sMute || sNoSound || pBufferId == PBadSoundId )	return 0;
	
	// Création d'une source
	SoundSource *lSrc =	 getFreeSource( pPriority );
	
	if( lSrc == NULL 
			||  lSrc->play( pBufferId, pGain, pPitch, pLoop ) == PBadSoundSourceId )
	 {			 
		 std::cout << " RETURN NULL" << std::endl ;
		 return NULL;
	 }
	
	lSrc->cPriority = pPriority;

	std::cout << " ID:" << lSrc->cSourceId << std::endl ;

	return lSrc;
}
//------------------------------------------------
// Simple function 

void 
SoundControler::playSample( PSoundId pBufferId, int pPriority, float pGain, float pPitch, bool pLoop){

	//	std::cout << "SoundControler::playSample" << pBufferId 
	//					<<  (sMute == GL_FALSE ? " ok ":" Mute ") 
	//					<<  ( sNoSound == GL_FALSE ? " sound ": " no_sound") << std::endl;
	
		internalPlaySample( pBufferId,  pPriority, pGain,  pPitch, pLoop );
}
//------------------------------------------------
// Simple function 

void 
SoundControler::internalPlaySampleOwner( SoundSourceOwner & pOwner, PSoundId pBufferId, int pPriority, float pGain, float pPitch, bool pLoop){

	//	std::cout << "SoundControler::playSample" << pBufferId 
	//					<<  (sMute == GL_FALSE ? " ok ":" Mute ") 
	//					<<  ( sNoSound == GL_FALSE ? " sound ": " no_sound") << std::endl;
	 internalPlaySample(  pBufferId,  pPriority, pGain,  pPitch, pLoop );
}
//------------------------------------------------
double
SoundControler::getPos( PSoundId pSource ) {

	if( sMute || sNoSound || pSource == PBadSoundId )	return 0;


	ALfloat lSeconds = 0.f;

	alGetSourcef( pSource, AL_SEC_OFFSET, &lSeconds);
 	return lSeconds;
}
//------------------------------------------------
PSoundId 
SoundControler::getStatus( PSoundId pSource ) {

	if( sMute || sNoSound || pSource == PBadSoundId )	return 0;

	ALint lStatus;
	
    // Récupération de l'état du son
	alGetSourcei( pSource, AL_SOURCE_STATE, &lStatus);
	
	return lStatus;
}
//------------------------------------------------
//------------------------------------------------
//------------------------------------------------
void SoundControler::freeSource( SoundSource* pSrc ){
	
	alSourceStop( pSrc->cSourceId );

	if( pSrc->getOwner() != NULL )
		{
			pSrc->getOwner()->remove( pSrc );
		}

	pSrc->cState = SoundSource::SourceState::FREE;
}
//------------------------------------------------
// On renvoie la premiere source libre ou a defaut 
// la moins prioritaire
// (on pourrait ajouter un critere de temps)

SoundSource* 
SoundControler::getFreeSource( int pPriority){

	int lMemPriority = pPriority;
	SoundSource* lMemSrc = NULL;
	float lMemTime =9E30;

	
	for( std::vector<SoundSource*>::iterator p=cSources.begin(); p!=cSources.end(); ++p)
		{		  
			SoundSource* lSrc = *p;
			
			ALint lSourceState; 
			
			

			if( lSrc->cState == SoundSource::SourceState::FREE ) {
				std::cout << " - FREE - " ;
				return lSrc;
			}

			alGetSourcei( lSrc->cSourceId, AL_SOURCE_STATE, &lSourceState);
			 
			if (lSourceState != AL_PLAYING) {
				lSrc->cState =  SoundSource::SourceState::FREE ;
				std::cout << " - FINISH - " ;
			 	return lSrc;
			}

			//	NSInteger lLooping;
			//alGetSourcei( lSrc->cSourceId, AL_LOOPING, &lLooping);

			// on exclut les sources en mode LOOP
			if( (lSrc->cState == SoundSource::SourceState::PLAY 
					 ||  lSrc->cState == SoundSource::SourceState::ERROR)
					&& lSrc->cPriority <= lMemPriority )
				{
					if( lSrc->cPriority == lMemPriority 
							&&  lSrc->cTime < lMemTime )
						{
							lMemSrc = lSrc;
							lMemTime = lSrc->cTime;
						}							
					else {
						 	lMemPriority = lSrc->cPriority;
							lMemSrc = lSrc;
							lMemTime = lSrc->cTime;
					}
				}
		}



	if( lMemSrc != NULL ) {
		std::cout << " - REUSE - " ;

		alSourceStop( lMemSrc->cSourceId );
		lMemSrc->cState =  SoundSource::SourceState::FREE;
	}

	return lMemSrc;
}
//*************************************************
//*************************************************
//*************************************************

SoundSource::SoundSource(  int pId, PSoundId pSourceId )
	:cId( pId ),
	 cSourceId( pSourceId ),
	 cOwner( NULL ),
	 cPriority(0),
	 cState( SoundSource::SourceState::FREE ),
	 cTime(0)
{
}
//------------------------------------											
SoundSource::~SoundSource()
{		


	if( cSourceId != PBadSoundId)
		{
			ALuint lSource = static_cast<ALuint>(cSourceId);

			alDeleteSources( 1, &lSource );
		}
}
//------------------------------------
PSoundSourceId 
	SoundSource:: play( PSoundId pBufferId,  float pGain, float pPitch, bool pLoop)
{
	ALenum err = alGetError(); // clear error code 
	
	alSourcei( cSourceId, AL_BUFFER, 0 );
	alSourcei( cSourceId, AL_BUFFER, pBufferId ); 
	
	if( pPitch != 1.0f )
		alSourcef( cSourceId, AL_PITCH, pPitch);
	if( pGain != 1.0f )
		alSourcef( cSourceId, AL_GAIN, pGain);
	
	if (pLoop) 
		{
			alSourcei(cSourceId, AL_LOOPING, AL_TRUE);		
			cState = SourceState::LOOP;
		}
	
	if( (err = alGetError()) != 0 ) 
		{
			std::cerr << "SoundSource:: play error" << std::endl;
			cState = SourceState::ERROR;
			return PBadSoundSourceId;
		}
	else
		cState = SourceState::PLAY;
	
	
	cTime = WorldControler::GetTime();
	alSourcePlay( cSourceId );

	return cId;
}
//------------------------------------

void 
SoundSource::setPosition( Double3 pPosition  )
{
}
//------------------------------------
void 
SoundSource::setSpeed(  Double3 pSpeed  )
{
}
//------------------------------------
void 
SoundSource::setPositionAndSpeed(  Double3 pPosition, Double3 pSpeed )
{
	
}
//*************************************************
//*************************************************
//*************************************************
SoundSourceOwner::SoundSourceOwner()
{
}
//------------------------------------
SoundSourceOwner::~SoundSourceOwner()
{

	for( std::vector<SoundSource*>::iterator p=cMySources.begin(); p!=cMySources.end(); ++p)
		{		  
			(*p)->setOwner( NULL ); 
		}
}
//------------------------------------
void SoundSourceOwner::remove(SoundSource* pSrc){

	for( std::vector<SoundSource*>::iterator p= cMySources.begin(); 
			 p!=cMySources.end();
			 ++p) 
		{
			if( *p == pSrc )
				cMySources.erase( p );
		}

}
//------------------------------------
void
SoundSourceOwner::playSoundSource( PSoundId pBufferId, int pPriority, float pGain, float pPitch, bool pLoop ){

	
	SoundSource *lSrc = SoundControler::sTheSoundControler->internalPlaySample( pBufferId,  pPriority, pGain,  pPitch, pLoop );

	if( lSrc == NULL )
		return ;

	 
	if( lSrc->getOwner() == this )
		return;

			
	if( lSrc->getOwner() != NULL )
		{
			lSrc->getOwner()->remove( lSrc );
		}

	lSrc->setOwner( this );

	cMySources.push_back( lSrc );
		
}
//------------------------------------

void 
SoundSourceOwner::setSoundSourcesPosition( Double3 pPosition  )
{
	for( std::vector<SoundSource*>::iterator p=cMySources.begin(); p!=cMySources.end(); ++p)
		{
			(*p)->setPosition( pPosition );
		}
}
//------------------------------------
void 
SoundSourceOwner::setSoundSourcesSpeed(  Double3 pSpeed  )
{
	for( std::vector<SoundSource*>::iterator p=cMySources.begin(); p!=cMySources.end(); ++p)
		{
			(*p)->setSpeed( pSpeed );
		}
}
//------------------------------------
void 
SoundSourceOwner::setSoundSourcesPositionAndSpeed(  Double3 pPosition, Double3 pSpeed )
{
		for( std::vector<SoundSource*>::iterator p=cMySources.begin(); p!=cMySources.end(); ++p)
		{
			(*p)->setPosition( pPosition );
			(*p)->setSpeed( pSpeed );
		}

}
//*************************************************

/*
const ALchar* Extensions = alGetString(AL_EXTENSIONS);
bool IsMultiChannelSupported = (alIsExtensionPresent("AL_EXT_MCFORMATS") == AL_TRUE);

// Définition de la position de l'écouteur (ici l'origine)
alListener3f(AL_POSITION, 0.f, 0.f, 0.f));
 
// Définition de la vitesse de l'écouteur (ici nulle)
alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f));
 
// Définition de l'orientation de l'écouteur (ici il regarde vers l'axe des Z)
ALfloat Orientation[] = {0.f, 0.f, 1.f, 0.f, 1.f, 0.f};
alListenerfv(AL_ORIENTATION, Orientation));
*/
