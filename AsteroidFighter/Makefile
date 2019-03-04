TARGET=AsteroidFighter
# TARGET=TestDev

SRCS = \
	MainMenu.cc \
	Help.cc \
	main.cc


OBJS =  $(SRCS:.cc=.o)


HDRS = $(SRCS:.cc=.h)


# ---------------------------------------------------
# -lboost_system -lboost_program_options-mt 

LDFLAGS=   -pthread 

LIBPATHS=  -L../T3d -L../O3d -L../Sprite3d -L../U3d -L../Space  -L. -L../plib/libs \
					  -L${DIR_AL}/lib  -L${DIR_SNDFILE}/lib  -L${DIR_PLIB}/lib  -L${DIR_OPENGL}/lib -L${DIR_GLUT_LIB} -L${DIR_X11_LIB}

LIBS=  -lSpace -lU3d -lSprite3d -lO3d -lT3d   -lplibpuaux -lplibpu -lplibul  -lplibpw -lplibfnt -lplibsg -lplibul -lplibsl -lsndfile -lopenal  -lGL -lGLU -lglut  -lstdc++ -lpthread   -lstdc++ -lrt -lXext -lX11  -lnsl -lm 

# LIBS=  -lSpace -lU3d -lSprite3d -lO3d -lT3d   -lplibpuaux -lplibpu -lplibul  -lplibpw -lplibfnt -lplibsg -lplibul  -lplibsl -lsndfile   -lGL -lGLU -lglut   -lstdc++ -lpthread   -lrt  -lXmu -lXext -lXi -lX11  -lnsl -mt -lm 


# ---------------------------------------------------
CFLAGS=  -DPUI_WIN  ${CC_DEBUG} -g -std=c++11 -Wall -O3  -m64 -pthread -D_POSIX_PTHREAD_SEMANTICS -m64 ${CC_PROFILING}

CINCLUDE=-I. -I.. -I../plib/include

# -I/usr/openwin/include  -I${DIR_OPENGL}/include -I${DIR_GLUT}/include -I${DIR_PLIB}/include



DEPEND = makedepend


# ---------------------------------------------------
all:: start

all:: $(OBJS)

all::	$(TARGET)


start:
	rm -f  $(TARGET)

clean::
		rm	 -f *.o	*.a $(TARGET)

LINKER=gcc



# ---------------------------------------------------
# Compilation
.cc.o:
		gcc  -pipe $(CFLAGS) $(CINCLUDE) -c  $*.cc 



# ---------------------------------------------------
# program

$(TARGET):
		rm -f $(TARGET)
	  $(LINKER) -o $(TARGET) $(LDFLAGS) $(LIBPATHS) $(OBJS)  $(LIBS)

#	 	/tools/public/pure/purify/purify -best-effort gcc -o $(TARGET) $(LDFLAGS) $(LIBPATHS) $(OBJS)  $(LIBS) 


# ---------------------------------------------------
# Depends

ALLDEFINES=$CINCLUDE

depend:: $(SRCS) $(HDRS)
	$(DEPEND)  -s "# DO NOT DELETE" -- $(ALLDEFINES) -- $(SRCS)
dependlocal:: $(SRCS) $(HEADERS)
	$(DEPEND)  -s "# DO NOT DELETE" -- $(ALLDEFINES) -- $(SRCS)
