cmake_minimum_required(VERSION 2.6)

project( Space )


set( LIBRARY_OUTPUT_PATH ../lib/${CMAKE_BUILD_TYPE} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{CC_FLAGS}")

file( GLOB_RECURSE
			 SrcFiles 
			 ./*.cc ./*.h)

add_definitions( -DPUI_WIN )

include_directories( . .. 
	/usr/openwin/include 
	${DIR_OPENGL_INC} 
	${DIR_GLUT_INC} 
	${DIR_PLIB_INC} 
	)

add_library( Space
	STATIC
	${SrcFiles}
	)
