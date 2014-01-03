TARGET=AsteroidFighter
# TARGET=TestDev

SRCS = \
	MainMenu.cc \
	Help.cc \
	main.cc


OBJS =  $(SRCS:.cc=.o)


HDRS = $(SRCS:.cc=.h)


# ---------------------------------------------------

LDFLAGS=  

LIBPATHS=  -L../T3d -L../O3d -L../Sprite3d -L../U3d -L../Space  -L. \
					  -L${DIR_PLIB}/lib  -L${DIR_OPENGL}/lib -L${DIR_GLUT_LIB} -L${DIR_X11_LIB}

LIBS=  -lSpace -lU3d -lSprite3d -lO3d -lT3d   -lplibpuaux -lplibpu -lplibul  -lplibpw -lplibfnt -lplibsg -lplibul -lplibsl   -lGL -lGLU -lglut   -lstdc++   -lXext -lX11  -lnsl -lm 

# LIBS=  -lSpace -lU3d -lSprite3d -lO3d -lT3d   -lplibpuaux -lplibpu -lplibul  -lplibpw -lplibfnt -lplibsg -lplibul -lplibsl   -lGL -lGLU -lglut   -lstdc++   -lXmu -lXext -lXi -lX11  -lnsl -mt -lm 


# ---------------------------------------------------
CFLAGS=  -DPUI_WIN -DSL_SOUND  ${CC_DEBUG}

CINCLUDE=-I. -I..

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
