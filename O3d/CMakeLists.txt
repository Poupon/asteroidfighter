cmake_minimum_required(VERSION 2.6)

project( O3d )


set( LIBRARY_OUTPUT_PATH ../lib/${CMAKE_BUILD_TYPE} )

file( GLOB_RECURSE
			 SrcFiles 
			 ./*.cc ./*.h)



include_directories( . .. 
	/usr/openwin/include 
	${DIR_OPENGL_INC} 
	${DIR_GLUT_INC} 
	${DIR_PLIB_INC} 
	)

add_library( O3d
	STATIC
	${SrcFiles}
	)
