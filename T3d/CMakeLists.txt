cmake_minimum_required(VERSION 2.6)

project( T3d )


# add_compile_options(-std=c++11) 
# add_compile_options(-O2) 
# add_compile_options(-Wall) 
# add_compile_options(-g) 

set( LIBRARY_OUTPUT_PATH ../lib/${CMAKE_BUILD_TYPE} )


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{CC_FLAGS}")

message(  ${CMAKE_CXX_FLAGS} )


file( GLOB_RECURSE
			 SrcFiles 
			 ./*.cc ./*.h)



include_directories( . ..
	/usr/openwin/include 
	${DIR_OPENGL_INC} 
	${DIR_GLUT_INC} 
	${DIR_PLIB_INC} 
	)

add_library( T3d
	STATIC
	${SrcFiles}
	)
