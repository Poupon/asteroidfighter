TARGET=libO3d.a

SRCS = \
	O3dKamera.cc \
	O3dObj.cc \
	O3dObjBSpline.cc \
	O3dObjBSplineSurf.cc \
	O3dObjBezier.cc \
	O3dObjFacet.cc \
	O3dObjLight.cc \
	O3dObjLine.cc \
	O3dObjNurbs.cc \
	O3dObjPoint.cc \
	O3dObjPrim.cc \
	O3dObjText.cc \
	O3dObjProps.cc \
	O3dObjShape.cc \
	O3dSelector.cc \
	O3dViewProps.cc \
	PToken.cc \
	O3dObjPLibFont.cc \

OBJS =  $(SRCS:.cc=.o)


HDRS = $(SRCS:.cc=.h)


# ---------------------------------------------------

CFLAGS=  ${CC_DEBUG}

CINCLUDE=-I. -I.. 

#  -I/usr/openwin/include  -I${DIR_OPENGL_INC} -I${DIR_GLUT_INC} -I${DIR_PLIB_INC}


# ---------------------------------------------------

all:: start

all:: $(OBJS)

all::	$(TARGET)

start:
	rm -f  $(TARGET)

clean::
		rm	 -f *.o	*.a


# ---------------------------------------------------
# Compilation
.cc.o:
		gcc $(CFLAGS) $(CINCLUDE) -c $*.cc 


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
