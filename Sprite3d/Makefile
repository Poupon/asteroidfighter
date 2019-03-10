include ${FLTK_PATH}/makeinclude

TARGET=libSprite3d.a

SRCS = \
	Collision.cc \
	ObjOdron.cc \
	ObjPart.cc \
	ObjText2d.cc \
	ObjVect.cc \
	Sprite3d.cc \
	Sprite3dObj.cc \
	Sprite3dPilot.cc \
	Text2d.cc \
	Utils3d.cc \
	WorldControler.cc \
	SoundControler.cc \
	World.cc \
	SceneManager.cc \
	AnimatObj.cc \
	Random.cc

OBJS =  $(SRCS:.cc=.o)


HDRS = $(SRCS:.cc=.h)


# ---------------------------------------------------

CFLAGS=  -DUSE_SOUND  ${CC_DEBUG} -g -std=c++11  -O3 -Wall  -m64 -pthread -D_POSIX_PTHREAD_SEMANTICS -m64  ${CC_PROFILING}
CFLAGS =  -DXXXXUSE_SOUND  ${CC_DEBUG} -g -std=c++17 -O3 -Wall  -m64 -pthread -D_POSIX_PTHREAD_SEMANTICS  -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT -I${FLTK_PATH} -I/usr/include/freetype2 ${CC_PROFILING}

CINCLUDE=-I. -I.. -DLINUX



# ---------------------------------------------------

all:: start

all:: $(OBJS)

all::	$(TARGET)

clean::
		rm	-f  *.o	*.a


start:
	rm -f $(TARGET)



# ---------------------------------------------------
# Compilation
.cc.o:
		gcc $(CFLAGS) $(CINCLUDE) -c  $*.cc 
 

# ---------------------------------------------------
# Library

$(TARGET):
		rm -f $(TARGET) 
	 	ar cq $(TARGET) $(OBJS)
		ranlib $(TARGET)


# ---------------------------------------------------
# Depends
DEPEND = makedepend

ALLDEFINES=$CINCLUDE

depend:: $(SRCS) $(HDRS)
	$(DEPEND)  -s "# DO NOT DELETE" -- $(ALLDEFINES) -- $(SRCS)
dependlocal:: $(SRCS) $(HEADERS)
	$(DEPEND)  -s "# DO NOT DELETE" -- $(ALLDEFINES) -- $(SRCS)
