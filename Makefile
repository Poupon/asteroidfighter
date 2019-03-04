all::
		cd T3d; make -f Makefile;cd ..;\
		cd O3d; make -f Makefile;cd ..;\
		cd Sprite3d; make -f Makefile;cd ..;\
	  cd U3d; make -f Makefile;cd ..;\
	  cd Space; make -f Makefile;cd ..;\
	  cd AsteroidFighter; make -f Makefile;cd ..;\
 
clean::
	cd T3d; make -f Makefile clean;cd ..;\
	cd O3d; make -f Makefile clean;cd ..;\
	cd Sprite3d; make -f Makefile clean;cd ..;\
	cd U3d; make -f Makefile clean;cd ..;\
	cd Space; make -f Makefile clean;cd ..;\
	cd AsteroidFighter; make -f Makefile clean;cd ..;\
	rm core AsteroidFighter AsteroidFighter.exe *.o  
	rm -rf Output/* OutputDebug/*
