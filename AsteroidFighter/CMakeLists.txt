cmake_minimum_required(VERSION 2.6)

project( AsteroidFighter )

set(EXECUTABLE_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})



add_definitions( -DPUI_WIN )

include_directories( . .. 
	/usr/openwin/include 
	${DIR_OPENGL_INC} 
	${DIR_GLUT_INC} 
	${DIR_PLIB_INC} 
	)

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../lib
	${DIR_PLIB}/lib
  ${DIR_OPENGL}/lib
	${DIR_GLUT_LIB} 
	${DIR_X11_LIB}
	)


	
file( GLOB_RECURSE
	SrcFiles 
	./*.cc ./*.h
	)

add_executable( AsteroidFighter
	${SrcFiles}
	)

target_link_libraries( AsteroidFighter
	Space 	U3d 	Sprite3d 	O3d 	T3d   
	plibpuaux plibpu plibul plibpw plibfnt plibsg plibul plibsl  
	GL GLU glut
  stdc++   
	Xext X11 
	nsl m 
)