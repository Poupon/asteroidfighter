TARGET=libSpace.a

SRCS = \
	Scene.cc \
  SceneArtifice.cc	\
	AsteroidesMaker.cc \
	ShipsMaker.cc \
	MinesMaker.cc \
	SceneAsteroide.cc \
	SceneAttack.cc \
	SceneGrotte.cc \
	SceneChaos.cc \
	SceneLife.cc \
	SceneBase.cc \
	ActionsShip.cc \
	WorldGame.cc \
	Pilot.cc

OBJS =  $(SRCS:.cc=.o)


HDRS = $(SRCS:.cc=.h)


# ---------------------------------------------------

CFLAGS=  -DPUI_WIN  ${CC_DEBUG}

CINCLUDE=-I. -I.. 
# -I/usr/openwin/include  -I${DIR_OPENGL_INC} -I${DIR_GLUT_INC} -I${DIR_PLIB_INC}

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
