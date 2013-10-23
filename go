# DISPLAY=padev013:0.0
LD_LIBRARY_PATH=$DIR_OPENGL/lib:$LD_LIBRARY_PATH
echo ./test4 -S1 -F10 $*
# ./test4 -X1 -F10 -geometry 5x5+0+0 -s $*
# AsteroidFighter/AsteroidFighter -X1 -F10 -s  $*
AsteroidFighter/AsteroidFighter   -F10 -s  $*
