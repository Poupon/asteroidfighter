include ${FLTK_PATH}/makeinclude

TARGET=libSpace.a

SRCS = \
	Scene.cc \
	SceneSprite.cc \
	AsteroidesMaker.cc \
	ShipsMaker.cc \
	MinesMaker.cc \
	SceneSprite.cc \
	SceneAsteroide.cc \
	SceneAttack.cc \
	SceneAttackCroisseur.cc \
	SceneGrotte.cc \
	SceneHammerAnvil.cc \
	SceneChaos.cc \
	SceneLife.cc \
	SceneBase.cc \
	ActionsShip.cc \
	WorldGame.cc \
	Pilot.cc
#        SceneArtifice.cc \

OBJS =  $(SRCS:.cc=.o)


HDRS = $(SRCS:.cc=.h)


# ---------------------------------------------------

CFLAGS=  ${CC_DEBUG} -g -std=c++11  -O3 -Wall  -pthread -D_POSIX_PTHREAD_SEMANTICS -m64  ${CC_PROFILING}

CINCLUDE=-I. -I.. 

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
