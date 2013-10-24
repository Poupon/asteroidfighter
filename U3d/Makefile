TARGET=libU3d.a

SRCS = \
	Tourelle.cc \
	ObjPrimPart.cc \
	Sky.cc \
	SpriteExplosion.cc \
	WeaponsMaker.cc \
	BonusMaker.cc \
	Banniere.cc

OBJS =  $(SRCS:.cc=.o)


HDRS = $(SRCS:.cc=.h)


# ---------------------------------------------------

CFLAGS= ${CC_DEBUG}

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
		gcc  $(CFLAGS) $(CINCLUDE) -c  $*.cc 
 

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
