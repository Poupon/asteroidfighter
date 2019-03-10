all::
	cd T3d; make ;cd ..;\
	cd O3d; make ;cd ..;\
	cd Sprite3d; make ;cd ..;\
	cd U3d; make -f ;cd ..;\
	cd Space; make ;cd ..;\
	cd AsteroidFighter; make ;cd ..;\

clean:
	cd T3d; make  clean;cd ..;\
	cd O3d; make  clean;cd ..;\
	cd Sprite3d; make  clean;cd ..;\
	cd U3d; make  clean;cd ..;\
	cd Space; make  clean;cd ..;\
	cd AsteroidFighter; make - clean;cd ..;\
	rm core AsteroidFighter AsteroidFighter.exe *.o  
	rm -rf Output/* OutputDebug/*
