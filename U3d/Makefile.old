TARGET=libU3d.a

SRCS = Banniere.cc \
		 BonusMaker.cc \
		 ContainersMaker.cc \
		 ObjPrimPart.cc \
		 Sky.cc \
		 SpriteExplosion.cc \
		 Tourelle.cc \
		 WeaponsMaker.cc \
		 


OBJS =  $(SRCS:.cc=.o)


HDRS = $(SRCS:.cc=.h)


# ---------------------------------------------------

CFLAGS=  -DPUI_WIN  ${CC_DEBUG}
# -DSL_SOUND

CINCLUDE=-I. -I.. -DLINUX -g -std=c++11 -Wall  -O3  -m64 -pthread -D_POSIX_PTHREAD_SEMANTICS -m64  ${CC_PROFILING}

#  -I/usr/openwin/include  -I${DIR_OPENGL_INC} -I${DIR_GLUT_INC} -I${DIR_PLIB_INC}


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
